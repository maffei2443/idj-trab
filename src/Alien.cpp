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
#include "Bullet.h"
#include <cmath>

using std::cout;
using std::endl;
using std::weak_ptr;
using std::shared_ptr;
using std::string;

static InputManager& inputManager = InputManager::GetInstance();
const int VEL = 3;
const string Alien::type("Alien");

void Alien::Shoot(Vec2 pos) {
    // abort();
    if(this->nMinions) {
        Minion* mini = ((Minion*)this->minionArray[0].lock().get());
        cout << "&Mini RECOVERED : " << mini << endl;
        cout << "Mini.associated.box : " << mini->GetBox() << endl;
        // myAbort(999);
        mini->Shoot(pos);   // TODO: fazer minion mais PRÓXIMO atirar
    }
    else {
        cout << "No minions to shoot" << endl;
    }

}

void Alien::UpdatePosAndSpeed() {
    if (this->click.targetX || this->click.targetY) {        
        double midX = (this->associated.box.x + (double)this->mySprite->GetWidth()/2);
        double midY = (this->associated.box.y + (double)this->mySprite->GetHeight()/2);

        double deltaX = -(midX-this->click.x);
        double deltaY = -(midY-this->click.y);

        double absDeltaX = fabs(deltaX);
        double absDeltaY = fabs(deltaY);

        double slope = deltaY / deltaX;
        double slopeInverse = deltaX / deltaY;
        
        Vec2 old_speed = this->speed;

        if (IsFloatZero(deltaX) or IsFloatZero(deltaY)) {
            this->gotoTarget();
        }
        else {
            if(absDeltaX < absDeltaY) { // velocidade em X deve ser MENOR em modulo
                this->speed.y = (deltaY > 0 ? VEL : -VEL);
                this->speed.x = this->speed.y * slopeInverse ;  // 
            }
            else {
                this->speed.x = (deltaX > 0 ? VEL : -VEL);
                this->speed.y = this->speed.x * slope;
            }
            // checar se vai ir para onde estava antes. Se sim, pare de se mover e teleporta ao ponto objetivo.
            if(IsDoubleDiffZero( (this->associated.box-old_speed).abs(), (this->associated.box+this->speed).abs() ) )  {
                this->gotoTarget();
            }
            else {
                this->associated.box.SetXY(this->associated.box.x + this->speed.x, this->associated.box.y + this->speed.y);
            }
        }
    }

}

void Alien::gotoTarget() {
    cout << "[Alien.gotoTarget] GOTO: " << this->click.x << ", " << this->click.y << endl;
    
    this->speed.x = this->speed.y = 0;
    
    this->click.targetX = this->click.targetY = false;
    this->associated.box.SetCenter(
        this->click.x,
        this->click.y);
    // myAbort (222);
}

Alien::Alien(GameObject& associated, int nMinions):Component(associated),
hitspoints(Alien::HEALTH_POINTS), nMinions(nMinions){
    /* Adiciona um componente do tipo Sprite ao associated e 
    inicializa as outras variáveis. [DUVIDA : QUAIS VARIAVEIS?] */
    this->mySprite = new Sprite(this->associated, "assets/img/alien.png");
    this->associated.AddComponent(this);
    this->associated.box.SetXYWH(512, 300, this->mySprite->GetWidth(), this->mySprite->GetHeight());
    cout << "ALIEN BOX :: " << this->associated.box << endl;
    printf("SHOULD BE %d, %d, %d, %d\n", 512, 300, this->mySprite->GetWidth(), this->mySprite->GetHeight());
    fflush(stdout);
    // myAbort(12345);
    this->taskQueue = std::queue<Action*>();
    this->nMinions = nMinions;
    this->mySprite = ((Sprite*)this->associated.GetComponent("Sprite"));
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
                this->Shoot(Vec2(action->pos.x, action->pos.y));
                break;}
            case Action::ActionType::MOVE:{
                this->click.targetX = true;
                this->click.targetY = true;
                this->click.x = action->pos.x;
                this->click.y = action->pos.y;
                // printf("META DO ALIEN : %d, %d\n", this->click.x, this->click.y);
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
        printf("MOVE TO %d %d\n", mouseX, mouseY);
        this->taskQueue.push( new Action(Action::ActionType::MOVE, mouseX, mouseY) );
    }

    // Mantem o alien andando ATEH QUE encontre o ponto clicado.
    this->UpdatePosAndSpeed();    

    // Devemos pedir para remover esse GameObject se a vida dele ficar
    // menor ou igual a 0.
    #pragma region
    if(this->hitspoints >> 31 || (this->hitspoints ^ 0x0000) == 0xFFFF) {    // se eh negativo OU igual a zero, morrreu :)
        cout << "hitspoints :: " << this->hitspoints << endl;
        this->associated.RequestDelete();
    }
    // cout << "END ALIEN.UPDATE\n";
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
    for(int i = 0; i < this->nMinions; i++) {
        weak_ptr<GameObject> weak_GO_of_this = Game::GetInstance().GetState().GetObjectPtr(&this->associated);
        if(&this->associated != (GameObject*)weak_GO_of_this.lock().get() ) {
            myAbort(111);
        }
        GameObject * minionGO = new GameObject();
        Minion* added = new Minion(*minionGO, weak_GO_of_this, 90.0, Vec2(200, 0) );
        cout << "MINION ADDED ++++++++++++++++++ " << added << endl;
        // TODO: CHAMAR SETSCALE P/ REDIMENTSIONAR IMAGEM DO MINION
        weak_ptr<GameObject> minionWeakPtr;
        minionWeakPtr = Game::GetInstance().GetState().AddObject(minionGO);
        cout << "MINION ADDED[weak_ptrVersion] ++++++++++++++++++ " << (Minion*)minionWeakPtr.lock().get() << endl;
        if ((Minion*)minionWeakPtr.lock().get() != added) {
            myAbort(666);
        }
        this->minionArray.push_back( minionWeakPtr );
    }
}
// Retorna ponteiro p/ minion que contém as coordenadas mais próximas dos pontos x,y.
Minion* Alien::GetNearestMinion(int x = inputManager.GetMouseX(), int y = inputManager.GetMouseY()) {
    Vec2 click(x, y);
    int idx_of_closest_minion;
    for(int i = 0; i < this->nMinions; i++) {
        
    }
    return nullptr;
}