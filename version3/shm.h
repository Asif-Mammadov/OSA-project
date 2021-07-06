#include <unistd.h>

struct Memory
{
    pid_t SHpid;
};

//integer category: can be 1 2 or 3, respectively represents student, Azerbaijani, French recipes
//if the category is anything other than 1 2 or 3, the error message is displayed on console and the programm terminates
//process identification pid: id of the current proccess
//the function sends the according signal based on category (SIGINT for student, SIGQUIT for Azerbaijani, SIGTERM for French )
//the function is used for "client" programm
void send_signal(int category, pid_t pid);

//returns process identificator
//pointer to Memory structure SharedMemPtr
//the function is used to create shared memory and return the id of the process
pid_t shared_mem(struct Memory *SharedMemPtr);

//handler for SIGINT signal, used by "server" programm
void handler_SIGINT(int);

//handler for SIGQUIT signal, used by "server" programm
void handler_SIGQUIT(int);

//handler for SIGTERM signal, used by "server" programm
void handler_SIGTERM(int);
