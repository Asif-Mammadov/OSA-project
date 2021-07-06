//structure for the message que to store its type and the message itself
struct message
{
    long message_type;
    char message_text[6000];
} message;

//generates a unique key, creates a message que and returns its id
int que();

//integer message_id : id of the message que
//structure message: structure of the message to be sent
//the function is used for the "reader" programm, in case the index sent was not 1 2 or 3, it prints the cause of error, terminates the programm and the message que
void error_message_reader(int message_id, struct message message);

//integer category: can be 1 2 or 3, respectively represents student, Azerbaijani, French recipes
//based on the category the function message_writer opens the directory 1 2 or 3 and reads all the recipes inside and stores is in the message structure
void message_writer(int category);

// integer category: can be 1 2 or 3, respectively represents student, Azerbaijani, French recipes
//message_id : id of the message que
//if the category is not 1,2 or 3 the function sends '0' to the reader programm (as indicator of error), terminates the programm and the message que
void error_message_writer(int category, int message_id);

//gets the integer from the user via STDIO for the category on the "writer" programm
int get_category();

//initilizing the message before writting new one, so the new message will not collide with the old one
void clean();

//integer category: can be 1 2 or 3, respectively represents student, Azerbaijani, French recipes
//string recipe_type: represents the category of recipe in string format ("student", "Azerbaijani", "French")
//string signal: represents the type of signal which was called
//this function based is called when signals SIGINT, SIGQUIT or SIGTERM are called
//the function reads the needed recipe from file, stores it in message and sends it to the client
void handler(int category, char *recipe_type, char *signal);