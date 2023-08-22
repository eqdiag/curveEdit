#include <iostream>

#include "core/gizmos/ico_sphere.h"

#define X .525731112119133606 
#define Z .850650808352039932

std::vector<core::VertexData> core::gizmos::IcoSphere::mVertices{
	VertexData{-X, 0.0, Z}, VertexData{ X, 0.0, Z }, VertexData{ -X, 0.0, -Z }, VertexData{ X, 0.0, -Z },
	VertexData{ 0.0, Z, X }, VertexData{ 0.0, Z, -X }, VertexData{ 0.0, -Z, X }, VertexData{ 0.0, -Z, -X },
		VertexData{ Z, X, 0.0 }, VertexData{ -Z, X, 0.0 }, VertexData{ Z, -X, 0.0 }, VertexData{ -Z, -X, 0.0 }
};

std::vector<GLuint> core::gizmos::IcoSphere::mIndices{
	0, 1, 4, 0,4,9 , 9,4,5,  4,8,5,  4,1,8,
	8,1,10 , 8,10,3, 5,8,3,  5,3,2,  2,3,7,
	7,3,10 , 7,10,6, 7,6,11, 11,6,0, 0,6,1,
	6,10,1 , 9,11,0, 9,2,11, 9,5,2,  7,11,2 
};




core::gizmos::IcoSphereGizmo::IcoSphereGizmo(std::shared_ptr<IcoSphere> mesh, float size):
	Gizmo{ mesh,Transform{math::Vec3(size)}}
{
}

core::gizmos::IcoSphereGizmo::~IcoSphereGizmo()
{
}


core::gizmos::IcoSphere::IcoSphere():
	Mesh{generateVertices(),generateIndices(),true}
{

}

core::gizmos::IcoSphere::~IcoSphere()
{
}

std::vector<core::VertexData> core::gizmos::IcoSphere::generateVertices()
{
	return mVertices;
}

std::vector<GLuint> core::gizmos::IcoSphere::generateIndices()
{
	return mIndices;
}
