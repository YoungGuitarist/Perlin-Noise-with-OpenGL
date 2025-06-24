//#include "glad/include/glad/glad.h"
//#include <GLFW/glfw3.h>
#include <cmath>
#include <fstream>
#include  "libs/glad/include/glad/glad.h"
#include  "libs/glfw-3.4/include/GLFW/glfw3.h"
#include <iostream>
#include <sstream>

std::string loadShader(const char *path) {
  std::ifstream file(path);
  std::stringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

GLuint compileShader(GLenum type, const char *src) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);
  return shader;
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Perlin Noise", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  gladLoadGL();

  float quad[] = {-1, -1, 0, 0, 0, 1,  -1, 0, 1, 0,
                  1,  1,  0, 1, 1, -1, 1,  0, 0, 1};
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  GLuint vao, vbo, ebo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  std::string vertCode =
      loadShader("shaders/vertex.glsl");
  std::string fragCode =
      loadShader("shaders/fragment.glsl");

  GLuint vert = compileShader(GL_VERTEX_SHADER, vertCode.c_str());
  GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragCode.c_str());

  GLuint shader = glCreateProgram();
  glAttachShader(shader, vert);
  glAttachShader(shader, frag);
  glLinkProgram(shader);
  glUseProgram(shader);

  GLint timeLoc = glGetUniformLocation(shader, "u_time");
  GLint resLoc = glGetUniformLocation(shader, "u_resolution");

  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
      break;

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glUniform2f(resLoc, (float)w, (float)h);

    float t = static_cast<float>(glfwGetTime());
    glUniform1f(timeLoc, t);

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
