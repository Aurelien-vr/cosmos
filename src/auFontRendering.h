#pragma once
#include "Shader.h"
#include "auCharacter.h"
#include "../lib/freetype2/freetype/fttypes.h"
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

  // Stores the number of points for each character
  // Example: [15, 28] means first char has 15 points, second has 28 points
  std::vector<short> nb_points_character;

  // Is a list of the list of the end position of the glyph contours
  // Example: [[3,10],[5,7]]. The first glyph first contour en at the index 3
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
