#include <stdio.h>
#include <usloss.h>
#include <phase1.h>
/*

//Check that getpid() functions correctly.

*/

int XXp1(char *), XXp2(char *), XXp3(char *), XXp4(char *);
int pidlist[5];
#define FLAG1 -2
int start1(char *arg)
{
	int ret1,ret2,ret3;
	int status;

	pidlist[0] = fork1("XXp1", XXp1, NULL, USLOSS_MIN_STACK, 2);
	pidlist[1] = fork1("XXp1", XXp1, NULL, USLOSS_MIN_STACK, 3);
	pidlist[2] = fork1("XXp1", XXp1, NULL, USLOSS_MIN_STACK, 4);
	ret1=join(&status);
	ret2=join(&status);
	ret3=join(&status);
	console("TEST:");console("exit getpid test.\n");

	quit(-1);
	return 0;
}

int XXp1(char *arg)
{
	static int i = 0;
	if (getpid()!= pidlist[i]){
		console("TEST:");
		console("Getpid failed. %d %d\n",getpid(),pidlist[i]);
	}
	else{
		console("TEST:");
		console("Getpid passed. %d %d\n",getpid(),pidlist[i]);
	}
	i++;

	quit(FLAG1);
	return 0;
}

