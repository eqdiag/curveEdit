#ifndef ICO_SPHERE_H
#define ICO_SPHERE_H

#include "core/gizmo.h"

namespace core::gizmos {

	class IcoSphere: public Mesh{
	public:
		IcoSphere();
		~IcoSphere();
		
	private:
		std::vector<VertexData> generateVertices();
		std::vector<GLuint> generateIndices();
		static std::vector<VertexData> mVertices;
		static std::vector<GLuint> mIndices;
	};

	class IcoSphereGizmo : public Gizmo {
	public:
		IcoSphereGizmo(std::shared_ptr<IcoSphere> mesh = std::make_unique<IcoSphere>(),float size = 1.0);
		~IcoSphereGizmo();
	};

}

#endif 
