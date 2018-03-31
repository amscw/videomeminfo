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
	HWND hWnd = GetDesktopWindow();
	try
	{
		grfxInfo_c grfxInfo;
		grfxInfo.CheckWDDMDriver();
		grfxInfo.CreateD3DDevice(hWnd);
	}
	catch (const exc_c &exc)
	{
		exc.ToStderr();
	}
	return 0;
}
