#include "curve.h"

Curve::Curve(Cursor& cursor,const std::vector<math::Vec3>& vertices):
	mCursor{cursor},mVertices{ vertices }
{

}

Curve::~Curve() {
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

void Curve::init() {

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

void Curve::Render(core::Shader& shader) {

	//Curve and nodes are blue
	shader.setUniformFloat3("color", math::Color3{0,0,1});

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

