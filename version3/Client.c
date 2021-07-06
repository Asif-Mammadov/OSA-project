#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "shm.h"
#include "message.h"

int main(void)
{
    int message_id;
    //shared memory for processes
    pid_t pid;
    struct Memory *SharedMemPtr;

    pid = shared_mem(SharedMemPtr);

    shmdt(SharedMemPtr); //detach shared memory segment

    while (1)
    {
        //getting category from the user
        int category = get_category();
        //sending signal to the Server according to the category
        send_signal(category, pid);
        message_id = que(); //creating message que

        //receiving message from the client, 
        //checking for error and printing it on the console
        msgrcv(message_id, &message, sizeof(message), 1, 0);
        error_message_reader(message_id, message);
        printf("Data Received is : %s \n",
               message.message_text);
    }
    //terminating message que
    msgctl(message_id, IPC_RMID, NULL);
    return 0;
}
