#include <stdio.h> // printf
#include <unistd.h> // getpid
#include <stdlib.h> // exit
#include <sys/wait.h> // wait
#include <fcntl.h> // open

int main()
{
    int fd = open("input.txt", O_RDONLY);
    if (fd == -1) {
        perror("Błąd odczytu");
        exit(1);
    }

    char buffer[1024];
    int readData = read(fd, buffer, 1024);
    // printf(buffer); - też chyba działa

    write(1, buffer, readData);

    close(fd);
    exit(0);
}