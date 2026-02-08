#pragma once
#include <fstream>
#include "../lib/glad.h"
#include <iostream>
#include <sstream>
#include <string>

std::string readShaderFile(const std::string &filePath);

class Shader {
public:
  unsigned int ID;

  Shader(std::string vertPath, std::string fracPath);
  void Activate();
  void Delete();
};
