#pragma once
#include <winscard.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;
class PCSC
{
	long*				ReturnValue;		// valeur de retour des fonction si 0 = ok
	SCARDCONTEXT		Context;			// Adresse du buffer ou on stocke le context récupéré
	char*				ListCardReader;		// pointeur sur la premiere case du tableau alloue.
	SCARDHANDLE			Cardhandle;			// ou est stocker le Handle de la carte
	DWORD				Size_CardReader;	// taille du buffer de CardReader
	DWORD				ActiveProtocol;		// Stock le protocole d'activation recupérer T=1, T=0 ou Raw
	WORD*				BuffNameReader;		//Buffer pour placer le nom	
	wchar_t				nameCardreader[256];//nom du lecteur choisie
	LPCSCARD_IO_REQUEST Request;			//Pointeur sur le protocole d'envoie
	BYTE				Commande[5];		//Commande pour retourner UID 
	BYTE                ResponseUID[300];	//Buffer pour recupere UID
	DWORD				SizeReponse;		//Recupere la taille de L'UID
	SCARD_READERSTATE	ReaderState;		//Status du reader
	LPBYTE				BuffATR;			//Buffer pour la récupération de l'ATR  
	DWORD				SizeATR;			//taille du buffer
public:
	PCSC(void);
	~PCSC(void);
	
	void	Status();			// méthode pour vérifier s'il n'a pas eu de probléme lors de l'éxécution
	void	Etablish_context(); //méthode pour etablir le context
	void	GetCardReader();	//méthode pour recuperer le nom du lecteur
	void	WaitCard();			//Attend que la carte soit connecter au lecteur 
	void	Connect();			//méthode permettant de ce connecter a la carte 
	void	TransmitUID();	    //méthode permettant de récupérer l'uid
	char*	ErrorString(long);	// méthode permettant d'avoir des renseignement sur l'erreur
	void	GetATR();			//Récupére l'ATR de la carte 
};

