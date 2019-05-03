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

static InputManager& inputManager = InputManager::GetInstance();
const int VEL = 3;

Alien::Alien(GameObject& associated, int nMinions):Component(associated),
hitspoints(Alien::HEALTH_POINTS), nMinions(nMinions){
    /* Adiciona um componente do tipo Sprite ao associated e 
    inicializa as outras variáveis. [DUVIDA : QUAIS VARIAVEIS?] */
    new Sprite(this->associated, "assets/img/alien.png");
    /* Mover a adição dos componentes de dependência (e de
GameObjects também, como veremos abaixo) para o construtor reduz o
tamanho e simplifica o construtor do state mas possui, na nossa engine, uma
desvantagem. Consegue descobrir qual é? [DUVIDA] */
    this->associated.box.x = 512;
    this->associated.box.y = 300;
    this->associated.AddComponent(this);
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
                this->associated.box.x = action->pos.x - AlienSprite->GetWidth()/2;
                this->associated.box.y = action->pos.y - AlienSprite->GetHeight()/2;

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
        // Queue.pop CHAMA O DESTRUTOR
        this->taskQueue.pop();
    }    
    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        // printf("TIRO!\n");
        fflush(stdout);
        // clique do botão esquerdo do mouse para um tiro
        int mouseX = inputManager.GetMouseX();
        int mouseY = inputManager.GetMouseY();

        this->taskQueue.push( new Action(Action::ActionType::SHOOT, mouseX, mouseY) );
        // printf("TIRO ADICIONADO\n");
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

        double absDeltaX = abs(deltaX);
        double absDeltaY = abs(deltaY);

        double slope = deltaY / deltaX;
        double slopeInverse = deltaX / deltaY;

        // TODO  encontrar forma melhor, 
        // que nao multiplicando por um booleano
        if (IsFloatZero(absDeltaX) or IsFloatZero(absDeltaY)) {
            this->speed.x = this->speed.y = 0;
            this->click.targetX = this->click.targetY = false;

            this->associated.box.x = this->click.x - ((double)AlienSprite->GetWidth())/2;
            this->associated.box.y = this->click.y - ((double)AlienSprite->GetHeight())/2;
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
            this->associated.box.x += this->speed.x;
            this->associated.box.y += this->speed.y;            
        }
    }
    #pragma endregion

    // Devemos pedir para remover esse GameObject se a vida dele ficar
    // menor ou igual a 0.
    #pragma region
    if(this->hitspoints >> 31) {
        this->associated.RequestDelete();
    }
    #pragma endregion
    // printf("END ALIEN UPDATE\n");fflush(stdout);
    // printf("final position : %lf %lf\n", this->associated.box.x, this->associated.box.y);
    // printf("META : %d %d\n", mouseX, mouseY);


}
void Alien::Render() {
    // Itentionally left empty.
    // Primeiro, faça A RENDERIZAÇÃO deles levar em
    // consideração a posição da câmera. (FIZ O UPDATE)
    // printf("Alien RENDER\n");

    // printf("x,y: %lf, %lf | X, Y: %lf, %lf\n", this->associated.box.x, this->associated.box.y, this->targetPoint.x, this->targetPoint.y);

}
bool Alien::Is(std::string type) {
    return type == "Alien";
}

// t5
void Alien::Start() {
    // printf("Alien.Start %p\n", this);
    this->started = true;
    /* Devemos popular o array de Minions com alguns destes objetos,
espaçados igualmente. Enquanto não tiver certeza que o Alien funciona como
desejado, não faça nada aqui. */
    if(this->nMinions) {
        weak_ptr<GameObject> self_weak_GO = Game::GetInstance().GetState().GetObjectPtr(&this->associated);

        // add apenas um minion no momento (TESTE)
        // pegar versao weak de this->associated
        // shared_ptr
        GameObject * minionGO = new GameObject();
        // shared_ptr<Minion> minion ( new Minion(*minionGO, self_weak_GO, 90.0) );
        new Minion(*minionGO, self_weak_GO, 90.0);
        // shared_ptr<Sprite> minionSprite(new Sprite(*minionGO, "assets/img/minion.png"));
        // TODO: chamar SetScale p/ redimentsionar imagem do minion
        

        weak_ptr<GameObject> minionWeakPtr;
        minionWeakPtr = Game::GetInstance().GetState().AddObject(minionGO);


        this->minionArray.push_back( minionWeakPtr );

    }
    printf("Alien.Start END %p\n", this);
}