/*
 * exc.h
 *
 *  Created on: 31 мар. 2018 г.
 *      Author: Alex
 */

#ifndef EXC_H_
#define EXC_H_


#include <exception>

struct exc_c /* : public std::exception*/
{
	std::string m_filename;
	std::string m_funcname;
	std::string m_descrmsg;

	exc_c(std::string filename, std::string funcname, std::string descrmsg = "") :
		m_filename(filename), m_funcname(funcname), m_descrmsg(descrmsg)
	{}
	virtual ~exc_c(){}
	virtual const std::string &Msg() const = 0;
    const std::string &Description() const {return m_descrmsg; }
	virtual void ToStderr() const = 0;
};


#endif /* EXC_H_ */
