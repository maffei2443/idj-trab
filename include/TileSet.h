#ifndef TILESET_H
#define TILESET_H
#include <string>
#include "GameObject.h"
#include "Sprite.h"
/* Uma classe de tileset é responsável por armazenar os tiles
utilizados na renderização do TileMap. Internamente, os tiles
fazem parte de um grande Sprite (img/tileset.png). QUANDO
QUEREMOS RENDERIZAR UM DELES, RECORTAMOS USANDO O CLIP DO SPRITE.
 */
class TileSet {
private:
    GameObject gameObjectOfSprite;
    Sprite tileSet;
    int rows, columns, totalTileSize;
    int tileWidth, tileHeight;
public:
    TileSet(int, int, std::string);
    void RenderTile(unsigned, float, float);
    int GetTileWidth();
    int GetTileHeight();
};

#endif
