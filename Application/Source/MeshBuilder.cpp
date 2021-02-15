#include "MeshBuilder.h"
#include <GL\glew.h>
#include "Vertex.h"
#include <vector>
#include "LoadOBJ.h"
#define PI 3.14159265
#define Rad PI/180
/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	int index = 0;
	//const GLfloat vertex_buffer_data[] = {
		//almost the same as GenerateQuad or GenerateCube
	v.pos.Set(-100.0f, 0.f, 0.f); v.Color.Set(1, 0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(100.0f, 0.f, 0.f); v.Color.Set(1, 0, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, -100.0f, 0.f); v.Color.Set(0, 1, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 100.0f, 0.f); v.Color.Set(0, 1, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 0.f, -100.0f); v.Color.Set(0, 0, 1);vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 0.f, 100.0f); v.Color.Set(0, 0, 1);vertex_buffer_data.push_back(v);
//	};
	//const GLfloat color_buffer_data[] = {
	//	0
	//};
	//const GLuint index_buffer_data[] = {
	//	0
	//};
	for (int i = 0; i < 6; i++)
	{
	index_buffer_data.push_back(i);
	}
	Mesh *mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),
	//	color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_LINES;
	mesh->indexSize = 6;
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName,Color color, float lengthX, float lengthY )
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	v.Color = color;
	// top right
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.f);   v.normal.Set(0, 0, 1); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v); //v0
	// top left
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.f);  v.normal.Set(0, 0, 1); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v); //v1
	// bottom left
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.f); v.normal.Set(0, 0, 1); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v); //v2
	// bottom right
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.f);  v.normal.Set(0, 0, 1); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v); //v3

	//tri1
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	//tri2
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	int index = 0;
	//const GLfloat vertex_buffer_data[] = {
	// top face
	v.pos.Set(-1.0f * lengthX, -1.0f * lengthY, -1.0f * lengthZ);   vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, -1.0f * lengthY, 1.0f * lengthZ);   vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, 1.0f * lengthY, 1.0f * lengthZ);   vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, 1.0f * lengthY, -1.0f * lengthZ); 
		 vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, -1.0f * lengthY, -1.0f * lengthZ); 
		 vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, 1.0f * lengthY, -1.0f * lengthZ);  
		 vertex_buffer_data.push_back(v);
		//right face
		v.pos.Set(1.0f * lengthX, -1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.439216f, 0.858824f, 0.576471f);  vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, -1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.62352f, 0.372549f, 0.623529f); vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, -1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.647059f, 0.164706f, 0.164706f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, 1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.372549f, 0.623529f, 0.623529f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, -1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(1.0f, 0.498039f, 0.0f);  vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, -1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.258824f, 0.258824f, 0.435294f);  vertex_buffer_data.push_back(v);

		v.pos.Set(-1.0f * lengthX, -1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.184314f, 0.309804f, 0.184314f);  vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, 1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.309804f, 0.309804f, 0.184314f);  vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, 1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.6f, 0.196078f, 0.8f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, -1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.419608f, 0.137255f, 0.556863f);  vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, -1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.184314f, 0.309804f, 0.309804f);  vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, -1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.439216f, 0.576471f, 0.858824f);  vertex_buffer_data.push_back(v);

		v.pos.Set(-1.0f * lengthX, 1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.556863f, 0.137255f, 0.137255f);  vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, -1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.137255f, 0.556863f, 0.137255f); vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, -1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.8f, 0.498039f, 0.196078f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, 1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.858824f, 0.858824f, 0.439216f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, -1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.576471f, 0.858824f, 0.439216f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, 1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.309804f, 0.184314f, 0.184314f);  vertex_buffer_data.push_back(v);

		v.pos.Set(1.0f * lengthX, -1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.623529f, 0.623529f, 0.372549f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, 1.0f * lengthY,  1.0f * lengthZ); v.Color.Set(0.74902f, 0.847059f, 0.847059f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, -1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.560784f, 0.560784f, 0.737255f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, 1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.196078f, 0.8f, 0.196078f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, 1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.556863f, 0.137255f, 0.419608f);  vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, 1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.196078f, 0.8f, 0.6f);  vertex_buffer_data.push_back(v);


		v.pos.Set(1.0f * lengthX, 1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.196078f, 0.196078f, 0.8f); vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, 1.0f * lengthY, -1.0f * lengthZ); v.Color.Set(0.419608f, 0.556863f, 0.137255f);  vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, 1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.917647f, 0.917647f, 0.678431f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, 1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.576471f, 0.439216f, 0.858824f);  vertex_buffer_data.push_back(v);
		v.pos.Set(-1.0f * lengthX, 1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.258824f, 0.435294f, 0.258824f);  vertex_buffer_data.push_back(v);
		v.pos.Set(1.0f * lengthX, -1.0f * lengthY, 1.0f * lengthZ); v.Color.Set(0.498039f, 1.0f, 0.0f);  vertex_buffer_data.push_back(v);

	for (int i = 0; i < 36; i++)
	{
		index_buffer_data.push_back(i);
	}
	Mesh *mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),
	//	color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = 36;
	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color Color )
{
	Vertex v;
	v.Color = Color;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	for (int phi = -90; phi < 90; phi += 10) {
		for (int theta = 0; theta <= 360; theta += 10) {
			v.pos.Set(  cos(phi * Rad) * cos(theta * Rad),  sin(phi * Rad),  cos(phi * Rad) * sin(theta * Rad));
			
			v.normal.Set( cos(phi * Rad) * cos(theta * Rad),  sin(phi * Rad),  cos(phi * Rad) * sin(theta * Rad)); v.normal.Normalized(); 
			
			vertex_buffer_data.push_back(v);
			v.pos.Set( cos((phi + 10) * Rad) * cos(theta * Rad),  sin((phi + 10) * Rad), cos((phi + 10) * Rad) * sin(theta * Rad));
			
			v.normal.Set(cos((phi + 10) * Rad) * cos(theta * Rad), sin((phi + 10) * Rad), cos((phi + 10) * Rad) * sin(theta * Rad)); v.normal.Normalized();
			
			vertex_buffer_data.push_back(v);
			
			
		}
	}
	for (int i = 0; i < 1332; i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = 1332;
	return mesh;

}

Mesh* MeshBuilder::GenerateHemiSphere(const std::string& meshName, Color colorx)
{
	Vertex v;
	v.Color = colorx;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	for (int phi = -90; phi < 90; phi += 10) {
		for (int theta = 0; theta <= 360; theta += 10) {
			v.pos.Set(cos(phi * Rad) * cos(theta * Rad), sin(phi * Rad), cos(phi * Rad) * sin(theta * Rad));

			v.normal.Set(cos(phi * Rad) * cos(theta * Rad), sin(phi * Rad), cos(phi * Rad) * sin(theta * Rad)); v.normal.Normalized();

			vertex_buffer_data.push_back(v);
			v.pos.Set(cos((phi + 10) * Rad) * cos(theta * Rad), sin((phi + 10) * Rad), cos((phi + 10) * Rad) * sin(theta * Rad));

			v.normal.Set(cos((phi + 10) * Rad) * cos(theta * Rad), sin((phi + 10) * Rad), cos((phi + 10) * Rad) * sin(theta * Rad)); v.normal.Normalized();

			vertex_buffer_data.push_back(v);


		}
	}
	for (int i = 0; i < 1332/2; i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = 1332;
	return mesh;

}

Mesh* MeshBuilder::GenerateTorus(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR)
{
		Vertex v;
		v.Color = color;
		std::vector<Vertex> vertex_buffer_data;
		std::vector<unsigned>index_buffer_data;
		float degreePerStack = (360.f / numStack) * (PI / 180);
		float degreePerSlice = (360.f / numSlice) * (PI / 180);
		float x1, z1; //y1 is always zero
		float x2, y2, z2;
		for (unsigned stack = 0; stack < numStack + 1; stack++) {
			for (unsigned slice = 0; slice < numSlice + 1; slice++) {
				z1 = outerR * cos(stack * degreePerStack);
				x1 = outerR * sin(stack * degreePerStack);
				z2 = (outerR + innerR * cos(slice * degreePerSlice)) * cos(stack * degreePerStack);
				y2 = innerR * sin(slice * degreePerSlice);
				x2 = (outerR + innerR * cos(slice * degreePerSlice)) * sin(stack * degreePerStack);

				v.pos.Set(x2, y2, z2); v.normal.Set(x2, y2, z2); v.normal.Normalized();  vertex_buffer_data.push_back(v);
			}
		}
		for (unsigned stack = 0; stack < numStack; stack++) {
			for (unsigned slice = 0; slice < numSlice + 1; slice++) {
				index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
				index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
			}
		}

		Mesh* mesh = new Mesh(meshName);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
			&vertex_buffer_data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
			&index_buffer_data[0], GL_STATIC_DRAW);;
		mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
		mesh->indexSize = 5000;
		return mesh;

}
Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, Color color, float lengthX, float lengthY)
{
	Vertex v;
	v.Color = color;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	for (int theta = 0; theta <= 360; theta += 10)
	{
		v.pos.Set(1.0f * cos(theta * (PI / 180)), 0, 1.0f * sin(theta * (PI / 180)));  
		v.normal.Set(1.0f * cos(theta * (PI / 180)), 0, 1.0f * sin(theta * (PI / 180))); v.normal.Normalized();
		vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, 0);
		v.normal.Set(0, 1, 0); v.normal.Normalized();
		vertex_buffer_data.push_back(v);
	}
	for (int i = 0; i < 73; i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() *
		sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = 73;
	return mesh;
}

