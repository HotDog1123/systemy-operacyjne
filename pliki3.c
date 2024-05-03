#include <stdio.h> // printf
#include <unistd.h> // getpid
#include <stdlib.h> // exit
#include <sys/wait.h> // wait
#include <fcntl.h> // open

int main()
{
    char buffer[1024];
    int readData = read(0, buffer, 1024);

    int fd = creat("output.txt", S_IRWXU);
    write(fd, buffer, readData);

    close(fd);
    exit(0);
}