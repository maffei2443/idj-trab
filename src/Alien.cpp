#include <unistd.h>
#include "Alien.h"
#include "Sound.h"
#include "Component.h"
#include "Macros.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Sprite.h"
#include <memory>
#include "Util.h"
#include "Minion.h"
#include "Game.h"
#include "Bullet.h"
#include <cmath>

// linear_congruential_engine constructor
/* #include <chrono>
#include <random>
unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
*/// linear_congruential_engine constructor

////
#include <chrono>
#include <random>


static std::default_random_engine randomGenerator;
// static std::uniform_real_distribution<double> radiusExtraRandom(60.0,100.0);
static std::uniform_real_distribution<double> radiusExtraRandom(0.0);

////
using std::cout;
using std::endl;
using std::weak_ptr;
using std::shared_ptr;
using std::string;
// std::minstd_rand0 GetRandom(seed1);  // minstd_rand0 is a standard linear_congruential_engine

static InputManager& inputManager = InputManager::GetInstance();
const int VEL = 2;
const string Alien::type("Alien");

Minion* Alien::GetMinion(int i) {
    Minion* ret =  (Minion*)(this->minionArray[i].lock().get())->GetComponent("Minion");
    return ret;
}

void Alien::Shoot(Vec2 pos) {
    // abort();
    if(this->nMinions) {
        Minion* mini = this->GetNearestMinion(pos);
        mini->Shoot(pos);   // TODO: fazer minion mais PRÓXIMO atirar
    }
    else {
        cout << "No minions to shoot" << endl;
    }

}

void Alien::UpdatePos(double dt) {
    myAbort(2345);
    if (this->click.targetX || this->click.targetY) {        
        double midX = (this->associated.box.x + (double)this->mySprite->GetWidth()/2);
        double midY = (this->associated.box.y + (double)this->mySprite->GetHeight()/2);

        double deltaX = -(midX-this->click.x);
        double deltaY = -(midY-this->click.y);

        this->click.targetX = !IsDoubleZero(deltaX);
        this->click.targetY = !IsDoubleZero(deltaY);

        double absDeltaX = fabs(deltaX);
        double absDeltaY = fabs(deltaY);

        double slope = deltaY / deltaX;
        double slopeInverse = deltaX / deltaY;
        
        Vec2 old_speed = this->speed;

        if (IsFloatZero(deltaX) and IsFloatZero(deltaY)) {
            cout << "WHY GO-TO ???" << endl;
            this->gotoTarget();
        }
        else {
            this->associated.box.AddXY(this->speed * dt);
        }
        // cout << "SPEED : " << this->speed << endl;
    }
}