Mesh* MeshBuilder::GenerateHexagon(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR)
{
	Vertex v;
	v.Color = color;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	float degreePerStack = (360.f / numStack) * (PI / 180);
	float degreePerSlice = (360.f / numSlice) * (PI / 180);
	float x1, z1; //y1 is always zero
	float x2, y2, z2;
	for (unsigned stack = 0; stack < numStack + 1; stack++) {
		for (unsigned slice = 0; slice < numSlice + 1; slice++) {
			z1 = outerR * cos(stack * degreePerStack);
			x1 = outerR * sin(stack * degreePerStack);
			z2 = (outerR + innerR * cos(slice * degreePerSlice)) * cos(stack * degreePerStack);
			y2 = innerR * sin(slice * degreePerSlice);
			x2 = (outerR + innerR * cos(slice * degreePerSlice)) * sin(stack * degreePerStack);
			v.pos.Set(x2, y2, z2); v.normal.Set(x2, y2, z2); v.normal.Normalized(); vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStack; stack++) {
		for (unsigned slice = 0; slice < numSlice + 1; slice++) {
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = 5000;
	return mesh;
}
Mesh* MeshBuilder::GenerateCylinder(const std::string& meshName,Color colour, unsigned numStack, unsigned numSlice, float radius , float height)
{
	//Vertex v;
	//std::vector<Vertex> vertex_buffer_data;
	//std::vector<unsigned>index_buffer_data;
	////Code for drawing with triangle strip, with multiple stack
	//float stackHeight = height / numstack;
	//for (int stack = 0; stack < numstack; ++stack) //stack
	//{
	//	for (int theta = 0; theta <= 360; theta += 10) //slice
	//	{
	//		v.pos.Set(radius * cos(theta * (PI / 180)), -height / 2 + stack * stackHeight, radius * sin(theta * (PI / 180))); v.Color.Set(1.0f, 0.0f, 0.5f); vertex_buffer_data.push_back(v);
	//		v.pos.Set(radius * cos(theta * (PI / 180)), -height / 2 + (stack + 1) * stackHeight, radius * sin(theta * (PI / 180))); v.Color.Set(1.0f, 0.5f, 0.0f); vertex_buffer_data.push_back(v);
	//	}
	//}
	//for (int theta = 0; theta <= 360; theta += 10) //top
	//{
	//	v.pos.Set(radius * cos(theta * (PI / 180)), height / 2, radius * sin(theta * (PI / 180))); v.Color.Set(1.0f, 0.0f, 0.5f); vertex_buffer_data.push_back(v);
	//	v.pos.Set(0, height / 2, 0); v.Color.Set(1.0f, 0.5f, 0.0f); vertex_buffer_data.push_back(v);
	//}
	//for (int theta = 0; theta <= 360; theta += 10) //bottom
	//{
	//	v.pos.Set(0, -height / 2, 0); v.Color.Set(1.0f, 0.0f, 0.5f); vertex_buffer_data.push_back(v);
	//	v.pos.Set(radius * cos(theta * (PI / 180)), -height / 2, radius * sin(theta * (PI / 180))); v.Color.Set(1.0f, 0.5f, 0.0f); vertex_buffer_data.push_back(v);
	//}

	//for (int i = 0; i < 5000; i++) {
	//	index_buffer_data.push_back(i);
	//}
	//Mesh* mesh = new Mesh(meshName);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
	//	&vertex_buffer_data[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
	//	&index_buffer_data[0], GL_STATIC_DRAW);;
	//mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	//mesh->indexSize = 5000;
	//return mesh;

	Vertex v;
	v.Color = colour;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLint> index_buffer_data;
	float degreePerSlice = 360.0f / numSlice;
	// bottom circle
	v.pos.Set(0, -0.5 * height, 0);
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		float theta = slice * degreePerSlice;
		v.pos.Set( radius * cos(Math::DegreeToRadian(theta)), -0.5 * height,  radius * sin(Math::DegreeToRadian(theta)));
		
		v.normal.Set(0, -1, 0); // to fix
		vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back( 0);
		index_buffer_data.push_back(slice + 1);
	}
	//curved part
	unsigned CylinderStartIndex = vertex_buffer_data.size();
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		
		float theta = slice * degreePerSlice;
		//bottom
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), -0.5 * height, radius * sin(Math::DegreeToRadian(theta)));
		
		v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
		//top
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0.5 * height, radius * sin(Math::DegreeToRadian(theta)));
		
		v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
	}
	for (int slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(CylinderStartIndex + 2 * slice + 0);
		index_buffer_data.push_back(CylinderStartIndex + 2 * slice + 1);
	}
	//top circle
	unsigned CircleStartIndex = vertex_buffer_data.size();
	v.pos.Set(0, 0.5*height, 0);
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		float theta = slice * degreePerSlice;
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0.5 * height, radius * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(0, 1, 0); // to fix
		vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(CircleStartIndex + slice + 1);
		index_buffer_data.push_back(CircleStartIndex + 0);

	}

	

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateFrustrum(const std::string& meshName, Color colour, unsigned numStack, unsigned numSlice, float radius, float height)
{
	Vertex v;
	v.Color = colour;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLint> index_buffer_data;
	float degreePerSlice = 360.0f / numSlice;
	// bottom circle
	v.pos.Set(0, -0.5 * height, 0);
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		float theta = slice * degreePerSlice;
		v.pos.Set(2.5*radius * cos(Math::DegreeToRadian(theta)), -0.5 * height, 2.5*radius * sin(Math::DegreeToRadian(theta)));
		
		v.normal.Set(0, -1, 0); // to fix
		vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(0);
		index_buffer_data.push_back(slice + 1);
	}
	//curved part
	unsigned CylinderStartIndex = vertex_buffer_data.size();
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{

		float theta = slice * degreePerSlice;
		//bottom
		v.pos.Set(2.5*radius * cos(Math::DegreeToRadian(theta)), -0.5 * height, 2.5*radius * sin(Math::DegreeToRadian(theta)));
		
		v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
		//top
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0.5 * height, radius * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
	}
	for (int slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(CylinderStartIndex + 2 * slice + 0);
		index_buffer_data.push_back(CylinderStartIndex + 2 * slice + 1);
	}
	//top circle
	unsigned CircleStartIndex = vertex_buffer_data.size();
	v.pos.Set(0, 0.5 * height, 0);
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		float theta = slice * degreePerSlice;
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0.5 * height, radius * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(0, 1, 0); 
		vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(CircleStartIndex + slice + 1);
		index_buffer_data.push_back(CircleStartIndex + 0);

	}



	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
