#include "Texture.h"

Texture::Texture(const char *path) {
  glGenTextures(1, &texture);
  Bind();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  imageData = stbi_load(filePath, &width, &height, &nrChannels, 0);
  if (imageData) {

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

  } else {
    std::cout << "ERROR::TEXTURE::FAILED TO LOAD TEXTURE\n";
  }

  stbi_image_free(imageData);
}
void Texture::Bind() { glBindTexture(GL_TEXTURE_2D, texture); }
