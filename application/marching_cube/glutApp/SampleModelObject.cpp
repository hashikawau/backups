/*
 * SampleModelObject.cpp
 *
 *  Created on: 2013/03/31
 *      Author: you
 */

#include "SampleModelObject.h"

#include <math.h>

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

	//float root2 = sqrt(2) / 2;
//	float v[] = {
//			//
//			-0.5,  0.0,  0.5,  0.0, /*  root2,  root2, 0.0, 0.0, */
//			 0.5,  0.0,  0.5,  0.0, /*  root2,  root2, 1.0, 0.0, */
//			-0.5,  0.5,  0.0,  0.0, /*  root2,  root2, 0.0, 1.0, */
//			 0.5,  0.5,  0.0,  0.0, /*  root2,  root2, 1.0, 1.0, */
//			-0.5,  0.0, -0.5,  0.0, /* -root2, -root2, 1.0, 0.0, */
//			 0.5,  0.0, -0.5,  0.0, /* -root2, -root2, 0.0, 0.0, */
//			-0.5, -0.5,  0.0,  0.0, /* -root2, -root2, 1.0, 1.0, */
//			 0.5, -0.5,  0.0,  0.0, /* -root2, -root2, 0.0, 1.0, */
//			//                      /*                           */
//			-0.5, -0.5,  0.0,  0.0, /* -root2,  root2, 1.0, 0.0, */
//			 0.5, -0.5,  0.0,  0.0, /* -root2,  root2, 1.0, 1.0, */
//			-0.5,  0.0,  0.5,  0.0, /* -root2,  root2, 0.0, 0.0, */
//			 0.5,  0.0,  0.5,  0.0, /* -root2,  root2, 0.0, 1.0, */
//			-0.5,  0.5,  0.0,  0.0, /*  root2, -root2, 1.0, 1.0, */
//			 0.5,  0.5,  0.0,  0.0, /*  root2, -root2, 1.0, 0.0, */
//			-0.5,  0.0, -0.5,  0.0, /*  root2, -root2, 0.0, 1.0, */
//			 0.5,  0.0, -0.5,  0.0, /*  root2, -root2, 0.0, 0.0, */
//			//                      /*                           */
//			-0.5,  0.5,  0.0, -1.0, /* 0.0,  0.0, 1.0, 0.0, */
//			-0.5,  0.0, -0.5, -1.0, /* 0.0,  0.0, 1.0, 1.0, */
//			-0.5,  0.0,  0.5, -1.0, /* 0.0,  0.0, 0.0, 0.0, */
//			-0.5, -0.5,  0.0, -1.0, /* 0.0,  0.0, 0.0, 1.0, */
//			 0.5,  0.5,  0.0,  1.0, /* 0.0,  0.0, 1.0, 0.0, */
//			 0.5,  0.0,  0.5,  1.0, /* 0.0,  0.0, 1.0, 1.0, */
//			 0.5,  0.0, -0.5,  1.0, /* 0.0,  0.0, 0.0, 0.0, */
//			 0.5, -0.5,  0.0,  1.0, /* 0.0,  0.0, 0.0, 1.0  */
//	};

//	int num = 8 * 3;
	int num = sizeof(v) / sizeof(float);
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
			0, 7, 2, 5,
			5, 0, 4, 7

	};
//	unsigned int indices[] = {
//			//z= -0.5
//			 0,  1,  2,
//			 3,  2,  1,
//			//z= 0.5
//			 4,  5,  6,
//			 7,  6,  5,
//			//y= -0.5
//			 8,  9, 10,
//			11, 10,  9,
//			//y= 0.5
//			12, 13, 14,
//			15, 14, 13,
//			//x= -0.5
//			16, 17, 18,
//			19, 18, 17,
//			//x= 0.5
//			20, 21, 22,
//			23, 22, 21
//	};

//	int num = 32;
	int num = sizeof(indices) / sizeof(float);
	m_numIndices = num;
	unsigned int* ret_array = new unsigned int[num];
	for(int i=0; i< num; ++i){
		ret_array[i] = indices[i];
	}

	return shared_ptr<unsigned int>(ret_array);
}


