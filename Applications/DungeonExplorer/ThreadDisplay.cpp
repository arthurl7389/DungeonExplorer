#include "ThreadDisplay.h"

ThreadDisplay::ThreadDisplay(Semaphore *sem,char *tab,Ecran *ec){
	sema=sem;
	tableauProCons=tab;
	ecran=ec;
};
void ThreadDisplay::run(){
	int i=0;
	char c;
	while (true) {
		sema->P();
		c=tableauProCons[i++];
		ecran->afficherCaractere(10,(i-1),BLANC,NOIR,c);
	}
};