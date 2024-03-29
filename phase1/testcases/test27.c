#include <stdio.h>
#include <usloss.h>
#include <phase1.h>

/*
 * The purpose of this test is to demonstrate that
 * an attempt to join by a process with no children
 * or no unjoined children returns -2.
 *
 * Expected output:
 * start1(): started
 * start1(): after fork of child 3
 * start1(): after fork of child 4
 * start1(): performing first join
 * XXp1(): started
 * XXp1(): arg = `XXp1'
 * XXp1(): performing join with no children
 * XXp1(): value returned by join is -2 expected value was -2
 * start1(): exit status for child 3 is -1
 * start1(): performing second join
 * XXp2(): started
 * XXp2(): arg = `XXp2'
 * start1(): exit status for child 4 is -2
 * start1(): performing third join, have no unjoined children
 * start1(): value returned by join is -2 expected value was -2
 */

int XXp1(char *), XXp2(char *), XXp3(char *);
char buf[256];

int start1(char *arg)
{
  int status, pid1, pid2, kidpid;

  printf("start1(): started\n");
  pid1 = fork1("XXp1", XXp1, "XXp1", USLOSS_MIN_STACK, 3);
  printf("start1(): after fork of child %d\n", pid1);
  pid2 = fork1("XXp2", XXp2, "XXp2", USLOSS_MIN_STACK, 3);
  printf("start1(): after fork of child %d\n", pid2);
  printf("start1(): performing first join\n");
  kidpid = join(&status);
  sprintf(buf,"start1(): exit status for child %d is %d\n", kidpid, status);
  printf("%s", buf);
  printf("start1(): performing second join\n");
  kidpid = join(&status);
  sprintf(buf,"start1(): exit status for child %d is %d\n", kidpid, status);
  printf("%s", buf); 
  printf("start1(): performing third join, have no unjoined children\n");
  kidpid = join(&status);
  sprintf(buf,"start1(): value returned by join is %d expected value was -2\n",
          kidpid);
  printf("%s", buf);
  return 0;
} /* start1 */

int XXp1(char *arg)
{
  int status, kidpid;

  printf("XXp1(): started\n");
  printf("XXp1(): arg = `%s'\n", arg);
  printf("XXp1(): performing join with no children\n");
  kidpid = join(&status);
  sprintf(buf,"XXp1(): value returned by join is %d expected value was -2\n",
          kidpid);
  printf("%s", buf);
  quit(-1);
  return 0;
} /* XXp1 */

int XXp2(char *arg)
{
  printf("XXp2(): started\n");
  printf("XXp2(): arg = `%s'\n", arg);
  quit(-2);
  return 0;
} /* XXp2 */

