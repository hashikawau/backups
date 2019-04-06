/*
 * _main.cpp
 *
 *  Created on: 2013/03/25
 *      Author: scientific
 */



#include "ApplicationForGLUT.h"
#include "Controller01.h"

#include <boost/shared_ptr.hpp>

//#include <windows.h>


int main(int argc, char* argv[]){
	std::cout << "main started" << std::endl;

	ApplicationForGLUT::start(
			argc,
			argv,
			boost::shared_ptr<IController>(new Controller01(
					boost::shared_ptr<Model01>(new Model01()))));

	std::cout << "main terminated" << std::endl;
	return 0;
}

