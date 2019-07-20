#include "GamePCH.h"

#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "Material.h"
#include "../GameObjects/Camera.h"

Mesh::Mesh()
{
    m_VBO = 0;
    m_IBO = 0;
	glPointSize(10.0f);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

    m_NumVerts = 0;
    m_NumIndices = 0;

    m_PrimitiveType = -1;
}

Mesh::~Mesh()
{
    glDeleteBuffers( 1, &m_VBO );
    glDeleteBuffers( 1, &m_IBO );
}

void Mesh::Init(VertexFormat* verts, int numVerts, unsigned int* indices, int numIndices, GLenum primitiveType, GLenum usage)
{
    m_NumVerts = numVerts;
    m_NumIndices = numIndices;
    m_PrimitiveType = primitiveType;

    // Generate and fill buffer with our vertex attributes.
    if( m_VBO == 0 )
        glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*numVerts, verts, usage );

    // Generate and fill buffer with our indices.
    if( m_IBO == 0 )
        glGenBuffers( 1, &m_IBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numIndices, indices, usage );

    CheckForGLErrors();
}

void Mesh::Init(const void* verts, int numVerts, GLenum primitiveType, GLenum usage)
{
    m_NumVerts = numVerts;
    m_NumIndices = 0;
    m_PrimitiveType = primitiveType;

    // Generate and fill buffer with our vertex attributes.
    if( m_VBO == 0 )
        glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat) * numVerts, verts, usage );

    CheckForGLErrors();
}

void SetUniform1f(GLuint shader, const char* uniformName, float value)
{
	GLint loc = glGetUniformLocation(shader, uniformName);
	if (loc != -1)
	{
		glUniform1f(loc, value);
	}
}

void SetUniform2f(GLuint shader, const char* uniformName, vec2 value)
{
	GLint loc = glGetUniformLocation(shader, uniformName);
	if (loc != -1)
	{
		glUniform2f(loc, value.x, value.y);
	}
}

void SetUniform3f(GLuint shader, const char* uniformName, vec3 value)
{
	GLint loc = glGetUniformLocation(shader, uniformName);
	if (loc != -1)
	{
		glUniform3f(loc, value.x, value.y, value.z);
	}
}

void SetUniform4f(GLuint shader, const char* uniformName, vec4 value)
{
	GLint loc = glGetUniformLocation(shader, uniformName);
	if (loc != -1)
	{
		glUniform4f(loc, value.x, value.y, value.z, value.w);
	}
}

void SetUniformMat4(GLuint shader, const char* uniformName, const float *m11)
{
	GLint loc = glGetUniformLocation(shader, uniformName);
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, false, m11);
	}
}

void Mesh::SetupAttributes(ShaderProgram* pShader)
{
    assert( m_VBO != 0 );
    assert( pShader != nullptr );
    assert( pShader->GetProgram() != 0 );
    CheckForGLErrors();

    GLuint shader = pShader->GetProgram();

    // Bind buffer and set up attributes.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

    GLint loc = glGetAttribLocation( shader, "a_Position" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Pos) );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation( shader, "a_Color" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Color) );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation( shader, "a_UV" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_UV) );
        glEnableVertexAttribArray( loc );
    }
}

void Mesh::SetupUniforms(mat4 matrix, Camera* camera, Material* material)
{
    assert(material->GetShader() != nullptr );
    assert(material->GetShader()->GetProgram() != 0 );
    CheckForGLErrors();

    GLuint shader = material->GetShader()->GetProgram();

    // Set up shader.
    glUseProgram( shader );

    // Set up uniforms.
	SetUniform1f(shader, "u_Time", (float)GetSystemTimeSinceGameStart());

	float ranges[4] = { 0.9f, 1.3f, 0.6f, 1.0f };
	vec3 origins[4] = { vec3(-4.0f, 0.0f, -2.0f) , vec3(-1.0f, 0.0f, 0.0f) , vec3(2.0f, 0.0f, 2.0f) , vec3(4.0f, 0.0f, 4.0f) };

	GLint loc = glGetUniformLocation(shader, "u_RippleRange");
	if (loc != -1)
	{
		glUniform1fv(loc, 4, &ranges[0]);
	}

	loc = glGetUniformLocation(shader, "u_RippleOrigin");
	if (loc != -1)
	{
		glUniform3fv(loc, 4, &origins[0].x);
	}

	mat4 view = camera->GetViewMatrix();
	mat4 proj = camera->GetProjectionMatrix();

	SetUniformMat4(shader, "u_WorldMatrix", &matrix.m11);
	SetUniformMat4(shader, "u_ViewMatrix", &view.m11);
	SetUniformMat4(shader, "u_ProjectionMatrix", &proj.m11);
	
	Texture* pTexture = material->GetTexture();

    // Setup our texture.
    if(pTexture != nullptr )
    {
        int textureUnitIndex = 0;
        glActiveTexture( GL_TEXTURE0 + textureUnitIndex );
        glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );
        GLint loc = glGetUniformLocation( shader, "u_TextureSampler" );
        if( loc != -1 )
        {
            glUniform1i( loc, textureUnitIndex );
        }
    }
    CheckForGLErrors();
}

void Mesh::Draw(ShaderProgram* pShader)
{
    assert( m_PrimitiveType != -1 );
    assert( m_NumVerts != 0 );
    assert( pShader != nullptr );
    assert( pShader->GetProgram() != 0 );
    CheckForGLErrors();

    // Draw.
    if( m_NumIndices > 0 )
    {
        glDrawElements( m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, 0 );
    }
    else
    {
        glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
    }

    // Disable the attribute arrays used.
    {
        GLuint shader = pShader->GetProgram();

        GLint aPos = glGetAttribLocation( shader, "a_Position" );
        GLint aColor = glGetAttribLocation( shader, "a_Color" );
        GLint aUV = glGetAttribLocation( shader, "a_UV" );

        glDisableVertexAttribArray( aPos );

        if( aColor != -1 )
            glDisableVertexAttribArray( aColor );

        if( aUV != -1 )
            glDisableVertexAttribArray( aUV );
    }
    CheckForGLErrors();
}
