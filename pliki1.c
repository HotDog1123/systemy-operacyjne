#include <stdio.h> // printf
#include <unistd.h> // getpid
#include <stdlib.h> // exit
#include <sys/wait.h> // wait
#include <fcntl.h> // open

int main()
{
    int fd1 = open("input.txt", O_RDONLY);
    if (fd1 == -1) {
        perror("Błąd odczytu");
        exit(1);
    }

    char buffer[1024];
    int readData = read(fd1, buffer, 1024);

    int fd2 = creat("output.txt", S_IRWXU);
    write(fd2, buffer, readData);

    close(fd1);
    close(fd2);
    exit(0);
}