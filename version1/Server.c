#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include "shm.h"

//Signal types and recipes.
Recipes Dishes[3][2] =
    {{SIGINT, {"Student", "Overnight oats", "One-Pot Spaghetti Carbonara"}},
     {SIGQUIT, {"Azeri", "YARPAG KHENGELI", "QUTAB"}},
     {SIGTERM, {"Frecnh", "Soupe à l’oignon", "Chocolate soufflé"}}};

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

void printrecipe(int a, int b)
{
    printf("\n");
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 30; i++)
        {
            printf("%c", Dishes[a][b].cooking_recipe_category[j][i]);
        }
        if (j != 2)
            printf(", ");
    }
    printf(".\n");
}

void handler_SIGINT(int message)
{
	//ignore signal, so terminal won't be interrupted.
    signal(message, SIG_IGN); 
    printrecipe(-1, 2);
    
    //handle signal via handler_SIGINT.
    signal(message, handler_SIGINT); 
}
void handler_SIGQUIT(int message)
{ //same principal as before
    signal(message, SIG_IGN);
    printrecipe(0, 2);
    signal(message, handler_SIGQUIT);
}
void handler_SIGTERM(int message)
{
    signal(message, SIG_IGN);
    printrecipe(1, 2);
    signal(message, handler_SIGTERM);
}
