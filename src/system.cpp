#include "system.h"
#include "schedule.h"
#include <dos.h>
#include <iostream.h>
#include <stdlib.h>
#include "pcb.h"

#include "IVTEntry.h"


volatile char System::dispatched = 0;
void interrupt (*System::oldRoutine)(...) =0;
volatile PCB* System::running = 0;
Thread* System::starting = 0;
IdleThread* System::idle = 0;
ListaSem * KernelSem::sviSemafori=new ListaSem();

System::System() {
	// TODO Auto-generated constructor stub

}

System::~System() {
	// TODO Auto-generated destructor stub
}

void System::load() {
	lock();
	

	//staru prekidnu rutinui cuvamo u oldRoutine
	//0x08 ulaz PC u IVT
	oldRoutine = getvect(0x08);
	//postavljamo novu rutinu
	//unosimo nasu prekidnu rutinu na mesto sistemskog brojaca od timera, ulaz 8
	setvect(0x08, timerIR);
	//Starting nit daje koncept nasoj pocetnoj main niti
	starting = new Thread(0x10000, 1);

	starting->myPCB->state = PCB::READY;

	running = (volatile PCB*)starting->myPCB;
	//nit koja radi kad ni jedna druga ne postoji u scheduleru
	idle = new IdleThread();
	idle->start();


	unlock();
}

void System::unload() {

	if( (PCB*)running != starting->myPCB ) {
		return;
	}
	lock();
	setvect(0x08, oldRoutine); // vracamo staru prekidnu rutinu
	// DEALOCIRAJ SVE
	delete starting;
	delete idle;
	delete KernelSem::sviSemafori;
	unlock();
}


void System::dispatch() {
	lock();
	//flag koji govori da je prekid pozvan eksplicitno, ako je 0 poziva na takt
	dispatched=1;
	timerIR();
	dispatched=0;
	unlock();
}

void interrupt System::timerIR(...) {

	static volatile unsigned int tsp, tss,tbp;
	static volatile PCB *newThread;

	//pozovi staru prekidnu rutinu
	if(!dispatched ) {
		KernelSem::decreaseTime();
		tick();
		(*oldRoutine)();
	}

	asm { cli };
	//ako je prekid i timeSlice nije nula (beskonacno vreme za nit) treba podesiti brojac
	if (!dispatched && running->pcbTimeSlice != 0)
		running->timePassedCounter += 1;
	//ako nije eksplicitno trazen dispatch() i nije proteklo vreme vrati se
	if (!dispatched && (running->timePassedCounter < running->pcbTimeSlice || running->pcbTimeSlice == 0) ) return;
	//resetujemo flag za eksplicitno preuzimanje ukoliko je bio setovan
	dispatched = 0;
	//ako je nit spremna i nije idle vracam je u Scheduler
	if( running->state == PCB::READY && running != idle->myPCB )
		Scheduler::put((PCB*)running);

	newThread = Scheduler::get();
			if (newThread == 0) newThread = idle->myPCB;
		asm {
			mov tsp, sp
			mov tss, ss

		}

		running->sp = tsp;
		running->ss = tss;
		running->bp = tbp;
		running = newThread;
		tsp = running->sp;
		tss = running->ss;


		asm {
			mov sp, tsp
			mov ss, tss

		}

		running->timePassedCounter = 0;
	return;
}

void System::wrapper() {
	//pokrece se nit
	System::running->myThread->run();
	//nit se zavrsila
	lock();

	//markiramo je kao gotovu
	running->state = PCB::OVER;

	PCB* temp;
	//kada dete odblokira sve koje je cekaju u svom redu blokiranih
	while( running->waitQueue->duz > 0 )
	{
		temp =running->waitQueue->get();
		temp->state = PCB::READY;
		Scheduler::put(temp);
	}
	//prelazak na drugu nit
	unlock();
	dispatch();

}
