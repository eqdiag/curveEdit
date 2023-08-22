#ifndef CYLINDER_H
#define CYLINDER_H

#include "core/mesh.h"
#include "core/gizmo.h"


namespace core::gizmos {

	class Cylinder : public Mesh{
	public:
		Cylinder(int numSideFaces = 20);
		~Cylinder();
	private:
		std::vector<VertexData> generateVertices(int numSideFaces);
		std::vector<GLuint> generateIndices(int numSideFaces);
	};

	class CylinderGizmo : public Gizmo {
	public:
		CylinderGizmo(float height = 1.0, float radius = 1.0, std::shared_ptr<Cylinder> mesh = std::make_shared<Cylinder>());
		~CylinderGizmo();
	};

}

#endif