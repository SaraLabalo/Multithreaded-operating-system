#include "system.h"

extern int userMain(int argc, char* argv[]);

class Queue;
int PCB::ID = 0;
int main(int argc, char* argv[]) {

//Pokrene operativni sistem
	System::load();

//Pozove test i prosledi argumente
	int value = userMain(argc, argv);

//Ugasi operativni sistem
	System::unload();

	return value;
}
