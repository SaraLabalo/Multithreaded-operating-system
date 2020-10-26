#ifndef _THREAD_H_
#define _THREAD_H_

class PCB;
typedef int ID;

typedef unsigned long StackSize;
typedef unsigned int Time;

const StackSize defaultStackSize = 4096;
const Time defaultTimeSlice = 2;


class Thread
{

public:
	PCB* myPCB;
	Time TimeSlice;
	StackSize stackSize;

	Thread (StackSize s=defaultStackSize, Time t=defaultTimeSlice);
	virtual void run() {}
	void start();
	virtual ~Thread();
	void waitToComplete();

	ID getId();
	static ID getRunningId();
	static Thread * getThreadById(ID id);


	//Thread* maker;

protected:
	friend class System;
	friend class IdleThread;
	friend class PCB;

};



void dispatch();
extern void tick();



#endif
