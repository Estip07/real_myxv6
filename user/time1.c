#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "Usage: time1 command [arguments...]\n");
    exit(1);
  }

  char *argv2[argc]; // Create an array of pointers to store arguments

  for (int i = 1; i < argc; i++) {
    argv2[i - 1] = argv[i];
  }
  argv2[argc - 1] = 0; // Null-terminate the array of arguments

  int time_start = uptime();
  int pid = fork();

  if (pid == -1) {
    fprintf(2, "fork failed\n");
    exit(1);
  } else if (pid == 0) {
    // Child process: execute the specified command
    exec(argv2[0], argv2);
    fprintf(2, "exec failed\n");
    exit(1);
  } else {
    // Parent process: wait for the child to finish
    int wpid, status;
    wpid = wait(&status);

    int time_end = uptime();
    printf("Time: %d ticks\n", time_end - time_start);

    if (wpid < 0) {
      fprintf(2, "wait returned an error\n");
      exit(1);
    }

    exit(0);
  }
}
