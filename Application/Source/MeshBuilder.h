#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName,Color color, float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateSphere(const std::string& meshName, Color colorx);
	static Mesh* GenerateHemiSphere(const std::string& meshName, Color colorx);
	static Mesh* GenerateTorus(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR);
	static Mesh* GenerateCircle(const std::string& meshName, Color color, float lengthX, float lengthY);
	static Mesh* GenerateHexagon(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR);
	static Mesh* GenerateCylinder(const std::string& meshName,Color colour, unsigned numStack, unsigned numSlice, float radius, float height);
	static Mesh* GenerateFrustrum(const std::string& meshName, Color colour, unsigned numStack, unsigned numSlice, float radius, float height);
	static Mesh* GenerateCone(const std::string& meshName, Color colour, float radius, float height);
	static Mesh* GenerateOBJ(const std::string& meshName, const std::string& file_path);
	static Mesh* GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol);
	static Mesh* GenerateOBJMTL(const std::string& meshName,const std::string& file_path, const std::string& mtl_path);
};

#endif