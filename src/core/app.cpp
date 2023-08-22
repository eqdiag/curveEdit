#include "app.h"

void core::App::init() {

}

void core::App::update()
{
}

void core::App::render()
{
}

void core::App::setDimensions(int width, int height)
{
	mWindowWidth = width;
	mWindowHeight = height;
}

int core::App::getWidth() const
{
	return mWindowWidth;
}

int core::App::getHeight() const
{
	return mWindowHeight;
}
