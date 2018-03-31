/*
 * grfxInfo.cpp
 *
 *  Created on: 31 мар. 2018 г.
 *      Author: Alex
 */
#include <iostream>
#include "grfxInfo.h"

const std::string grfxExc_c::errmsgs[] = {
		 "OK"
		,"driver model is not WDDM"
};

grfxInfo_c::grfxInfo_c() throw (grfxExc_c) {
	try {
		checkWDDMDriver();
	} catch (const exc_c &exc) {
		throw;
	}
	// create direct
}

void grfxInfo_c::checkWDDMDriver() throw (grfxExc_c)
{
    HMODULE hD3D9 = LoadLibrary("d3d9.dll");

    if (hD3D9 == NULL) {
        throw grfxExc_c(grfxExc_c::errCode_t::ERR_WDDMCHECKFAIL, __FILE__, __FUNCTION__, "hD3D9 is null");
    }

    /*  Try to create IDirect3D9Ex interface (also known as a DX9L interface). This interface can only be created if the driver is a WDDM driver.
	 */

    pD3D9Create9Ex = (LPDIRECT3DCREATE9EX) GetProcAddress( hD3D9, "Direct3DCreate9Ex" );

    if (pD3D9Create9Ex == NULL) {
    	throw grfxExc_c(grfxExc_c::errCode_t::ERR_WDDMCHECKFAIL, __FILE__, __FUNCTION__, "pD3D9Create9Ex is null");
    }
}
