#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define FILE_NAME           "teste.txt"
#define NUMBER_EXECUTIONS   2
#define TRUE                1
#define FALSE               0

void write_file(int lockFile){

    FILE* fd = fopen(FILE_NAME, "a");

    if(lockFile){
        flockfile(fd);
    }

    char hostname[1024];
    gethostname(hostname, 1024);

    struct timeval uSec;
    time_t current_time = time(0);

    gettimeofday(&uSec, NULL);

    struct tm *current = localtime(&current_time);
    fprintf(fd,"Docker name: %s  Time: %d:%d:%d\n", hostname, current->tm_hour, current->tm_min, current->tm_sec);


    if(lockFile){
        funlockfile(fd);
    }

    fclose(fd);
}

int main(int argc, char **argv) {
    int nExecutions = NUMBER_EXECUTIONS;

    while(nExecutions--){
        if(argc > 1) {
            write_file(TRUE);
        } else {
            write_file(FALSE);
        }
        sleep(5);
    }

    return 0;
}