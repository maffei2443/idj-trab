#include "TileSet.h"
#include <string>
#include <cmath>
// "OK"
TileSet :: TileSet(int tileWidth, int tileHeight,std::string file, GameObject& associated) :
        tileWidth(tileWidth), tileHeight(tileHeight),  tileSet(associated, file) {
/*     Se abertura (do Sprite) for bem sucedida, descobre, pelo
     TAMANHO DO SPRITE E DOS TILES, QUANTAS COLUNAS E QUANTAS LINHAS O TILESET TEM.*/
    printf("TileSet dim: %d %d\n", this->tileSet.GetWidth(), this->tileSet.GetHeight());
    this->columns = (int)ceil(this->tileSet.GetWidth() / this->tileWidth);
    this->rows = (int)ceil(this->tileSet.GetHeight() / tileHeight);
    this->totalTileSize = this->rows * this->columns;
    printf("col: %d, row: %d, totalTileSize: %d\n", columns, rows, totalTileSize);/* abort(); */
}

// Ok está sendo chamado.
void TileSet::RenderTile (unsigned index, float x, float y) {
    // printf("totalTileSize ---> %d\n", totalTileSize);
    
    // std::cout << "index ::: " << index << std::endl;
    // printf("index > -1 && index < totalTileSize ? %d\n", index > -1 && index < totalTileSize);
    printf("index >>> %u\n", index );
    if(index > 0 && index < totalTileSize) {
        int xSet = (index/this->columns);
        int ySet = index%this->columns;
        printf("\033[0;31m(x, y) <--> ");
        printf("\033[0;34m(%f, %f)\n", x, y);
        printf("\033[0;m");
        // calcule e sete o clip desejado no sprite,
        this->tileSet.SetClip(xSet*this->tileWidth, ySet*this->tileHeight, 
            this->tileWidth, this->tileHeight);
        printf("tileWidth tileHeight : %d %d\n", tileWidth, tileHeight);
        // e renderize na posição dada
        this->tileSet.Render(x, y);
        // this->tileSet.Render(xSet*this->tileWidth, ySet*this->tileHeight);
    }
    // else
    //     printf("pika pika pika\n");
}

int TileSet:: GetTileWidth(){
    return this->tileWidth;
}

int TileSet:: GetTileHeight(){
    return this->tileHeight;
}
