#include "auFontRendering.h"
#include "../lib/freetype2/freetype/freetype.h"
#include "../lib/freetype2/freetype/fttypes.h"
#include "Shader.h"
#include "VBO.h"
#include "liberation_sans.h"
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

// NOTE: Is caleld at each frame -> methode to keep the char in memory if they
// does not change
int auFontRendering::auSetText(std::string text) {

  // Needed because this function is used mutiple time in the life of the class
  sentence.clear();
  listCharacters.clear();

  short indicies_vector_total_size = 0;

  float space_next_word = 0;

  for (char &letter : text) {
    auCharacter chara;
    getGlyph(letter);

    chara.setVerticies(face, size, position, space_next_word);
    chara.setOutlineEnd(face);

    space_next_word += chara.offset_letter;

    for (auVector2 point : chara.verticies) {
      sentence.push_back(point.x);
      sentence.push_back(point.y);
    }

    listCharacters.push_back(chara);
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

  // WARNING: Put the verticies on the GPU, done each frame and not opti

  vao = new VAO();
  vao->Bind();

  vbo = new VBO(sentence.data(), sentence.size() * sizeof(float));
  vao->LinkVBO(*vbo, 0);

  int total_vertices = sentence.size() / 2;
  std::vector<GLuint> indices(total_vertices);
  std::iota(indices.begin(), indices.end(), 0);

  ebo = new EBO(indices);

  vao->Unbind();
  vbo->Unbind();
  ebo->Unbind();

  return 0;
}

int auFontRendering::auDraw() {
  vao->Bind();
  int offset = 0;

  for (const auCharacter &character : listCharacters) {
    glDrawArrays(GL_POINTS, offset, character.verticies.size());
    offset += character.verticies.size();
  }

  return 0;
}
