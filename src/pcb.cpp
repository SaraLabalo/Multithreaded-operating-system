

#include "schedule.h"
#include <dos.h>

#include "pcb.h"

#include "system.h"
#include <stdlib.h>
#include<iostream.h>

class System;



//konstruktor
PCB::PCB(Thread* myT, StackSize stackSize, Time timeSlice):myThread(myT),pcbStackSize(stackSize),pcbTimeSlice(timeSlice),pcbSP(0),state(NEW),timePassedCounter(0) {
	lock();
	pcbID = ID++;
	waitQueue = new Queue();
	unlock();
}

int PCB::returnID() {
	return pcbID;
}

PCB::~PCB() {
	lock();

	delete waitQueue;
	delete pcbSP;

	unlock();
}

static int n;

//kreiranje pocetnog steka niti
void PCB::createStack() {

	lock();

	//alociramo kao unsigned
	n = this->pcbStackSize/2;

	unsigned * st1 = new unsigned[n];
	this->pcbSP = (unsigned *)st1;

	st1[n-1] = 0x200; //PSw sa setovanim I bitom
	st1[n-2] = FP_SEG(&(System::wrapper)); //wrapper pozivamo polimorfno run pc
	st1[n-3] = FP_OFF(&(System::wrapper));
	// sledecih devet je ya programsko dostupne registre ali nije bitna njihova vrednost
	this->sp = FP_OFF(st1+n-12);
	this->ss = FP_SEG(st1+n-12);


	unlock();


	}









