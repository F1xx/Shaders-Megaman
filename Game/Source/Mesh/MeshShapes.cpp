#include "GamePCH.h"

#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"

void Mesh::CreateBox(vec2 size, vec2 offset)
{
    VertexFormat vertexAttributes[] =
    {
        VertexFormat( vec2( -size.x/2, -size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec2( 0.0f, 0.0f ) ),
        VertexFormat( vec2( -size.x/2,  size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec2( 0.0f, 1.0f ) ),
        VertexFormat( vec2(  size.x/2,  size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec2( 1.0f, 1.0f ) ),
        VertexFormat( vec2(  size.x/2, -size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec2( 1.0f, 0.0f ) ),
    };

    unsigned int indices[6] = { 0,2,1, 0,3,2 };

    Init( vertexAttributes, 4, indices, 6, GL_TRIANGLES, GL_STATIC_DRAW );
};

void Mesh::CreateCube(vec3 size, vec3 offset)
{
	VertexFormat vertexAttributes[] =
	{
		//HARDCODED UVs FOR FUN!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//front
		VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.1666f, 0.0f)),//3
		VertexFormat(vec3(size.x / 2,  size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.1666f, 1.0f)),//2
		VertexFormat(vec3(-size.x / 2,  size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.0f, 1.0f)),//1
		VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.0f, 0.0f)),//0
		//top
		VertexFormat(vec3(size.x / 2, size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.3333f, 0.0f)),//7
		VertexFormat(vec3(size.x / 2,  size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.3333f, 1.0f)),//6
		VertexFormat(vec3(-size.x / 2,  size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.1666f, 1.0f)),//5
		VertexFormat(vec3(-size.x / 2, size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.1666f, 0.0f)),//4
		//back
		VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.3333f, 0.0f)),//8
		VertexFormat(vec3(-size.x / 2,  size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.3333f, 1.0f)),//9
		VertexFormat(vec3(size.x / 2,  size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.5f, 1.0f)),//10
		VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.5f, 0.0f)),//11
		//bottom
		VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.5f, 0.0f)),//12
		VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.5f, 1.0f)),//13
		VertexFormat(vec3(size.x / 2,  -size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.6666f, 1.0f)),//14
		VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.6666f, 0.0f)),//15
		//left
		VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.8333f, 0.0f)),//19
		VertexFormat(vec3(-size.x / 2,  size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.8333f, 1.0f)),//18
		VertexFormat(vec3(-size.x / 2,  size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.6666f, 1.0f)),//17
		VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.6666f, 0.0f)),//16
		//right
		VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(1.0f, 0.0f)),//23
		VertexFormat(vec3(size.x / 2,  size.y / 2, -size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(1.0f, 1.0f)),//22
		VertexFormat(vec3(size.x / 2,  size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.8333f, 1.0f)),//21
		VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2) + offset, MyColor(255, 255, 255, 255), vec2(0.8333f, 0.0f)),//20
	};

	unsigned int indices[36] =
	{
		//front face
		0,1,2, 0,2,3,
		//top
		4,5,6, 4,6,7,
		//back
		8,9,10, 8,10,11,
		//bottom
		12,13,14, 12,14,15,
		//right
		16,17,18, 16,18,19,
		//left
		20,21,22, 20,22,23
	};

	Init(vertexAttributes, 24, indices, 36, GL_TRIANGLES, GL_STATIC_DRAW);
};

void Mesh::CreatePlane(vec2 worldsize, ivec2 vertcount)
{
	vec2 pivot = worldsize / 2.0f;

	int totalVertexCount = vertcount.x * vertcount.y;
	int totalIndexCount = (vertcount.x - 1) * (vertcount.y - 1) * 6;

	VertexFormat* vertexAttributes = new VertexFormat[totalVertexCount];
	unsigned int* indices = new unsigned int[totalIndexCount];

	float stepX = worldsize.x / (vertcount.x - 1);
	float stepY = worldsize.y / (vertcount.y - 1);

	float uvStepX = 5.0f / (vertcount.x - 1);
	float uvStepY = 5.0f / (vertcount.y - 1);

	for (int y = 0; y < vertcount.y; y++)
	{
		for (int x = 0; x < vertcount.x; x++)
		{
			vertexAttributes[y * vertcount.x + x].m_Pos = vec3(x * stepX - pivot.x, 0, y* stepY - pivot.y);
			vertexAttributes[y * vertcount.x + x].m_UV = vec2(x * uvStepX, y * uvStepY);
		}
	}

	// Setup indices.
	int iStepX = 1;
	int iStepY = vertcount.x;
	int indicesIndex = 0;

	for (int y = 0; y < vertcount.y - 1; y++)
	{
		for (int x = 0; x < vertcount.x - 1; x++)
		{
			int lowerLeftIndex = y * vertcount.x + x;
			//int indicesIndex = ( y * ( vertexCount.x - 1 ) + x ) * 6;

			indices[indicesIndex + 0] = lowerLeftIndex + 0;
			indices[indicesIndex + 1] = lowerLeftIndex + vertcount.x;
			indices[indicesIndex + 2] = lowerLeftIndex + vertcount.x + 1;
			indices[indicesIndex + 3] = lowerLeftIndex + 0;
			indices[indicesIndex + 4] = lowerLeftIndex + vertcount.x + 1;
			indices[indicesIndex + 5] = lowerLeftIndex + 1;

			indicesIndex += 6;
		}
	}

	glPolygonMode(GL_FRONT, GL_LINE);
	glPointSize(10);

	Init(vertexAttributes, totalVertexCount, indices, totalIndexCount, GL_TRIANGLES, GL_STATIC_DRAW);

	delete[] vertexAttributes;
	delete[] indices;
};

void Mesh::GenerateOBJ(const char* objfilename, float scale /* = 1.0f*/)
{
	long length = 0;
	char* buffer = LoadCompleteFile(objfilename, &length);

	if (buffer == 0 || length == 0) 
	{ 
		delete[] buffer; 
		return; 
	}  

	char* next_token = 0; 
	char* line = strtok_s(buffer, "\n", &next_token);

	std::vector<VertexFormat> vertexAttributes;
	std::vector<vec3> verts;
	std::vector<vec3> normals;
	std::vector<vec2> uvs;

	while (line) 
	{ 
		char str[5];
		float x;
		float y;
		float z;
		int faces[9];

		sscanf_s(line, "%s %f %f %f", str, 5, &x, &y, &z);

		std::string word = str;

		if (word == "v")
		{
			verts.push_back(vec3(x * scale, y * scale, z * scale));
		}
		else if (word == "vt")
		{
			uvs.push_back(vec2(x, y));
		}
		else if (word == "vn")
		{
			normals.push_back(vec3(x, y, z));
		}
		else if (word == "f")
		{
			sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faces[0], &faces[1], &faces[2], &faces[3], &faces[4], &faces[5], &faces[6], &faces[7], &faces[8]);
		

			MyColor color = MyColor(255, 255, 255, 255);

			vertexAttributes.push_back(VertexFormat(verts[faces[0] - 1], color, uvs[faces[1] - 1]));
			vertexAttributes.push_back(VertexFormat(verts[faces[3] - 1], color, uvs[faces[4] - 1]));
			vertexAttributes.push_back(VertexFormat(verts[faces[6] - 1], color, uvs[faces[7] - 1]));
		}


		line = strtok_s(0, "\n", &next_token);
	}

	Init(&vertexAttributes[0], vertexAttributes.size(), GL_TRIANGLES, GL_STATIC_DRAW);
	delete[] buffer;
}