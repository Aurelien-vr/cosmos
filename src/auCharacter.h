#pragma once

#include <freetype/freetype.h>
#include <freetype/ftimage.h>
#include <freetype/fttypes.h>
#include <vector>

class auCharacter {
public:
  std::vector<float> verticies;
  std::vector<unsigned int> indices;

  void setVerticies(FT_Vector *list, unsigned short size, FT_UShort EM_size);
};
