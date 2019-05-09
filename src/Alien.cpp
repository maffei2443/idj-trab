#include <unistd.h>
#include "Alien.h"
#include "Sound.h"
#include "Component.h"
#include "Macros.h"
#include "Camera.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Sprite.h"
#include <memory>
#include "Util.h"
#include "Minion.h"
#include "Game.h"

using std::cout;
using std::endl;
using std::weak_ptr;
using std::shared_ptr;
using std::string;

static InputManager& inputManager = InputManager::GetInstance();
const int VEL = 3;
const string Alien::type("Alien");
void Alien::gotoTarget(Sprite* AlienSprite) {
    this->speed.x = this->speed.y = 0;
    this->click.targetX = this->click.targetY = false;
    this->associated.box.SetXY(
        this->click.x - ((double)AlienSprite->GetWidth())/2,
        this->click.y - ((double)AlienSprite->GetHeight())/2);
}

Alien::Alien(GameObject& associated, int nMinions):Component(associated),
hitspoints(Alien::HEALTH_POINTS), nMinions(nMinions){
    /* Adiciona um componente do tipo Sprite ao associated e 
    inicializa as outras variáveis. [DUVIDA : QUAIS VARIAVEIS?] */
    new Sprite(this->associated, "assets/img/alien.png");
    this->associated.AddComponent(this);
    this->associated.box.SetXY(512, 300);

    this->taskQueue = std::queue<Action*>();
    this->nMinions = nMinions;
}
Alien::~Alien() {
    // Esvaziar o array com os minions.
    this->minionArray.clear();
}



