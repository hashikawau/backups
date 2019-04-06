/*
 * SampleModelObject.cpp
 *
 *  Created on: 2013/03/31
 *      Author: you
 */

#include "SampleModelObject.h"

SampleModelObject::SampleModelObject()
	:m_vertices(0),
	 m_numVertices(0),
	 m_numIndices(0),
	 m_numX(0),
	 m_numY(0),
	 m_numZ(0)
{
	m_numX = 2;
	m_numY = 2;
	m_numZ = 2;
	int numTotal = m_numX * m_numY * m_numZ;
	m_numVertices = numTotal * 3;
	float* values = new float[numTotal];
	for(int i=0; i<  numTotal; ++i){
		values[i] = 0.0f;
	}
}

SampleModelObject::~SampleModelObject() {
}

shared_ptr<float> SampleModelObject::getVertices() const{
	float v[] = {
			-0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f
	};

	int num = 8 * 3;
	float* ret_array = new float[num];
	for(int i=0; i< num; ++i){
		ret_array[i] = v[i];
	}
//	shared_ptr<float> ret_array(new float[getNumVertices()]);

//	for(int i=0; i< m_numX; ++i){
//		for(int j=0; j< m_numY; ++j){
//			for(int k=0; k< m_numZ; ++k){
//				int index = i * m_numX * m_numY + j * m_numX + k;
//				ret_array[index * 3 + 0] = i / (float)m_numX - 0.5;
//				ret_array[index * 3 + 1] = j / (float)m_numY - 0.5;
//				ret_array[index * 3 + 2] = k / (float)m_numZ - 0.5;
//			}
//		}
//	}

//	return ret_array;
	return shared_ptr<float>(ret_array);
}
shared_ptr<unsigned int> SampleModelObject::getIndices(){
	unsigned int indices[] = {
			0, 1, 3, 2,
			0, 4, 6, 1,
			0, 2, 5, 4,
			4, 5, 7, 6,
			7, 5, 2, 3,
			1, 6, 7, 3,
			0, 7, 2, 5
//			5, 0, 4, 7,

	};

	int num = 28;
	m_numIndices = num;
	unsigned int* ret_array = new unsigned int[num];
	for(int i=0; i< num; ++i){
		ret_array[i] = indices[i];
	}

	return shared_ptr<unsigned int>(ret_array);
}


