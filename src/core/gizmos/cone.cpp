#include <iostream>
#include <cmath>


#include "core/gizmo.h"
#include "core/gizmos/cone.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef TPI
#define TPI 2.0*M_PI
#endif



core::gizmos::Cone::Cone(int numSideFaces):
	Mesh{generateVertices(numSideFaces),generateIndices(numSideFaces),true}
{
}

core::gizmos::Cone::~Cone()
{

}

std::vector<core::VertexData> core::gizmos::Cone::generateVertices(int numSideFaces)
{
	std::vector<VertexData> vertices{};


	//Add vertices on rim
	for (int i = 0; i < numSideFaces; i++) {
		float dx = (float(i) / numSideFaces) * TPI;
		vertices.push_back(
			VertexData{
				cos(dx),
				0.0,
				sin(dx)
			}
		);
	}


	//Add top vertex
	vertices.push_back(VertexData{ 0.0,1.0,0.0 });
	vertices.push_back(VertexData{ 0.0,0.0,0.0 });


	return vertices;
}

std::vector<GLuint> core::gizmos::Cone::generateIndices(int numSideFaces)
{
	std::vector<GLuint> indices{};
	int midTopIdx = numSideFaces;
	int midBotIdx = numSideFaces + 1;

	//Add side faces
	for (int i = 0; i < numSideFaces; i++) {
		indices.push_back((i + 1) % numSideFaces);
		indices.push_back(i);
		indices.push_back(midTopIdx);
	}

	//Add bot faces
	for (int i = 0; i < numSideFaces; i++) {
		indices.push_back(midBotIdx);
		indices.push_back(i);
		indices.push_back((i + 1) % numSideFaces);
	}


	return indices;
}

core::gizmos::ConeGizmo::ConeGizmo(float height, float radius, std::shared_ptr<Cone> mesh):
	Gizmo{ mesh, Transform{math::Vec3(radius,height * 0.5,radius)} }
{
}

core::gizmos::ConeGizmo::~ConeGizmo()
{
}
