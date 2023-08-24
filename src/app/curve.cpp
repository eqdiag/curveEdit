#include <limits>


#include "curve.h"

Curve::Curve(Cursor& cursor,const std::vector<math::Vec3>& vertices):
	mCursor{cursor},mVertices{ vertices },mDepth{0}
{

}

Curve::~Curve() {
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

void Curve::init(const std::vector<math::Vec3>& vertices) {

	mVertices = vertices;

	mCursor.init();

	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER,mVertices.size()*sizeof(math::Vec3),mVertices.data(), GL_DYNAMIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

void Curve::addPoint(math::Vec3& p)
{
	mVertices.push_back(p);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(math::Vec3), mVertices.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}

void Curve::removeLastPoint()
{
	if (mVertices.size() < 1) return;
	mVertices.pop_back();

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(math::Vec3), mVertices.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}

void Curve::setClosestPoint(const math::Vec3& p)
{
	if (mVertices.size() <= 0) return;
	auto [index, _] = getClosestPoint(p);
	mVertices[index] = p;

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(math::Vec3), mVertices.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}

void Curve::subdivide()
{
	mDepth++;

	//Compute edge midpts
	std::vector<math::Vec3> midpts{};
	for (int i = 0; i < (mVertices.size() - 1); i++) {
		midpts.push_back(mVertices[i].lerp(mVertices[i + 1], 0.5));
	}

	//Compute new weighted old point
	std::vector<math::Vec3> adjusted{};
	for (int i = 1; i < (mVertices.size() - 1); i++) {
		auto v = mVertices[i - 1] + mVertices[i] * 6.0 + mVertices[i + 1];
		adjusted.push_back(v/8.0);
	}
	  
	//Now update original array
	mVertices.clear();
	int newNumVertices = midpts.size() + adjusted.size();
	for (int i = 0; i < newNumVertices; i++) {
		if (i % 2 == 0) {
			mVertices.push_back(midpts[i/2]);
		}
		else {
			mVertices.push_back(adjusted[i/2]);
		}
	}


	//Update gpu rep
	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(math::Vec3), mVertices.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}

void Curve::clear(const std::vector<math::Vec3>& vertices)
{
	reset(vertices);
	mDepth = 0;

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(math::Vec3), mVertices.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}


void Curve::recompute(const std::vector<math::Vec3>& vertices)
{

	if (vertices.size() == 0) {
		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(math::Vec3), mVertices.data(), GL_DYNAMIC_DRAW);

		glBindVertexArray(0);
		return;
	}
	reset(vertices);

	int oldDepth = mDepth;
	mDepth = 0;
	if (vertices.size() <= 2) oldDepth = 0;
	for (int i = 0; i < oldDepth; i++) subdivide();

	//Update gpu rep
	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(math::Vec3), mVertices.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}



const std::vector<math::Vec3>& Curve::getVertices() const
{
	return mVertices;
}

int Curve::getSubdivisionDepth() const
{
	return mDepth;
}

const int Curve::numVertices() const
{
	return mVertices.size();
}

void Curve::Render(core::Shader& shader) {

	if (mVertices.size() <= 1) return;

	//Draw curve itself
	glBindVertexArray(mVAO);
	glDrawArrays(GL_LINE_STRIP, 0,mVertices.size());
	glBindVertexArray(0);

	//Draw curve nodes
	for (auto& v : mVertices) {
		shader.setUniformMat4("model", math::Mat4::fromTranslation(v).getRawData());
		mCursor.Render();
		shader.setUniformMat4("model", math::Mat4::identity().getRawData());
	}
}


void Curve::reset(const std::vector<math::Vec3>& vertices)
{
	mVertices.clear();
	mVertices = vertices;
}

std::pair<int, math::Vec3> Curve::getClosestPoint(const math::Vec3& p) const
{
	float dist = std::numeric_limits<float>::infinity();
	int index = 0;
	math::Vec3 closest = mVertices[0];
	for (int i = 0; i < mVertices.size(); i++) {
		float newDist = (mVertices[i] - p).norm2();
		if (newDist < dist) {
			dist = newDist;
			closest = mVertices[i];
			index = i;
		}
	}
	return std::make_pair(index, closest);
}

Bezier::Bezier(int numSamples) :
	mNumSamples{ numSamples }
{
	mSamples.reserve(numSamples);
}

Bezier::~Bezier()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

void Bezier::init(const Curve& controlCurve)
{

	//computeSamples(controlCurve);

	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mSamples.size() * sizeof(math::Vec3), mSamples.data(), GL_DYNAMIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

void Bezier::increaseSamples(const Curve& controlCurve)
{
	mNumSamples++;
	computeSamples(controlCurve);
}

void Bezier::decreaseSamples(const Curve& controlCurve)
{
	if (mNumSamples <= 2) return;
	mNumSamples--;
	computeSamples(controlCurve);
}

void Bezier::recompute(const Curve& controlCurve)
{
	if (controlCurve.numVertices() <= 1) return;
	computeSamples(controlCurve);
}

const int Bezier::getNumberSamples() const
{
	return mNumSamples;
}

void Bezier::Render(const Curve& controlCurve)
{
	if (controlCurve.numVertices() <= 2) return;

	//Draw spline
	glBindVertexArray(mVAO);
	glDrawArrays(GL_LINE_STRIP, 0, mSamples.size());
	glBindVertexArray(0);
}

void Bezier::computeSamples(const Curve& controlCurve)
{
	if (controlCurve.numVertices() <= 1) return;

	mSamples.clear();
	mSamples.reserve(mNumSamples);

	for (int i = 0; i < mNumSamples; i++) {
		float t = static_cast<float>(i) / static_cast<float>(mNumSamples - 1);
		mSamples.push_back(computeSampleAt(t, controlCurve));
	}

	//Update points on gpu
	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mSamples.size() * sizeof(math::Vec3), mSamples.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}

math::Vec3 Bezier::computeSampleAt(float t, const Curve& controlCurve)
{
	std::vector<math::Vec3> points = controlCurve.getVertices();
	//For each layer
	for (int i = 0; i < (points.size() - 1); i++) {
		for (int j = 0; j < (points.size() - 1 - i); j++) {
			points[j] = points[j].lerp(points[j + 1], t);
		}
	}

	return points[0];
}

BSpline::BSpline(int numSamples) :
	mNumSamples{ numSamples }
{
	mSamples.reserve(numSamples);
}

BSpline::~BSpline()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

void BSpline::init(const Curve& controlCurve)
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mSamples.size() * sizeof(math::Vec3), mSamples.data(), GL_DYNAMIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

void BSpline::increaseSamples(const Curve& controlCurve)
{
	mNumSamples++;
	computeSamples(controlCurve);
}

void BSpline::decreaseSamples(const Curve& controlCurve)
{
	if (mNumSamples <= 2) return;
	mNumSamples--;
	computeSamples(controlCurve);
}

void BSpline::recompute(const Curve& controlCurve)
{
	if (controlCurve.numVertices() <= 3) return;
	computeSamples(controlCurve);
}

const int BSpline::getNumberSamples() const
{
	return mNumSamples;
}

void BSpline::Render(const Curve& controlCurve)
{
	if (controlCurve.numVertices() <= 2) return;

	glBindVertexArray(mVAO);
	glDrawArrays(GL_LINE_STRIP, 0, mSamples.size());
	glBindVertexArray(0);
}

void BSpline::computeSamples(const Curve& controlCurve)
{
	if (controlCurve.numVertices() <= 1) return;

	mSamples.clear();
	mSamples.reserve(mNumSamples);

	for (int i = 0; i < mNumSamples; i++) {
		float t = (static_cast<float>(i) / static_cast<float>(mNumSamples - 1));

		t = t * (controlCurve.numVertices() - 3) + 1;
		mSamples.push_back(computeSampleAt(t, controlCurve));
	}

	//Update points on  gpu
	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mSamples.size() * sizeof(math::Vec3), mSamples.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}

math::Vec3 BSpline::computeSampleAt(float t, const Curve& controlCurve)
{
	auto& points = controlCurve.getVertices();

	int k = static_cast<int>(std::floor(t));
	if (k >= (controlCurve.numVertices() - 2)) {
		k--;
	}
	float t_norm = (t - k);

	auto p0 = points.at(k - 1);
	auto p1 = points.at(k);
	auto p2 = points.at(k + 1);
	auto p3 = points.at(k + 2);

	auto p01 = p0.lerp(p1, 2.0 / 3.0);
	auto p32 = p3.lerp(p2, 2.0 / 3.0);

	auto q1 = p2.lerp(p1, 2.0 / 3.0);
	auto q2 = p1.lerp(p2, 2.0 / 3.0);

	auto q0 = p01.lerp(q1, 0.5);
	auto q3 = p32.lerp(q2, 0.5);

	auto q01 = q0.lerp(q1, t_norm);
	auto q12 = q1.lerp(q2, t_norm);
	auto q23 = q2.lerp(q3, t_norm);

	auto q012 = q01.lerp(q12, t_norm);
	auto q123 = q12.lerp(q23, t_norm);

	return q012.lerp(q123, t_norm);
}