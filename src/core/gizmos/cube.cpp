#include <iostream>

#include "core/gizmos/cube.h"

std::vector<core::VertexData> core::gizmos::Cube::mVertices{
		VertexData{-0.5, -0.5, 0.5},
		VertexData{ 0.5,-0.5,0.5 },
		VertexData{ 0.5,0.5,0.5 },
		VertexData{ -0.5,0.5,0.5 },

		VertexData{ -0.5,-0.5,-0.5 },
		VertexData{ 0.5,-0.5,-0.5 },
		VertexData{ 0.5,0.5,-0.5 },
		VertexData{ -0.5,0.5,-0.5 },
};

std::vector<GLuint> core::gizmos::Cube::mIndices{
		//Front face
		0, 1, 3,
		3, 1, 2,

		//Right face
		1, 5, 2,
		2, 5, 6,

		//Left face
		4, 0, 7,
		7, 0, 3,

		//Back face
		5, 4, 6,
		6, 4, 7,

		//Top face
		3, 2, 6,
		3, 6, 7,

		//Bottom face
		0, 4, 5,
		0, 5, 1
};

core::gizmos::Cube::Cube():
	Mesh{generateVertices(),generateIndices(),true}
{

}

core::gizmos::Cube::~Cube()
{

}

std::vector<core::VertexData> core::gizmos::Cube::generateVertices()
{
	return mVertices;
}

std::vector<GLuint> core::gizmos::Cube::generateIndices()
{
	return mIndices;
}


core::gizmos::CubeGizmo::CubeGizmo(const Transform& localTransform,std::shared_ptr<Cube> cube) :
	Gizmo{ 
		cube,
		localTransform
	}
{
}

core::gizmos::CubeGizmo::~CubeGizmo()
{

}




