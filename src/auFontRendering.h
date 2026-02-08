#pragma once
#include "Shader.h"
#include "auCharacter.h"
#include <freetype/fttypes.h>
#include <ft2build.h>
#include <string>
#include <vector>

#include "EBO.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include FT_FREETYPE_H

#include "auColor.h"
#include "auVector2.h"

class auFontRendering {
public:
  auVector2 position;
  int size;
  auColor color;
  VAO *vao = nullptr;
  VBO *vbo = nullptr;
  EBO *ebo = nullptr;

  // All the verticies of all the glyph to draw
  // Needed to send all the data at once to the VBO
  std::vector<float> sentence;

  // Liste of the characters containing the data for the drawing as a list of
  // object auCharacters
  std::vector<auCharacter> listCharacters;

  Shader shaders;

  auFontRendering(auVector2 position, int size, auColor color);
  ~auFontRendering();

  int auSetText(std::string text);
  int setFont(std::string path);
  int auDraw();

private:
  FT_Library library;
  FT_Face face;

  int auInitFreeType();
  int auLoadFace();
  int auLoadFace(std::string path);
  int getGlyph(FT_ULong charcode);
};
