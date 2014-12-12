#include <winscard.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>

using namespace std ;
//#define Macro_Status(lRetValue,msg)
//if(lRetValue == SCARD_S_SUCCESS){}else{}

void main(){
	char*         pmszReaders = NULL;
	LPTSTR          pszReader;
	char		pszaReaders[16];
	DWORD           cch = SCARD_AUTOALLOCATE;
	int				iNumberOfReaders;
	int 			iSelectedReader;
	SCARDCONTEXT		m_hContext;	
	long				lRetValue;
	SCARDHANDLE			m_hCard;
	DWORD				m_dwActiveProtocol;
	char				m_szSelectedReader[256] = {'A','C','S',' ','A','C','R','1','2','2',0};// nom du lecteur
	LPWSTR			monreader;
	

	//LPDWORD			size;
	
	////////////////Etablisement du context////////////////
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
		

	////////////////recuperation du nom ////////////////
	//methode récupérant le nom du lecteur connecter : 
	lRetValue = SCardListReaders(
                    m_hContext,             // Resource manager handle. 
                    NULL, // NULL: list all readers in the system 
                    (LPTSTR)&pmszReaders, // Returs the card readers list.
                    &cch );
	
	iNumberOfReaders = 0;
	


	while ( *pszReader != '\0' )
	{
		printf("\n      Reader [%2d] %s", iNumberOfReaders, pszReader);
		pszaReaders[ iNumberOfReaders ] = *pszReader;// = (LPTSTR)pszReader;
		pszReader = pszReader + strlen((char*)pszReader) + 1;
		iNumberOfReaders++;
	}
	byte* PtChar;
	byte Valeur;
	WORD *PtWord;
	PtChar = (byte*)pmszReaders;
	PtWord = (WORD*)pmszReaders;
	PtChar++;
	PtChar++;	

	Valeur = (byte)*PtWord;
	PtWord++;
	Valeur = (byte)*PtWord;
	PtWord++;
	Valeur = (byte)*PtWord;

	getchar();
	
	//strcpy(m_szSelectedReader, (char*)pszaReaders[0]);

	////////////////connection ////////////////
	lRetValue = SCardConnect( 
                    m_hContext, // Resource manager handle.
					(LPCWSTR)m_szSelectedReader,     // Reader name.
					SCARD_SHARE_EXCLUSIVE,  // Share Mode.
					SCARD_PROTOCOL_Tx, //Preferred protocols (T=0 or T=1).
					&m_hCard,               // Returns the card handle.
					&m_dwActiveProtocol);
	

	////////////////recuperation UID ////////////////
	BYTE commande[] = {0xFF,0xCA,0x00,0x00,0x0A}; 
	DWORD			taille = 0x05;  
	BYTE			reception[30];
	DWORD			tailleReception =6; 
	
	lRetValue = SCardTransmit(m_hContext,NULL,commande,taille,NULL,reception,&tailleReception);
	
	getchar();
}