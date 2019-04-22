#include "TileMap.h"
#include <string>
#include "GameObject.h"
#include "Sprite.h"
#include "TileSet.h"
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#define ERR std::cerr
// TileMap simula uma matriz tridimensional, representando
// nosso mapa e suas diversas camadas. Essa matriz contém, em cada
// posição, um índice de tile no TileSet.

// Chama Load com a string passada e seta o tileset.
TileMap::TileMap(GameObject& associated, TileSet* tileSet):
    Component(associated)/* , type("TileMap") */ {
        std::string file("assets/map/tileMap.txt");
        this->Load(file);
        // Setar tileSet
        this->SetTileSet(tileSet);
        this->associated.AddComponent(this);
}


int& TileMap::At(int x, int y, int z){
    return this->tileMatrix[this->layerSize * z + this->mapWidth * y + x];
}

void TileMap::Load(std::string _file /* para nao conflitar com ifstream */){
    const char * fileName = _file.c_str();
    char c;
    std::ifstream fp(fileName, std::ifstream::in);
    fp >> this->mapWidth >> c >> this->mapHeight >> c >> this->mapDepth >> c; 
    this->layerSize = this->mapHeight * this->mapWidth;
    int tileNum = this->mapWidth * this->mapHeight * this->mapDepth;
    this->tileMatrix.resize(tileNum);
    for(int i = 0; i < tileNum; i++) {
        int aux;
        fp >> aux >> c;
        aux -= 1;
        this->tileMatrix[i] = aux;
    }
}

void TileMap::SetTileSet(TileSet* tileSet){
    this->tileSet = tileSet;
}

// Por padrao, passa os argumentos da CAMERA para o renderLayer (defnido no .h)
void TileMap::Render(){
    for(int layer = 0; layer < this->mapDepth; layer++)
        this->RenderLayer(layer);    
}
// Renderiza uma camada do mapa, TILE A TILE. Note que há dois ajustes a
// se fazer:
/*
● Deve-se compensar o deslocamento da câmera (ver parametro padrao no .h )
● Deve-se considerar o tamanho de cada tile (use os membros
GetTileWidth() e GetTileHeight() de TileSet) */
// Ok, funciona.
// TODO: fazer mover todo o tileMap caso paralax esteja false
// Atualmente, move-se apenas a segunda camada (ou seja, é obrigatório o paralax)
void TileMap::RenderLayer(int layer, float cameraX, float cameraY, bool paralax){

    int cX = cameraX*(layer+paralax);
    int cY = cameraY*(layer+paralax);
    for(int idY = 0; idY < this->mapHeight; idY++) {
      for(int idX = 0; idX < this->mapWidth; idX++) {
        int index = this->At(idX, idY, layer);
        // printf("index --> %d\n", index);
        int tileX = idX * this->tileSet->GetTileWidth();
        int tileY = idY * this->tileSet->GetTileHeight();
        this->tileSet->RenderTile(index,tileX+cX, tileY+cY);
      }
    }
}

int TileMap::GetTileWidth(){
    return this->mapWidth;
}

int TileMap::GetTileHeight(){
    return this->mapHeight;
}

int TileMap::GetDepth(){
    return this->mapDepth;
}

bool TileMap::Is(std::string type) {
    return type == this->type;
}

void TileMap::Update(float dt) {
    (void)dt;
}

