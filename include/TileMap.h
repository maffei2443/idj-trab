#ifndef TILEMAP_H
#define TILEMAP_H
#include <string>
#include "GameObject.h"
// #include "Sprite.h"
#include "TileSet.h"
#include <string>
#include <vector>
#include "Camera.h"
// TileMap simula uma matriz tridimensional, representando
// nosso mapa e suas diversas camadas. Essa matriz contém, em cada
// posição, um índice de tile no TileSet.

class TileMap : public Component {
private:
    int layerSize;
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth, mapHeight, mapDepth;
public:
    const std::string type = std::string("TileMap");
    TileMap(GameObject&,  TileSet*);
    void Load(std::string);
    void SetTileSet(TileSet*);
    int& At(int, int, int z = 0);
    // Fazendo ajuste: por padrao, recebe posicao da camera para fazer os ajustes
    void RenderLayer(int, int cameraX=Camera::pos.x, int cameraY=Camera::pos.y);
    
    int GetTileWidth();
    int GetTileHeight();
    int GetDepth();

    // Herda de component
    void Render();
    bool Is(std::string);
    void Update(float);

    const inline std::string GetType(){        
        return this->type;
    }
};

#endif
