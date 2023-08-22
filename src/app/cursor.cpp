#include "cursor.h"



Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

void Cursor::init()
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cursorData),cursorData, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

math::Vec3 Cursor::getPosition() const
{
	return mPosition;
}

void Cursor::clampPosition()
{
	mPosition = mPosition.clamp();
}

void Cursor::computePosition(float x,float y,int screenWidth, int screenHeight, const core::Camera& camera)
{
	double xndc = 2.0 * (x/ screenWidth) - 1;
	double yndc = 2.0 * (1.0 - (y / screenHeight)) - 1.;

	double xscale = xndc * camera.getEye().z() + camera.getEye().x();
	double yscale = yndc * camera.getEye().z() + camera.getEye().y();
	mPosition =  math::Vec3(xscale,yscale,0.0);
}

void Cursor::Render()
{
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
