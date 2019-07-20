#ifndef __Mesh_H__
#define __Mesh_H__

class Texture;
class Camera;
class Material;

struct VertexFormat
{
    vec3 m_Pos;
    MyColor m_Color;
    vec2 m_UV;
	VertexFormat() {}
    VertexFormat(vec3 pos, MyColor color, vec2 uv)
    {
        m_Pos = pos;
        m_Color = color;
        m_UV = uv;
    }

	VertexFormat(vec3 pos, vec2 uv)
	{
		m_Pos = pos;
		m_Color = MyColor(255,0,0,255);
		m_UV = uv;
	}

	VertexFormat(vec3 pos)
	{
		m_Pos = pos;
		m_Color = MyColor(255, 0, 0, 255);
		m_UV = vec2(0,0);
	}
};

class Mesh
{
protected:
    GLuint m_VBO;
    GLuint m_IBO;

    unsigned int m_NumVerts;
    unsigned int m_NumIndices;

    GLenum m_PrimitiveType;

public:
    Mesh();
    virtual ~Mesh();

    void Init(VertexFormat* verts, int numVerts, unsigned int* indices, int numIndices, GLenum primitiveType, GLenum usage);
    void Init(const void* verts, int numVerts, GLenum primitiveType, GLenum usage);

    void SetupAttributes(ShaderProgram* pShaderProgram);
    static void SetupUniforms(mat4 matrix, Camera* camera, Material* material);
    void Draw(ShaderProgram* pShaderProgram);

    // The following functions are defined in MeshShapes.cpp:
    void CreateBox(vec2 size, vec2 offset);
	void CreateCube(vec3 size, vec3 offset);
	void CreatePlane(vec2 worldsize, ivec2 vertcount);
	void GenerateOBJ(const char* objfilename, float scale = 1.0f);
};

#endif //__Mesh_H__
