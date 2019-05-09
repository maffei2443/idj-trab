#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Component.h"
#import "Sprite.h"
#include "Vec2.h"
#include <string>
using std::string;

// Bullet é um projétil que segue em linha reta após sua criação.
class Bullet : public Component {
private:
    const static string type;
    Vec2 speed;
    double distanceLeft;
    int damage;
public:
    Bullet(GameObject&, double, double, int, double, string);
    void Update(double);
    void Render();
    bool Is(const string&);
    const inline string GetType() const {
        return this->type;
    }
    int GetDamage();
};

#endif