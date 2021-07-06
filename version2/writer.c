#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "message.h"

int main()
{

    while (1)
    {

        key_t key;
        int message_id;
        int category;

        message_id = que();
        message.message_type = 1;

        clean();

        category = get_category();
        error_message_writer(category, message_id);
        message_writer(category);
        msgsnd(message_id, &message, sizeof(message), 0);
    }
    return 0;
}
