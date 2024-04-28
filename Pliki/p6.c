#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd, offset, p;
    char buffer[100];

    // Otwieranie pliku
    fd = open("plik.txt", O_RDWR);
    if (fd == -1) {
        perror("Nie można otworzyć pliku");
        return 1;
    }

    // Ustawianie wskaźnika pozycji na początku pliku
    offset = lseek(fd, 0, SEEK_SET);
    if (offset == -1) {
        perror("Błąd podczas ustawiania wskaźnika pozycji");
        return 1;
    }

    // Czytanie danych z pliku
    int bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("Błąd podczas czytania z pliku");
        return 1;
    }

    // Wyświetlanie danych z pliku
    printf("Odczytane dane z pliku: %s\n", buffer);

    // Ustawianie wskaźnika pozycji na koniec pliku
    offset = lseek(fd, 0, SEEK_END);
    if (offset == -1) {
        perror("Błąd podczas ustawiania wskaźnika pozycji");
        return 1;
    }

    // Dopisywanie danych na koniec pliku
    char *data = "\nAaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA.";
    int bytesWritten = write(fd, data, strlen(data));
    if (bytesWritten == -1) {
        perror("Błąd podczas zapisywania do pliku");
        return 1;
    }
   


    // Zamykanie pliku
    close(fd);

    return 0;
}
