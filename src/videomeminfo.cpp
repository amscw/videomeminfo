//============================================================================
// Name        : videomeminfo.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "grfxInfo.h"

int main() {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	grfxInfo_c grfxInfo;
	try
	{

	}
	catch (const exc_c &exc)
	{
		exc.ToStderr();
	}
	return 0;
}
