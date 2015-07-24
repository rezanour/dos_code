#include <stdio.h>
#include "W_SYS.H"

void main(int argc, char* argv[])
{
  W_initmem();
  W_allocmem(10);
  W_allocmem(10);
  W_allocmem(1400);
  W_allocmem(10);
  W_allocmem(10);
  W_printstats();
  W_freeall();
  getchar();
}
