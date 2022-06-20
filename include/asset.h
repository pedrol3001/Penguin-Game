#ifndef ASSET_HPP
#define ASSET_HPP

#include <string>

using namespace std;

class Asset {
public:
  virtual void Open (string file) = 0;
  virtual bool IsOpen() = 0;
};

#endif