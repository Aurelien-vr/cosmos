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
  std::vector<float> sentence;
  // List of number of point in the glyph to draw
  std::vector<short> glyph;
  // List of list of contours -> [[3,5],[2,4]]
  std::vector<std::vector<short>> list_contours;
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
