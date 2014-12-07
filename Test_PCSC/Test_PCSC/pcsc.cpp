#include "pcsc.h"



pcsc::pcsc()
{
}


pcsc::~pcsc()
{
}

long pcsc::Connection_PCSC(LPTSTR sReader)
{
	LPTSTR          pmszReaders = NULL;
	LPTSTR          pszReader;
	LPTSTR			pszaReaders[16];
	DWORD           cch = SCARD_AUTOALLOCATE;
	int				iNumberOfReaders;
	int 			iSelectedReader;

	lRetValue = SCardEstablishContext(
		SCARD_SCOPE_USER, // Scope of the resource manager context.
		NULL,             // r.f.u
		NULL,             // r.f.u
		&m_hContext);	 // Returns the resource manager handle.
	
	// On appel la méthode pour savoir le status
	Status_PCSC(lRetValue, "SCardEstablishContext");

	//LPTSTR Test = sReader;
	if (sReader != NULL)
	{
		strcpy_s(m_szSelectedReader, (char*)sReader );
		return lRetValue;
	}

	// The SCardListReaders function provides the list of readers 
	lRetValue = SCardListReaders(
		m_hContext,             // Resource manager handle. 
		NULL, // NULL: list all readers in the system 
		(LPTSTR)&pmszReaders, // Returs the card readers list.
		&cch);
		Status_PCSC(lRetValue, "SCardListReaders");

	iNumberOfReaders = 0;
	
	pszReader = pmszReaders;
	/*wstring reader = pszReader ; 
	cout << reader  <<endl ; */
	
	
	
	cout << endl ;// retour a la ligne supplémentaire 

	// Extract the reader strings form the null separated string and 
	// get the total number of readers.
	while (*pszReader != '\0')
	{
		printf("%s", pszReader);
		pszaReaders[iNumberOfReaders] = (LPTSTR)pszReader;
		pszReader = pszReader + strlen((char*)pszReader) + 1;
		iNumberOfReaders++;
	}
	
	cout << endl ;// retour a la ligne supplémentaire 
	
	

	return lRetValue;
}


long pcsc::Status_PCSC(long Value,char* msg)
{
	// Si la connection est OK :
	if (Value == SCARD_S_SUCCESS)					  
	{													  
		cout<<"\n   " <<msg<<  ": " <<SCardGetErrorString(Value)<<endl;		  
	}		
	// Sinon , on affiche une erreur :
	else												  
	{												  
		cout<<"\n   " <<msg<<  ": Error 0x%04X "<<Value<<" "<< SCardGetErrorString(Value)<<endl; 
		return Value;								  
	}
}

// a traduire : 
char*  pcsc::SCardGetErrorString(long ErrorValue)
{
	switch (ErrorValue)
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
