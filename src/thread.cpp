#include "system.h"
#include "pcb.h"
#include "thread.h"
#include "schedule.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>;

class Scheduler;
class System;
static int starts = 0;


Thread::Thread(StackSize s, Time t) {
	TimeSlice=t;
	stackSize=s;
	lock();
	myPCB = new PCB(this, stackSize,TimeSlice);
	unlock();
}
Thread::~Thread() {
	lock();
	waitToComplete();
	delete myPCB;
	unlock();
}

void Thread::start() {
	lock();
	// Pravimo stek i njegov kontekst
	myPCB->createStack();
	myPCB->state = PCB::READY;
	// ubacujemo u scheduler na red spremnih
	Scheduler::put(myPCB);

	unlock();
}


void Thread::waitToComplete() {
	lock();

	// ne smemo na samom sebi da pozovemo
		if(myPCB == (PCB*)System::running) {
			unlock();
			return;
		}
		// ne smemo na idle
		if(this == System::idle) {
			unlock();
			return;
		}
		// ne smemo na starting inace deadlock
		if(this == System::starting) {
			unlock();
			return;
		}

		if (myPCB->state == PCB::NEW || myPCB->state == PCB::OVER)
			{
				unlock();
				return;
			}

		//podesiti stanje niti na blokirano
				System::running->state = PCB::BLOCKED;
		//ubacujemo nit u red za cekanje
				myPCB->waitQueue->put((PCB*)System::running);

				dispatch();

		unlock();
}

void dispatch() {
	lock();
	System::dispatched=1;
	System::timerIR();
	System::dispatched=0;
	unlock();
}

//void tick() {}; //

ID Thread::getId(){
	lock();
	if(myPCB == 0){
		unlock();

		return -1;
	}
	unlock();

	return myPCB->pcbID;

}

ID Thread::getRunningId(){
	lock();
	if(System::running->myThread!=0){
		unlock();
		return System::running->pcbID;

	}
	unlock();
	return -1;

}








