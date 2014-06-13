////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: stringUtils.cpp
// Author	: Pavel Alexeev
// Created	: 2007-11-07 11:47
//
//	2008-08-29
//	- DDX_Check() function moved to afx_bool.h
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stringUtils.h"
#include <sstream>

namespace strUtils{
	////////////////////////////////////////////////////////
	std::string uint2str(unsigned long inInteger){
	std::ostringstream lStringOS;
	lStringOS << inInteger;
	return lStringOS.str();
	}

	////////////////////////////////////////////////////////
	std::string WORD2str(WORD inInteger){
	std::ostringstream lStringOS;
	lStringOS << inInteger;
	return lStringOS.str();
	}

	////////////////////////////////////////////////////////
	WORD string2WORD (std::string Str){
	std::istringstream lStringOS;
	WORD retVal;
	lStringOS >> retVal;
	return retVal;
	}

	////////////////////////////////////////////////////////
	//http://64.233.183.104/search?q=cache:seOTNaSIkiIJ:www.experts-exchange.com/Programming/Languages/CPP/Q_21846537.html+std::replace&hl=ru&ct=clnk&cd=3&gl=ru
	std::string replaceAll (const std::string& input, const std::string& sold, const std::string& snew){
	std::string output = input;
	size_t pos = 0;
	size_t lpos = 0;
		while ((pos = output.find(sold, lpos)) != std::string::npos){
		output.replace(pos, sold.length(), snew);
		lpos = pos+ 1 + snew.length();
		}
	return output;
	}
}//namespace strUtils
