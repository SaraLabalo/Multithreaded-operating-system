/*
 * kernelse.h
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#ifndef KERNELSE_H_
#define KERNELSE_H_
#include "queue.h"
#include "listaSem.h"
typedef unsigned int Time;

class Queue;
class KernelSem {
public:
	Queue *waitQ, *timeQ;
	static ListaSem *sviSemafori;

	int value;

	KernelSem(int init=1);
	virtual ~KernelSem();

	int val () const;

	virtual int wait (Time vremeCekanja);
	virtual int signal(int n);
	static void decreaseTime();
};

#endif /* KERNELSE_H_ */
