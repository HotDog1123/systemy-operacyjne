# Systemy Operacyjne - Kolokwium Powtórzenie

## PODSTAWY
### Tworzenie pliku C
`touch file.c`

### Kompilowanie pliku C
`gcc file.c`

### Uruchamianie skompilowanego pliku
`./a.out`

### Jakiś tam podstawowy programik
```
#include <stdio.h> // printf

int main()
{
    printf("Hello world\n");
}

```

## PROCESY (fork)
### Tworzenie procesu potomnego
`int P1 = fork()`

### Obsługa błędów
```
if (P1 < 0)
    {
        perror("Błąd podczas tworzenia procesu potomnego");
        exit(1);
    }
```

### Program tworzący dwa procesy potomne
```
#include <stdio.h> // printf
#include <unistd.h> // getpid
#include <stdlib.h> // exit
#include <sys/wait.h> // wait

int main()
{
    printf("Proces macierzysty, PID:%d\n", getpid());

    int P1 = fork();
    if (P1 < 0)
    {
        perror("Błąd podczas tworzenia procesu potomnego");
        exit(1);
    }
    else if (P1 == 0)
    {
        printf("Proces potomny 1. PID: %d, PPID: %d\n", getpid(), getppid());
        exit(0);
    }
    wait(NULL);
    int P2 = fork();
    if (P2 < 0)
    {
        perror("Błąd podczas tworzenia procesu potomnego");
        exit(1);
    }
    else if (P2 == 0)
    {
        printf("Proces potomny 2. PID: %d, PPID: %d\n", getpid(), getppid());
        exit(0);
    }
    wait(NULL);
    exit(0);
}
```
### Proces zombie
Proces zombie to proces który został osierocony - proces macierzysty zakończył już działanie. Efekt wywołujemy za pomocą funkcji `sleep`.

Przykład:
```
    if (P1 == 0)
    {
        printf("Proces potomny 1. PID: %d, PPID: %d\n", getpid(), getppid());
        sleep(30);
    }
    exit(0);
```

## Procesy i polecenia (execl)
### Wywoływanie programu podanego jako paramentr funkcji
`int execl ( char *path, char *arg0, ..., char *argn, char *null )`

### Przykład
`execl("/bin/ls", "ls", "-l", NULL)` - nie wiem czy NULL jest potrzebny, ale powinny być (CHYBA) 4 argumenty


### Program tworzący proces potomny i wywołujący w nim polecenie PWD

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

## Operacje na plikach
### Deskryptory standardowe
Podstawowe deskryptory w systemach Unix/Linux:
- `0` - standardowe wejście, odczyt od użytkownika (stdin)
- `1` - standardowe wyjście, wyświetlanie dla użytkownika (stdout)
- `2` - standardowy strumień błędów (stderr)

### Otwieranie istniejącego pliku (open)
Otwarcie pliku:

`int fd = open("input.txt", O_RDONLY);`

Flagi dostępu:
- `O_RDONLY` - tylko do odczytu
- `O_WRONLY` - tylko do zapisu
- `O_RDWR` - odczyt i zapis
- `O_APPEND` – operacje pisania odbywają się na końcu pliku. Użycie operatorem bitowym OR `|` w połączeniu z jednym z powyższych argumentów.

### Obsługa błędów (plik nie istnieje):
```
    if (fd == -1) {
        perror("Błąd odczytu");
        exit(1);
    }
```

### Zamknięcie pliku:
`close(fd);`

Obsługa błędów
```
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
```


### Utworzenie nowego pliku (creat)
Utworzenie pliku i otwarcie do zapisu:

`fd = creat("output.txt", S_IRWXU);`

Tryby dostępu (mode):
- `S_IRWXU` - Uprawnienia odczytu, zapisu i wykonywania, dla właściciela pliku (rwx)
- `S_IRUSR` - Prawo do odczytu dla właściciela pliku (r)
- `S_IWUSR` - Prawo do zapisu dla właściciela pliku (w)
- `S_IXUSR` - Prawo do wykonywania dla właściciela pliku (x)

### Odczyt z pliku (read)
Odczyt fragmentu pliku:
```
char buffer[1024];
int readData = read(fd, buffer, 1024);
```

Obsługa błędów
```
    if (readData == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
```

### Zapis do pliku (write)
Zapis fragmentu pliku:
```
int fd2 = creat("output.txt", S_IRWXU);
write(fd2, buffer, readData);
```
Obsługa błędów
```
        if (write(1, buffer, readData) != readData) {
            perror("write");
            exit(EXIT_FAILURE);
        }
```

### Duplikacja deskryptora
```
    fd2 = dup2(fd1, 10); // Nowy deskryptor pliku będzie 10
    if (fd2 == -1) {
        perror("Błąd podczas duplikowania deskryptora pliku");
        return 1;
    }
```

### Przykład - odczyt z pliku input.txt i zapis do pliku output.txt
```
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
```
### Przykład - odczyt z pliku i zapis do wyjścia standardowego
```
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
```

### Przykład - odczyt z wejścia standardowego i zapis do pliku
```
#include <stdio.h> // printf`
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
```

### Ustawianie wskaźnika pozycji
`long lseek(inf fd, off_t offset, int whence)`

Argumenty funkcji:
- `fd` - deskryptor pliku, do którego mają zostać zapisane dane
- `offset` - liczba bajtów, o jaką należy przesunąć wskaźnik
- `whence` - parametr określający pozycję względem której jest przesuwany wskaźnik
    - `SEEK_SET` - początek pliku
    - `SEEK_END` - koniec pliku
    - `SEEK_CUR` - bieżąca pozycja


Przykład:
```
// Ustawianie wskaźnika pozycji na początku pliku
offset = lseek(fd, 0, SEEK_SET);
if (offset == -1) {
    perror("Błąd podczas ustawiania wskaźnika pozycji");
    return 1;
}
```

## Wątki
### Funkcja wykonywana przez wątek
```
void *Hello (void *arg)
{ 
    int i;
    for (i=0; i<20; i++)
    { 
	    printf("Wątek mówi cześć!\n"); 
	    sleep(1);
    }
    return NULL; 
}
```
### Tworzenie nowego wątku w funkcji main
```
    pthread_t mojwatek;

    // Tworzenie wątku
    if (pthread_create(&mojwatek, NULL, Hello, NULL))
    {
	    printf("Błąd przy tworzeniu wątku\n"); 
	    abort(); 
    }

    // Oczekiwanie na zakończenie wątku
    if (pthread_join (mojwatek, NULL ))
    {
	    printf("Błąd w kończeniu wątku\n");
	    exit(0); 
    }
```

### Przykład
```
#include <stdio.h> // printf
#include <unistd.h> // getpid
#include <stdlib.h> // exit
#include <sys/wait.h> // wait
#include <fcntl.h> // open
#include <pthread.h> // pthread

// Funkcja wykonywana przez wątek
void *Hello (void *arg)
{ 
    int i;
    for (i=0; i<20; i++)
    { 
	    printf("Wątek mówi cześć!\n"); 
	    sleep(1);
    }
    return NULL; 
}

int main(void)
{
    pthread_t mojwatek;

    // Tworzenie wątku
    if (pthread_create(&mojwatek, NULL, Hello, NULL))
    {
	    printf("Błąd przy tworzeniu wątku\n"); 
	    abort(); 
    }

    // Oczekiwanie na zakończenie wątku
    if (pthread_join (mojwatek, NULL ))
    {
	    printf("Błąd w kończeniu wątku\n");
	    exit(0); 
    }
    exit(0);
}
```
