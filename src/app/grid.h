#ifndef GRID_H
#define GRID_H

#include "core/shader.h"
#include "math/vec.h"

//Infinite grid rendered in shader

const static float gridData[] = {
	//Left tri
	-1.0,-1.0,0.99,0.0,0.0,
	1.0,-1.0,0.99,1.0,0.0,
	-1.0,1.0,0.99,0.0,1.0,
	//Right tri
	-1.0,1.0,0.99,0.0,1.0,
	1.0,-1.0,0.99,1.0,0.0,
	1.0,1.0,0.99,1.0,1.0
};

class Grid {
public:
	Grid();
	void init();
	~Grid();
	void Render(const math::Vec3& eye);
private:
	core::Shader mShader{};
	GLuint mVAO, mVBO;
};


#endif