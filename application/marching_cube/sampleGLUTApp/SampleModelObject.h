/*
 * SampleModelObject.h
 *
 *  Created on: 2013/03/31
 *      Author: you
 */

#ifndef SAMPLEMODELOBJECT_H_
#define SAMPLEMODELOBJECT_H_

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;
#include <boost/scoped_array.hpp>
using boost::scoped_array;

class SampleModelObject {
public:
	SampleModelObject();
	~SampleModelObject();

	shared_ptr<float> getVertices() const;
	shared_ptr<unsigned int> getIndices();

	int getNumVertices() const{
		return m_numVertices;
	}
	int getNumIndices() const{
		return m_numIndices;
	}

private:
	scoped_array<float> m_vertices;
	scoped_array<unsigned int> m_indices;
	int m_numVertices;
	int m_numIndices;

	int m_numX;
	int m_numY;
	int m_numZ;
};

#endif /* SAMPLEMODELOBJECT_H_ */
