/*
 * GLCamera.h
 *
 *  Created on: 2013/04/01
 *      Author: you
 */

#ifndef GLCAMERA_H_
#define GLCAMERA_H_

#include "GLVector.h"
#include "GLMatrix.h"

namespace glutApp {

class GLCamera {
public:
	GLCamera();
	~GLCamera();

	void setPosition(const GLVector3& position){
		m_position = position;
	}
	void setFovy(float fovy){
		m_fovy = fovy;
	}
	void setVolume(float width, float height, float depth){
		m_width = width;
		m_height = height;
		m_depth = depth;
	}
	void setScale(float scale){
		m_scale = scale;
	}

	GLVector3& getPosition(){
		return m_position;
	}
	const GLVector3 getPosition() const{
		return m_position;
	}
	const GLMatrix4 getRotation() const{
		return m_rotation;
	}

	void rotate(const GLMatrix4& rotation);

	const GLMatrix4 getModelViewProjectionMatrix() const;
	const GLMatrix4 getModelViewMatrix() const;
	const GLMatrix3 getNormalMatrix() const;

private:
	GLVector3 m_position;
	GLMatrix4 m_rotation;
	float m_fovy;
	float m_width;
	float m_height;
	float m_depth;
	float m_scale;
};

} /* namespace glutApp */
#endif /* GLCAMERA_H_ */
