#ifndef __GLHelpers_H__
#define __GLHelpers_H__

void CheckForGLErrors();

GLuint LoadTexture(const char* filename);
GLuint LoadTextureCubemap(const char** filenames, GLuint oldTextureHandle = 0);
void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height);

#endif //__GLHelpers_H__
