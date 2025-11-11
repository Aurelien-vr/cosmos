#include <cstdlib>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

int main() {
  if (!glfwInit()) {
    exit(1);
  }
  glfwTerminate();
}
