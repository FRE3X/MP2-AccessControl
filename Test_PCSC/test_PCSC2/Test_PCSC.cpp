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
	
	LPWSTR			monreader;
	

	//LPDWORD			size;
	
	////////////////connection////////////////
	lRetValue = SCardEstablishContext(
		SCARD_SCOPE_USER, // Le contexte est un contexte utilisateur, et toutes les opérations de base sont effectuées dans le domaine de l'utilisateur.
		NULL,             
		NULL,             
		&m_hContext);	 // Adresse du buffer ou on stocke le context récupéré

	if(lRetValue == 0){
		cout << "Connection ok" << endl ;
	}else
	{
		cout << "Erreur : " << lRetValue ; 
	}
	
	/*

	////////////////lecture ////////////////
	//methode récupérant le nom du lecteur connecter : 
	lRetValue = SCardListReaders(
                    m_hContext,             // Resource manager handle. 
                    NULL, // NULL: list all readers in the system 
                    (LPTSTR)&pmszReaders, // Returs the card readers list.
                    &cch );

	LPTSTR monbuffer = pmszReaders; 
	int i = 0; 
	while (i != strlen(pmszReaders))
	{
		//monbuffer[i] = pmszReaders[i];
		cout << pmszReaders[i] << endl; 
		i++; 
	}
	getchar();
	
	*/

	////////////////recuperation UID ////////////////
	BYTE commande[] = {0xFF,0xCA,0x00,0x00,0x0A}; 
	SCARDHANDLE		hcard ;
	DWORD			taille = 0x05;  
	BYTE			reception[30];
	LPDWORD			tailleReception; 
	
	lRetValue = SCardTransmit(hcard,NULL,commande,taille,NULL,reception,tailleReception);
	
	getchar();
}