#ifndef GIZMO_H
#define GIZMO_H

#include <memory>

#include "core/transform.h"
#include "core/mesh.h"
#include "core/shader.h"

namespace core {

	class Gizmo {
	public:
		Gizmo(std::shared_ptr<Mesh> mesh,const Transform& localTransform = Transform{});
		virtual ~Gizmo();

		Transform getTransform() const;
		void setTransform(const Transform& transform);

		void Render(Shader& shader, const Transform& parentTransform = math::Mat4{});

		bool isSelected() const;
		void select();
		void deselect();

	protected:
		void addGizmo(std::shared_ptr<Gizmo> gizmo);


		std::shared_ptr<Mesh> mMesh;
		Transform mLocalTransform;
		std::vector<std::shared_ptr<Gizmo>> mChildGizmos;
		bool mSelected;
	};

}

#endif