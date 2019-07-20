#ifndef __Texture_H__
#define __Texture_H__

class Texture
{
protected:
    GLuint m_TextureID;

public:
    Texture(const char* filename);
    virtual ~Texture();

    GLuint GetTextureID() { return m_TextureID; }
};

#endif //__Texture_H__
