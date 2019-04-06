/*
 * _main.cpp
 *
 *  Created on: 2012/12/06
 *      Author: scientific
 */


#include <iostream>
#include <omp.h>
#include <fstream>
#include <string>
#include <typeinfo>
#include <sys/time.h>
#include <math.h>

#include "A.h"

//===============================================
inline long int getTick(){
	return clock();// / CLOCKS_PER_SEC;
	timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

//===============================================
void tester(){
	double a = sqrt(pow(1.4, 1.4) + pow(1.5, 1.5));
//	std::cout << a << std::endl;
}

//===============================================
int main(int argc, char* argv[]){

//	std::string file(__FILE__);
//	std::cout << file << std::endl;
//	std::ofstream fo((std::string(__FILE__) + std::string("sample.txt")).c_str());
	std::ofstream fo("sample.txt");
	fo << "dfghkl" << std::endl;

//	int count = 100;
//#pragma omp parallel num_threads(4), reduction(+ :count)
////#pragma omp parallel num_threads(10)
////#pragma omp parallel for private(count)
////#pragma omp parallel for firstprivate(count)
//	{
//		std::cout << omp_get_thread_num() << ", first = " << count << std::endl;
//		int temp = 0;
//#pragma omp for// firstprivate(temp), lastprivate(temp)
//		for(int i=0; i< 1000000000; ++i){
//			temp += 1;
//		}
//		std::cout << omp_get_thread_num() << ", last = " << temp << std::endl;
////#pragma omp atomic
////		count = count + temp; //wrong
//		count += temp;
//	}
//
//	std::cout << "result = ";
//	std::cout << count << std::endl;
//
//	int i=0;
////	while(++i < 5){
//	while(i++ < 5){
//		std::cout << i << std::endl;
//	}
//
//	std::cout << typeid(1e3).name() << std::endl;

	long int time = getTick();
	std::cout << "size = " << sizeof(time) << std::endl;

	int n;// = 700;
	n=1000;
	bool doParallelise = argc > 1;
	std::cout << "parallelized = " << doParallelise << std::endl;
	std::cout << std::endl;
//	doParallelise = true;
	double** a = new double*[n];
	double** b = new double*[n];
	double** c = new double*[n];

	//===========================================
	for(int i=0; i< n; ++i){
		a[i] = new double[n];
		b[i] = new double[n];
		c[i] = new double[n];
	}
	std::cout << "created time = " << getTick() - time << std::endl;
	time = getTick();

#pragma omp parallel for if(doParallelise)
	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			for(int nn=0; nn< n; ++nn){
				a[i][j] = i *2;
				b[i][j] = j *2;
				c[i][j] = 0.0;
			}
		}
	}
	std::cout << "inited time = " << getTick() - time << std::endl;
	time = getTick();

#pragma omp parallel for if(doParallelise)
	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			for(int nn=0; nn< n; ++nn){
				c[i][j] = sqrt(pow(a[i][j], 2) + pow(b[i][j], 2));
			}
		}
	}
	std::cout << "calculated time = " << getTick() - time << std::endl;
	time = getTick();

	for(int i=0; i< n; ++i){
		delete [] a[i];
		delete [] b[i];
		delete [] c[i];
	}
	delete [] a;
	delete [] b;
	delete [] c;
//	std::cout << "time = " << getTick() - time << std::endl;
	time = getTick();

	std::cout << "deleted time = " << getTick() - time << std::endl;
	std::cout << std::endl;
	time = getTick();


	//===========================================
	InlinedA** a1 = new InlinedA*[n];
	for(int i=0; i< n; ++i){
		a1[i] = new InlinedA[n];
//		for(int j=0; j< n; ++j){
//			a1[i][j] = new InlinedA();
//		}
	}
	std::cout << "created time = " << getTick() - time << std::endl;
	time = getTick();

