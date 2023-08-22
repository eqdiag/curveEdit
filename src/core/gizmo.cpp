#include <iostream>

#include "core/gizmo.h"


core::Gizmo::Gizmo(std::shared_ptr<Mesh> mesh,const Transform& localTransform):
	mMesh{ mesh },mLocalTransform{ localTransform },mSelected{false}
{

}

core::Gizmo::~Gizmo()
{

}

core::Transform core::Gizmo::getTransform() const
{
	return mLocalTransform;
}

void core::Gizmo::setTransform(const Transform& transform)
{
	mLocalTransform = transform;
}


void core::Gizmo::addGizmo(std::shared_ptr<Gizmo> gizmo)
{
	mChildGizmos.emplace_back(gizmo);
}

void core::Gizmo::Render(Shader& shader,const Transform& parentTransform)
{
	//Update model transform for this gizmo
	Transform totalTransform{ parentTransform * mLocalTransform };
	//Transform totalTransform{ localTransform };
	math::Mat4 transformMat{totalTransform.getMatrix()};
	shader.setUniformMat4("model", transformMat.getRawData());

	//First render this gizmo's mesh
	if(mMesh != nullptr) mMesh->Render();

	//Then render all children gizmos
	for (auto& gizmo : mChildGizmos) {
		gizmo->Render(shader,totalTransform);
	}
}

bool core::Gizmo::isSelected() const
{
	return mSelected;
}

void core::Gizmo::select()
{
	mSelected = true;
}

void core::Gizmo::deselect()
{
	mSelected = false;
}
