#include <string>
#include <algorithm>
#include <memory>
#include <cmath>
#include <unistd.h>
#include <cstdio>
#define PI M_PI

#define INCLUDE_SDL
#include "State.h"
#include "Sprite.h"
#include "SDL_include.h" // SDL_
#include "GameObject.h"
#include "Sound.h"
#include "Macros.h"
#include "Face.h"
#include "TileSet.h"
#include "TileMap.h"
#include "State.h"
#include "InputManager.h"

State :: State() : music(Music("assets/audio/stageState.ogg") ) {
  GameObject * me = new GameObject;
  bg = new Sprite( *me, "assets/img/ocean.jpg" );
	std::string tileSetPath("assets/img/tileset.png");
	TileSet * tileSet = new TileSet(64, 64, tileSetPath, *me);
	new TileMap(*me, tileSet);
	this->objectArray.emplace_back( me );
  this->quitRequested = false;
  this->music.Play(-1);
}

State :: ~State() {
	objectArray.clear();
}


void State :: Update(double dt) {
    /* Setar a flag de quit de State se ESC 
    for pressionado ou se o
    InputManager apontar evento de Quit; */

	this->quitRequested = 
		this->inputManager->KeyPress(ESCAPE_KEY)
		|| this->inputManager->QuitRequested();
	// Se clicou, ver se aplica dano ou nao
	// if(this->inputManager->KeyPress(SDLK_ESCAPE)) {
	// 	printf("gg outa\n");
	// } 
	if( this->inputManager->KeyPress(SPACE_KEY)) {
		printf("GG SPACE!\n");fflush(stdout);
		abort();
		Vec2 objPos = Vec2( 200, 0 );
		objPos.rotate( rand() % 360 );
		Vec2 aux (inputManager->GetMouseX(), inputManager->GetMouseY() );
		objPos = objPos + aux;
		AddObject((int)objPos.x, (int)objPos.y);
	}
	if( this->inputManager->MousePress(LEFT_MOUSE_BUTTON)) {
		int mouseX = this->inputManager->GetMouseX();
		int mouseY = this->inputManager->GetMouseY();
		for(int i = objectArray.size() - 1; i >= 0; --i) {
			printf("DAMAGE?? %d\n", i);
			// Obtem o ponteiro e casta pra Face.
			GameObject* go = (GameObject*) objectArray[i].get();
			if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
				Face* face = (Face*)go->GetComponent( "Face" );
				if ( face != nullptr ) {
					// Aplica dano
					face->Damage(std::rand() % 10 + 10);
					// Sai do loop (só queremos acertar um)
					break;
				}
			}
		}
	}

	for(auto& GO : this->objectArray) {
		GO->Update(dt);
	}
	for(auto it = this->objectArray.begin();
		 it != this->objectArray.end();) {
			if((**it).IsDead()) {
        it = this->objectArray.erase(it);
      }
			else {
				it++;
			}
	}
	// //////printf("Apagou os mortos ? \n");
}


//  trata da etapa 4 de Game::Run
void State :: Render() {
	for(auto& GO : this->objectArray) {
		GO->Render();
	}
}

void State :: AddObject(int mouseX, int mouseY) {
	// criar um GameObject que conterá as informações do nosso primeiro inimigo.
	GameObject * enemy = new GameObject;
	
	// Sprite aponta para enemy
	Sprite * sprite = new Sprite(*enemy, "assets/img/penguinface.png");
	// setar a largura e altura da box do GameObject que o contém (associated)
	// baseado no carregado pela Sprite em seu construtor.
	enemy->box.x = mouseX - sprite->GetWidth()/2;
	enemy->box.y = mouseY - sprite->GetHeight()/2;
	enemy->box.w = sprite->GetWidth();
	enemy->box.h = sprite->GetHeight();
	
	// Depois disso, adicionemos a esse GameObject [enemy] o Componente Sound
	// usando audio/boom.wav 
	Sound * enemySound = new Sound(*enemy, "assets/audio/boom.wav");
	// e, por último, o que o define: Face.
	Face * enemyFace = new Face(*enemy);
	
  enemy->AddComponent(sprite);
  enemy->AddComponent(enemySound);
  enemy->AddComponent(enemyFace);
  
	this->objectArray.emplace_back( enemy );
}

bool State :: QuitRequested() {
  return this->quitRequested;
}

void State :: LoadAssets() {
  //  Para esse trabalho, chame o render do fundo (bg). [?]
}

// deprecation...
void State :: Input() {
	/* TODO : deletar essa função.
	Agora quem lida com isso é o InputManager */
	printf("inputa (sem ofensas)\n");
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {
		// Se o evento for quit, setar a flag para encerrar o game
		if(event.type == SDL_QUIT) {
			this->quitRequested = true;
		}
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			printf("CLICK! %d\n", event.button.button);
			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( face != nullptr ) {
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
			// Senão, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 );
				objPos.rotate( rand() % 360 );
				Vec2 aux (mouseX, mouseY );
				objPos = objPos + aux;
				if(event.key.repeat)
    		      printf("REPEATING KEY!\n");
				else
					AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}
