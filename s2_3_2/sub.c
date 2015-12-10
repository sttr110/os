#include <stdio.h>
#include <pthread.h>

int counter = 0;
int num = 0;


void* thread( void* args )
{
    num = num + 10; 

    printf("%d\n", num);
    return NULL;
}


int main() 
{
    pthread_t th;

    pthread_create( &th, NULL, thread, (void *)NULL );

    pthread_join( th, NULL );

    pthread_exit(NULL);
    return 0;
}
