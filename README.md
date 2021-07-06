# OSA-project


## Version 1
The first version of cooking recipe server entails:
- The Cooking recipe server consists of a simple server, which receives signals, and prints
to the screen the matching type of cooking recipe to be printed.
- A Cooking recipe client, which randomly chooses one of the three signals ‘SIGINT’,
‘SIGQUIT’ an ‘SIGTERM’ and sends it to the server. This operation is repeated 100 times.
The client and the server are each a dedicated program in C language.
The association between signal_type and cooking_recipe_category is stored in a matrix.
Use: SIGINT for cooking_recipe_category: ‘Student’, SIGQUIT for
cooking_recipe_category: ’Azeri’, SIGTERM for cooking_recipe_category: ‘French’.

## Version 2

The second version of Cooking recipe server entails:
- A cooking recipe reader program, which creates a message queue for exchanging
cooking recipe text. All cooking recipes are stored in three directories, one directory for
Student Cooking recipes, one directory for Azeri Cooking recipes and one directory for
French Cooking recipes. A method read_cooking_recipe(int category) reads
the message queue of type 1 when the category is 1 (‘student’), and the message queue of
type 2 when the category is 2 (‘Azeri’) and the message queue of type 3 when the
category is 3 (‘French’).
In version 2, the reader must read 2 cooking recipes of each type.
- A cooking recipe writer program, which go through the various cooking recipe
categories (represented as an array). Cooking_recipe_writer is a dedicated
program.
First, store the cooking recipes in three directories: ‘students’, ‘Azeri’ or ’French’, one for
each category. Each cooking recipe is in an individual file.
The cooking recipe writer writes messages of type ‘1’ that contain cooking recipes for
students, of type 2 that contain ‘Azeri’ cooking recipes, and of type 3 that contain
‘French’ cooking recipes.
All available cooking recipes must be read from the files and stored in the message
queue.

## Version 3

The third version of cooking recipe server binds the bricks from version 1 and version 2, to print
a cooking recipe of given type when the matching signal is received.
- In Cooking recipe server, the method read_cooking_recipe(int category)
from the reader is called which suitable value for category when the matching signal is
received: SIGINT for cooking_recipe_category: ‘Student’; SIGQUIT for
cooking_recipe_category: ’Azeri’, SIGTERM for cooking_recipe_category:
‘French’.
- In Cooking recipe writer, check that each category entails an entry. Otherwise, refill it
with the cooking recipes read from the file.
