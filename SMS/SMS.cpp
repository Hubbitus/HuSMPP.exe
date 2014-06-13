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

	//����������� (�� UCS2-�������, �� 2 �����!)
	for(std::string::size_type i=0; i<strLength; i+=sizeof(WORD)){
	bufCode[0] = input[i];
	bufCode[1] = input[i+1];
	WORD code = *( ( WORD* ) bufCode );
	code = ntohs (code);
		//���������� ������� ��������������
		if((code >> 8) == 4){ // russian symbol
			if(code == 1025) code = 168; // �
			else if(code == 1105) code = 184; // �
			else code -= 848; // all other symbols �-�, �-�
		}

		/*
		char ch = (code & 0xFF);
		code & 0xFF ������ ��� ���� ����� �� ���� ������ ���������� � �������� ����
		��� ������������ � ����������� ������, ��� �� �������� � ����������
		������������������, � ����������� ��������� ��� �����������
		*/
		//�������������� � ������������ char
		//char ch = char(code);
		unsigned char ch = 0;
		if ( (ch = (char)(code & 0xFF)) != code ){
		//������ ����� ������ �� �������, ��� �� ������������� � CP1251, ����� ������� ��� � <#1234#>
		CString buf;
		buf.Format(_T("%d"), ch);
		Result += "<#" + buf + "#>";
		}
		else {
			if((ch >= 0) &&  (ch < ' ')) ch = '?';//�������� ������������, ���� ���, �� ���� ������� �����
		Result += ch;
		}
	}

return Result;
}

//////////////////////////////////////////////////////////////////
/*�������� UCS2toCP1251 */
std::string SMS::CP1251toUCS2 (std::string input){
//char bufCode[2];
std::string::size_type strLength = input.length();
std::string Result = "";

	//�����������
	for(std::string::size_type i=0; i<strLength; i++){
	WORD code = (unsigned char)input[i];

		if ( code >= 192 /* 0x0410 UCS2 */ || code == 168 || code == 184){//Russian symbols
			//���������� ������� ��������������
			if(code == 168) code = 1025; // �
			else if(code == 184) code = 1105; // �
			else code += 848; // all other symbols �-�, �-�
		}
	Result += (char)(code >> 8);
	Result += (char)(code & 0x00FF);
	}

return Result;
}

//////////////////////////////////////////////////////////////////
/*��������� ������������� �������� 0b � int, ������ � 11*/
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
/*������, ��������� �������������, � ��������. ������ ������ - ����� �������, ���-�� ����� ������:
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
