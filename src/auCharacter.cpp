#include "auCharacter.h"
#include <iostream>

void auCharacter::setVerticies(FT_Face face, float space) {
  FT_Vector *list = face->glyph->outline.points;
  unsigned short size = face->glyph->outline.n_points;
  FT_UShort EM_size = face->units_per_EM;

  for (int i = 0; i < size; i++) {
    float dpi = 96.f;
    float scaling = 1.5f;
    float ndc_x =
        (((list[i].x * ((41 * (dpi * scaling)) / 72.f)) / EM_size / 800) *
         2.0f) +
        space;
    float ndc_y =
        1.0f -
        ((list[i].y * ((41 * (dpi * scaling)) / 72.f)) / EM_size / 600) * 2.0f -
        1.0f;

    offset_letter =
        ((face->glyph->metrics.horiAdvance * ((41 * (dpi * scaling)) / 72.f)) /
         EM_size / 800) *
        2.0f;

    verticies.push_back(ndc_x);
    verticies.push_back(-ndc_y);

    // std::cout << "x: " << ndc_x << " y: " << ndc_y << std::endl;
  }
}
