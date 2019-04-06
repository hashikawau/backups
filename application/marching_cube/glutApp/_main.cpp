/*
 * _main.cpp
 *
 *  Created on: 2013/03/30
 *      Author: you
 */


#include "SampleWindow.h"

#include <iostream>
#include <glutApp/GLApplication.h>
using namespace glutApp;

int main(int argc, char* argv[]){
	std::cout << "main started" << std::endl;

	GLApplication::init(argc, argv);
	GLApplication::start(new SampleWindow(argv[0]));

	std::cout << "main terminated" << std::endl;
	return 0;
}

