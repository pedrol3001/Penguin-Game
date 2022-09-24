#ifndef TEXT_H
#define TEXT_H


#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include <SDL_include.h>
#include <Component.h>

class Text : public Component{
public:
  enum TextStyle{ SOLID, SHADED, BLENDED };
  Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color);
  ~Text();

  void Update(float dt);
  void Render();
  bool Is(string type);

  void SetText(string text);
  void SetColor(SDL_Color color);
  void SetStyle(TextStyle style);
  void SetFontFile(string fontFile);
  void SetFontSize(int fontSize);

private:
  void RemakeTexture();

  TTF_Font* font;
  SDL_Texture* texture;

  string text;
  TextStyle style;
  string fontFile;
  int fontSize;
  SDL_Color color;

};

#endif