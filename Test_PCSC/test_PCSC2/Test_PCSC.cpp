#include <winscard.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>

using namespace std ; 
void main(){
	LPTSTR          pmszReaders = NULL;
	LPTSTR          pszReader;
	LPTSTR			pszaReaders[16];
	DWORD           cch = SCARD_AUTOALLOCATE;
	int				iNumberOfReaders;
	int 			iSelectedReader;
	SCARDCONTEXT		m_hContext;	
	long				lRetValue;

	lRetValue = SCardEstablishContext(
		SCARD_SCOPE_USER, // Scope of the resource manager context.
		NULL,             // r.f.u
		NULL,             // r.f.u
		&m_hContext);	 // Returns the resource manager handle.

	cout << lRetValue << endl ; 
}