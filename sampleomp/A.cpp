/*
 * A.cpp
 *
 *  Created on: 2013/05/01
 *      Author: scientific
 */

#include "A.h"


//===============================================
IA::~IA(){}

////===============================================
//void InlinedA::calc(){
//	c = sqrt(pow(a, 2) + pow(b, 2));
//}
//
////===============================================
//void A::set(int i, int j){
//	a = i*2.0;
//	b = j*2.0;
//	c = 0.0;
//}
//void A::calc(){
//	c = sqrt(pow(a, 2) + pow(b, 2));
//}

//===============================================
IA* createA(){
	class newA: public IA{
	public:
		newA():IA(), a(0.0), b(0.0), c(0.0){
//			std::cout << "newA is created" << std::endl;
		}
		virtual ~newA(){}
		virtual void set(int i, int j){a = i*2.0;b = j*2.0;c = 0.0;}
		virtual void calc(){c = sqrt(pow(a, 2) + pow(b, 2));}
	public:
		double a;
		double b;
		double c;
	};
	return new newA();
}


