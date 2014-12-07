#pragma once
#include <winscard.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>
#include <Windows.h> 
using namespace std; 



class pcsc
{
private :
	SCARDCONTEXT		m_hContext;				 
	SCARDHANDLE			m_hCard;				   
	DWORD				m_dwActiveProtocol;
	CHAR				m_szSelectedReader[256];
	long				lRetValue;
	BYTE				baResponseApdu[300];	
public:
	pcsc();
	~pcsc();
	
	//gere la connection : 
	long Connection_PCSC(LPTSTR);
	
	//renseigne le status : 
	long Status_PCSC(long, char*);
	
	//affiche les erreurs :  
	char*  SCardGetErrorString(long);

};

