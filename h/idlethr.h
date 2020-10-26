#ifndef _IDLETH_H_
#define _IDLETH_H_
#include "thread.h"

class Thread;

class IdleThread : public Thread {
public:
	IdleThread();

	void start();

	virtual void run();



};

#endif
