SRC="*.c ";
gcc -fsanitize=leak -pedantic -Wall -Werror -g -o main $SRC;
