#include "Texture.h"
void Texture::Bind(){
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    unsigned char * data = stbi_load(filePath,&width,&height,&nrChannels,0);

}
