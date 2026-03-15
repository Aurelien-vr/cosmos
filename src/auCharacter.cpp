#include "auCharacter.h"
#include <freetype/ftimage.h>
#include <iostream>
#include <vector>

auCharacter::auCharacter(FT_Face face, short resolution)
    : face(face), resolution(resolution) {}

void auCharacter::setOutlineEnd() {
  for (short index = 0; index < face->glyph->outline.n_contours; index++) {
    outlineEnd.push_back(face->glyph->outline.contours[index]);
  }
}

void auCharacter::setResolution() {
  // std::cout << "res: " << resolution << std::endl;

  float interval = 1.f / (resolution + 1);

  FT_Outline outline = face->glyph->outline;

  for (short i_point = 0; i_point < outline.n_points; i_point++) {

    if (outline.tags[i_point] == FT_CURVE_TAG_ON) {
      verticies.push_back(outline.points[i_point]);

    } else if (outline.tags[i_point] == FT_CURVE_TAG_CONIC) {

      std::vector<FT_Vector_> bezierCurvePoints =
          bezierPoints(interval, outline.points[i_point - 1],
                       outline.points[i_point + 1], outline.points[i_point]);

      // std::cout << "size list: " << bezierCurvePoints.size() << std::endl;

      verticies.insert(verticies.end(), bezierCurvePoints.begin(),
                       bezierCurvePoints.end());
    }
  }
  // std::cout << "End of chara" << std::endl;
}

long auCharacter::lerp(float a, float b, float f) {
  return a * (1.f - f) + (b * f);
}

// Computes sample points along a quadratic Bézier curve using De Casteljau’s
// method. For each parameter t (stepped by `interval`), it:
//  1) linearly interpolates (lerps) between `start` and `pivot`  -> point A
//  2) linearly interpolates (lerps) between `pivot` and `end`    -> point B
//  3) linearly interpolates (lerps) between A and B using the same t
// The result of step (3) is the actual point on the Bézier curve at that t.
// All computed points are stored in `lerpPoints` and returned.

std::vector<FT_Vector_> auCharacter::bezierPoints(float interval,
                                                  FT_Vector_ start,
                                                  FT_Vector_ end,
                                                  FT_Vector_ pivot) {

  std::vector<FT_Vector_> lerpPoints;

  for (float f = interval; f < 1; f += interval) {
    FT_Vector_ lerpPointA = {lerp(start.x, pivot.x, f),
                             lerp(start.y, pivot.y, f)};
    FT_Vector_ lerpPointB = {lerp(pivot.x, end.x, f), lerp(pivot.y, end.y, f)};

    FT_Vector_ lerpPointCurve = {lerp(lerpPointA.x, lerpPointB.x, f),
                                 lerp(lerpPointA.y, lerpPointB.y, f)};

    lerpPoints.push_back(lerpPointCurve);
  }
  return lerpPoints;
}
