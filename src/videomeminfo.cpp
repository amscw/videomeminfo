//============================================================================
// Name        : videomeminfo.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <memory>
#include <vector>
#include "grfxInfo.h"


int main() {
	try
	{
		grfxInfo_c grfxInfo;
		grfxInfo.CreateIDXGIFactory();
		std::cout << "found: " << grfxInfo.RetrieveDXGIDescriptors() << " adapters";
	}
	catch (const exc_c &exc)
	{
		exc.ToStderr();
	}
	return 0;
}
