In 1. Open a Linux terminal inside the folder containing source codes and compile both source codes inside the terminal by entering the commands `gcc writer.c functions.c -o writer` and `gcc reader.c functions.c -o reader`.
>It can be compiled to program of any name of choosing by changing the word that comes after `-o`
2. Open another Linux terminal
3. In one of the terminals, run the Server program by entering `./writer` or whichever name you've given it
4. In the other terminal, run the Client program by entering `./reader` or whichever name you've given it
5. Doing this will prompt you to enter an index, which should be either of `1`, `2` or `3`. Entering another value will cause an error.
6. Entering 1 will display student recipes in the other terminal, entering 2 will display Azerbaijani recipes and entering 3 will display French recipes
7. You can stop the program by pressing Ctrl+Z button combination inside the terminal 
