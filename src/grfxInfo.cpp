/*
 * grfxInfo.cpp
 *
 *  Created on: 31 мар. 2018 г.
 *      Author: Alex
 */

// https://msdn.microsoft.com/ru-ru/library/windows/desktop/bb219676(v=vs.85)
// https://stackoverflow.com/questions/1669111/how-do-i-get-the-window-handle-of-the-desktop

#include <iostream>
#include "grfxInfo.h"

const std::string grfxExc_c::errmsgs[] = {
		 "OK"
		,"driver model is not WDDM"
		,"cannot create IDirect3D9Ex"
		,"cannot create D3D device"
};

grfxInfo_c::grfxInfo_c()
{
	hD3D9 = LoadLibrary("d3d9.dll");
}

grfxInfo_c::~grfxInfo_c()
{
	if (pDevice != NULL) {pDevice->Release(); pDevice = NULL; }
	if (pD3D != NULL) {	pD3D->Release(); pD3D = NULL; }
	FreeLibrary(hD3D9);
}

void grfxInfo_c::CheckWDDMDriver()
{
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

void grfxInfo_c::CreateD3DDevice(HWND hWnd)
{
	HRESULT hr;

	// create D3D object
	hr = pD3D9Create9Ex(D3D_SDK_VERSION, reinterpret_cast<void**>(&pD3D));
	if (FAILED(hr))
		throw grfxExc_c(grfxExc_c::errCode_t::ERR_CREATE_IDIRECT3D9EX,
				__FILE__, __FUNCTION__);

	// Set up the structure used to create the D3DDevice.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	// create Direct3D device
	hr = pD3D->CreateDeviceEx(D3DADAPTER_DEFAULT,  D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, NULL, &pDevice);
	if (FAILED(hr))
		throw grfxExc_c(grfxExc_c::errCode_t::ERR_CREATE_IDIRECT3DDEVICE,
				__FILE__, __FUNCTION__);
}
