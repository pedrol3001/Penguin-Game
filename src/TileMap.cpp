#include "TileMap.h"

#include "SDL_exception.h"
#include <fstream>
#include <iostream>
#include "Camera.h"

using namespace std;

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component(associated) {
  Load(file);
  SetTileSet(tileSet);
}

void TileMap::Load(string file) {
  ifstream fp(file);
  string data = "";

  getline(fp, data);
  char* dimensions = (char*) data.c_str();

  mapWidth = stoi(strtok(dimensions,","));
  mapHeight = stoi(strtok (NULL, ","));
  mapDepth = stoi(strtok (NULL, ","));

  while(getline(fp, data,','))
  {
    try{
      tileMatrix.push_back(stoi(data) - 1);
    }catch(invalid_argument &err){
      cout << "File " << file << " with char -> " << data << " <- invalid. Skipping it." << endl;
    }
  }
  fp.close();
}

void TileMap::SetTileSet(TileSet *tileSet) {
  this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z) {
  int index = x + (y * mapWidth) + (z * mapWidth * mapHeight);
  return tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
  for (int i = 0; i < mapWidth; i++){
    for (int j = 0; j < mapHeight; j++){
      int x = (i * tileSet->GetTileWidth()) - cameraX;
      int y = (j * tileSet->GetTileHeight()) - cameraY;

      if (x < associated.box.w && y < associated.box.h) {
        if(At(i, j, layer) == -1) continue;

        tileSet->RenderTile(At(i, j, layer), x, y);
      }
    }
  }
}

int TileMap::GetWidth() {
  return mapWidth;
}

int TileMap::GetHeight() {
  return mapHeight;
}

int TileMap::GetDepth() {
  return mapDepth;
}

void TileMap::Render() {
  for (int i = 0; i < mapDepth; i++) {
    RenderLayer(i, Camera::pos.x, Camera::pos.y);
  }
}

bool TileMap::Is(string type) {
    return type == "TILE_MAP";
}

void TileMap::Update(float dt) {}