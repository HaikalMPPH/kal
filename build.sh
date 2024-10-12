SRC="*.c ";
gcc --std=c23 -fsanitize=leak,address -pedantic -Wall -Werror -g -o main $SRC;
