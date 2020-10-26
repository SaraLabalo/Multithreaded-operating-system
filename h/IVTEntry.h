/*
 * IVTEntry.h
 *
 *  Created on: May 4, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "KernelEv.h"
#include "thread.h"//peca
#include "system.h"
#include "Event.h"



typedef void interrupt(*pInterrupt)(...);


class KernelEv;

class IVTEntry{
public:
	IVTEntry( int ivtNo,pInterrupt newIR);
	~IVTEntry();


	pInterrupt oldIR;
	static IVTEntry* IVTTable[256];
	int ivtNo1;
	KernelEv* event;

	void callOldRoutine();
	void signal();
};

#endif /* IVTENTRY_H_ */
