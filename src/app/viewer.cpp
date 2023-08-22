#include "core/settings.h"

#include "app/viewer.h"
#include <cassert>

Viewer::Viewer():
	App{},
	mViewerOpen{true},
	mMousePressed{false},
	mMouseInit{false},
	mMouseX{},
	mMouseY{}
{

}

void Viewer::init()
{

	//Create graphics assets

	mCamera = std::make_unique<core::TopDownCamera>(math::Vec3(0, 0, 1));


	mGrid.init();
	mCursor.init();
	mCurve.init();

	mCurveShader.init(SHADER_DIR, "curve.vs", "curve.fs");

	mModelMatrix = math::Mat4::identity();
	mViewMatrix = mCamera->getViewMatrix();
	mProjMatrix = math::Mat4::perspectiveProjection(3.14 * 45.0 / 180.0, 800.0 / 600.0, 0.1, 1000.);

	mCurveShader.use();
	mCurveShader.setUniformMat4("model", mModelMatrix.getRawData());
	mCurveShader.setUniformMat4("view", mViewMatrix.getRawData());
	mCurveShader.setUniformMat4("proj", mProjMatrix.getRawData());

	

	glClearColor(0.32f, 0.32f, 0.32f, 1.0f);
	glEnable(GL_DEPTH_TEST);

}

void Viewer::update()
{
	//x += 0.01;
}

void Viewer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mViewMatrix = mCamera->getViewMatrix();

	mCurveShader.use();
	mCurveShader.setUniformMat4("view", mViewMatrix.getRawData());
	mCurveShader.setUniformFloat3("eye", mCamera->getEye());

	//Cursor for selection is green
	mCurveShader.setUniformFloat3("color", math::Color3{0, 1, 0});
	mCurveShader.setUniformMat4("model",math::Mat4::fromTranslation(mCursor.getPosition()).getRawData());
	mCursor.Render();
	mCurveShader.setUniformMat4("model", math::Mat4::identity().getRawData());

	mCurve.Render(mCurveShader);
	
	mGrid.Render(mCamera->getEye());
}
