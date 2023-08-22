#ifndef ARROW_H
#define ARROW_H

#include "core/mesh.h"
#include "core/gizmo.h"


namespace core::gizmos {

	class ArrowGizmo : public Gizmo {
	public:
		ArrowGizmo(float height = 1.0, float radius = 1.0);
		~ArrowGizmo();
	};

}

#endif