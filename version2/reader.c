#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message.h"

int main()
{
	int message_id;

	while (1)
	{
		message_id = que();
		//receiving message from the client, checking for error and printing it on the console
		msgrcv(message_id, &message, sizeof(message), 1, 0);
		error_message_reader(message_id, message);
		printf("Data Received is : %s \n",
			   message.message_text);
	}
	//terminating message que

	msgctl(message_id, IPC_RMID, NULL);

	return 0;
}
