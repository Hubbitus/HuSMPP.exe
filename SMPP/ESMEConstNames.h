////////////////////////////////////////////////////////
// Project : HuSMPP
// Module  : ESMEConstNames.h
// Author  : Pavel Alexeev (Pahan-Hubbitus)
// Date    : 2008-07-21
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include <string>
#include <map>

////////////////////////////////////////////////////////

class ESMEConstNames{
public:
	ESMEConstNames(void);
	~ESMEConstNames(void);

	std::string operator[] ( DWORD index ){ return names_[ index ]; };
private:
	std::map<DWORD, std::string> names_;
};
