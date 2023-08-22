#ifndef CURVE_H
#define CURVE_H

#include <vector>

#include "math/vec.h"
#include "core/shader.h"
#include "cursor.h"

class Curve {
public:
	Curve(Cursor& cursor,const std::vector<math::Vec3>& vertices = {});
	~Curve();
	void init();
	void addPoint(math::Vec3& p);
	void Render(core::Shader& shader);
private:
	std::vector<math::Vec3> mVertices;
	Cursor& mCursor;
	GLuint mVAO, mVBO;
};

#endif