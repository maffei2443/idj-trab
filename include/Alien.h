#ifndef ALIEN_H
#define ALIEN_H
#include "Component.h"
#include "Vec2.h"
#include <queue>
#include <memory>
#include "Action.h"
#include "Click.h"
#include "Sprite.h"
#include "Minion.h"
#define BIG_DIST 1e12
using std::queue;
using std::vector;
using std::weak_ptr;
using std::string;
class Alien : public Component {
    /* Alien é um objeto controlado pelo mouse. Ele executa uma
     sequência de ações, uma a uma, contidas numa fila */
/* Quando um dos botões do mouse
é pressionado em determinado ponto da tela, o Alien cria uma ação e a
enfileira. Além disso, ele mantêm um array de ponteiros para
GameObjects (serão os Minions), os quais ele usará para atirar. */     
private:
    int baseRadius = 150;
    int maxExtraRadius = 40;    // nao usado no momento
    void Shoot(Vec2);
    void UpdatePosAndSpeed();
    void UpdatePos(double dt);
    const static string type;
    void gotoTarget();
    const static int HEALTH_POINTS = 30;
    int hitspoints;
    // t5
    Vec2 speed;
    int hp;
    int nMinions;
    queue<Action*> taskQueue;
    vector<weak_ptr<GameObject>> minionArray;
    // 
    Minion* GetMinion(int);
    Click click;
    Vec2 targetPoint;
    Sprite* mySprite;
public:
    
    Alien(GameObject&, int);
    ~Alien();
    // herda de Component
    void Update(double dt);
    void Render();
    bool Is(string type);
    const inline string GetType() const {
        return this->type;
    }
    // t5
    bool started = false;
    void Start();
    // t5 [gambs]
    Minion* GetNearestMinion(int, int);
    Minion* GetNearestMinion(Vec2);
};

#endif