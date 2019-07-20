#include "GamePCH.h"
#include "DebugDraw.h"
#include "../GameObjects/Camera.h"
#include "../Mesh/Mesh.h"
#include "../Mesh/Material.h"

DebugDraw::DebugDraw()
{
	m_pCamera = nullptr;
	m_pMaterial = nullptr;
}

DebugDraw::~DebugDraw()
{

}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	//set up vertex array
	GLfloat glverts[16]; //allow for polygons up to 8 vertices
	glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
	glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays

	//fill in vertex positions as directed by Box2D
	for (int i = 0; i < vertexCount; i++) {
		glverts[i * 2] = vertices[i].x;
		glverts[i * 2 + 1] = vertices[i].y;
	}

	//draw solid area
	glColor4f(color.r, color.g, color.b, 1);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

	//draw lines
	glLineWidth(3); //fat lines
	glColor4f(1, 0, 1, 1); //purple
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	GLuint shader = m_pMaterial->GetShader()->GetProgram();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLint loc = glGetAttribLocation(shader, "a_Position");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, &vertices[0].x);
		glEnableVertexAttribArray(loc);
	}

	glDisable(GL_DEPTH_TEST);

	mat4 matrix;
	matrix.SetIdentity();
	Mesh::SetupUniforms(matrix, m_pCamera, m_pMaterial);

	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
}

//this doesn't work
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	GLuint shader = m_pMaterial->GetShader()->GetProgram();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	int vertcount = 360;
	std::vector<VertexFormat> format;
	//Center Position
	format.push_back(VertexFormat(vec3(center.x, center.y, 0)));

	//The main body vertices
	float referenceAngle = 2 * PI / vertcount;
	float angle = 0;
	for (int x = 0; x < vertcount; x++)
	{
		float vertx = center.x + (radius * cosf(angle));
		float verty = center.y + (radius * sinf(angle));

		format.push_back(VertexFormat(vec3(vertx, verty, 0)));

		angle += referenceAngle;
	}

	//The last vertex which is in the same place as the first, non-center, vertex to complete the object
	format.push_back(format.at(1));

	//Add the 2 extra points so the buffer can know about them
	vertcount += 2;
	// Generate and fill buffer with our attributes.


	GLint loc = glGetAttribLocation(shader, "a_Position");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, &center.x);
		glEnableVertexAttribArray(loc);
	}

	glDisable(GL_DEPTH_TEST);

	mat4 matrix;
	matrix.SetIdentity();
	Mesh::SetupUniforms(matrix, m_pCamera, m_pMaterial);

	//glDrawArrays(GL_TRIANGLE_FAN, 0, vertcount);
	
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
}

void DebugDraw::SetCamera(Camera* cam)
{
	m_pCamera = cam;
}

void DebugDraw::SetMaterial(Material* mat)
{
	m_pMaterial = mat;
}
