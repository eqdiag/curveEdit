#ifndef CURSOR_H
#define CURSOR_H

#include "core/shader.h"
#include "core/camera.h"
#include "math/vec.h"

const static float cursorData[] =
{
	-0.25,-0.25,0.0,
	0.25,-0.25,0.0,
	-0.25,0.25,0.0,

	-0.25,0.25,0.0,
	0.25,-0.25,0.0,
	0.25,0.25,0.0
};

class Cursor {
public:
	Cursor();
	~Cursor();
	void init();
	math::Vec3 getPosition() const;
	void clampPosition();
	void computePosition(float x, float y, int screenWidth, int screenHeight, const core::Camera& camera);
	void Render();
private:
	GLuint mVAO, mVBO;
	math::Vec3 mPosition;
};


#endif