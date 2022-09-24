#include <TileSet.h>

TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight){
  rows = tileSet.GetHeight() / tileHeight;
  columns = tileSet.GetWidth() / tileWidth;
}

void TileSet::RenderTile(unsigned index, float x, float y){
  if(static_cast<int>(index) >= rows * columns -1) return;

  tileSet.SetClip((index % columns) * tileWidth, (index / columns) * tileHeight, tileWidth, tileHeight);
  tileSet.Render(x, y);
}

int TileSet::GetTileWidth(){
  return tileWidth;
}

int TileSet::GetTileHeight(){
  return tileHeight;
}