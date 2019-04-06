/*
 * GLMatrix.h
 *
 *  Created on: 2013/03/31
 *      Author: you
 */

#ifndef GLMATRIX_H_
#define GLMATRIX_H_

namespace glutApp {

class GLMatrix {
public:

private:
	GLMatrix();
	~GLMatrix();

};

class GLMatrix4;
class GLMatrix3
{
public:
	GLMatrix3();
	GLMatrix3(const float* vector);
	GLMatrix3(const GLMatrix4& matrix4);
	~GLMatrix3();
	GLMatrix3(const GLMatrix3& ref);
	GLMatrix3 operator=(const GLMatrix3& ref);

	const float* get() const{
		return m_matrix;
	}
	void transpose(){
		float temp;

		temp = m_matrix[1];
		m_matrix[1] = m_matrix[3];
		m_matrix[3] = temp;

		temp = m_matrix[2];
		m_matrix[2] = m_matrix[6];
		m_matrix[6] = temp;

		temp = m_matrix[5];
		m_matrix[5] = m_matrix[7];
		m_matrix[7] = temp;

	}

	static GLMatrix3 createIdentity(){
		float ret_mat[] = {
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
		};
		return GLMatrix3(ret_mat);
	}

private:
	float m_matrix[9];
};

class GLMatrix4
{
public:
	GLMatrix4();
	GLMatrix4(const float* matrix);
	~GLMatrix4();
	GLMatrix4(const GLMatrix4& ref);
	GLMatrix4& operator=(const GLMatrix4& ref);

	const float* get() const{
		return m_matrix;
	}
	void transpose(){
		float temp;

		temp = m_matrix[1];
		m_matrix[1] = m_matrix[4];
		m_matrix[4] = temp;

		temp = m_matrix[2];
		m_matrix[2] = m_matrix[8];
		m_matrix[8] = temp;

		temp = m_matrix[3];
		m_matrix[3] = m_matrix[12];
		m_matrix[12] = temp;

		temp = m_matrix[6];
		m_matrix[6] = m_matrix[9];
		m_matrix[9] = temp;

		temp = m_matrix[7];
		m_matrix[7] = m_matrix[13];
		m_matrix[13] = temp;

		temp = m_matrix[11];
		m_matrix[11] = m_matrix[14];
		m_matrix[14] = temp;
	}

	static GLMatrix4 createZero();
	static GLMatrix4 createIdentity(){
		float ret_mat[] = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
		};
		return GLMatrix4(ret_mat);
	}
	static GLMatrix4 createScale(float x, float y, float z);
	static GLMatrix4 createTranslation(float x, float y, float z);
	static GLMatrix4 createRotation(float angle, float x, float y, float z);
	static GLMatrix4 createProjection(float fovy, float width, float height, float depth);

private:

	float m_matrix[16];
};

} /* namespace glutApp */
#endif /* GLMATRIX_H_ */
