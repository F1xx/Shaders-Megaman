#ifndef __ShaderBase_H__
#define __ShaderBase_H__

class ShaderProgram
{
protected:
    char* m_VertShaderString;
    char* m_FragShaderString;

    GLuint m_VertShader;
    GLuint m_FragShader;
    GLuint m_Program;

public:
    ShaderProgram();
    ShaderProgram(const char* vertFilename, const char* fragFilename);
    virtual ~ShaderProgram();

    void Cleanup();

    void CompileShader(GLuint& shaderHandle, const char* shaderString);
    bool Init(const char* vertFilename, const char* fragFilename);
    bool Reload();

    GLuint GetProgram() { return m_Program; }
};

#endif //__ShaderBase_H__
