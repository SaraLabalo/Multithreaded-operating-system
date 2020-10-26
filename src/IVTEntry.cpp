/*
 * IVTEntry.cpp
 *
 *  Created on: May 4, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "system.h"
#include "Event.h"
#include <dos.h>

IVTEntry* IVTEntry::IVTTable[256];

IVTEntry::IVTEntry(int ivtNo,pInterrupt newIR) {
	lock();

	event=0;
	ivtNo1=ivtNo;

	oldIR = getvect(ivtNo);
	setvect(ivtNo, newIR);

	IVTTable[ivtNo]=this;

	unlock();
}

IVTEntry::~IVTEntry() {
	lock();


	setvect(ivtNo1, oldIR);

	//IVTTable[ivtNo1] = 0;

	unlock();
}

void IVTEntry::signal(){

//ne mora lock()
	if(event){
		event->signal();
	}

}

void IVTEntry::callOldRoutine() {

	oldIR();

}
