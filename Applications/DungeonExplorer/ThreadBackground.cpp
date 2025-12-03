#include "ThreadBackground.h"

ThreadBackground::ThreadBackground(Semaphore *sem,char *tab,Ecran *ec){
	sema=sem;
	tableauProCons=tab;
	ecran=ec;
};

void ThreadBackground::run(){
	int n=0;
	for (int i=0;i<70;i++) {
		tableauProCons[i]='$';
		ecran->afficherCaractere(9,i,BLANC,NOIR,tableauProCons[i]);
		sema->V();
	}
};