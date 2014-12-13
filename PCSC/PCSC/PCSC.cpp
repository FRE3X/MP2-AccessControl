#include "PCSC.h"

#define RcvLenMax 300l  
PCSC::PCSC(void)
{
	
	//Allocation dynamique 
	ReturnValue = new long;
	ListCardReader = new char;
	BuffNameReader = new WORD;
    
	


	ListCardReader = NULL ; 
	Size_CardReader = SCARD_AUTOALLOCATE;
	Request = SCARD_PCI_T1;
	SizeReponse = RcvLenMax; 
	
	//instanciation Commande : 
	Commande[0] = 0xFF;
	Commande[1] = 0xCA;
	Commande[2] = 0x00;
	Commande[3] = 0x00;
	Commande[4] = 0x00;

	//Appelle des methodes 
	Etablish_context();
	GetCardReader();
	Connect();
	Transmit(); 
}



void PCSC::Status(){
	if(*ReturnValue != 0x00)
	{
		cout <<	ErrorString(*ReturnValue) << endl ; 
	}
}


void PCSC::Etablish_context(){
	*ReturnValue = SCardEstablishContext(
		SCARD_SCOPE_USER, // Le contexte est un contexte utilisateur, et toutes les opérations de base sont effectuées dans le domaine de l'utilisateur.
		NULL,             
		NULL,             
		&Context); // Adresse du buffer ou on stocke le context récupéré
	Status(); 
}

void PCSC::GetCardReader(){
	int i = 0 ;
	 
	*ReturnValue = SCardListReaders(
					Context,             //Context récupérer
                    NULL, // si NULL liste tous les reader du system
					(LPTSTR)&ListCardReader, //retourne la liste des reader
					&Size_CardReader); //taille de celui-ci 
	Status();
	
	//Placement du Lecteur dans le wchar_t NameCardreader
	BuffNameReader = (WORD*)ListCardReader; 
	while (i  < Size_CardReader)
	{
		nameCardreader[i] = (byte)*BuffNameReader; 
		BuffNameReader++; 
		i++;
	}
}

void PCSC::Connect(){
	*ReturnValue = SCardConnect( 
					Context, // Adresse du buffer ou on stocke le context récupéré
					nameCardreader,     //nom du lecteur
					SCARD_SHARE_EXCLUSIVE,  // mode de partage
					SCARD_PROTOCOL_Tx, //protocole (T=0 ou T=1).
					&Cardhandle,               // retourn l'handle de la carte
					&ActiveProtocol);
	Status();
}

void PCSC::Transmit(){
	*ReturnValue = SCardTransmit(Cardhandle,		//handle.
							Request,		// Pointer vers le protocole
							Commande,	// La commande
							(DWORD)sizeof(Commande),	// taille de la commande
							NULL,			
							ResponseUID,	// buffer de reponse
							&SizeReponse);	// taille de la reponse 
	Status(); 

}

char* PCSC::ErrorString(long valeur){
	
	switch(valeur)
	{
        case 0x0l:
                return "SCard OK";
                break;

        case 0x80100001:
                return "SCard internal error";
                break;

        case 0x80100002:
                return "SCard cancelled";
                break;

        case 0x80100003:
                return "SCard invalid handle";
                break;

        case 0x80100004:
                return "SCard invalid parameter";
                break;

        case 0x80100005:
                return "SCard invalid target";
                break;

        case 0x80100006:
                return "SCard no memory";
                break;

        case 0x80100007:
                return "SCard waited too long";
                break;

        case 0x80100008:
                return "SCard insufficient buffer";
                break;

        case 0x80100009:
                return "SCard unknown reader";
                break;

        case 0x8010000a:
                return "SCard timeout";
                break;

        case 0x8010000b:
                return "SCard sharing violation";
                break;

        case 0x8010000c:
                return "SCard no smartcard";
                break;

        case 0x8010000d:
                return "SCard unknown card";
                break;

        case 0x8010000e:
                return "SCard cant dispose";
                break;

        case 0x8010000f:
                return "SCard proto mismatch";
                break;

        case 0x80100010:
                return "SCard not ready";
                break;

        case 0x80100011:
                return "SCard invalid value";
                break;

        case 0x80100012:
                return "SCard system cancelled";
                break;

        case 0x80100013:
                return "SCard communications error";
                break;

        case 0x80100014:
                return "SCard unknown error";
                break;

        case 0x80100015:
                return "SCard invalid atr";
                break;

        case 0x80100016:
                return "SCard not transacted";
                break;

        case 0x80100017:
                return "SCard reader unavailable";
                break;

        case 0x80100018:
                return "SCard p shutdown";
                break;

        case 0x80100019:
                return "SCard pci too small";
                break;

        case 0x8010001a:
                return "SCard reader unsupported";
                break;

        case 0x8010001b:
                return "SCard duplicate reader";
                break;

        case 0x8010001c:
                return "SCard card unsupported";
                break;

        case 0x8010001d:
                return "SCard no service";
                break;

        case 0x8010001e:
                return "SCard service stopped";
                break;

        case 0x8010001f:
                return "SCard unexpected";
                break;

        case 0x80100020:
                return "SCard icc installation";
                break;

        case 0x80100021:
                return "SCard icc createorder";
                break;

        case 0x80100022:
                return "SCard unsupported feature";
                break;

        case 0x80100023:
                return "SCard dir not found";
                break;

        case 0x80100024:
                return "SCard file not  ound";
                break;

        case 0x80100025:
                return "SCard no dir";
                break;

        case 0x80100026:
                return "SCard no file";
                break;

        case 0x80100027:
                return "SCard no access";
                break;

        case 0x80100028:
                return "SCard write too many";
                break;

        case 0x80100029:
                return "SCard bad seek";
                break;

        case 0x8010002a:
                return "SCard invalid chv";
                break;

        case 0x8010002b:
                return "SCard unknown res mng";
                break;

        case 0x8010002c:
                return "SCard no such certificate";
                break;

        case 0x8010002d:
                return "SCard certificate unavailable";
                break;

        case 0x8010002e:
                return "SCard no readers available";
                break;

        case 0x80100065:
                return "SCard warning unsupported card";
                break;

        case 0x80100066:
                return "SCard warning unresponsive card";
                break;

        case 0x80100067:
                return "SCard warning unpowered card";
                break;

        case 0x80100068:
                return "SCard warning reset card";
                break;

        case 0x80100069:
                return "SCard warning removed card";
                break;

        case 0x8010006a:
                return "SCard warning security violation";
                break;

        case 0x8010006b:
                return "SCard warning wrong chv";
                break;

        case 0x8010006c:
                return "SCard warning chv blocked";
                break;

        case 0x8010006d:
                return "SCard warning eof";
                break;

        case 0x8010006e:
                return "SCard warning cancelled by user";
                break;

        case 0x0000007b:
                return "SCard inaccessible boot device";
                break;

	default:
		return "invalid error code";

	}

}

PCSC::~PCSC(void)
{
	delete ReturnValue;
	delete ListCardReader;
	delete[] BuffNameReader;
	
}
