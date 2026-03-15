#pragma once
#include "../lib/freetype2/freetype/fttypes.h"
#include "DrawElementsIndirectCommand.h"
#include "Shader.h"
#include "auCharacter.h"
#include <ft2build.h>
#include <string>
#include <vector>

#include "EBO.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include FT_FREETYPE_H

#include "../lib/GLFW/glfw3.h"
#include "DIB.h"
#include "auColor.h"
#include "auVector2.h"

class auFontRendering {
public:
  auVector2 position;
  int size;
  auColor color;

  int screenHeight, screenWidth;

  VAO *vao = nullptr;
  VBO *vbo = nullptr;
  EBO *ebo = nullptr;
  DIB *dib = nullptr;

  GLFWwindow *window;
  Shader shaders;

  // All the verticies of all the glyph to draw
  // Needed to send all the data at once to the VBO
  std::vector<float> sentence;

  // Liste of the characters containing the data for the drawing as a list of
  // object auCharacters
  std::vector<auCharacter> listCharacters;
  std::vector<DrawElementsIndirectCommand> cmdBuffer;

  auFontRendering(GLFWwindow *window, auVector2 position, int size,
                  auColor color);
  ~auFontRendering();

  void loadFont();
  int auSetText(std::string text);
  int setFont(std::string path);
  int auDraw();

private:
  FT_Library library;
  FT_Face face;

  int auInitFreeType();
  int auLoadFace();
  int auLoadFace(std::string path);
  int getGlyph(FT_ULong charcode);
  void clearBuffer();
  void onResize();
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
};

// Are the parameter adressed by indirect in the funtion
// glMultiDrawElementsIndirect
