#include "auCharacter.h"
#include <iostream>

void auCharacter::setVerticies(FT_Face face, int size, auVector2 position,
                               float space) {
  FT_Vector *list = face->glyph->outline.points;
  unsigned short nbPoints = face->glyph->outline.n_points;
  FT_UShort EM_size = face->units_per_EM;

  for (int i = 0; i < nbPoints; i++) {
    float dpi = 96.f;
    float scaling = 1.5f;
    float ndc_x =
        ((((list[i].x * ((size * (dpi * scaling)) / 72.f)) / EM_size / 800) *
          2.0f) +
         space) +
        position.x;
    float ndc_y =
        1.0f -
        ((list[i].y * ((size * (dpi * scaling)) / 72.f)) / EM_size / 600) *
            2.0f -
        1.0f - position.y;

    offset_letter = ((face->glyph->metrics.horiAdvance *
                      ((size * (dpi * scaling)) / 72.f)) /
                     EM_size / 800) *
                    2.0f;

    verticies.push_back(ndc_x);
    verticies.push_back(-ndc_y);
  }
}
