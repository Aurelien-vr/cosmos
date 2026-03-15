#pragma once

#include "../lib/freetype2/freetype/freetype.h"
#include "../lib/freetype2/freetype/ftimage.h"
#include "../lib/freetype2/freetype/fttypes.h"
#include "auVector2.h"
#include <freetype/ftimage.h>
#include <vector>

class auCharacter {
public:
  std::vector<FT_Vector_> verticies;
  std::vector<short> outlineEnd;
  float offset_letter;
  bool compound;
  FT_Face face;
  short resolution;

  auCharacter(FT_Face face, short resolution);

  void setResolution();

  void setVerticies(int size, auVector2 position, float space);
  void setOutlineEnd();
  int getSize() { return verticies.size(); };

private:
  std::vector<FT_Vector_> bezierPoints(float interval, FT_Vector_ start,
                                       FT_Vector_ end, FT_Vector_ pivot);
  long lerp(float a, float b, float f);
};
