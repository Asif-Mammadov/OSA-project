#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <dirent.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include "message.h"

//creates a message que and returns its id if ran successfully
//in case the unique key was not generated or the message_id was not generated
//the programm terminates by displaying error on the console
int que()
{
    key_t key;
    int message_id;

    key = ftok("/etc/passwd", 'F');
    if (key == -1)
        perror("ftok failure");

    message_id = msgget(key, 0666 | IPC_CREAT);
    if (message_id == -1)
        perror("msgget failure");

    return message_id;
}

void clean()
{
    for (int i = 0; i < 6000; i++)
    {
        message.message_text[i] = '\0';
    }
}

//when the "reader" programm gets the message which starts with '0'
//it indicates that the user in "writer" programm inputted the wrong index
//based on this information the "reader" programm displays the error message on console,
//terminates the programm and the message que
void error_message_reader(int message_id, struct message message)
{
    if (message.message_text[0] == '0')
    {
        printf("The wrong index of recipe was entered so the programm is terminated\n");
        printf("Next time input 1 for recipes for students\n");
        printf("2 for Azerbaijani recipes\n");
        printf("3 for French recipes\n");
        msgctl(message_id, IPC_RMID, NULL);
        exit(1);
    }
}

//simple function to get the input of the category of recipe from console for "writer" programm
int get_category()
{
    int category;
    printf("Input index to get the recipe: ");
    scanf("%d", &category);
    return category;
}

/* the function opens the directory based on category
in the directory the function reads all files inside
 and stores 
the information read in the message
in case the programm failed to open the directory 
or the files it terminates and shows the  corresponding error*/
void message_writer(int category)
{
    DIR *dr;
    FILE *f;
    char ch;
    int count = 0;
    char category_path[100];
    char recipe_file_path[500];
    sprintf(category_path, "%s%d/", "./recipes/", category);
    struct dirent *de;

    //opening the directory
    dr = opendir(category_path);
    if (dr == NULL)
    {
        perror("opendir");
        exit(1);
    }
    //going through files in the directory
    while ((de = readdir(dr)) != NULL)
    {
        if (de->d_name[0] == '.')
            continue;
        sprintf(recipe_file_path, "%s%s", category_path, de->d_name);
        f = fopen(recipe_file_path, "r");
        if (f == NULL)
        {
            perror("No such file");
            exit(1);
        }
        //storing the insides of file in the message structure
        while ((ch = fgetc(f)) != EOF)
        {
            message.message_text[count] = ch;
            count++;
        }
        fclose(f);
    }

    closedir(dr);
}

//when the wrong category is inputted by user (meaning not 1 2 or 3),
//the "writer" programm sends the error message ('0') to the "reader" programm,
//then terminates itself after displaying error message
void error_message_writer(int category, int message_id)
{
    if (category != 1 && category != 2 && category != 3)
    {

        printf("The wrong index of recipe was entered so the programm is terminated\n");
        printf("Next time input 1 for recipes for students\n");
        printf("2 for Azerbaijani recipes\n");
        printf("3 for French recipes\n");
        message.message_text[0] = '0';
        msgsnd(message_id, &message, sizeof(message), 0);
        exit(1);
    }
}
