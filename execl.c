#include <stdio.h> // printf
#include <unistd.h> // getpid
#include <stdlib.h> // exit
#include <sys/wait.h> // wait

int main()
{
    printf("Proces macierzysty, PID:%d\n", getpid());

    int P1 = fork();
    if (P1 == 0)
    {
        printf("Proces potomny 1. PID: %d, PPID: %d\n", getpid(), getppid());
        execl("/bin/pwd", "pwd", NULL, NULL);
        exit(0);
    }
    wait(NULL);
    exit(0);
}