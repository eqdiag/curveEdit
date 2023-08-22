#ifndef CONE_H
#define CONE_H

#include "core/gizmo.h"
#include "core/mesh.h"

namespace core::gizmos {


	class Cone : public Mesh {
	public:
		Cone(int numSideFaces = 20);
		~Cone();
	private:
		std::vector<VertexData> generateVertices(int numSideFaces);
		std::vector<GLuint> generateIndices(int numSideFaces);
	};

	class ConeGizmo : public Gizmo {
	public:
		ConeGizmo(float height = 1.0, float radius = 1.0, std::shared_ptr<Cone> mesh = std::make_shared<Cone>());
		~ConeGizmo();
	};
}

#endif