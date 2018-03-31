//============================================================================
// Name        : videomeminfo.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <sstream>
#include "grfxInfo.h"

#define TRACE(strm) {\
	std::cout << "TRACE:" << __FILE__ << "(" << __FUNCTION__ << ")-" <<\
	strm.str() << std::endl;\
	strm.str("");\
	strm.clear();\
}

int main() {
	int key;
	std::ostringstream oss;
	grfxInfo_c grfxInfo;

	try
	{
		grfxInfo.CreateIDXGIFactory();
		oss << "found: " << grfxInfo.RetrieveDXGIDescriptors() << " adapters";
		TRACE(oss);
	}
	catch (const exc_c &exc)
	{
		exc.ToStderr();
	}
	grfxInfo.Show();

	std::cin >> key;
	return 0;

}
