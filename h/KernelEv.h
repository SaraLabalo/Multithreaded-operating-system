/*
 * KernelEv.h
 *
 *  Created on: May 4, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include "system.h"
#include "thread.h"
#include "event.h"
#include"kernelse.h"

typedef unsigned char IVTNo;
class Thread;
class PCB;

class KernelEv {
public:

	KernelEv(IVTNo ivtNo);
	~KernelEv();

	int value;
	PCB* boss;


	void wait();
	void signal();
	KernelSem *mySem;
	IVTNo ivtNo1;



};

#endif /* KERNELEV_H_ */
