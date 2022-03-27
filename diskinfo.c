// #include <stdio.h>
// #include <stdint.h>
// #include <sys/mman.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <string.h>
// #include <sys/types.h>
// #include <stdlib.h>
// #include <time.h>
// #include <limits.h>
// #include <assert.h>


//parse arguments in file
void parse_args(){
    return;
}



int main(int argc, char *argv[]) { 
    char* file;

    //get filename from args
	if (argc < 2) {
		fprintf(stderr, "Usage: Can you spare some arguments?\n");
	} else {
        file = argv[1];
        printf("%s\n", file);
	}
}