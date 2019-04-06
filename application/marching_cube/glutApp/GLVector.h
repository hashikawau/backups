/*
 * GLVector.h
 *
 *  Created on: 2013/04/01
 *      Author: you
 */

#ifndef GLVECTOR_H_
#define GLVECTOR_H_

namespace glutApp {

class GLVector {
public:
	GLVector();
	~GLVector();
};

class GLMatrix4;
class GLVector3
{
public:
	GLVector3(float x, float y, float z);
	~GLVector3();
	GLVector3(const GLVector3& ref);
	GLVector3& operator=(const GLVector3& ref);

	const int getX() const{
		return m_vector[0];
	}
	const int getY() const{
		return m_vector[1];
	}
	const int getZ() const{
		return m_vector[2];
	}

	void rotate(const GLMatrix4& rotation);

private:
	float m_vector[3];
};

} /* namespace glutApp */
#endif /* GLVECTOR_H_ */
