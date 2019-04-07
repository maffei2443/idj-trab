#include "TileSet.h"
#include <string>
#include <cmath>

TileSet :: TileSet(int tileWidth, int tileHeight,std::string file) :
        tileWidth(tileWidth), tileHeight(tileHeight), tileSet(this->gameObjectOfSprite, file){
/*     Se abertura (do Sprite) for bem sucedida, descobre, pelo
     TAMANHO DO SPRITE E DOS TILES, QUANTAS COLUNAS E QUANTAS LINHAS O TILESET TEM.*/
    this->columns = (int)ceil(this->tileSet.GetWidth() / this->tileWidth);
    this->rows = (int)ceil(this->tileSet.GetHeight() / tileHeight);
    this->totalTileSize = this->rows * this->columns;
}

void TileSet::RenderTile (unsigned index, float x, float y) {
    if(index > -1 && index < totalTileSize) {
        // calcule e sete o clip desejado no sprite, e renderize na posição dada
    }
}

int TileSet:: GetTileWidth(){
    return this->tileWidth;
}

int TileSet:: GetTileHeight(){
    return this->tileHeight;
}
