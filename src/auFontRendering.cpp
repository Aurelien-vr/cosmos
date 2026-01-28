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

// NOTE: Is caleld at each frame -> methode to keep the char in memory if they
// does not change
int auFontRendering::auSetText(std::string text) {

  // Needed because this function is used mutiple time in the life of the class
  sentence.clear();
  nb_points_character.clear();
  list_contours.clear();

  short indicies_vector_total_size = 0;

  float space_next_word = 0;

  for (char &letter : text) {
    auCharacter chara;
    // NOTE: The function get glyph take the glyp from the file each time the
    // function is called. Maybe change this for opti
    getGlyph(letter);

    // NOTE: The verticies are store and calculate on setVerticies then store in
    // an array then store on another array somme work seems to be done 2 times.
    // Maybe auCharacter is useless

    // Get the points of the different caracter and set them on the right place
    // Fill the list chara.verticies with the position in space of the different
    // verticies.
    // THIS IS FOR ONE LETTER
    chara.setVerticies(face, size, position, space_next_word);

    // Set the offsdet for the next occurence of setVerticies
    space_next_word += chara.offset_letter;

    // NOTE: Faster way?
    for (float vertex : chara.verticies)
      // Sentence is the data feed to the vbo
      sentence.push_back(vertex);

    // Because one point is 2 coordinates X and Y
    int actual_points = chara.verticies.size() / 2;

    indicies_vector_total_size += actual_points;

    nb_points_character.push_back(actual_points);

    std::vector<short> contours;

    // NOTE: Weird to do this in the auFontRendering and do the setVerticies in
    // auCharacter
    for (short index = 0; index < face->glyph->outline.n_contours; index++) {
      contours.push_back(face->glyph->outline.contours[index]);

      // unsigned char *tags = face->glyph->outline.tags;
      // for (int i = 0; i < face->glyph->outline.n_points; i++) {
      //   unsigned char tag = tags[i];
      //   std::cout << "Point: " << i << ":"
      //             << "(" << face->glyph->outline.points[i].x << ", "
      //             << face->glyph->outline.points[i].y << ") "
      //             << "Tag=" << static_cast<int>(tag) << " -> ";
      //
      //   if (tag & FT_CURVE_TAG_ON) { // bit 0
      //     std::cout << "ON";
      //   } else {
      //     std::cout << "OFF (";
      //     if (tag & FT_CURVE_TAG_CUBIC) { // bit 1
      //       std::cout << "cubic";
      //     } else {
      //       std::cout << "quadratic";
      //       if (tag & FT_CURVE_TAG_CONIC) {
      //         std::cout << "\n conic";
      //       }
      //     }
      //     std::cout << ")";
      //   }
      //
      //   std::cout << std::endl;
      // }
    }

    list_contours.push_back(contours);
  }

  // Reste VAO, VBO et EBO
  // Useful if they where used on the previous frame

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

  for (unsigned long glyhe_index = 0; glyhe_index < nb_points_character.size();
       glyhe_index++) {

    int nb_points = nb_points_character[glyhe_index]; // Use int
    std::cout << nb_points << std::endl;
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
