#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "pcb.h"
class PCB;

class Elem {
public:
	PCB* pcb;
	Elem* sled;

};

class Queue {
public:
	Elem* prvi;
	int duz;

	//konstruktor
	Queue();

	//destruktor
	~Queue();

	//f-je get i put
	PCB* get();
	void put(PCB* pcb);
	void deleteQueue();

	PCB * PronajiPoId(ID);
	Queue& ObrisiPoId(ID);

	//sortiranje
	void SortirajNeopadajuce();
	void SortirajOpadajuce();



	void ObrisiPoPcb1(PCB* pcb);


};


#endif
