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
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "Util.h"

using std::endl;
State::State() : music(Music("assets/audio/stageState.ogg") ) {
  GameObject * bg = new GameObject;
  new Sprite( *bg, "assets/img/ocean.jpg" );
	// new CameraFollower(*bg); // still not sure about this necessity
	/* T5
	A única coisa
que precisa fazer é no Update fazer com que a posição de seu gameObject
associado seja igual à posição da câmera.
Adicione esse componente ao gameObject que contêm a Sprite de
fundo e voilà! */
	std::string tileSetPath("assets/img/tileset.png");
	TileSet * tileSet = new TileSet(64, 64, tileSetPath, *bg);
	new TileMap(*bg, tileSet);
	this->objectArray.emplace_back( bg );
	printf("Added >>>>>>>>>> %p\n", bg);
	printf("emplaced background\n");
	// No construtor de State, crie um Alien
	// (criar GO e adicionar componente Alien)
	GameObject * AlienGO = new GameObject;
	new Alien(*AlienGO, 10);  // TODO: IMPLEMENTAR MINIONS
	this->objectArray.emplace_back( AlienGO );
	printf("Added >>>>>>>>>> %p\n", AlienGO);

	printf("emplaced alien\n");
  printf("HOW MANY GO : %lu\n", this->objectArray.size());
	this->quitRequested = false;
  // this->music.Play(-1);
}

State::~State() {
	objectArray.clear();
}


void State::Update(double dt) {
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
		// printf("GG SPACE!\n");fflush(stdout);
		Vec2 objPos = Vec2( 200, 0 );
		objPos.rotate( rand() % 360 );
		Vec2 aux (inputManager->GetMouseX(), inputManager->GetMouseY() );
		objPos = objPos + aux;
		this->AddObject((int)objPos.x, (int)objPos.y);
	}
	// TODO: perguntaro deve se o bloco abaixo deve permanecer aqui
	// Acerta [UM] pinguim sobre o mouse
	#pragma region
	if( this->inputManager->MousePress(LEFT_MOUSE_BUTTON)) {
		printf("LEFT CLICK\n");
		int mouseX = this->inputManager->GetMouseX();
		int mouseY = this->inputManager->GetMouseY();
		// Iterar de tras para frente para dar dano no ultimo inserido.
		// TODO: adicionar robusteza a essa parte
		for(int i = objectArray.size() - 1; i >= 0; --i) {
			// printf("DAMAGE?? %d\n", i);
			// Obtem o ponteiro e casta pra Face.
			GameObject* go = (GameObject*) objectArray[i].get();
			if(go->box.Contains( {(double)mouseX, (double)mouseY} ) ) {
				Face* face = (Face*)go->GetComponent( "Face" );
				if ( face != nullptr ) {
					// Aplica dano
					face->Damage(std::rand() % 10 + 10);
					// Sai do loop (só queremos acertar um [bala nao perfurante])
					break;
				}
			}
		}
	}
	#pragma endregion

	for(auto& GO : this->objectArray) {
		// std::cout << "CALLING UPDATE FROM --> " << &GO << std::endl;
		// printf("State.Update %p\n", GO.get());
		GO->Update(dt);
	}
	// abort();
	// ERR << "Checking for dead... " << endl;
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
	// [T4] Usaremos a câmera sem foco, por enquanto.
	/* 	Em State::Update, chame o
		update da câmera, e [...]*/ 
	
	
	Camera::Update(dt);
}


//  trata da etapa 4 de Game::Run
void State::Render() {
	/*em State::Render, PASSE AS COORDENADAS DA CÂMERA PARA
		O TILEMAP, E TESTE SE ELE SE MOVE CORRETAMENTE.*/
	// this->tileMap
	for(auto& GO : this->objectArray) {
		GO->Render();
	}
}

void State::AddObject(int mouseX, int mouseY) {
	// criar um GameObject que conterá as informações do nosso primeiro inimigo.
	GameObject * enemy = new GameObject;
	
	// Sprite aponta para enemy
	Sprite * sprite = new Sprite(*enemy, "assets/img/penguinface.png");
	
	/* 
		Terceiro, em State::AddObject, também leve em consideração
		a câmera na hora de posicionar as Faces. [?? Como assim?]
	 */
	

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

bool State::QuitRequested() {
  return this->quitRequested;
}

void State::LoadAssets() {
  //  Para esse trabalho, chame o render do fundo (bg). [?]
}

// t5
void State::Start() {
// 	Em State::Start você deve chamar LoadAssets e depois deve percorrer
// o objectArray chamando o Start de todos eles. Ao final, coloque true em
// started.
	this->LoadAssets();
	this->started = true;;
	for(auto& i : this->objectArray) {
		i.get()->Start();
	}
}

// t5
std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	/* Em State::AddObject, ao invés de simplesmente colocar o GameObject
passado no vetor, você vai criar um std:shared_ptr< GameObject > passando
esse GameObject* como argumento de seu construtor. */
	std::shared_ptr<GameObject> weakPtr = 
		std::shared_ptr<GameObject>(go);
	/* Depois faça um
PUSH_BACK desse shared_ptr em objectArray */
	this->objectArray.push_back(weakPtr);
	/* Se started já tiver sido
chamado, chame o start desse GameObject. */
	if(this->started)
		weakPtr.get()->Start();
	/* E retorne um std::weak_ptr <
GameObject > construído usando o shared_ptr criado */
	return std::weak_ptr<GameObject>(weakPtr);	// POSSIVEL BUG [??]
	/* Em Game::Run, chame o Start do State logo antes do while. */
}

/* Essa função é geralmente usada para se obter o
weak_ptr de algum objeto que já temos o ponteiro puro dele e que já foi
adicionado ao vetor de objetos. */
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	/* percorrer o vetor de objetos que
temos comparando o endereço armazenado em cada std::shared_ptr com o
passado como argumento. */
	for(auto& i : this->objectArray) {
		/*  Crie e retorne um std::weak_ptr a partir do
		std::shared_ptr quando os endereços forem iguais. */
		if(i.get() == go) {
			return std::weak_ptr<GameObject>(i);
		}
	}
	return std::weak_ptr<GameObject>();
}

