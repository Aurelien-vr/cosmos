#pragma once

#include "auVector2.h"
#include <freetype/freetype.h>
#include <freetype/ftimage.h>
#include <freetype/fttypes.h>
#include <vector>

class auCharacter {
public:
  std::vector<float> verticies;
  float offset_letter;
  void setVerticies(FT_Face face, int size, auVector2 position, float space);
};
