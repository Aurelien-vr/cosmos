#include <string>
#define GLFW_INCLUDE_NONE
#include "Shader.h"
#include "auFontRendering.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <glad/glad.h>
#include <iostream>
#include <vector>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main() {
  // GLFW INIT
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_FLOATING, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Cosmos", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  // NOTE: Remove VSync that cap fps to the max monitor refresh rate
  glfwSwapInterval(0);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);

  auFontRendering font = auFontRendering({0, 0}, 11, {1, 1, 1});
  font.auSetText("1234567dfghj");

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  double lastTime = glfwGetTime();
  int fps = 0;

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window)) {

    // fps conter
    double currentTime = glfwGetTime();
    fps++;
    if (currentTime - lastTime >= 1.f) {
      std::cout << "FPS: " << fps << std ::endl;
      font.auSetText(std::to_string(fps));
      fps = 0;
      lastTime = currentTime;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    font.shaders.Activate();

    font.auDraw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  font.shaders.Delete();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
