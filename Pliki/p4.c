#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int fd;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];

    // Otwieranie pliku do odczytu
    fd = open("input.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Odczytywanie danych z pliku i wyświetlanie ich
    bytes_read = read(fd, buffer, BUFFER_SIZE);
        // Wypisywanie odczytanych danych na standardowe wyjście
        if (write(1, buffer, bytes_read) != bytes_read) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    

    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Zamykanie pliku
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