void Alien::Update(double dt) {
    (void)dt;
    /* Primeiro, CHECAMOS
SE HOUVE INPUT QUE GERE UMA AÇÃO: clique do botão esquerdo do mouse para
um tiro, ou direito para movimento. */
    // printf("ALIEN UPDATE\n");
    if (this->taskQueue.size() > (size_t)0) {
        Action *action = this->taskQueue.front();
        switch(action->type) {
            case Action::ActionType::SHOOT:{
                // Caso a ação seja de tiro... por enquanto, apenas tire a ação da fila.
                // Precisamos implementar mais algumas coisas antes.
                
                this->speed = {0, 0};
                this->click.targetX = this->click.targetY = false;
                Sprite * AlienSprite = ((Sprite*)this->associated.GetComponent("Sprite"));
                this->associated.box.SetXY(
                    action->pos.x - AlienSprite->GetWidth()/2,
                    action->pos.y - AlienSprite->GetHeight()/2);
                // Colcocar um bullet na origem

                break;}
            case Action::ActionType::MOVE:{
                this->click.targetX = true;
                this->click.targetY = true;
                this->click.x = action->pos.x;
                this->click.y = action->pos.y;
                printf("META DO ALIEN : %d, %d\n", this->click.x, this->click.y);
                // abort();
                Sprite * AlienSprite = ((Sprite*)this->associated.GetComponent("Sprite"));
                double midX = (this->associated.box.x + AlienSprite->GetWidth()/2);
                double midY = (this->associated.box.y + AlienSprite->GetHeight()/2);
        
                double deltaX = this->click.x - midX;
                double absDeltaX = abs(deltaX);

                double deltaY = this->click.y - midY;
                double absDeltaY = abs(deltaY);

                double slope = deltaY / deltaX;
                double slopeInverse = deltaX / deltaY;

                if(absDeltaX < absDeltaY) { // velocidade em X deve ser MENOR em modulo
                    this->speed.y = (deltaY > 0 ? VEL : -VEL);
                    this->speed.x = this->speed.y * slopeInverse ;  // 
                }
                else {
                    this->speed.x = (deltaX > 0 ? VEL : -VEL);
                    this->speed.y = this->speed.x * slope;  //                 
                }
                break;
            }
        }
        // Queue.pop CHAMA O DESTRUTOR APOS ter executado o que deeveria...
        this->taskQueue.pop();
    }    
    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        fflush(stdout);
        // clique do botão esquerdo do mouse para um tiro
        int mouseX = inputManager.GetMouseX();
        int mouseY = inputManager.GetMouseY();

        this->taskQueue.push( new Action(Action::ActionType::SHOOT, mouseX, mouseY) );
    }
    if(inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
        // direito para movimento
        int mouseX = inputManager.GetMouseX();
        int mouseY = inputManager.GetMouseY();
        Action * action = new Action(Action::ActionType::MOVE, mouseX, mouseY);
        printf("MOVE TO %d %d\n", mouseX, mouseY);
        this->taskQueue.push( action );
    }

    // Mantem o alien andando ATEH QUE encontre o ponto clicado.
    #pragma region
    int mouseX = inputManager.GetMouseX();
    int mouseY = inputManager.GetMouseY();
    // TODO: otimizar. Isso deveria ser feito apenas uma vez [?]
    if (this->click.targetX || this->click.targetY) {

        Sprite * AlienSprite = ((Sprite*)this->associated.GetComponent("Sprite"));
        double midX = (this->associated.box.x + (double)AlienSprite->GetWidth()/2);
        double midY = (this->associated.box.y + (double)AlienSprite->GetHeight()/2);

        double deltaX = -(midX-mouseX);
        double deltaY = -(midY-mouseY);

        double absDeltaX = fabs(deltaX);
        double absDeltaY = fabs(deltaY);

        double slope = deltaY / deltaX;
        double slopeInverse = deltaX / deltaY;
        
        Vec2 old_speed = this->speed;

        if (IsFloatZero(deltaX) or IsFloatZero(deltaY)) {
            this->gotoTarget(AlienSprite);
        }
        else {
            if(absDeltaX < absDeltaY) { // velocidade em X deve ser MENOR em modulo
                this->speed.y = (deltaY > 0 ? VEL : -VEL) * this->click.targetY;
                this->speed.x = this->speed.y * slopeInverse ;  // 
            }
            else {
                this->speed.x = (deltaX > 0 ? VEL : -VEL);
                this->speed.y = this->speed.x * slope;
            }
            // checar se vai ir para onde estava antes. Se sim, pare de se mover e teleporta ao ponto objetivo.
            if(/* IsDoubleDiffZero(old_pos.x, this->associated.box.x) or IsDoubleDiffZero(old_pos.y, this->associated.box.y)
                or */ IsDoubleDiffZero( (this->associated.box-old_speed).abs(), (this->associated.box+this->speed).abs() ) )  {
                this->gotoTarget(AlienSprite);
            }
            else {
                this->associated.box.SetXY(this->associated.box.x + this->speed.x, this->associated.box.y + this->speed.y);
            }
            

        }
    }
    #pragma endregion

    // Devemos pedir para remover esse GameObject se a vida dele ficar
    // menor ou igual a 0.
    #pragma region
    if(this->hitspoints >> 31 || (this->hitspoints ^ 0x0000) == 0xFFFF) {    // se eh negativo OU igual a zero, morrreu :)
        cout << "hitspoints :: " << this->hitspoints << endl;
        this->associated.RequestDelete();
    }
    #pragma endregion
}
void Alien::Render() {
    // Itentionally left empty.
    // Primeiro, faça A RENDERIZAÇÃO deles levar em
    // consideração a posição da câmera. (FIZ O UPDATE)
    // printf("Alien RENDER\n");

    // printf("x,y: %lf, %lf | X, Y: %lf, %lf\n", this->associated.box.x, this->associated.box.y, this->targetPoint.x, this->targetPoint.y);

}
bool Alien::Is(string type) {
    return type == "Alien";
}

// t5
void Alien::Start() {
    this->started = true;
    /* Devemos popular o array de Minions com alguns destes objetos,
espaçados igualmente. Enquanto não tiver certeza que o Alien funciona como
desejado, não faça nada aqui. */
    // if(this->nMinions) {
    for(int i = 0; i < this->nMinions; i++) {
        weak_ptr<GameObject> self_weak_GO = Game::GetInstance().GetState().GetObjectPtr(&this->associated);

        GameObject * minionGO = new GameObject();
        new Minion(*minionGO, self_weak_GO, i*10+100*(i&1? -1:1)+90.0, Vec2(i*10+100*(i&1? -1:1), i*15+100* (i&1? 1:-1)) );
        // TODO: CHAMAR SETSCALE P/ REDIMENTSIONAR IMAGEM DO MINION

        weak_ptr<GameObject> minionWeakPtr;
        minionWeakPtr = Game::GetInstance().GetState().AddObject(minionGO);
        this->minionArray.push_back( minionWeakPtr );
    }
    printf("Alien.Start END %p\n", this);
}