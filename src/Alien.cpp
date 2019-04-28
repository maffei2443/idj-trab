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
using std::cout;
using std::endl;
static InputManager& inputManager = InputManager::GetInstance();

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



void Alien::Update(float dt) {
    (void)dt;
    /* Primeiro, CHECAMOS
SE HOUVE INPUT QUE GERE UMA AÇÃO: clique do botão esquerdo do mouse para
um tiro, ou direito para movimento. */
    // printf("ALIEN UPDATE\n");
    int mouseX = inputManager.GetMouseX();
    int mouseY = inputManager.GetMouseY();
    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        // printf("TIRO!\n");
        fflush(stdout);
        // clique do botão esquerdo do mouse para um tiro
        this->taskQueue.push( new Action(Action::ActionType::SHOOT, mouseX, mouseY) );
        printf("TIRO ADICIONADO\n");
    }
    if(inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
        // direito para movimento
        Action * action = new Action(Action::ActionType::MOVE, mouseX, mouseY);
        this->taskQueue.push( action );
    }
    if (this->taskQueue.size() > (size_t)0) {
        Action *action = this->taskQueue.front();
        switch(action->type) {
            case Action::ActionType::SHOOT:
                // Caso a ação seja de tiro... por enquanto, apenas tire a ação da fila.
                // Precisamos implementar mais algumas coisas antes.
                break;
            case Action::ActionType::MOVE:
                // IMPLEMENTAR MOVIMENTO
            /*  Para ações de
            movimento, devemos calcular velocidades nos eixos x e y de forma que O ALIEN
            SE MOVA EM LINHA RETA ATÉ AQUELE PONTO, E QUE O MÓDULO DA VELOCIDADE DELE
            SEJA SEMPRE CONSTANTE. */
            printf("Alien.x: %lf, Alien.y: %lf\n",
            this->associated.box.x, this->associated.box.y);
            printf("MouseX: %d, MouseY: %d\n", mouseX, mouseY);
            // Ajuste para centralizar corretamente no ponteiro do mouse
            Sprite * AlienSprite = ((Sprite*)this->associated.GetComponent("Sprite"));
            this->associated.box.x = mouseX - AlienSprite->GetWidth()/2;
            this->associated.box.y = mouseY - AlienSprite->GetHeight()/2;
            break;
        }
        // Queue.pop chama o destrutor
        this->taskQueue.pop();
    }
    // Devemos pedir para remover esse GameObject se a vida dele ficar
    // menor ou igual a 0.
    #pragma region
    if(this->hitspoints >> 31) {
        this->associated.RequestDelete();
    }
    #pragma endregion
    // printf("END ALIEN UPDATE\n");fflush(stdout);
}
void Alien::Render() {
    // Itentionally left empty.
    // Primeiro, faça A RENDERIZAÇÃO deles levar em
    // consideração a posição da câmera. (FIZ O UPDATE)
    // printf("Alien RENDER\n");
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