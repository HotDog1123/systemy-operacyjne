#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Tworzenie procesu potomnego
    pid = fork();

    if (pid < 0) {
        // Błąd podczas tworzenia procesu potomnego
        fprintf(stderr, "Błąd podczas wywoływania fork()");
        exit(1);
    } else if (pid == 0) {
        // Kod procesu potomnego
        printf("Jestem procesem potomnym.\n");
        exit(5); // Proces potomny kończy się z kodem wyjścia 5
    } else {
        // Kod procesu macierzystego
        printf("Jestem procesem macierzystym.\n");
        // Oczekiwanie na zakończenie działania procesu potomnego
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("Proces potomny zakończył działanie z kodem wyjścia: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Proces potomny zakończył działanie z sygnałem: %d\n", WTERMSIG(status));
        }
    }

    return 0;
}


//WIFEXITED(status): Sprawdza, czy proces potomny zakończył swoje działanie normalnie (bez sygnału).
//WEXITSTATUS(status): Zwraca kod wyjścia procesu potomnego.
//WIFSIGNALED(status): Sprawdza, czy proces potomny zakończył się z powodu otrzymania sygnału.
//WTERMSIG(status): Zwraca numer sygnału, który spowodował zakończenie procesu potomnego.

