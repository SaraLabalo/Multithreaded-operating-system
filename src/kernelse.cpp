/*
 * kernelse.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#include "kernelse.h"
#include "queue.h"
#include "listaSem.h"

#include"system.h"
#include"schedule.h"


extern int syncPrintf (const char* format, ... );

KernelSem::KernelSem(int init) {
	lock();
	value=init;
	waitQ= new Queue();
	timeQ= new Queue();

	sviSemafori->put(this);
	unlock();
}

KernelSem::~KernelSem() {
	lock();

	delete waitQ;
	delete timeQ;

	sviSemafori->deleteSem(this);
	unlock();
}

int KernelSem::val() const {

	return value;

}

int KernelSem::wait(Time vremeCekanja){
	lock();

	System::running->povratnaVrednost=1;
	int brniz=1;
	value--;

	if(value<0){
		System::running->state=PCB::BLOCKED;

		//bude se ili na vreme ili na signal ali tek posto je waitQ prazan

		if(vremeCekanja>0){
			//s
			if (brniz!=0){
			brniz=0;
			}

			System::running->myTimeBlocked=vremeCekanja;
			timeQ->put((PCB *)System::running);
		}
		//bude se samo na signal
		else if(vremeCekanja==0){
			//s
			if (brniz!=0){
				brniz=0;
			}

			waitQ->put((PCB *)System::running);
		}
	//promena konteksta
		unlock();
	System::dispatch();

	}else{
		unlock();
	}


	return System::running->povratnaVrednost;
}
int KernelSem::signal(int n){
	lock();
	int brniz=1;
	if(n==0){
		value++;
		if(value<=0){

			//ako je wait
			if(waitQ->duz!=0){
				//s
				if (brniz!=0){
				brniz=0;
				}
				PCB* nit=waitQ->get();
				nit->povratnaVrednost=1;
				nit->state=PCB::READY;
				Scheduler::put(nit);
			}else{
				//s
				if (brniz!=0){
				brniz=0;
				}


				PCB* nit=timeQ->get();
				nit->povratnaVrednost=1;
				nit->state=PCB::READY;
				Scheduler::put(nit);
			}
		}
		unlock();
		return 0;
	}
	//odblokirati n niti
	else if(n>0){

			int brOdblokiranih=0;
			for(int i=0;i<n;i++){
				value++;

				if(value<=0){

					if(waitQ->duz!=0){

						//s
						if (brniz!=0){
							brniz=0;
							}

									PCB* nit=waitQ->get();
									nit->povratnaVrednost=1;
									nit->state=PCB::READY;
									Scheduler::put(nit);
					}else{

						//s
						if (brniz!=0){
							brniz=0;
							}

									PCB* nit=timeQ->get();
									nit->povratnaVrednost=1;
									nit->state=PCB::READY;
									Scheduler::put(nit);
					}
					brOdblokiranih++;
				}
			}
			unlock();
			return brOdblokiranih;
		}

	else{
		unlock();
		return n;
	}

}
void KernelSem::decreaseTime(){
	lock();
	int brniz=1;

	ElemS *curr;

	for(curr=sviSemafori->prvi;curr!=0;curr=curr->sled){

		Elem *tek= curr->sem->timeQ->prvi;

		while(tek!=0){

			if(tek->pcb->myTimeBlocked>0){

				tek->pcb->myTimeBlocked=tek->pcb->myTimeBlocked-1;

			}

		if(tek->pcb->myTimeBlocked==0){

			//s
			if (brniz!=0){
				brniz=0;
			}


				tek->pcb->state=PCB::READY;
				tek->pcb->povratnaVrednost=0;
				Scheduler::put(tek->pcb);
				curr->sem->timeQ->ObrisiPoPcb1(tek->pcb);
				curr->sem->value++;



			}


					//s
					if (brniz!=0){
						brniz=0;
					}

			tek=tek->sled;
		}

	}


	unlock();
}
