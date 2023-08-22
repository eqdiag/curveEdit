#include <iostream>
#include <cmath>

#include "core/gizmos/cylinder.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef TPI
#define TPI 2.0*M_PI
#endif



core::gizmos::Cylinder::Cylinder(int numSideFaces):
	Mesh{generateVertices(numSideFaces),generateIndices(numSideFaces),true}
{

}

core::gizmos::Cylinder::~Cylinder()
{
}

std::vector<core::VertexData> core::gizmos::Cylinder::generateVertices(int numSideFaces)
{
	std::vector<VertexData> vertices{};
	
	//Add vertices on top outer rim
	for (int i = 0; i < numSideFaces; i++) {
		float dx = (float(i) / numSideFaces) * TPI;
		vertices.push_back(
			VertexData{
				cos(dx),
				0.5,
				sin(dx)
			}
		);
	}

	//Add vertices on bottom outer rim
	for (int i = 0; i < numSideFaces; i++) {
		float dx = (float(i) / numSideFaces) * TPI;
		vertices.push_back(
			VertexData{
				cos(dx),
				-0.5,
				sin(dx)
			}
		);
	}

	//Add middle top and bottom vertices
	vertices.push_back(VertexData{ 0.0,0.5,0.0 });
	vertices.push_back(VertexData{ 0.0,-0.5,0.0 });


	return vertices;
}

std::vector<GLuint> core::gizmos::Cylinder::generateIndices(int numSideFaces)
{
	std::vector<GLuint> indices{};
	int topStartIdx = 0;
	int botStartIdx = numSideFaces;
	int midTopIdx = 2 * numSideFaces;
	int midBotIdx = midTopIdx + 1;

	//Add top faces
	for (int i = 0; i < numSideFaces; i++) {
		indices.push_back((i + 1) % numSideFaces);
		indices.push_back(i);
		indices.push_back(midTopIdx);
	}

	//Add bot faces
	for (int i = 0; i < numSideFaces; i++) {
		indices.push_back(midBotIdx);
		indices.push_back(i + botStartIdx);
		indices.push_back(((i+1) % numSideFaces) + botStartIdx);
	}

	//Add side faces
	for (int i = 0; i < numSideFaces; i++) {
		//First triangle
		indices.push_back(i + botStartIdx);
		indices.push_back(i);
		indices.push_back((i + 1) % numSideFaces);

		//Second triangle
		indices.push_back(((i + 1) % numSideFaces) + botStartIdx);
		indices.push_back(i + botStartIdx);
		indices.push_back((i + 1) % numSideFaces);
	}


	return indices;
}

core::gizmos::CylinderGizmo::CylinderGizmo(float height, float radius, std::shared_ptr<Cylinder> mesh):
	Gizmo {mesh, Transform{math::Vec3(radius,height * 0.5,radius)}}
{
}

core::gizmos::CylinderGizmo::~CylinderGizmo()
{
}
