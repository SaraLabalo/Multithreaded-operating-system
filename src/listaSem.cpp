/*
 * listaSem.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */
#include <stdlib.h>
#include "listaSem.h"
#include "system.h"
#include "iostream.h"
extern int syncPrintf (const char* format, ... );
int ListaSem::duz = 0;

ListaSem::ListaSem() {
	lock();
    prvi= 0;
	posl = 0;

	unlock();
}

ListaSem::~ListaSem() {
	lock();
		ElemS* tek=prvi;
		ElemS* stari;
		while( tek )
		{
			stari=tek;
			tek=tek->sled;
			delete stari;
		}
		duz=0;

		prvi=posl=NULL;
	unlock();
}

KernelSem* ListaSem::get(){
	lock();
	if( prvi == NULL ) {
		unlock();
		return NULL;
	}
	ElemS* novi = prvi;
	prvi = prvi->sled;
	//prvi->pret=NULL;
	KernelSem *rez=novi->sem;
	duz=duz-1;
	unlock();
	return rez;
}
void ListaSem::pisi(){
	/*
	ElemS *tek;
	syncPrintf("UsaoIspis %d", prvi->sem->idSem);
	for(tek=prvi;tek!=0;tek=tek->sled){
		syncPrintf("%d ",tek->sem->idSem);
	}
	*/
}
void ListaSem::put(KernelSem* s){

	lock();

	ElemS *novi=new ElemS();
	ElemS *tek;
	novi->sled=NULL;
	novi->sem=s;
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



void ListaSem::deleteSem(KernelSem* s){
	lock();
		ElemS *pret=NULL,*tek=prvi;
		while(tek && tek->sem!=s){
			pret=tek;
			tek=tek->sled;

		}
		if(tek){
			ElemS* stari=tek;
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
		return;
}

int ListaSem::brSemafora(){
	return duz;
}

