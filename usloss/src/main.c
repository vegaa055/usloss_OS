
#include <stdlib.h>
#include "project.h"
#include "usloss.h"
#include "main.h"
#include "globals.h"
#include "dev_alarm.h"
#include "dev_clock.h"
#include "dev_disk.h"
#include "dev_term.h"
#include "devices.h"
#include "sig_ints.h"

static context startup_context;
dynamic_def(context finish_context);
int dumpcore = 0;

static void starter(void) {
    startup();
    rpt_sim_trap("startup returned!\n");
}

int main(int argc, char **argv)
{
    char stack[USLOSS_MIN_STACK];
    unsigned int psr;
    /*  Call the per-module initialization routines */
    globals_init();
    devices_init();
    alarm_init();
    clock_init();
    disk_init();
    term_init();
    sig_ints_init();	/*  Must disable interrupts */

    /*  Set up the initial context that runs the user's startup code */
    getcontext(&startup_context.context);
    startup_context.context.uc_stack.ss_sp = stack;
    startup_context.context.uc_stack.ss_size = sizeof(stack);
    startup_context.context.uc_link = &finish_context.context;
    startup_context.context.uc_link = NULL;
    makecontext(&startup_context.context, (FN_CAST) starter, 0);

    /*  Turn on the timer and start running (user must unblock SIG_ALARM via
	the int_disable() function */
    set_timer();
    psr = current_psr;
    swapcontext(&finish_context.context, &startup_context.context);

    /*  Finished from swapcontext() - user has called USLOSS_Halt.  We will call
	their finish() routine and exit */
    current_psr = psr;
    finish();
    exit(0);
}

