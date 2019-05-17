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
#include <string>
#include "PenguinBody.h"

using std::string;
using std::endl;
State::State() : music(Music("assets/audio/stageState.ogg") ) {
  GameObject * me = new GameObject;
  new Sprite( *me, "assets/img/ocean.jpg", 1, 10000000 );
  
	// me->AddComponent(new CameraFollower(*me));
	// new CameraFollower(*me);
	// Causa efeito de repetiçã oda imagem...
	/* T5
	A única coisa que precisa fazer é no Update fazer com que a posição de seu gameObject
	associado seja igual à posição da câmera. Adicione esse componente ao gameObject
	que contêm a Sprite de fundo e voilà! */
	string tileSetPath("assets/img/tileset.png");
	TileSet * tileSet = new TileSet(64, 64, tileSetPath, *me);
	new TileMap(*me, tileSet);
	this->objectArray.emplace_back( me );
	
	GameObject * AlienGO = new GameObject;
	new Alien(*AlienGO, 10);
	this->objectArray.emplace_back( AlienGO );
	printf("emplaced alien\n");


	GameObject * PenguinBodyGO = new GameObject;
	new PenguinBody(*PenguinBodyGO);
	this->objectArray.emplace_back( PenguinBodyGO );
	printf("emplaced alien\n");


	this->quitRequested = false;
  // this->music.Play(-1);
}

State::~State() {
	objectArray.clear();
}


void State::Update(double dt) {
	this->quitRequested = this->inputManager->KeyPress(ESCAPE_KEY)
	|| this->inputManager->QuitRequested();
	// Se clicou, ver se aplica dano ou nao
	if( this->inputManager->KeyPress(SPACE_KEY)) {
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
		// printf("LEFT CLICK\n");
		int mouseX = this->inputManager->GetMouseX();
		int mouseY = this->inputManager->GetMouseY();
		// Iterar de tras para frente para dar dano no ultimo inserido.
		// TODO: adicionar robusteza a essa parte
		for(int i = objectArray.size() - 1; i >= 0; --i) {
			// Obtem o ponteiro e casta pra Face. TODO : otimizar isso. Talvez cast estahtico
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
	// cout << "STATE.UPDATE.UPDATE\n";
	auto siz = this->objectArray.size();
	auto begin = this->objectArray.begin();
	// Por alguma razão, alguns GO estava virando nullptr (TODO: descobrir motivo)
	for(int i = 0; i < siz;) {
		if (!this->objectArray[i].get()) {
			cout << "GHOOOOSST!" << endl;
			this->objectArray.erase(begin + i);
			siz--;
			continue;
		}
		else  {
			this->objectArray[i]->Update(dt);
			i++;
		}
		// cout << "[State.Update] KALL END " << GO << endl;
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
	// [T4] Usaremos a câmera sem foco, por enquanto.
	/* 	Em State::Update, chame o
		update da câmera, e [...]*/ 
	Camera::Update(dt);
}


//  trata da etapa 4 de Game::Run
void State::Render() {
	/*em State::Render, PASSE AS COORDENADAS DA CÂMERA PARA
		O TILEMAP, E TESTE SE ELE SE MOVE CORRETAMENTE.*/
	for(auto& GO : this->objectArray) {
		GO->Render();
	}
}

void State::AddObject(int mouseX, int mouseY) {
	// criar um GameObject que conterá as informações do nosso primeiro inimigo.
	GameObject * enemy = new GameObject;
	
	// Sprite aponta para enemy
	Sprite * sprite = new Sprite(*enemy, "assets/img/penguinface.png");
	
	enemy->box.x = mouseX - sprite->GetWidth()/2;
	enemy->box.y = mouseY - sprite->GetHeight()/2;
	enemy->box.w = sprite->GetWidth();
	enemy->box.h = sprite->GetHeight();
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
	this->started = true;
	for(auto& i : this->objectArray) {
		auto p = i.get();
		if(!p) {
      cout << "Some GameObject suddenly died... " << endl;
      continue;
			// myAbort(666);
		}
		cout << "STAT STAT STAT" << p << "\n";
		p->Start();
		cout << "END END END\n";
	}
}

weak_ptr<GameObject> State::AddObject(GameObject* go) {
	shared_ptr<GameObject> sharedGO(go);
	if(this->started && !go->started)
		go->Start();
	this->objectArray.push_back(sharedGO);  // TINHA ME ESQUECIDO DESSA LINHA....
	return weak_ptr<GameObject>(sharedGO);	// POSSIVEL BUG [??]
}

/* Essa função é geralmente usada para se obter o
weak_ptr de algum objeto que já temos o ponteiro puro dele e que já foi
adicionado ao vetor de objetos. */
weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
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

