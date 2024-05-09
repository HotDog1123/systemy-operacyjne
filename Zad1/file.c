#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

int main()
{
    // ZAD 1: Utworzenie katalogu, podkatalogu i pliku
    int P1 = fork();
    if (P1 == 0)
    {
        execl("/bin/mkdir","mkdir","-p","katalog1/katalog2");
    }
    wait(NULL);

    int P2 = fork();
    if (P2 == 0)
    {
        execl("/bin/touch","touch","katalog1/plik1",NULL);
    }
    wait(NULL);




    // ZAD 2: Pobranie tekstu od użytkownika i zapis do plik2
    int fd = creat("katalog1/plik2",S_IRWXU);
    if (fd == 1)
    {
        perror("Błąd odczytu");
        return 1;
    }

    char *data = NULL;
    data = malloc(50);
    read(STDIN_FILENO, data, 50);

    int offset = lseek(fd, 0, SEEK_SET);
    if (offset == -1)
    {
        perror("Błąd ustawiania wskaźnika");
        return 1;
    }

    int writeData = write(fd, data, 50);
    if (writeData == -1)
    {
        perror("Błąd zapisu");
    }

    close(fd);




    // ZAD 3: Pobranie tekstu od użytkownika i zamiana małych liter na duże, wyświetlenie wyniku
    char *data2 = NULL;
    data2 = malloc(50);

    read(STDIN_FILENO, data2, 50);
    for (int i = 0; i<50;i++)
    {
        printf("%c",toupper(data2[i]));
    }




    // ZAD 4: Odczyt z plik2 i zapis do plik1
    int fd2 = open("katalog1/plik2", O_RDONLY);
    if (fd2 == -1) {
        perror("Błąd odczytu");
        exit(1);
    }
    int offset2 = lseek(fd2, 0, SEEK_SET);
    if (offset2 == -1)
    {
        perror("Błąd ustawiania wskaźnika");
        return 1;
    }

    int fd3 = open("katalog1/plik1", O_RDWR);
    if (fd == -1) {
        perror("Błąd odczytu");
        return 1;
    }
    int offset3 = lseek(fd3, 0, SEEK_SET);
    if (offset3 == -1)
    {
        perror("Błąd ustawiania wskaźnika");
        return 1;
    }
    char data3[50];
    int readData = read(fd2, data3, 50);
    if (readData == -1)
    {
        perror("Błąd odczytu");
    }
    int writeData2 = write(fd3,data,50);
    close(fd2);
    close(fd3);




    // ZAD 5: Sprawdzanie praw dostępu, dodanie lub odebranie.
    if (access("katalog1/plik1", R_OK) != 1)
    {
        printf("Plik ma uprawnienia do odczytu.\n");
    } else
    {
        printf("Plik nie ma uprawnień do odczytu.\n");
    }

    if (access("katalog1/plik1", W_OK) != 1)
    {
        printf("Plik ma uprawnienia do zapisu. Zostaną one usunięte.\n");
        int P2 = fork();
        if (P2 == 0)
        {
            execl("/bin/chmod","chmod","-w","katalog1/plik1");
        }
        wait(NULL);
    } else
    {
        printf("Plik nie ma uprawnień do zapisu. Zostaną one dodane.\n");
        chmod("katalog1/plik2", S_IWUSR);
    }

    if (access("katalog1/plik1", X_OK) != 1)
    {
        printf("Plik ma uprawnienia do wykonywania.\n");
    } else
    {
        printf("Plik nie ma uprawnień do wykonywania.\n");
    }



    // ZAD 5: Usunięcie pliku, próba usunięcia katalogu pustego/niepustego
    int del = remove("katalog1/plik1");
    if (del == 0)
    {
        printf("Usunięto plik\n");
    } else
    {
        printf("Błąd usuwania pliku\n");
    }

    int del2 = remove("katalog1/katalog2");
    if (del2 == 0)
    {
        printf("Usunięto pusty katalog\n");
    } else
    {
        printf("Błąd usuwania pustego katalogu\n");
    }

    int del3 = remove("katalog1");
    if (del3 == 0)
    {
        printf("Usunięto niepusty katalog\n");
    } else
    {
        printf("Błąd usuwania niepustego katalogu\n");
    }

    // Można w ten sposób usunąć jedynie pusty katalog.

    return 0;
}
