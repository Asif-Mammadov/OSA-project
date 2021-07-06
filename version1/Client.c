/*File: Client.c , authors Team 1 : Asif Mammadov, Aydin Gasimov , Leyla Gasimova , Sabir Khanlarov.
Date: April 2021 Course : OSA.
Summary: This file contains a dedicated program in C language, which uses shared memory to pass and receive signals(server pid), uses kill function to send signals.
*/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "shm.h"

int main(void)
{
     pid_t pid;
     struct Memory *SharedMemPtr;

     pid = shared_mem(SharedMemPtr);

     shmdt(SharedMemPtr); //detach shared memory segment

     time_t t;
     srand((unsigned)time(&t));

     for (int i = 0; i < 100; i++)
     {
          int random = 1 + (rand() % 3); //generate random number from 1 to 3
          send_signal(random, pid);
          printf("\n-----------------\n");
          sleep(0.3); //to prevent signals overlapping.
     }

     return 0;
}

//returns process identificator
//pointer to Memory structure SharedMemPtr
//the function is used to create shared memory and return the id of the process
pid_t shared_mem(struct Memory *SharedMemPtr)
{
     pid_t pid;
     key_t ProgKey;
     int SharedMemId;
     ProgKey = ftok(".", 'x');  //used to generate a unique key.
     //identifier for shared memory segment.
     SharedMemId = shmget(ProgKey, sizeof(struct Memory), 0666); 
     if (SharedMemId < 0)
     {
          printf("*** shmget error (client) ***\n");
          exit(1);
     }
     //attach shared memory segment
     SharedMemPtr = (struct Memory *)shmat(SharedMemId, (void *)0, 0); 

     pid = SharedMemPtr->SHpid;
     return pid;
}

/* integer category: can be 1 2 or 3, respectively represents
 student, Azerbaijani, French recipes
if the category is anything other than 1 2 or 3, 
the error message is displayed on console and the programm terminates
process identification pid: id of the current proccess
the function sends the according signal 
based on category (SIGINT for student, SIGQUIT for Azerbaijani,
 SIGTERM for French )
the function is used for "client" programm */
void send_signal(int category, pid_t pid)
{
     if (category == 1)
     {
          kill(pid, SIGINT); //send signal to other process.
          printf("Sent a SIGINT signal\n");
     }
     if (category == 2)
     {
          printf("Sent a SIGQUIT signal\n");
          kill(pid, SIGQUIT);
     }
     if (category == 3)
     {
          printf("Sent a SIGTERM signal\n");
          kill(pid, SIGTERM);
     }
}