void Alien::UpdatePosAndSpeed(double dt) {
    if (this->click.targetX || this->click.targetY) {        
        double midX = (this->associated.box.x + (double)this->mySprite->GetWidth()/2);
        double midY = (this->associated.box.y + (double)this->mySprite->GetHeight()/2);

        double deltaX = -(midX-this->click.x);
        double deltaY = -(midY-this->click.y);

        this->click.targetX = !IsDoubleZero(deltaX);
        this->click.targetY = !IsDoubleZero(deltaY);

        double absDeltaX = fabs(deltaX);
        double absDeltaY = fabs(deltaY);

        double slope = deltaY / deltaX;
        double slopeInverse = deltaX / deltaY;
        
        Vec2 old_speed = this->speed;

        if (IsFloatZero(deltaX) and IsFloatZero(deltaY)) {
            this->gotoTarget();
        }
        else {
            if(absDeltaX < absDeltaY) { // velocidade em X deve ser MENOR em modulo
                this->speed.y = (deltaY > 0 ? VEL : -VEL)*dt;
                this->speed.x = this->speed.y * slopeInverse * this->click.targetY ;  // 
            }
            else {
                this->speed.x = (deltaX > 0 ? VEL : -VEL)*dt;
                this->speed.y = this->speed.x * slope * click.targetX;
            }
            // checar se vai ir para onde estava antes. Se sim, pare de se mover e teleporta ao ponto objetivo.
            cout << "MISSING TO TARGET : " << this->associated.box - this->targetPoint << endl;
            if(IsDoubleDiffZero( (this->associated.box-old_speed).abs(), (this->associated.box+this->speed).abs()) )  {
                cout << "GOTO ESTRANHO?? Maybe..." << endl;
                if (!IsDoubleZero(old_speed.abs()) and !IsDoubleZero(this->speed.abs()) )
                    this->gotoTarget();
            }
            else {
                this->associated.box.SetXY(this->associated.box.x + this->speed.x*dt, this->associated.box.y + this->speed.y*dt);
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
}

Alien::Alien(GameObject& associated, int nMinions):Component(associated),
hitspoints(Alien::HEALTH_POINTS), nMinions(nMinions){
    /* Adiciona um componente do tipo Sprite ao associated e 
    inicializa as outras variáveis. [DUVIDA : QUAIS VARIAVEIS?] */
    this->mySprite = new Sprite(this->associated, "assets/img/alien.png");
    this->mySprite->angleToRotate = -.02;

    this->associated.AddComponent(this);
    this->associated.box.SetXYWH(512, 300, this->mySprite->GetWidth(), this->mySprite->GetHeight());
    // cout << "ALIEN BOX :: " << this->associated.box << endl;
    // printf("SHOULD BE %d, %d, %d, %d\n", 512, 300, this->mySprite->GetWidth(), this->mySprite->GetHeight());
    // fflush(stdout);
    this->taskQueue = std::queue<Action*>();
    this->nMinions = nMinions;
    new CameraFollower(this->associated);
    // myAbort(1991919);
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
                // this->UpdatePosAndSpeed();
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
    this->UpdatePosAndSpeed(dt);    
    // this->UpdatePos(dt);    

    // Devemos pedir para remover esse GameObject se a vida dele ficar
    // menor ou igual a 0.
    #pragma region
    if(this->hitspoints >> 31 || (this->hitspoints ^ 0x0000) == 0xFFFF) {    // se eh negativo OU igual a zero, morrreu :)
        cout << "hitspoints :: " << this->hitspoints << endl;
        this->associated.RequestDelete();
    }
    // this->associated.box.AddXY(Camera::speed * dt);

    // cout << "END ALIEN.UPDATE\n";
    #pragma endregion
}
void Alien::Render() {
    // Itentionally left empty.
    // Primeiro, faça A RENDERIZAÇÃO deles levar em
    // consideração a posição da câmera. (FIZ O UPDATE)
    // printf("Alien RENDER\n");

}
bool Alien::Is(string type) {
    return type == "Alien";
}

// t5
void Alien::Start() {
    this->started = true;
    cout << "MINIONS : " << this->nMinions << endl; 
    double offSet = 360.0 / this->nMinions;
    double arc = 0.0;
    for(int i = 0; i < this->nMinions; i++) {
        weak_ptr<GameObject> self_weak_GO = Game::GetInstance().GetState().GetObjectPtr(&this->associated);

        GameObject * minionGO = new GameObject();
        Minion* added =
            new Minion(*minionGO, self_weak_GO, arc, Vec2(this->baseRadius + radiusExtraRandom(randomGenerator) , 0));
        arc += offSet;
        shared_ptr<GameObject>* srd = new shared_ptr<GameObject>(minionGO);
        weak_ptr<GameObject> minionWeakPtr;        
        minionWeakPtr = Game::GetInstance().GetState().AddObject(srd->get());
        this->minionArray.emplace_back( minionWeakPtr );
    }
}

// Retorna ponteiro p/ minion que contém as coordenadas mais próximas dos pontos x,y.
// Retorna nullptr se nao houver minions
Minion* Alien::GetNearestMinion(int x = inputManager.GetMouseX(), int y = inputManager.GetMouseY()) {
    Vec2 click(x, y);
    if (!this->nMinions){
        return nullptr;
    }
    // cout << "\n\n\n\n" << endl;
    // cout << "Where should the bullte go? " << Vec2(x,y) << endl;
    Minion* nearestMinion = this->GetMinion(0);
    Minion* nearestCandidate;
    // double minDist = nearestMinion->GetBox().center.dist(click);
    double minDist = nearestMinion->GetBox().GetCenter().dist(click);
    double minDistCanditate;
    for(int i = 1; i < this->nMinions; i++) {
        nearestCandidate = this->GetMinion(i);
        // Vec2 center = nearestCandidate->GetBox().center;
        Vec2 center = nearestCandidate->GetBox().GetCenter();
        minDistCanditate = center.dist(click);
        if (minDistCanditate < minDist) {
            nearestMinion = nearestCandidate;
            minDist = minDistCanditate;
        }
    }
    return (Minion*)nearestMinion; 
}

Minion* Alien::GetNearestMinion(Vec2 pos) {
    return this->GetNearestMinion(pos.x, pos.y);
}