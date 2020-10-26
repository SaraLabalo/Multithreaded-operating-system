#include "system.h"
#include "idlethr.h"
#include "pcb.h"
#include <iostream.h>
#include "thread.h"

//==========================KONSTRUKTOR=============================
IdleThread::IdleThread(): Thread(1024, 1) {

}
//==========================RUN=============================
void IdleThread::run() {

	while(1){

	}
}
//==========================METODE=============================


void IdleThread::start() {
	lock();

	myPCB->state = PCB::READY;



	myPCB->createStack();
	//isto kao kod treda samo smo redefinisali posto ne smemo daje stavljamo u scheduler
	unlock();

}

