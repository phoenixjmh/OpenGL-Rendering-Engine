#pragma once
// #include <GLFW/glfw3.h>
#include "glad/glad.h"
#include <iostream>
#include "vendor/stb_image/stb_image.h"
class Texture {
public:
  Texture(const char *path);
  ~Texture();
  void Bind();

private:
  const char *filePath;
  int width, height, nrChannels;
  unsigned int m_RendererID;
  unsigned int texture;
  unsigned char *imageData;
};
