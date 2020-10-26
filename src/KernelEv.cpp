/*
 * KernelEv.cpp
 *
 *  Created on: May 4, 2020
 *      Author: OS1
 */
#include "IVTEntry.h"
#include "KernelEv.h"
#include "system.h"
#include "event.h"
#include "SCHEDULER.h"

KernelEv::KernelEv(IVTNo ivtNo) {

	ivtNo1=ivtNo;

		boss=(PCB*)System::running;

		mySem = new KernelSem(0);

		IVTEntry::IVTTable[ivtNo]->event=this;





}

KernelEv::~KernelEv() {

	IVTEntry::IVTTable[ivtNo1]->event=0;
	delete mySem;

}

void KernelEv::wait(){
	lock();

	if((PCB*)System::running==boss){
		mySem->wait(0);
	}

	unlock();



}

void KernelEv::signal(){
lock();
	if (mySem->value==1) {

		unlock();
		return;

	}

		mySem->signal(0);
		unlock();


}
