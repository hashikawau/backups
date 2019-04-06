/*
 * A.h
 *
 *  Created on: 2013/05/01
 *      Author: scientific
 */

#ifndef sampleomp_A_H_
#define sampleomp_A_H_


#include <math.h>

//===============================================
class IA{
public:
	IA(){}
	virtual ~IA() =0;
	virtual void set(int i, int j) =0;
	virtual void calc() =0;
};

//===============================================
IA* createA();

//===============================================
struct InlinedA{
public:
	InlinedA()
	: a(0),
	  b(0),
	  c(0){
	}
	~InlinedA(){
	}
	inline void set(int i, int j){a = i*2.0;b = j*2.0;c = 0.0;}
	inline void calc(){c = sqrt(pow(a, 2) + pow(b, 2));}

public:
	double a;
	double b;
	double c;
};
//void InlinedA::set(int i, int j){
//	a = i*2.0;
//	b = j*2.0;
//	c = 0.0;
//}
//void InlinedA::calc(){
//	c = sqrt(pow(a, 2) + pow(b, 2));
//}

//===============================================
class A{//: public IA{
public:
	A()
	: a(0),
	  b(0),
	  c(0){
	}
	//virtual
	~A(){
	}
//	virtual
	inline void set(int i, int j){a = i*2.0;b = j*2.0;c = 0.0;}
//	virtual
	inline void calc(){c = sqrt(pow(a, 2) + pow(b, 2));}

public:
	double a;
	double b;
	double c;
};

#endif /* sampleomp_A_H_ */
