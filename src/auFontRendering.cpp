#include "auFontRendering.h"
#include "Shader.h"
#include "VBO.h"
#include "liberation_sans.h"
#include <freetype/freetype.h>
#include <freetype/fttypes.h>
#include <numeric>
#include <vector>

auFontRendering::auFontRendering(auVector2 position, int size, auColor color)
    : position(position), size(size), color(color),
      shaders("../src/ressources/default.vert",
              "../src//ressources/default.frag") {
  auInitFreeType();
  auLoadFace();
}

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

  sentence.clear();
  glyph.clear();
  list_contours.clear();

  short indicies_vector_total_size = 0;

  float space_next_word = 0;

  for (char &letter : text) {
    auCharacter chara;
    getGlyph(letter);

    chara.setVerticies(face, size, position, space_next_word);
    space_next_word += chara.offset_letter;

    for (float vertex : chara.verticies)
      sentence.push_back(vertex);

    int actual_points = chara.verticies.size() / 2;

    indicies_vector_total_size += actual_points;
    glyph.push_back(actual_points);

    std::vector<short> contours;
    for (short index = 0; index < face->glyph->outline.n_contours; index++)
      contours.push_back(face->glyph->outline.contours[index]);

    list_contours.push_back(contours);
  }

  if (vao != NULL) {
    delete vao;
    vao = nullptr;
  }

  if (vbo != NULL) {
    delete vbo;
    vbo = nullptr;
  }

  if (ebo != NULL) {
    delete ebo;
    ebo = nullptr;
  }

  vao = new VAO();
  vao->Bind();

  vbo = new VBO(sentence.data(), sentence.size() * sizeof(float));

  vao->LinkVBO(*vbo, 0);
  std::vector<GLuint> indices(indicies_vector_total_size);
  std::iota(indices.begin(), indices.end(), 0);

  ebo = new EBO(indices);

  vao->Unbind();
  vbo->Unbind();
  ebo->Unbind();

  return 0;
}

int auFontRendering::auDraw() {
  vao->Bind();

  long offset = 0;

  for (unsigned long glyhe_index = 0; glyhe_index < glyph.size();
       glyhe_index++) {

    int nb_points = glyph[glyhe_index]; // Use int
    unsigned int cpt_nb_contours = 0;
    int start = 0;

    for (int i = 0; i < nb_points; i++) {
      if (cpt_nb_contours >= list_contours[glyhe_index].size()) {
        break;
      }

      if (i == list_contours[glyhe_index][cpt_nb_contours]) {
        GLsizei count = i - start + 1;

        unsigned long long byteOffset = (offset + start) * sizeof(GLuint);

        glDrawElements(GL_LINE_LOOP, count, GL_UNSIGNED_INT,
                       (void *)byteOffset);

        start = i + 1;
        cpt_nb_contours++;
      }
    }
    offset += nb_points;
  }

  return 0;
}
