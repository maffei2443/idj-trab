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
TileMap :: TileMap(GameObject& associated, TileSet* tileSet):
    Component(associated)/* , type("TileMap") */ {
        std::string file("assets/map/tileMap.txt");
        this->Load(file);
        // TODO : setar tileSet
        this->SetTileSet(tileSet);
        this->associated.AddComponent(this);
}

// TODO : check for BUG
// At é um método acessor. Ele retorna uma referência ao elemento
// [x][y][z] de tileMatrix.
int& TileMap :: At(int x, int y, int z){
    return this->tileMatrix[this->mapWidth * this->mapHeight * z + this->mapWidth * y + x];
    // return this->tileMatrix[
    //     x * this->heightPlusDepth + y * this->mapHeight + z
    // ];
}

void TileMap :: Load(std::string _file /* para nao conflitar com ifstream */){
    const char * fileName = _file.c_str();
    std::cout << "file-name: " << fileName << std::endl;
    char c;

    std::ifstream fp(fileName, std::ifstream::in);
    printf("WOW");
    fp >> this->mapWidth >> c >> this->mapHeight >> c >> this->mapDepth >> c;
 
    fprintf(stdout, "%d,%d,%d,%c\n\n", 
        this->mapWidth, this->mapHeight, this->mapDepth, c);
    this->heightPlusDepth = this->mapHeight + this->mapDepth;
    // Em seguida, vêm os tiles, que devem ser carregados em ordem 
    // para a matriz de tiles.
/*  Note que, para o arquivo que usamos na disciplina, tiles vazios 
    são representados por 0, que é o padrão do editor de tilemaps 
    open source TileD. Para o nosso código, é mais conveniente que eles
    sejam representados por 1, e o primeiro tile do tileset por 0.
    Portanto, SUBTRAIA UM DE CADA ÍNDICE LIDO DO ARQUIVO. */
    int tileNum = this->mapWidth * this->mapHeight * this->mapDepth;
    this->tileMatrix.reserve(tileNum);
    for(int i = 0; i < tileNum; i++) {
        int aux;
        fp >> aux >> c;
        this->tileMatrix[i] = --aux;

    }
    // return;
    // for(int depthIdx = 0; depthIdx < this->mapDepth; depthIdx++) {
    //     for(int widthIdx = 0; widthIdx < this->mapWidth; widthIdx++)  {
    //         for(int heightIdx = 0; heightIdx < this->mapHeight; heightIdx++) {
    //             int px;/*  = this->At(widthIdx, heightIdx, depthIdx); */
    //             fp >> px >> c;
    //             px--;
    //             std::cout << px << c;
    //             this->At(widthIdx, heightIdx, depthIdx) = px;
    //         }
    //         // abort();
    //     }
    // }
    // // for(int i = 0; i < tileNum; i++) {        
    // //     fscanf(fp, "%d", &this->tileMatrix[i]);
    // //     this->tileMatrix[i] --;
    // // }
}

void TileMap :: SetTileSet(TileSet* tileSet){
    this->tileSet = tileSet;
}

void TileMap :: Render(){
    printf("TILE MAP RENDER\n");
    for(int layer = 0; layer < this->mapDepth; layer++)
        this->RenderLayer(layer);    
}
// Renderiza uma camada do mapa, TILE A TILE. Note que há dois ajustes a
// se fazer:
void TileMap :: RenderLayer(int layer, int cameraX, int cameraY){
    (void)cameraX;
    (void)cameraY;
    printf("TILE MAP RENDER_LAYER{%d}\n", layer);
    // TODO : ● Deve-se considerar o tamanho de cada tile
    using namespace std;
    cout << "w,h " << mapWidth << "," << mapHeight << endl;
    // TODO : ● Deve-se compensar o deslocamento da câmera
    
    int tile;
    for(int idY = 0; idY < this->mapHeight; idY++) {
        for(int idX = 0; idX < this->mapWidth; idX++) {
            // this->At(idX, idY, layer) = this->tileSet;
            // Ok passa o indice dorreto de tile
            unsigned index = (unsigned)this->At(idX, idY, layer);
            int tileX = idX * this->tileSet->GetTileWidth();
            int tileY = idY * this->tileSet->GetTileHeight();
            this->tileSet->RenderTile(index,idX*64, idY*64);
            // gambs
        }
    }
}

int TileMap :: GetTileWidth(){

}

int TileMap :: GetTileHeight(){

}

int TileMap :: GetDepth(){

}

bool TileMap :: Is(std::string type) {
    return type == this->type;
}

void TileMap :: Update(float dt) {
    (void)dt;
}

