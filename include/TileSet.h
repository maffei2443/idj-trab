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
    unsigned totalTileSize;
    int rows, columns;
    int tileWidth;
    int tileHeight;
    Sprite tileSet;
public:
    TileSet(int, int, std::string, GameObject&);
    void RenderTile(unsigned, float, float);
    int GetTileWidth();
    int GetTileHeight();
};

#endif
