#ifndef CUBE_H
#define CUBE_H

#include "core/gizmo.h"
#include "core/mesh.h"

namespace core::gizmos {

	class Cube: public Mesh{
	public:
		Cube();
		~Cube();
	private:
		std::vector<VertexData> generateVertices();
		std::vector<GLuint> generateIndices();
		static std::vector<VertexData> mVertices;
		static std::vector<GLuint> mIndices;
	};

	class CubeGizmo : public Gizmo {
	public:
		CubeGizmo(const Transform& localTransform = Transform{}, std::shared_ptr<Cube> mesh = std::make_shared<Cube>());
		~CubeGizmo();
	};

}

#endif // !CUBE_H
