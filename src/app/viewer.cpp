#include "core/settings.h"

#include "app/viewer.h"
#include <cassert>

Viewer::Viewer():
	App{},
	mViewerOpen{true},
	mMousePressed{false},
	mMouseInit{false},
	mMouseX{},
	mMouseY{},
	mMode{EditMode::CurveMode}
{

}

void Viewer::init()
{

	//Create graphics assets

	mCamera = std::make_unique<core::TopDownCamera>(math::Vec3(0, 0, 1));


	mGrid.init();
	mCursor.init();
	mCurve.init();

	mBezierSpline.init(mCurve);
	mBSplineSpline.init(mCurve);
	mSubdivCurve.init(mCurve.getVertices());

	std::cout << mSubdivCurve.numVertices() << std::endl;

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
	mCurveShader.setUniformFloat3("color", math::Color3{0.12, 0.53, 0.18});
	mCurveShader.setUniformMat4("model",math::Mat4::fromTranslation(mCursor.getPosition()).getRawData());
	mCursor.Render();
	mCurveShader.setUniformMat4("model", math::Mat4::identity().getRawData());

	if (mControlCurveVisible) {
		mCurveShader.setUniformFloat3("color", math::Color3{.18, .42, .72});
		mCurve.Render(mCurveShader);
	}
	if (mBezierCurveVisible) {
		mCurveShader.setUniformFloat3("color", math::Color3{0.95, 0.32, 0.26});
		mBezierSpline.Render(mCurve);
	}
	if (mBSplineCurveVisible) {
		mCurveShader.setUniformFloat3("color", math::Color3{0.07, 0.74, 0.63});
		mBSplineSpline.Render(mCurve);
	}

	if (mSubdivCurveVisible) {
		mCurveShader.setUniformFloat3("color", math::Color3{0.66, 0.07, 0.99});
		mSubdivCurve.Render(mCurveShader);
	}
	
	mGrid.Render(mCamera->getEye());
}

const char* Viewer::getEditModeStr() const
{
	return editModeStr[mMode];
}

void Viewer::changeMode()
{
	mMode = static_cast<EditMode>((mMode + 1) % EditMode::Size);
}

const char *Viewer::editModeStr[] = {
		"Curve Mode",
		"Surface Mode"
};