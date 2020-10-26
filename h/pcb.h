
#ifndef _PCB_H_
#define _PCB_H_

#include "thread.h"
#include "queue.h"
#include "system.h"

class Thread;
class Queue;
class PCB{
public:
	static const enum{NEW=0,READY=1,BLOCKED=2,OVER=3};
	static int ID;
	int pcbID;
	int returnID();
	int povratnaVrednost;

	Thread* myThread;
	unsigned int sp, ss,bp;

	PCB(Thread* myT, StackSize stackSize, Time timeSlice);
	virtual ~PCB();

	void createStack();



	unsigned * pcbSP;
	Time pcbTimeSlice;
	Time myTimeBlocked;
	volatile unsigned long timePassedCounter;
	StackSize pcbStackSize;

	volatile int state;
	//red blokiranih niti koji ceka na nju
	Queue* waitQueue;


};

#endif
