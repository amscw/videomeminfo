/*
 * grfxInfo.h
 *
 *  Created on: 31 мар. 2018 г.
 *      Author: Alex
 */

#ifndef GRFXINFO_H_
#define GRFXINFO_H_

#include <iostream>
#include <memory>
#include <vector>
#include "windows.h"
#include "D3D10.h"
#include "exc.h"

//----------------------------------------------------------------------------
// Исключение
//----------------------------------------------------------------------------
struct grfxExc_c : public exc_c
{
	static const std::string errmsgs[];

    enum class errCode_t : std::uint32_t
    {
         ERR_OK
        ,ERR_WDDMCHECKFAIL
		,ERR_CREATE_DXGIFACTORY
		,ERR_GET_DXGIADAPTERDESC
		,ERR_NO_ADAPTERS_FOUND
		,ERR_UNKNOWN_VENDOR
    } m_errCode;


    grfxExc_c(enum errCode_t errCode, std::string filename, std::string funcname, std::string descrmsg="") :
        exc_c(filename, funcname, descrmsg), m_errCode(errCode)
    {}

    const std::string &Msg() const { return errmsgs[static_cast<std::uint32_t>(m_errCode)]; }

    void ToStderr() const
    {
        std::cerr << "WTF:" << m_filename << "(" << m_funcname << "):" << Msg() <<
                "-" << m_descrmsg << std::endl;
    }
};

//----------------------------------------------------------------------------
// Оснвной информационный класс
//----------------------------------------------------------------------------
class grfxInfo_c
{
	using desc_t = std::unique_ptr<DXGI_ADAPTER_DESC>;
	using it_t = std::vector<desc_t>::iterator;

	// Функтор для поиска нужного DXGI_ADAPTER_DESC
	struct IsMatch : public std::unary_function<desc_t, bool>
	{
	    bool operator()(const desc_t &desc) const
	    {
	        return desc->VendorId == m_nVendorId;
	    }
	    IsMatch(UINT VendorId) : m_nVendorId(VendorId) {}

	private:
	    UINT m_nVendorId;
	};


	IDXGIFactory *m_pFactory = nullptr;
	std::vector<std::unique_ptr<DXGI_ADAPTER_DESC>> m_dxgiDescriptors;

public:
	grfxInfo_c();
	~grfxInfo_c();

	std::size_t RetrieveDXGIDescriptors();
	SIZE_T DedicatedVideoMemory(UINT VendorId);
	SIZE_T SharedSystemMemory(UINT VendorId);
	void Show() noexcept;

private:
	void checkWDDMDriver();
	void createIDXGIFactory();
};



#endif /* GRFXINFO_H_ */
