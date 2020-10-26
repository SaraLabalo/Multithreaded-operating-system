/*
 * semaphor.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */
#include <stdlib.h>
#include "system.h"
#include "kernelse.h"
#include "semaphor.h"



Semaphore::Semaphore(int init) {
	lock();
	myImpl = new KernelSem(init);
	unlock();

}

Semaphore::~Semaphore() {
	lock();
	delete myImpl;
	unlock();
}

int Semaphore::wait(Time maxTimeToWait){
	int rez;
	lock();
	rez=myImpl->wait(maxTimeToWait);
	unlock();
	return rez;
}

int Semaphore::signal(int n){
	int rez;
	lock();
	rez=myImpl->signal(n);
	unlock();
	return rez;
}

int Semaphore::val() const{
	int rez;
	lock();
	rez=myImpl->val();
	unlock();
	return rez;
}
