#include "auFontRendering.h"
#include "liberation_sans.h"
#include <freetype/freetype.h>
#include <freetype/fttypes.h>

auFontRendering::auFontRendering(auVector2 position, int size, auColor color)
    : position(position), size(size), color(color),
      shaders("../src/ressources/default.vert",
              "../src//ressources/default.frag") {}

auFontRendering::~auFontRendering() { shaders.Delete(); }

int auFontRendering::auInitFreeType() { return !FT_Init_FreeType(&library); }

int auFontRendering::auLoadFace() {
  return FT_New_Memory_Face(library, LiberationMono_Regular_ttf,
                            LiberationMono_Regular_ttf_len, 0, &face);
}

int auFontRendering::auLoadFace(std::string path) {
  return FT_New_Face(library, path.c_str(), 0, &face);
}

int auFontRendering::getGlyph(FT_ULong charcode) {
  FT_UInt index = FT_Get_Char_Index(face, charcode);
  return FT_Load_Glyph(face, index, FT_LOAD_NO_BITMAP);
}

int auFontRendering::auSetText(std::string text) {
  auInitFreeType();
  auLoadFace();
  getGlyph(0);
  auCharacter chara;
  chara.setVerticies(face->glyph->outline.points, face->glyph->outline.n_points,
                     face->units_per_EM);
  sentence.push_back(chara);

  vao = new VAO();
  vao->Bind();

  for (int i = 0; i < chara.verticies.size(); i++) {
    if (i % 2 == 0) {
      chara.verticies[i] += 0.2;
    } else {
      chara.verticies[i] -= 0.2;
    }
  }

  vbo = new VBO(chara.verticies.data(), chara.verticies.size() * sizeof(float));
  vao->LinkVBO(*vbo, 0);

  GLuint indices[] = {0, 1, 2, 3, 4, 5, 6, 7};
  ebo = new EBO(indices, sizeof(indices));

  vao->Unbind();
  vbo->Unbind();
  ebo->Unbind();

  return 0;
}

int auFontRendering::auDraw() {
  shaders.Activate();
  vao->Bind();
  glDrawElements(GL_LINE_LOOP, 8, GL_UNSIGNED_INT, 0);
  return 0;
}
