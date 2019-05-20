#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Vec2.h"
#include <string>
#include "Click.h"
#include "Bullet.h"

using std::string;

// Bullet é um projétil que segue em linha reta após sua criação.
class Bullet : public Component {
private:
    void UpdatePos(double);
    void UpdatePosAndSpeed();
    void SetTarget(int, int);
    void gotoTarget(Sprite* );
    const static string type;
    Vec2 speed;
    double distanceLeft;
    int damage;
    Click click;
    // Vec2 target;     // deve conter as coordenadas do alvo
    Sprite * mySprite;
public:
    bool targetsPlayer = false;

    Bullet(GameObject&, double, double, int,
        double, string, int, int);
    ~Bullet();
    void Update(double);
    void Render();
    bool Is(string);
    const inline string GetType() const {
        return this->type;
    }
    int GetDamage();
    void Start();
    void NotifyCollision(GameObject& other);
};

#endif