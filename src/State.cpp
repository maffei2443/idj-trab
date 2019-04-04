#include "State.h"
#include "Sprite.h"
#define INCLUDE_SDL
#include "SDL_include.h" // SDL_
#include "GameObject.h"
#include <string>
#include <algorithm>
#include <memory>
#include "Face.h"
#include <cmath>
#define PI M_PI


State :: State() : music(Music("assets/audio/stageState.ogg")) {
  // O construtor de State inicializa quitRequested e instancia o Sprite,
  this->quitRequested = false;
  this->music.Play(-1);
  // Instanciar o Sprite
  // this->bg = Sprite("assets/img/lose.jpg");
  // this->music = Musicl();
}
State :: ~State() {
	objectArray.clear();
}

void State :: Update(double dt) {
  // this->quitRequested = SDL_QuitRequested();
	this->Input();
	// UpdateAll
	for(auto& GO : this->objectArray) {
		GO->Update(dt);
	}
	// remove if dead
	this->objectArray.erase( 
		std::remove_if(
			this->objectArray.begin(),
			this->objectArray.end(),
			[](std::unique_ptr<GameObject>& GO) {return GO->IsDead();})
	);
}


//  trata da etapa 4 de Game::Run
void State :: Render() {
  //  Para esse trabalho, chame o render do fundo (bg). [?]
  // printf("Before State.Render\n");
  for(auto& GO : this->objectArray)
		GO->Render();
}

void AddObject(int mouseX, int mouseY) {
	GameObject * enemy = new GameObject;
	Sprite * sprite = new Sprite(std::string("assets/img/penguinface.png"));
	enemy->box.x = mouseX - sprite->GetWidth()/2;
	enemy->box.y = mouseY - sprite->GetHeight()/2;
	enemy->box.w = sprite->GetWidth();
	enemy->box.h = sprite->GetHeight();
	
	// enemy->box.y = mouseY;
	// enemy->box.y = mouseY;
	// enemy->box.y = mouseY;
}

bool State :: QuitRequested() {
  return this->quitRequested;
}

void State :: LoadAssets() {
  //  Para esse trabalho, chame o render do fundo (bg). [?]
}


void State :: Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			this->quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do std::unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 );
				objPos.rotate( -PI + PI*(rand() % 1001)/500.0 );
				Vec2 aux (mouseX, mouseY );
				objPos = objPos + aux;
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}
