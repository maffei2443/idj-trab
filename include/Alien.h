#ifndef ALIEN_H
#define ALIEN_H
#include "Component.h"
#include "Vec2.h"
#include <queue>
#include <memory>
#include "Action.h"
#include "Click.h"

class Alien : public Component {
    /* Alien é um objeto controlado pelo mouse. Ele executa uma
     sequência de ações, uma a uma, contidas numa fila */
/* Quando um dos botões do mouse
é pressionado em determinado ponto da tela, o Alien cria uma ação e a
enfileira. Além disso, ele mantêm um array de ponteiros para
GameObjects (serão os Minions), os quais ele usará para atirar. */     
private:
    const static int HEALTH_POINTS = 30;
    int hitspoints;
    // t5
    Vec2 speed;
    int hp;
    std::queue<Action*> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    // 
    Click click;
    Vec2 targetPoint;
public:
    const std::string type = std::string("Alien");
    Alien(GameObject&, int);
    ~Alien();
    // herda de Component
    void Update(double dt);
    void Render();
    bool Is(std::string type);
    const inline std::string GetType(){
        return this->type;
    }
    // t5
    bool started = false;
    void Start();
};

#endif