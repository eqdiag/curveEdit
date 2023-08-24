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
	void init(const std::vector<math::Vec3>& vertices = {});
	void addPoint(math::Vec3& p);
	void removeLastPoint();
	void setClosestPoint(const math::Vec3& p);
	void subdivide();
	void clear(const std::vector<math::Vec3>& vertices);
	void recompute(const std::vector<math::Vec3>& vertices);
	const std::vector<math::Vec3>& getVertices() const;
	int getSubdivisionDepth() const;
	const int numVertices() const;
	void Render(core::Shader& shader);
private:

	void reset(const std::vector<math::Vec3>& vertices);
	std::pair<int, math::Vec3> getClosestPoint(const math::Vec3& p) const;
	std::vector<math::Vec3> mVertices;
	Cursor& mCursor;
	GLuint mVAO, mVBO;
	//Subdivision depth
	int mDepth;
};


class Bezier {
public:
	Bezier(int numSamples);
	~Bezier();
	void init(const Curve& controlCurve);
	void increaseSamples(const Curve& controlCurve);
	void decreaseSamples(const Curve& controlCurve);
	void recompute(const Curve& controlCurve);

	const int getNumberSamples() const;
	void Render(const Curve& controlCurve);
private:

	void computeSamples(const Curve& controlCurve);
	math::Vec3 computeSampleAt(float t, const Curve& controlCurve);

	int mNumSamples;
	//mNumSamples equally spaced in parameter space
	std::vector<math::Vec3> mSamples;
	GLuint mVAO, mVBO;

};

class BSpline {
public:
	BSpline(int numSamples);
	~BSpline();
	void init(const Curve& controlCurve);
	void increaseSamples(const Curve& controlCurve);
	void decreaseSamples(const Curve& controlCurve);
	void recompute(const Curve& controlCurve);
	const int getNumberSamples() const;
	void Render(const Curve& controlCurve);
private:

	void computeSamples(const Curve& controlCurve);
	math::Vec3 computeSampleAt(float t, const Curve& controlCurve);

	int mNumSamples;
	//mNumSamples equally spaced in parameter space
	std::vector<math::Vec3> mSamples;
	GLuint mVAO, mVBO;
};



#endif