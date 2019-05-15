#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H
#include "Component.h"
#include "Vec2.h"
#include <queue>
#include <memory>
#include "Action.h"
#include "Click.h"
#include "Sprite.h"
#include "Minion.h"
#include "PenguinBody.h"
#define BIG_DIST 1e12
using std::queue;
using std::vector;
using std::weak_ptr;
using std::string;
class PenguinCannon : public Component {
    /* Alien é um objeto controlado pelo mouse. Ele executa uma
     sequência de ações, uma a uma, contidas numa fila */
/* Quando um dos botões do mouse
é pressionado em determinado ponto da tela, o Alien cria uma ação e a
enfileira. Além disso, ele mantêm um array de ponteiros para
GameObjects (serão os Minions), os quais ele usará para atirar. */     
private:
    // void UpdatePosAndSpeed(double dt);
    // void UpdatePos(double dt);
    const static string type;
    // void gotoTarget();
    const static int HEALTH_POINTS = 30;
    int hitspoints;
    // t5
    Vec2 speed = Vec2(0,0);
    double angle = 0;
    weak_ptr<GameObject> pbody;

public:
    
    PenguinCannon(GameObject&, weak_ptr<GameObject> penguinBody);
    ~PenguinCannon();
    // herda de Component
    void Start();
    void Update(double dt);
    void Render();
    bool Is(string type);
    const inline string GetType() const {
        return this->type;
    }
    void Shoot();
};

#endif