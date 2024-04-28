# Systemy Operacyjne - Kolokwium Powtórzenie

## PODSTAWY
Tworzenie pliku C

`touch file.c`


Kompilowanie pliku C

`gcc file.c`


Uruchamianie skompilowanego pliku

`./a.out`


Jakiś tam podstawowy programik
```
#include <stdio.h> // printf

int main()
{
    printf("Hello world\n");
}

```

## PROCESY (FORK)
Tworzenie procesu potomnego

`int P1 = fork()`


Program tworzący dwa procesy potomne
```
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
        exit(0);
    }
    wait(NULL);
    int P2 = fork();
    if (P2 == 0)
    {
        printf("Proces potomny 2. PID: %d, PPID: %d\n", getpid(), getppid());
        exit(0);
    }
    wait(NULL);
    exit(0);
}
```


## Procesy i polecenia
Wywoływanie programu podanego jako paramentr funkcji

`int execlp( char *file, char *arg0, ..., char *argn, char *null )`


Przykład

`execl("/bin/ls", "ls", "-l", NULL)` - nie wiem czy NULL jest potrzebny, ale powinny być (CHYBA) 4 argumenty


Program tworzący proces potomny i wywołujący w nim polecenie PWD

```
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
```
