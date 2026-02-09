#pragma once

#include "auVector2.h"
#include "../lib/freetype2/freetype/freetype.h"
#include "../lib/freetype2/freetype/ftimage.h"
#include "../lib/freetype2/freetype/fttypes.h"
#include <vector>

class auCharacter {
public:
  std::vector<auVector2> verticies;
  std::vector<short> outlineEnd;
  float offset_letter;
  bool compound;

  void setVerticies(FT_Face face, int size, auVector2 position, float space);
  void setOutlineEnd(FT_Face face);
  int getSize() { return verticies.size(); };
};
