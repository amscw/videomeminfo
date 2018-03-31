/*
 * grfxInfo.cpp
 *
 *  Created on: 31 мар. 2018 г.
 *      Author: Alex
 */

// about DXGI
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb219822(v=vs.85).aspx

#include "grfxInfo.h"
#include "comdef.h"

const std::string grfxExc_c::errmsgs[] = {
		 "OK"
		,"driver model is not WDDM"
		,"cannot create DXGI factory"
		,"cannot get DXGI adapter descriptor"
};

grfxInfo_c::grfxInfo_c()
{

}

grfxInfo_c::~grfxInfo_c()
{
	if (m_pFactory != NULL) { m_pFactory->Release(); m_pFactory = NULL; }
}

void grfxInfo_c::CheckWDDMDriver()
{
	// Define a function pointer to the Direct3DCreate9Ex function.
	typedef HRESULT (WINAPI *LPDIRECT3DCREATE9EX)( UINT, void **);

	HMODULE hD3D9 = LoadLibrary("d3d9.dll");
    if (hD3D9 == NULL) {
        throw grfxExc_c(grfxExc_c::errCode_t::ERR_WDDMCHECKFAIL, __FILE__, __FUNCTION__, "d3d9.dll is missing");
    }

    /*  Try to create IDirect3D9Ex interface (also known as a DX9L interface). This interface can only be created if the driver is a WDDM driver.
	 */
    LPDIRECT3DCREATE9EX pD3D9Create9Ex = (LPDIRECT3DCREATE9EX) GetProcAddress( hD3D9, "Direct3DCreate9Ex" );
    if (pD3D9Create9Ex == NULL) {
    	FreeLibrary(hD3D9);
    	throw grfxExc_c(grfxExc_c::errCode_t::ERR_WDDMCHECKFAIL, __FILE__, __FUNCTION__, "pD3D9Create9Ex is null");
    }
    FreeLibrary(hD3D9);
}

void grfxInfo_c::CreateIDXGIFactory()
{
	HRESULT hr;

	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pFactory);
	if (FAILED(hr))
	{
		_com_error err(hr);
		throw grfxExc_c(grfxExc_c::errCode_t::ERR_CREATE_DXGIFACTORY, __FILE__, __FUNCTION__);
	}
}

std::size_t grfxInfo_c::RetrieveDXGIDescriptors()
{
	int i;
	HRESULT hr;
	IDXGIAdapter *pAdapter;

	while ((hr = m_pFactory->EnumAdapters(i, &pAdapter)) != DXGI_ERROR_NOT_FOUND)
	{
		std::unique_ptr<DXGI_ADAPTER_DESC> pDesc = std::make_unique<DXGI_ADAPTER_DESC>();
		hr = pAdapter->GetDesc(pDesc.get());
		pAdapter->Release();
		if (FAILED(hr))
		{
			_com_error err(hr);
			throw grfxExc_c(grfxExc_c::errCode_t::ERR_GET_DXGIADAPTERDESC, __FILE__, __FUNCTION__);
			continue;
		}
		m_dxgiDescriptors.emplace_back(std::make_unique<DXGI_ADAPTER_DESC>(*pDesc.release()));
		i++;
	}

	return i;
}

void grfxInfo_c::Show() noexcept
{
	it_t it;
	int i;


	for (it = m_dxgiDescriptors.begin(), i = 0; it != m_dxgiDescriptors.end(); it++, i++)
	{
		std::cout << "#" << i << std::endl;
		std::wcout << (*it)->Description << std::endl;
		std::cout << std::hex;
		std::cout << "VendorId - 0x" << (*it)->VendorId << std::endl;
		std::cout << "DeviceId - 0x" << (*it)->DeviceId << std::endl;
		std::cout << "SubSysId - 0x" << (*it)->SubSysId << std::endl;
		std::cout << std::dec;
		std::cout << "Revision - " << (*it)->Revision << std::endl;
		std::cout << "Dedicated video memory = " << (*it)->DedicatedVideoMemory << " bytes (" << (*it)->DedicatedVideoMemory/1024/1024 << "Mb)" << std::endl;
		std::cout << "Dedicated system memory = " << (*it)->DedicatedSystemMemory << " bytes (" << (*it)->DedicatedSystemMemory/1024/1024 << "Mb)" << std::endl;
		std::cout << "Shared system memory = " << (*it)->SharedSystemMemory << " bytes (" << (*it)->SharedSystemMemory/1024/1024 << "Mb)" << std::endl;
		std::cout << std::endl;
	}
}

