/*
 * grfxInfo.h
 *
 *  Created on: 31 мар. 2018 г.
 *      Author: Alex
 */

#ifndef GRFXINFO_H_
#define GRFXINFO_H_
#include "windows.h"
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

	LPDIRECT3DCREATE9EX pD3D9Create9Ex = nullptr;

public:
	grfxInfo_c() throw(grfxExc_c);

private:
	void checkWDDMDriver() throw (grfxExc_c);
};



#endif /* GRFXINFO_H_ */
