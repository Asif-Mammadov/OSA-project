#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include "shm.h"
#include "message.h"

int main()
{
    int SharedMemID;
    struct Memory *SharedMemPtr;
    //getting process pid, to send via shared memory
    pid_t pid = getpid();          
    //a key based on path and id that is usable in subsequent calls
    key_t ProgKey = ftok(".", 'x'); 

    //an identifier for the shared memory segment
    SharedMemID = shmget(ProgKey, sizeof(struct Memory), 0666 | IPC_CREAT);
    if (SharedMemID < 0)
    {
        printf("*** shmget error (server) ***\n");
        exit(1);
    }
    //attach shared memory segment
    SharedMemPtr = (struct Memory *)shmat(SharedMemID, (void *)0, 0); 

    SharedMemPtr->SHpid = pid;

    //calling signal handlers
    if (signal(SIGINT, handler_SIGINT) == SIG_ERR)
    {
        printf("SIGINT intall error\n");
        exit(1);
    }
    if (signal(SIGQUIT, handler_SIGQUIT) == SIG_ERR)
    {
        printf("SIGQUIT intall error\n");
        exit(2);
    }
    if (signal(SIGTERM, handler_SIGTERM) == SIG_ERR)
    {
        printf("SIGTERM intall error\n");
        exit(3);
    }

    while (1) //loop
    {
        printf("\nTo shut down server press \"S\" button\n");
        char c;
        scanf(" %c", &c);

        if (c == 's' || c == 'S')
        {
        	//detach shared memory segment.
            shmdt(SharedMemPtr);              
            //destroy shared memory.
            shmctl(SharedMemID, IPC_RMID, NULL); 
            exit(4);
        }
        sleep(1);
    }

    return 0;
}
