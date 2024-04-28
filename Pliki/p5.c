#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd1, fd2;

    // Otwieranie pliku
    fd1 = open("plik.txt", O_RDONLY);
    if (fd1 == -1) {
        perror("Nie można otworzyć pliku");
        return 1;
    }

    // Duplicating file descriptor
    fd2 = dup2(fd1, 10); // Nowy deskryptor pliku będzie 10
    if (fd2 == -1) {
        perror("Błąd podczas duplikowania deskryptora pliku");
        return 1;
    }

    // Zamykanie pierwotnego deskryptora
    close(fd1);

    // Używanie nowego deskryptora pliku
    char buffer[256];
    ssize_t bytesRead = read(fd2, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("Błąd podczas czytania z pliku");
        return 1;
    }

    // Wyświetlanie danych
    printf("Odczytane dane: %s\n", buffer);

    // Zamykanie deskryptora pliku
    close(fd2);

    return 0;
}
