#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h>

void *Hello(void *arg) { 
int i;
for ( i=0; i<20; i++ ) { 
	printf("Wątek mówi cześć!\n"); 
	sleep(1);
}
return NULL; 
}

int main(void) {
pthread_t mojwatek;
if( pthread_create(&mojwatek, NULL, Hello,NULL) ){
	printf("błąd przy tworzeniu wątku\n"); 
	abort(); 
}
if ( pthread_join ( mojwatek, NULL ) ) {
	printf("błąd w kończeniu wątku\n");
	exit(0); 
}
exit(0); 
}