#ifndef VIEWER_H
#define VIEWER_H

#include <memory>

#include "core/app.h"
#include "core/shader.h"
#include "core/mesh.h"
#include "core/asset_loader.h"
#include "core/camera.h"

#include "math/matrix.h"

#include "grid.h"
#include "curve.h"
#include "cursor.h"



class Viewer : public core::App {
public:

	enum EditMode{CurveMode,SurfaceMode,Size};


	Viewer();
	void init() override;
	void update() override;
	void render() override;

	const char* getEditModeStr() const;
	void changeMode();

	//Input state variables
	bool mViewerOpen;
	bool mMousePressed;
	bool mMouseInit;
	float mMouseX;
	float mMouseY;
	EditMode mMode;

	//Toggle which curves are visible
	bool mControlCurveVisible{ true };
	bool mBezierCurveVisible{ true };
	bool mBSplineCurveVisible{ false };
	bool mSubdivCurveVisible{ false };


	//Shader uniforms
	math::Mat4 mModelMatrix{};
	math::Mat4 mViewMatrix{};
	math::Mat4 mProjMatrix{};

	//Camera and objects
	std::unique_ptr<core::TopDownCamera> mCamera;

	//Cursor
	Cursor mCursor{};

	//Control curve
	Curve mCurve{
		mCursor,
		{}
	};

	//Spline
	Bezier mBezierSpline{10};
	BSpline mBSplineSpline{ 10 };
	Curve mSubdivCurve{
		mCursor,
		{}
	};

private:

	//Grid
	Grid mGrid{};

	

	//Curves
	core::Shader mCurveShader{};
	
	const static char* editModeStr[];


};


#endif