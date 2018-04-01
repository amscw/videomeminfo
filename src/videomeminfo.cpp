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

	try
	{
		grfxInfo_c grfxInfo;
		oss << "found: " << grfxInfo.RetrieveDXGIDescriptors() << " adapters";
		TRACE(oss);
		grfxInfo.Show();

		// find certain adapter
		UINT VendorId = 0x10de;
		SIZE_T nTotal = grfxInfo.DedicatedVideoMemory(VendorId)/1024/1024 + grfxInfo.SharedSystemMemory(VendorId)/1024/1024;
		oss << "Total video memory for 0x" << std::hex << 0x10de << " only: " << std::dec << nTotal << "Mb";
		TRACE(oss);
	}
	catch (const exc_c &exc)
	{
		exc.ToStderr();
	}


	// std::cin >> key;
	return 0;

}
