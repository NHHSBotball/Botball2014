cd /kovan/src/Botball2014
#READ BUILD FILE and only build the programs you want.
#gcc -lkovan -o /kovan/binaries/all-off all-off.c -Wall
#gcc -lkovan -o /kovan/binaries/primary primary.c -Wall
gcc -lkovan -o /kovan/binaries/test test.c -Wall -std=c99
gcc -lkovan -o /kovan/binaries/test2 test2.c -Wall -std=c99
#gcc -lkovan -o /kovan/binaries/test3 test3.c -Wall -std=c99
#gcc -lkovan -o /kovan/binaries/calibrate calibrate.c -Wall -std=c99
#gcc -lkovan -o /kovan/binaries/botguy-primary botguy-primary.c -Wall -std=c99
#gcc -lkovan -lncurses -o /kovan/binaries/create-drive create-drive.c -Wall