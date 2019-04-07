#include "TileMap.h"
#include <string>
#include "GameObject.h"
#include "Sprite.h"
#include "TileSet.h"
#include <string>
#include <vector>
#include <cstdio>
// TileMap simula uma matriz tridimensional, representando
// nosso mapa e suas diversas camadas. Essa matriz contém, em cada
// posição, um índice de tile no TileSet.
TileMap :: TileMap(GameObject& associated, std::string file, TileSet* tileSet):
    Component(associated) {
        this->Load(file);
        // TODO : setar tileSet
}

// TODO : check for BUG
// At é um método acessor. Ele retorna uma referência ao elemento
// [x][y][z] de tileMatrix.
int& TileMap :: At(int x, int y, int z){
    return this->tileMatrix[
        x * this->heightPlusDepth + y * this->mapHeight + z
    ];
}

void TileMap :: Load(std::string file){
    const char * fileName = file.c_str(); 
    FILE * fp = fopen(fileName, "r");
    fscanf(fp, "%d %d %d\n", 
        &this->mapWidth, &this->mapHeight, &this->mapDepth);
    this->heightPlusDepth = this->mapHeight + this->mapDepth;
    // Em seguida, vêm os tiles, que devem ser carregados em ordem 
    // para a matriz de tiles.
/*  Note que, para o arquivo que usamos na disciplina, tiles vazios 4
    são representados por 0, que é o padrão do editor de tilemaps 
    open source TileD. Para o nosso código, é mais conveniente que eles
    sejam representados por 1, e o primeiro tile do tileset por 0.
    Portanto, subtraia um de cada índice lido do arquivo. */
    // this->mapWidth --;
    // this->mapHeight --;
    // this->mapDepth --;
    int tileNum = this->mapWidth * this->mapHeight * this->mapDepth;
    int read;
    this->tileMatrix.reserve(tileNum);
    for(int i = 0; i < tileNum; i++) {        
        fscanf(fp, "%d", &this->tileMatrix[i]);
        this->tileMatrix[i] --;
    }
}

void TileMap :: SetTileSet(TileSet* tileSet){
    this->tileSet = tileSet;
}

void TileMap :: Render(){

}
// Renderiza uma camada do mapa, TILE A TILE. Note que há dois ajustes a
// se fazer:
void TileMap :: RenderLayer(int layer, int cameraX, int cameraY){
    // TODO : ● Deve-se considerar o tamanho de cada tile
    
    // TODO : ● Deve-se compensar o deslocamento da câmera
    
    int tile;
    for(int idX = 0; idX < this->mapWidth; idX++) {
        for(int idY = 0; idY < this->mapWidth; idX++) {
            tile = this->At(idX, idY, layer);
            this->Render(  );
        }

    }
}

int TileMap :: GetTileWidth(){

}

int TileMap :: GetTileHeight(){

}

int TileMap :: GetDepth(){

}

