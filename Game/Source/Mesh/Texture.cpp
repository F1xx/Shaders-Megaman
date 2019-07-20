#include "GamePCH.h"

#include "Mesh/Texture.h"

Texture::Texture(const char* filename)
{
    m_TextureID = LoadTexture( filename );
}

Texture::~Texture()
{
    glDeleteTextures( 1, &m_TextureID );
}
