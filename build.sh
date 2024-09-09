SRC="*.c ";
gcc --std=c23 -fsanitize=leak -pedantic -Wall -Werror -g -o main $SRC;
