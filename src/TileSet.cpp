#include "TileSet.h"
#include <string>
#include <cmath>
// "OK"
TileSet :: TileSet(int tileWidth, int tileHeight,std::string file, GameObject& associated) :
        tileWidth(tileWidth), tileHeight(tileHeight),  tileSet(associated, file) {
/*     Se abertura (do Sprite) for bem sucedida, descobre, pelo
     TAMANHO DO SPRITE E DOS TILES, QUANTAS COLUNAS E QUANTAS LINHAS O TILESET TEM.*/
    //////printf("TileSet dim: %d %d\n", this->tileSet.GetWidth(), this->tileSet.GetHeight());
    this->columns = (int)ceil(this->tileSet.GetWidth() / this->tileWidth);
    this->rows = (int)ceil(this->tileSet.GetHeight() / tileHeight);
    this->totalTileSize = this->rows * this->columns;
    //////printf("col: %d, row: %d, totalTileSize: %d\n", columns, rows, totalTileSize);/* abort(); */
}

// Ok está sendo chamado.
// Ok testado. Funciona.
void TileSet::RenderTile (unsigned index, float x, float y) {
    if( index < totalTileSize) {
        int xSet = (index/this->columns);
        int ySet = index%this->columns;
        int clipX = xSet * this->tileWidth;
        int clipY = ySet * this->tileHeight;
        // calcule e sete o clip desejado no sprite,
        this->tileSet.SetClip(clipY, clipX, this->tileWidth, this->tileHeight);
        // e renderize na posição dada
        this->tileSet.Render(x, y);
    }
}

int TileSet:: GetTileWidth(){
    return this->tileWidth;
}

int TileSet:: GetTileHeight(){
    return this->tileHeight;
}
