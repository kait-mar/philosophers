

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
     return (ptr);
}

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;

void *functionC()
{
    void    *ptr;

   //pthread_mutex_lock( &mutex1 );
   counter++;
   printf("Counter value: from 1\n");
  // pthread_mutex_unlock( &mutex1 );
   return (ptr);
}

void *functionC2()
{
    void    *ptr;

   //pthread_mutex_lock( &mutex1 );
   counter++;
   printf("Counter value from 2\n");
  // pthread_mutex_unlock( &mutex1 );
   return (ptr);
}

int main()
{
   int rc1, rc2;
   pthread_t thread1, thread2;

   /* Create independent threads each of which will execute functionC */

   if( (rc1=pthread_create( &thread1, NULL, &functionC, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc1);
   }

   if( (rc2=pthread_create( &thread2, NULL, &functionC2, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc2);
   }

   // printf("here\n");
   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL); 

   exit(0);
}
