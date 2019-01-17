#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
/**
 * THESE DEFINE VALUES CANNOT BE CHANGED.
 * DOING SO WILL CAUSE POINTS TO BE DEDUCTED
 * FROM YOUR GRADE (15 points)
 */
 /** BEGIN VALUES THAT CANNOT BE CHANGED */
#define MAX_THREADS 16
#define MAX_ITERATIONS 40
/** END VALUES THAT CANNOT BE CHANGED */


/**
 * use this struct as a parameter for the function
 * nanosleep. 
 * For exmaple : nanosleep(&ts, NULL);
 */
struct ThreadArgs
{
    pthread_t tid;
    int id;
    //int count;
};

struct timespec ts = {0, 12};
int globalValue = 0;

/*void* thread_func(void * arg)
{
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    int i;
    for(i =0; i <= args->count;i++)
    {
        printf("Thread id: %-4d,Count Value: %-5d\n", args->id, i);
    }
    return NULL;
}*/  

void* adderThread (void * arg) {

	struct ThreadArgs* args = (struct ThreadArgs*)arg;
	int i ;

    nanosleep(&ts, NULL);

	for (i = 0; i <= MAX_ITERATIONS; i++){

        //nanosleep(&ts, NULL);

		int temp = globalValue;

        nanosleep(&ts, NULL);
		
		temp = temp + 3;
		globalValue = temp;

		printf("Current Value written to Global Variables by ADDER thread id: %lu is %d\n", args -> tid, globalValue);
	}
}

void* subtractorThread (void * arg) {

	struct ThreadArgs* args = (struct ThreadArgs*)arg;
	int i ;

    nanosleep(&ts, NULL);

	for (i = 0; i <= MAX_ITERATIONS; i++){

        //nanosleep(&ts, NULL);

		int temp = globalValue;

        nanosleep(&ts, NULL);
		
		temp = temp - 3;
		globalValue = temp;

		printf("Current Value written to Global Variables by SUBTRACTOR thread id: %lu is %d\n", args -> tid, globalValue);
	}
}

int
main(int argc, char const *argv[])
{
	//declare an array of structs of size MAX_THREADS
    struct ThreadArgs thread_info[MAX_THREADS];
    int i, ret_val;

    nanosleep(&ts, NULL);

    //create MAX_THREADS threads
    for(i=0; i < MAX_THREADS;i++)
    {
        nanosleep(&ts, NULL);
    	//save thread-s info in next struct
        thread_info[i].id = i+1;
        //thread_info[i].count = 10-i;
        //ret_val = pthread_create(&thread_info[i].tid, NULL, thread_func, (void *)&thread_info[i]);
        
        if(ret_val < 0)
        {
            perror("Error creating thread..");
            return -2;
        }

        //even numbered iterations
        if (i % 2 == 0){
        	ret_val = pthread_create(&thread_info[i].tid, NULL, adderThread, (void *)&thread_info[i]);
            //nanosleep(&ts, NULL);
        	//adderThread(ret_val);
        }

        //odd numbered iterations
        else {
        	ret_val = pthread_create(&thread_info[i].tid, NULL, subtractorThread, (void *)&thread_info[i]);
            //nanosleep(&ts, NULL);
        	//subtractorThread(ret_val);
        }
    }
                                                                                                                              
    for(i = 0; i < MAX_THREADS; i++)
    {
        ret_val = pthread_join(thread_info[i].tid, NULL);
        if(ret_val)
        {
            perror("Error joining thread: ");
            return -3;
        }
    }

    //printf("Main Has Joined All Threads\n");
    printf("Final Value of Shared Var: %d\n", globalValue);
    return 0;
}
