////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : SMS.cpp
// Pavel Alexeev
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMS.h"

SMS::SMS(){
isParsed = false;
}

//////////////////////////////////////////////////////////////////
SMS::~SMS(void){

}

//////////////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
SMS::GetOptionalParameter (WORD paramID){
//return m_pdu->GetOptionalParameters()->GetParameter(paramID);
	CH<IPDUOptionalParameters> opts = m_pdu->GetOptionalParameters();
	CH<IPDUOptionalParameter> retVal = opts->GetParameter(paramID);
	return retVal;
}

//////////////////////////////////////////////////////////////////
long
SMS::GetlOption(){
	if (isNoOption()) return NoOption;
long lOption = NoOption;
/*
0	(00000000): Normal SMS messages
2	(00000010): Delivery notification
4	(00000100): Direct display messages
8	(00001000): 8bit encoded messages
16	(00010000): User Data Header (UDH, logo or ringing tone)
32	(00100000): Virtual SMSC
64	(01000000): Unicode messages
128	(10000000): EMS messages
*/
	if (isDeliveryNotification()) lOption += DeliveryNotification;
	if (isDirectDisplay()) lOption += DirectDisplay;
	if (is8bit()) lOption += Bin8bit;
	if (isUDH()) lOption += UDH;
	if (isVirtualSMSC()) lOption += VirtualSMSC;
	if (isUCS2()) lOption += UCS2;
	if (isEMS()) lOption += EMS;
return lOption;
}

//////////////////////////////////////////////////////////////////
std::string
SMS::UCS2toCP1251(std::string input){
char bufCode[2];
std::string::size_type strLength = input.length();
std::string Result = "";

	//Посимвольно (но UCS2-символы, по 2 байта!)
	for(std::string::size_type i=0; i<strLength; i+=sizeof(WORD)){
	bufCode[0] = input[i];
	bufCode[1] = input[i+1];
	WORD code = *( ( WORD* ) bufCode );
	code = ntohs (code);
		//собственно главное преобразование
		if((code >> 8) == 4){ // russian symbol
			if(code == 1025) code = 168; // Ё
			else if(code == 1105) code = 184; // ё
			else code -= 848; // all other symbols А-Я, а-я
		}

		/*
		char ch = (code & 0xFF);
		code & 0xFF ТОЛЬКО для того чтобы НЕ было ошибки приведения к меньшему типу
		как утверждается в возникающей ошибке, это НЕ приводит к уменьшению
		производительности, и оптимизатор нормально это преобразует
		*/
		//Преобразование в однобайтовый char
		//char ch = char(code);
		unsigned char ch = 0;
		if ( (ch = (char)(code & 0xFF)) != code ){
		//Тоесть сивол похоже не русский, или не преобразуется в CP1251, тогда выделим его в <#1234#>
		CString buf;
		buf.Format(_T("%d"), ch);
		Result += "<#" + buf + "#>";
		}
		else {
			if((ch >= 0) &&  (ch < ' ')) ch = '?';//Проверка корректности, если нет, то знак вопроса пишем
		Result += ch;
		}
	}

return Result;
}

//////////////////////////////////////////////////////////////////
/*Обратная UCS2toCP1251 */
std::string SMS::CP1251toUCS2 (std::string input){
//char bufCode[2];
std::string::size_type strLength = input.length();
std::string Result = "";

	//Посимвольно
	for(std::string::size_type i=0; i<strLength; i++){
	WORD code = (unsigned char)input[i];

		if ( code >= 192 /* 0x0410 UCS2 */ || code == 168 || code == 184){//Russian symbols
			//собственно главное преобразование
			if(code == 168) code = 1025; // Ё
			else if(code == 184) code = 1105; // ё
			else code += 848; // all other symbols А-Я, а-я
		}
	Result += (char)(code >> 8);
	Result += (char)(code & 0x00FF);
	}

return Result;
}

//////////////////////////////////////////////////////////////////
/*Текстовое представление например 0b в int, тоесть в 11*/
long
SMS::HexStringToBinInt(std::string S){
long res = 0;

	for(std::string::size_type i = 0; i < S.length(); i++){
	unsigned char ch = (unsigned char)tolower(S[i]);
		if(isdigit(ch))	res = res * 16 + (ch - '0');
		else res = res * 16 + (10 + ch - 'a');
	}
return res;
}

//////////////////////////////////////////////////////////////////
/*Строку, текстовое представление, в бинарное. Каждый символ - двумя байтами, что-то вроде такого:
0734534574DB74565A657FF
*/
std::string
SMS::HexStringToBinString(std::string input){
std::string Result;// = "";

	for(std::string::size_type i=0;i<input.length(); i+=2){
	int code = HexStringToBinInt(input.substr(i,2));
	char ch = char(code);
	Result = Result + ch;
	}
return Result;
}
