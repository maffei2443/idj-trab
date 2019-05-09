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
using std::string;
class TileMap : public Component {
private:
    int layerSize;
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth, mapHeight, mapDepth;
    const static string type;
public:
    TileMap(GameObject&,  TileSet*);
    void Load(string);
    void SetTileSet(TileSet*);
    int& At(int, int, int z = 0);
    // Fazendo ajuste: por padrao, recebe posicao da camera para fazer os ajustes
    void RenderLayer(int, double cameraX=Camera::pos.x, 
                     double cameraY=Camera::pos.y, bool paralax = true);
    
    int GetTileWidth();
    int GetTileHeight();
    int GetDepth();

    // Herda de component
    void Render();
    bool Is(string);
    void Update(double);

    const inline string GetType() const {        
        return TileMap::type;
    }
    // t5
    bool started = false;
    void Start();    
};

#endif
