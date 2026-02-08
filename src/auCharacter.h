#pragma once

#include "auVector2.h"
#include "../lib/freetype2/freetype/freetype.h"
#include "../lib/freetype2/freetype/ftimage.h"
#include "../lib/freetype2/freetype/fttypes.h"
#include <vector>

class auCharacter {
public:
  std::vector<float> verticies;
  float offset_letter;
  void setVerticies(FT_Face face, int size, auVector2 position, float space);
};
