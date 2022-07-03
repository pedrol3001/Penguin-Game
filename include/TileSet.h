#ifndef TILESET_H
#define TILESET_H

#include <string>
#include "Sprite.h"

using namespace std;

class TileSet {
public:
  TileSet(int tileWidth, int tileHeight, string file);

  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();

private:
  Sprite tileSet;

  int rows;
  int columns;

  int tileWidth;
  int tileHeight;
};

#endif