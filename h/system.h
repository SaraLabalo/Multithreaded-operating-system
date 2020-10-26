
#ifndef _SYTEM_H_
#define _SYTEM_H_


#include "pcb.h"
#include "idlethr.h"
#include "thread.h"
#include "kernelse.h"

//celear interrupt i setinterrupt imaju problem ugnjezdenih prekida
typedef void (interrupt *InterruptRoutine)();
#define lock() {asm{pushf; cli;}}
#define unlock() {asm{popf}}

class Queue;
class System {
public:
	System();
		virtual ~System();

		friend class PCB;
		friend class Thread;
		static volatile char dispatched;

		static void load();
		static void unload();
		static void dispatch();


		static void wrapper();
		static void interrupt timerIR(...);
		static void interrupt (*oldRoutine)(...);

		static volatile PCB* running;
		static Thread* starting;
		static IdleThread* idle;


};

#endif
