////////////////////////////////////////////////////////
// Project	: HuSMPPClient(SMPPRouter)
// Module	: error.h
// Author	: Pavel Alexeev
////////////////////////////////////////////////////////

#pragma once

#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <string>

class CError
{
public:
  CError(const std::string& err = "") : m_Error(err) {}
  virtual ~CError() {}
  
  const std::string& GetDescription(){
  return m_Error;
  }

protected:
  std::string m_Error;
};


class BindFailed : public CError{ //For exceptions
public:
	BindFailed (const std::string& err = "") : CError(err){}
//int err_code;
//BindFailed (int err_f = 0) {err_code = err_f;}
};

class ConnectFailed : public CError{ //For exceptions
public:
	ConnectFailed (const std::string& err = "") : CError(err){}
//int err_code;
//BindFailed (int err_f = 0) {err_code = err_f;}
};


#endif
// =================== END OF THE FILE =================
////////////////////////////////////////////////////////
