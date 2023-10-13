#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  if(argc != 2){
<<<<<<< HEAD
    fprintf(2, "usage: sleep ticks\n");
=======
    fprintf(2, "usage: sleep <ticks>\n");
>>>>>>> hw2.2
    exit(1);
  }
  sleep(atoi(argv[1]));
  exit(0);
}
