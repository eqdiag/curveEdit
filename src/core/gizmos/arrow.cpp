#include "core/gizmos/cone.h"
#include "core/gizmos/cylinder.h"
#include "core/gizmos/arrow.h"

core::gizmos::ArrowGizmo::ArrowGizmo(float height, float radius):
	Gizmo{ nullptr,Transform{} }
{
	addGizmo(std::make_shared<core::gizmos::CylinderGizmo>(height,radius*0.5));
	
	auto cone = std::make_shared<core::gizmos::ConeGizmo>();
	cone->setTransform(Transform::buildTranslation(math::Vec3(0.0,height*0.25,0.0)) * Transform { math::Vec3(radius, height * 0.01, radius) });
	addGizmo(cone);
}

core::gizmos::ArrowGizmo::~ArrowGizmo()
{
}
