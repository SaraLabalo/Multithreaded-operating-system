/*
 * listaSem.h
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#ifndef LISTASEM_H_
#define LISTASEM_H_

class KernelSem;

class ElemS {
public:
	KernelSem *sem;
	ElemS* sled;
	//ElemS* pret;
};


class ListaSem {
public:
	ElemS* prvi;
	ElemS *posl;
	static int duz;

	ListaSem();
	virtual ~ListaSem();

	void put(KernelSem* s);
	KernelSem *get();
	void deleteSem(KernelSem*s);
	void pisi();
	int brSemafora();
};



#endif /* LISTASEM_H_ */