#pragma omp parallel for if(doParallelise)
	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			for(int nn=0; nn< n; ++nn){
//				aaa[i][j].getA() = i *2;
//				aaa[i][j].getB() = j *2;
//				aaa[i][j].getC() = 0.0;
//				aaa[i][j].a = i *2;
//				aaa[i][j].b = j *2;
//				aaa[i][j].c = 0.0;
				a1[i][j].set(i, j);
			}
		}
	}
	std::cout << "inited time = " << getTick() - time << std::endl;
	time = getTick();

#pragma omp parallel for if(doParallelise)
	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			for(int nn=0; nn< n; ++nn){
//				aaa[i][j].getC() = sqrt(pow(aaa[i][j].getA(), 2) + pow(aaa[i][j].getB(), 2));
//				aaa[i][j].c = sqrt(pow(aaa[i][j].a, 2) + pow(aaa[i][j].b, 2));
				a1[i][j].calc();
			}
		}
	}
	std::cout << "calculated time = " << getTick() - time << std::endl;
	time = getTick();

	for(int i=0; i< n; ++i){
//		for(int j=0; j< n; ++j){
//			delete a1[i][j];
//		}
		delete[] a1[i];
	}
	delete[] a1;
	std::cout << "deleted time = " << getTick() - time << std::endl;
	std::cout << std::endl;
	time = getTick();

	//===========================================
	A*** a2 = new A**[n];
	for(int i=0; i< n; ++i){
		a2[i] = new A*[n];
		for(int j=0; j< n; ++j){
			a2[i][j] = new A();
		}
	}
	std::cout << "created time = " << getTick() - time << std::endl;
	time = getTick();

#pragma omp parallel for if(doParallelise)
	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			for(int nn=0; nn< n; ++nn){
				a2[i][j]->set(i, j);
			}
		}
	}
	std::cout << "inited time = " << getTick() - time << std::endl;
	time = getTick();

#pragma omp parallel for if(doParallelise)
	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			for(int nn=0; nn< n; ++nn){
				a2[i][j]->calc();
			}
		}
	}
	std::cout << "calculated time = " << getTick() - time << std::endl;
	time = getTick();

	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			delete a2[i][j];
		}
		delete[] a2[i];
	}
	delete[] a2;
	std::cout << "deleted time = " << getTick() - time << std::endl;
	std::cout << std::endl;
	time = getTick();

	//===========================================
	IA*** aaa = new IA**[n];
	for(int i=0; i< n; ++i){
		aaa[i] = new IA*[n];
		for(int j=0; j< n; ++j){
			aaa[i][j] = createA();
		}
	}
	std::cout << "created time = " << getTick() - time << std::endl;
	time = getTick();

#pragma omp parallel for if(doParallelise)
	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			for(int nn=0; nn< n; ++nn){
				aaa[i][j]->set(i, j);
			}
		}
	}
	std::cout << "inited time = " << getTick() - time << std::endl;
	time = getTick();

#pragma omp parallel for if(doParallelise)
	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			for(int nn=0; nn< n; ++nn){
				aaa[i][j]->calc();
			}
		}
	}
	std::cout << "calculated time = " << getTick() - time << std::endl;
	time = getTick();

	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			delete aaa[i][j];
		}
		delete[] aaa[i];
	}
	delete[] aaa;
	std::cout << "deleted time = " << getTick() - time << std::endl;
	std::cout << std::endl;
	time = getTick();

//	auto dd = createA();

	//===========================================
	n = 1000;
#pragma omp parallel for if(doParallelise)
	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			for(int nn=0; nn< n; ++nn){
				tester();
			}
		}
	}
	std::cout << "tester() time = " << getTick() - time << std::endl;
	time = getTick();

	void (*pt)() = &tester;
	void (*pt2)() = tester;
#pragma omp parallel for if(doParallelise)
	for(int i=0; i< n; ++i){
		for(int j=0; j< n; ++j){
			for(int nn=0; nn< n; ++nn){
				(*pt)();
//				(*pt2)();
			}
		}
	}
	std::cout << "(*tester)() time = " << getTick() - time << std::endl;
	std::cout << std::endl;
	time = getTick();

	std::cout << "terminated" << std::endl;

	return 0;
}
