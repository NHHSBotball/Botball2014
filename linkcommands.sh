cd /kovan/src/Botball2014
gcc -lkovan -o /kovan/binaries/primary primary.c -Wall
gcc -lkovan -o /kovan/binaries/test test.c -Wall
gcc -lkovan -lncurses -o /kovan/binaries/create-drive create-drive.c -Wall