Mesh* MeshBuilder::GenerateCone(const std::string& meshName, Color colour,float radius, float height)
{
	Vertex v;
	v.Color = colour;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	//Code for drawing with triangle strip, with multiple stack
	for (int theta = 0; theta <= 360; theta += 10) //slice
	{
		v.pos.Set(radius * cos(theta * (PI / 180)), -height / 2, radius * sin(theta * (PI / 180)));
		v.normal.Set(radius * cos(theta * (PI / 180)), -height / 2, radius * sin(theta * (PI / 180)));
		v.normal.Normalized();
		vertex_buffer_data.push_back(v);
		v.pos.Set(0, height / 2, 0); v.normal.Set(0, height / 2, 0); v.normal.Normalized(); vertex_buffer_data.push_back(v);
	}
	for (int theta = 0; theta <= 360; theta += 10) //bottom
	{
		v.pos.Set(0, -height / 2, 0); v.normal.Set(0, -height / 2, 0); v.normal.Normalized(); vertex_buffer_data.push_back(v);
		v.pos.Set(radius * cos(theta * (PI / 180)), -height / 2, radius * sin(theta * (PI / 180))); v.normal.Set(radius * cos(theta * (PI / 180)), -height / 2, radius * sin(theta * (PI / 180))); v.normal.Normalized(); vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < 5000; i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = 5000;
	return mesh;

}

Mesh* MeshBuilder::GenerateOBJ(const std::string& meshName, const std::string
	& file_path) {
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	//Use triangle list and remember to set index size

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	
	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	

	

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	unsigned offset = 0;
	for (unsigned row = 0; row < numRow; ++row)
	{
		for (unsigned col = 0; col < numCol; ++col)
		{
			//Task: Add 4 vertices into vertex_buffer_data
			v.pos.Set(0.5f, 0.5f, 0.f);   v.normal.Set(1, 1, 1); v.texCoord.Set(width * (col+1), 1.f - (height * row)); vertex_buffer_data.push_back(v); //v0
			v.pos.Set(-0.5f, 0.5f, 0.f);  v.normal.Set(-1, 1, 1); v.texCoord.Set(width *(col), 1.f -(height * row)); vertex_buffer_data.push_back(v); //v1
			v.pos.Set(-0.5f, -0.5f, 0.f); v.normal.Set(-1,-1, 1); v.texCoord.Set(width * (col), 1.f - (height * (row+1))); vertex_buffer_data.push_back(v); //v2
			v.pos.Set(0.5f, -0.5f, 0.f);  v.normal.Set(1,-1, 1); v.texCoord.Set(width * (col+1) ,1.f -( height * (row + 1))); vertex_buffer_data.push_back(v); //v3

			 //bottom left
			 //bottom right
			 //top right
			 //top left

			


			//Task: Add 6 indices into index_buffer_data

			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);

			offset += 4;

		}
	}
	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
Mesh* MeshBuilder::GenerateOBJMTL(const std::string& meshName,const std::string& file_path, const std::string& mtl_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	std::vector<Material> materials;
	bool success = LoadOBJMTL(file_path.c_str(), mtl_path.c_str(),
		vertices, uvs, normals, materials);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data,
		vertex_buffer_data);
	Mesh* mesh = new Mesh(meshName);
	for (Material& material : materials)
		mesh->materials.push_back(material);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	return mesh;
}
