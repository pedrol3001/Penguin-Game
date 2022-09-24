#include <Game.h>
#include <Camera.h>

#include <Resources.h>
#include <Text.h>

Text::Text(
  GameObject &associated,
  string fontFile,
  int fontSize,
  TextStyle style,
  string text,
  SDL_Color color
) : Component(associated),
texture(nullptr),
text(text),
style(style),
fontFile(fontFile),
fontSize(fontSize),
color(color){
  RemakeTexture();
}

Text::~Text(){
  if (texture == nullptr) return;

  SDL_DestroyTexture(texture);
}

void Text::Update(float dt){}

void Text::Render(){
  SDL_Rect clipRect = {
    0,
    0,
    static_cast<int>(associated.box.w),
    static_cast<int>(associated.box.h)
  };
  SDL_Rect destRect = {
    static_cast<int>((associated.box + Camera::pos).x),
    static_cast<int>((associated.box + Camera::pos).y),
    static_cast<int>(clipRect.w),
    static_cast<int>(clipRect.h)
  };

  SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

bool Text::Is(string type){
  return type == "TEXT";
}

void Text::SetText(string text){
  Text::text = text;
  RemakeTexture();
}

void Text::SetColor(SDL_Color color){
  Text::color = color;
  RemakeTexture();
}

void Text::SetStyle(TextStyle style){
  Text::style = style;
  RemakeTexture();
}

void Text::SetFontSize(int fontSize){
  Text::fontSize = fontSize;
  RemakeTexture();
}

void Text::SetFontFile(string fontFile){
  Text::fontFile = fontFile;
}

void Text::RemakeTexture(){
  if (texture != nullptr) SDL_DestroyTexture(texture);

  TTF_Font* font = Resources::GetInstance().GetFont(fontFile, fontSize);

  SDL_Surface *surface = nullptr;

  switch (style){
    case TextStyle::SOLID:
      surface = TTF_RenderText_Solid(font, text.c_str(), color);
      break;
    case TextStyle::SHADED:
      surface = TTF_RenderText_Shaded(font, text.c_str(), color, { 0, 0, 0, 255 });
      break;
    case TextStyle::BLENDED:
      surface = TTF_RenderText_Blended(font, text.c_str(), color);
      break;
  }

  texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
  SDL_SetTextureAlphaMod(texture, color.a);

  if(surface){
    associated.box.w = surface->w;
    associated.box.h = surface->h;
  }

  SDL_FreeSurface(surface);
}