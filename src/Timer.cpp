#include "Timer.h"

void Timer::Update(double dt) {
    this->time += dt;
}

void Timer::Restart() {
    this->time = 0.0;
}

double Timer::Get() const{
    return this->time;
}
Como foi dito, um componente muito simples. A primeira coisa em que
você deve aplicar o Timer é o PenguinCannon: Use o Timer para impor um
cooldown nos tiros dele. Não é necessário fazer o mesmo para o Alien, pois
temos outros planos pra ele mais tarde.