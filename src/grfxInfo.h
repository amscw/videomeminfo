/*
 * grfxInfo.h
 *
 *  Created on: 31 мар. 2018 г.
 *      Author: Alex
 */

#ifndef GRFXINFO_H_
#define GRFXINFO_H_
#include "windows.h"
#include <D3D9.h>
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
		,ERR_CREATE_IDIRECT3D9EX
		,ERR_CREATE_IDIRECT3DDEVICE
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
	// Define a function pointer to the Direct3DCreate9Ex function.
	typedef HRESULT (WINAPI *LPDIRECT3DCREATE9EX)( UINT, void **);

	HMODULE hD3D9;
	LPDIRECT3DCREATE9EX pD3D9Create9Ex = nullptr;
	IDirect3D9Ex *pD3D = nullptr;
	IDirect3DDevice9Ex *pDevice = nullptr;

public:
	grfxInfo_c();
	~grfxInfo_c();

	void CheckWDDMDriver();
	void CreateD3DDevice(HWND hWnd);
};



#endif /* GRFXINFO_H_ */
