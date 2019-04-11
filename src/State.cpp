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

State :: State() : music(Music("assets/audio/stageState.ogg") ) {
  GameObject * me = new GameObject;

	TileSet * tileSet = new TileSet(64, 64, "assets/img/tileset.png", *me);
	TileMap * tileMap = new TileMap(*me, tileSet);
	/* Acrescente no construtor um GameObject com o TileMap(map/tileMap.txt),
	lembrando de construir o Tileset(img/tileset.png) para enviar ao
	TileMap. As dimensões das subimagens do tileset são 64x64.
	COLOQUE O BOX DESSE GAMEOBJECT EM (0,0). 
	Importante: não se esqueça de desalocar o TileSet na hora certa!
 */



  bg = new Sprite( *me, "assets/img/ocean.jpg" );
	this->objectArray.emplace_back( me );
  // setar a largura e altura da box do GameObject que o contém (associated)
	// baseado no carregado pela Sprite em seu construtor.
	
	// Depois disso, adicionemos a esse GameObject [enemy] o Componente Sound
	// usando audio/boom.wav 
	// Sound * enemySound = new Sound(*enemy, "assets/audio/boom.wav");
	
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
 	// printf("[State.cpp] this->Input()\n");
	this->Input();

	for(auto& GO : this->objectArray) {
		GO->Update(dt);
	}

	for(auto it = this->objectArray.begin();
		 it != this->objectArray.end();) {
			if((**it).IsDead()) {
        it = this->objectArray.erase(it);
        printf("morreu!\n");
      }
			else it++;
	}
	// printf("Apagou os mortos ? \n");
}


//  trata da etapa 4 de Game::Run
void State :: Render() {
  //  Para esse trabalho, chame o render do fundo (bg). [?]
  // printf("Before State.Render\n");
  for(auto& GO : this->objectArray)
		GO->Render();
  // printf("After State.Render\n");
}

// BUG
void State :: AddObject(int mouseX, int mouseY) {
  printf("mouseX, mouseY %d, %d", mouseX, mouseY );
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
  printf("penguins |---> %u\n", this->objectArray.size());
}

bool State :: QuitRequested() {
  // printf("[Log] Returning from bool State :: QuitRequested()\n");
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
	// printf(" while (SDL_PollEvent(&event))\n ");
	while (SDL_PollEvent(&event)) {
		// usleep(20);
		// Se o evento for quit, setar a flag para terminação
		// printf("if(event.type == SDL_QUIT)\n");
		if(event.type == SDL_QUIT) {
			this->quitRequested = true;
		}
		// Se o evento for clique...
		// printf("if(event.type == SDL_MOUSEBUTTONDOWN)\n");
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			// LOG("SDL_MOUSEBUTTONDOWN)\n");

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
            printf("MOOOOOORRRRREU\n");
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		// printf("if( event.type == SDL_KEYDOWN )\n");
		if( event.type == SDL_KEYDOWN ) {
			// LOG("SDL_KEYDOWN)\n");

			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 );
				objPos.rotate( rand() % 360 );
				Vec2 aux (mouseX, mouseY );
				objPos = objPos + aux;
				AddObject((int)objPos.x, (int)objPos.y);
        printf("added penguin!?\n");
			}
		}
	}
}
