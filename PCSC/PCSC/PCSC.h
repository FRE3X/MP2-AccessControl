#pragma once
#include <winscard.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>


using namespace std;
class PCSC
{
	long*				ReturnValue;		// valeur de retour des fonction si 0 = ok
	SCARDCONTEXT		Context;			// Adresse du buffer ou on stocke le context r�cup�r�
	char*				ListCardReader;		// pointeur sur la premiere case du tableau alloue.
	SCARDHANDLE			Cardhandle;			// ou est stocker le Handle de la carte
	DWORD				Size_CardReader;	// taille du buffer de CardReader
	DWORD				ActiveProtocol;
	WORD*				BuffNameReader;		//Buffer pour placer le nom	
	wchar_t				nameCardreader[256];//nom du lecteur choisie
	LPCSCARD_IO_REQUEST Request;			//Pointeur sur le protocole d'envoie
	BYTE				Commande[5];		//Commande pour retourner UID 
	BYTE                ResponseUID[300];
	DWORD				SizeReponse; 
public:
	PCSC(void);
	~PCSC(void);
	
	void	Status();			// m�thode pour v�rifier s'il n'a pas eu de probl�me lors de l'�x�cution
	void	Etablish_context(); //m�thode pour etablir le context
	void	GetCardReader();	//m�thode pour recuperer le nom du lecteur
	void	Connect();			//m�thode permettant de ce connecter a la carte 
	void	Transmit();			//m�thode permettant de r�cup�rer l'uid
	char*	ErrorString(long);	// m�thode permettant d'avoir des renseignement sur l'erreur
};

