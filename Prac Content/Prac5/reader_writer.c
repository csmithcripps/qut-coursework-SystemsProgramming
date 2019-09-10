#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define READERS 4
#define WRITERS 4

int 			current_time;
int 			ready = 0;
int 			go = 0;
pthread_mutex_t ready_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t 	ready_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t go_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t 	go_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t screen = PTHREAD_MUTEX_INITIALIZER;

int rc;	/* readcount */
pthread_mutex_t rc_mutex;
pthread_mutex_t r_mutex;
pthread_mutex_t w_mutex;

/* Init of the mutexes */

void ReadWriteMutexInit( ) {

	rc = 0;
	pthread_mutex_init( &rc_mutex, NULL );
	pthread_mutex_init( &r_mutex, NULL );
	pthread_mutex_init( &w_mutex, NULL );
	}

/* Read action lock */

void ReadLock( ) {

	pthread_mutex_lock( &r_mutex );
	pthread_mutex_lock( &rc_mutex );
	rc++;
	if ( rc == 1 ) pthread_mutex_lock( &w_mutex );
	pthread_mutex_unlock( &rc_mutex );
	pthread_mutex_unlock( &r_mutex );
	}

/* Read action unlock */

void ReadUnlock( ) {

	pthread_mutex_lock( &rc_mutex );
	rc--;
	if (rc == 0) pthread_mutex_unlock( &w_mutex );
	pthread_mutex_unlock( &rc_mutex );
	}

/* Write action lock */

void WriteLock( ) {

	pthread_mutex_lock(&r_mutex);
	pthread_mutex_lock(&w_mutex);
	}

/* Write action unlock */

void WriteUnlock( ) {
	pthread_mutex_unlock(&w_mutex);
	pthread_mutex_unlock(&r_mutex);
	}

/**********************************************************************/
/* Below is the program for testing the above protocol.               */
/* We create several readers which read `current_time' and writers    */
/* which set `current_time'.                                          */
/**********************************************************************/

void ReadyToGo( )	{

	pthread_mutex_lock( &ready_mutex );
	ready++;
	pthread_mutex_unlock( &ready_mutex );
	pthread_cond_signal( &ready_cond );
	pthread_mutex_lock( &go_mutex );
	while ( go == 0 ) pthread_cond_wait( &go_cond, &go_mutex );
	pthread_mutex_unlock( &go_mutex );
	}

void *Reader( void *arg )	{
  
	int i, j;
	int local_time;

	ReadyToGo( );

	for ( i = 0; i < 100; i++ ) {

		
		ReadLock();
		for (j = 0; j < 1000000; j++) local_time = current_time;
		/* screen lock is necessary for readers because multiple readers
		    can print simultanously. */
		pthread_mutex_lock(&screen);
		fprintf( stderr, "Thread %lu : i = %d read current_time = %d\n", (long unsigned)pthread_self(), i, local_time );
		pthread_mutex_unlock(&screen);
		ReadUnlock();
		}
		
	return NULL;
	}

void *Writer( void *arg )	{
	int i, j;
	
	ReadyToGo( );
	
	for ( i = 0; i < 100; i++ ) {
		WriteLock( );
		for ( j = 0; j < 100000; j++ ) current_time = time( 0 );
		fprintf( stderr, "Thread %lu : i = %d write current_time = %d\n", (long unsigned)pthread_self(), i, current_time );
		WriteUnlock( );
		}
		
	return NULL;
	}

int main( void )	{
	int i;
	pthread_t rid[READERS], wid[WRITERS];

	for ( i = 0; i < READERS; i++ ) {
		pthread_create( &rid[i], NULL, Reader, NULL );
	}
	for ( i = 0; i < WRITERS; i++ ) {
		pthread_create( &wid[i], NULL, Writer, NULL );
	}

	pthread_mutex_lock( &ready_mutex );
	while (ready != READERS + WRITERS )
	pthread_cond_wait( &ready_cond, &ready_mutex );
	pthread_mutex_unlock( &ready_mutex );
	go = 1;
	pthread_cond_broadcast( &go_cond );

	for ( i = 0; i < READERS; i++ ) {
		pthread_join( rid[i], NULL );
	}
	for ( i = 0; i < WRITERS; i++ ) {
		pthread_join( wid[i], NULL );
	}

	return 0;
	}
