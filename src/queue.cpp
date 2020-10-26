

#include "queue.h"
#include <stdlib.h>
#include "schedule.h"
#include "pcb.h"
#include "system.h"
#include "iostream.h"


//  KONSTRUKTOR
Queue::Queue() {
	lock();
	prvi = NULL;
	duz = 0;
	unlock();
}

//DESTRUKTOR
Queue::~Queue() {
	lock();
	deleteQueue();
	unlock();
}

void Queue::deleteQueue(){
	lock();
		Elem *old= new Elem;
		while (prvi) {
		old=prvi;
		prvi=prvi->sled;
		delete old;
		}
		prvi=0;
		duz=0;
	unlock();
}
//  GET I PUT
PCB* Queue::get() {
	lock();
	if (prvi==0) {
		unlock();
		return 0;

	}
	else{
		Elem* t=prvi;
		PCB *t_pcb=t->pcb;
		prvi=prvi->sled;

		duz--;


		unlock();
		return t_pcb;
	}
}


void Queue::put(PCB* pcb) {
	lock();
	Elem *novi=new Elem();
	Elem *tek;
	novi->sled=NULL;
	novi->pcb=pcb;
	if (!prvi){
		prvi=novi;
	}
	else{
		for(tek=prvi;tek->sled; tek=tek->sled);
		tek->sled=novi;
	}
	duz++;
	unlock();
}

// pronalazenje po IDu
PCB* Queue::PronajiPoId(int i) {
	lock();
		Elem* tek=prvi;
		while(tek){
			if(tek->pcb->pcbID != i){
				tek=tek->sled;

			}
			else{
				unlock();
				return tek->pcb;
			}
		}
			unlock();
			return 0;
}
Queue& Queue::ObrisiPoId(int i){
	lock();
		Elem *pret=NULL,*tek=prvi;
		while(tek && tek->pcb->pcbID!=i){
			pret=tek;
			tek=tek->sled;

		}
		if(tek){
			Elem* stari=tek;
			tek=tek->sled;
			if(pret){
				pret->sled=tek;

			}
			else {
				prvi=tek;
			}
			duz--;
			delete stari;
		}
		unlock();
		return *this;
}



void Queue::ObrisiPoPcb1(PCB* pcb){
	lock();
		Elem *pret=NULL,*tek=prvi;
		while(tek && tek->pcb!=pcb){
			pret=tek;
			tek=tek->sled;
		}
		if(tek){
			Elem* stari=tek;
			tek=tek->sled;
			if(pret){
				pret->sled=tek;
			}
			else {
				prvi=tek;
			}

			duz--;

			unlock();
			return;
		}
		unlock();
		return;

}

//sortiranje
void Queue::SortirajNeopadajuce(){
	lock();
	Elem *i, *j, *pom;
	for(i=prvi;i;i=i->sled){
		for(j=i->sled;j;j=j->sled){
			if(j->pcb->returnID()<i->pcb->returnID())
				pom=j;
				j=i;
				i=pom;
		}
	}
	unlock();
}

void Queue::SortirajOpadajuce(){
	lock();
		Elem *i, *j, *pom;
		for(i=prvi;i;i=i->sled){
			for(j=i->sled;j;j=j->sled){
				if(j->pcb->returnID()>i->pcb->returnID())
					pom=j;
					j=i;
					i=pom;
			}
		}
		unlock();

}



