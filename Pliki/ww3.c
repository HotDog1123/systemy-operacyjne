#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int mojazmiennaglobalna;
pthread_mutex_t mojmuteks=PTHREAD_MUTEX_INITIALIZER;
void *Hello(void *arg) { 
int i,j;
for ( i=0; i<20; i++ ) { 
pthread_mutex_lock(&mojmuteks);
j=mojazmiennaglobalna; 
j=j+1;
printf(".");
fflush(stdout);
sleep(1);
mojazmiennaglobalna=j; 
pthread_mutex_unlock(&mojmuteks);
}
return NULL;
}

int main(void) {
pthread_t mojwątek;
int i;
if( pthread_create( &mojwątek, NULL, Hello, NULL) ) {
printf("błąd przy tworzeniu wątku."); 
abort();
}
for ( i=0; i<20; i++) {
pthread_mutex_lock(&mojmuteks); 
mojazmiennaglobalna=mojazmiennaglobalna+1;
printf("o"); 
fflush(stdout); 
sleep(1);
}
if ( pthread_join( mojwątek, NULL ) ) {
printf("błąd przy kończeniu wątku.");
abort(); 
}
printf("\nWartość zmiennej globalnej wynosi %d\n",mojazmiennaglobalna);
exit(0);
}
