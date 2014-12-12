#include <winscard.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>

using namespace std; 

void main(){
	long lRetValue; // valeur de retour des fonction
	SCARDCONTEXT		m_hContext;	// Adresse du buffer ou on stocke le context récupéré
	char*				pmszReaders = NULL; // pointeur sur la premiere case du tableau alloue.
	DWORD				cch = SCARD_AUTOALLOCATE;//le nombre de caractere
	SCARDHANDLE			m_hCard;
	DWORD				m_dwActiveProtocol;
	
	wchar_t				m_szSelectedReader[256] = {'A','C','S',' ','A','C','R','1','2','2',' ','0',0};// nom du lecteur
	
	WORD *PtWord;
	byte Valeur; // La valeur de mon caractere
	
	////////////////Etablisement du context////////////////
	lRetValue = SCardEstablishContext(
		SCARD_SCOPE_USER, // Le contexte est un contexte utilisateur, et toutes les opérations de base sont effectuées dans le domaine de l'utilisateur.
		NULL,             
		NULL,             
		&m_hContext);	 // Adresse du buffer ou on stocke le context récupéré
	
	
	//verifications :
	if(lRetValue == 0){
		cout << "Connection ok" << endl ;
	}else
	{
		cout << "Erreur : " << lRetValue ; 
	}

	////////////////recuperation du nom ////////////////
	lRetValue = SCardListReaders(
                    m_hContext,             // Resource manager handle. 
                    NULL, // NULL: list all readers in the system 
                    (LPTSTR)&pmszReaders, // Returs the card readers list.
                    &cch );
	
	PtWord = (WORD*)pmszReaders; //initialisation de PtWord
	int i = 0;
	
	//affichage du nom :
	while (i < cch)
	{
		Valeur = (byte)*PtWord;
		cout << Valeur ;
		PtWord++;
		i++; 
	}
	cout << endl ; 

	////////////////connection ////////////////
	lRetValue = SCardConnect( 
                   m_hContext, // Adresse du buffer ou on stocke le context récupéré
					m_szSelectedReader,     // Reader name.
					SCARD_SHARE_EXCLUSIVE,  // Share Mode.
					SCARD_PROTOCOL_Tx, //Preferred protocols (T=0 or T=1).
					&m_hCard,               // Returns the card handle.
					&m_dwActiveProtocol);
	
	getchar(); 
}