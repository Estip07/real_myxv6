#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(2, "Usage: %s <command> [args...]\n", argv[0]);
        exit(1);
    }

    // Create argv2 with the same size as argc - 1
    char *argv2[argc - 1]; 

    for (int i = 1; i < argc; i++) {
        argv2[i - 1] = argv[i];
    }
    // Set last element to 0
    argv2[argc - 1] = 0;

    int start = uptime();

    int pid = fork();

    if (pid == -1) {
        printf("%s: fork failed\n", argv[0]);
        exit(1);
    } else if (pid == 0) {
        exec(argv2[0], argv2);
        printf("%s: exec failed\n", argv[0]);
        exit(1);
    } else {
        struct rusage ru;
        int pid2 = wait2(0, &ru);
        int end = uptime();
        int duration = end - start;
        printf("elapsed time: %d ticks, cpu time: %d ticks, %d%% CPU\n", duration, ru.cputime, (ru.cputime * 100) / duration);
        if (pid2 == pid) {
            // Restart
            exit(1);
        } else if (pid2 < 0) {
            printf("wait returned an error\n");
            exit(1);
        } else {

        }
    }

    exit(0);
}

