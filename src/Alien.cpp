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

using std::cout;
using std::endl;
static InputManager& inputManager = InputManager::GetInstance();
const int VEL = 3;

Alien::Alien(GameObject& associated, int nMinions):Component(associated),
hitspoints(Alien::HEALTH_POINTS){
    (void)nMinions;
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
    if (this->taskQueue.size() > (size_t)0) {
        Action *action = this->taskQueue.front();
        switch(action->type) {
            case Action::ActionType::SHOOT:{
                // Caso a ação seja de tiro... por enquanto, apenas tire a ação da fila.
                // Precisamos implementar mais algumas coisas antes.
                this->speed = {0, 0};
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
                double midX = (this->associated.box.x + (double)AlienSprite->GetWidth()/2);
                double midY = (this->associated.box.y + (double)AlienSprite->GetHeight()/2);
        
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
    // Mantem o alien andando ATEH QUE encontre o ponto clicado.
    #pragma region
    if (this->click.targetX || this->click.targetY) {
        int mouseX = inputManager.GetMouseX();
        int mouseY = inputManager.GetMouseY();

        Sprite * AlienSprite = ((Sprite*)this->associated.GetComponent("Sprite"));
        double midX = (this->associated.box.x + (double)AlienSprite->GetWidth()/2);
        double midY = (this->associated.box.y + (double)AlienSprite->GetHeight()/2);

        double deltaX = mouseX - midX;
        double deltaY = mouseY - midY;

        double absDeltaX = abs(deltaX);
        double absDeltaY = abs(deltaY);

        double slope = deltaY / deltaX;
        double slopeInverse = deltaX / deltaY;

        // TODO  encontrar forma melhor, 
        // que nao multiplicando por um booleano
        if (IsFloatZero(absDeltaX) and IsFloatZero(absDeltaY)) {
            this->speed.x = this->speed.y = 0;
            this->click.targetX = this->click.targetY = false;
            // this->associated.box.x = this->click.x - midX;
            // this->associated.box.y = this->click.y - midY;
        }
        else if (IsFloatZero(absDeltaX) and !IsFloatZero(absDeltaY)) {
            this->speed.x = 0;  this->click.targetX = false;
            this->speed.y = (deltaY > 0 ? VEL : -VEL) * this->click.targetY;
        }
        else if (!IsFloatZero(absDeltaX) and IsFloatZero(absDeltaY)) {
            this->speed.y = 0;  this->click.targetY = false;
            this->speed.x = (deltaX > 0 ? VEL : -VEL) * this->click.targetX;
        }
        else if (!IsFloatZero(absDeltaX) and !IsFloatZero(absDeltaY)) {
            if(absDeltaX < absDeltaY) { // velocidade em X deve ser MENOR em modulo
                this->speed.y = (deltaY > 0 ? VEL : -VEL) * this->click.targetY;
                this->speed.x = this->speed.y * slopeInverse ;  // 
            }
            else {
                this->speed.x = (deltaX > 0 ? VEL : -VEL);
                this->speed.y = this->speed.x * slope;  //                 
            }
        }

        // printf("My point!\n");
    }
    else {
        printf("reached : %lf, %lf\n", this->associated.box.x, this->associated.box.y);
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
    this->associated.box.x += this->speed.x;
    this->associated.box.y += this->speed.y;

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
    this->started = true;
    /* Devemos popular o array de Minions com alguns destes objetos,
espaçados igualmente. Enquanto não tiver certeza que o Alien funciona como
desejado, não faça nada aqui. */
}