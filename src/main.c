#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define FILE_NAME           "teste.txt"
#define NUMBER_EXECUTIONS   2
#define TRUE                1
#define FALSE               0

void write_file(FILE *fd){

    char hostname[1024];
    gethostname(hostname, 1024);

    struct timeval uSec;
    time_t current_time = time(0);

    gettimeofday(&uSec, NULL);

    struct tm *current = localtime(&current_time);
    fprintf(fd,"Docker name: %s  Time: %d:%d:%d\n", hostname, current->tm_hour, current->tm_min, current->tm_sec);

}

void read_file(FILE *fd){
    char *buffer = NULL;
    int string_size, read_size;

    if (fd)
    {
        fseek(fd, 0, SEEK_END);
        string_size = ftell(fd);

        rewind(fd);

        buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

        read_size = fread(buffer, sizeof(char), string_size, fd);

        buffer[string_size] = '\0';

        if (string_size != read_size)
        {
            free(buffer);
            buffer = NULL;
        }
    }

    printf("\nLeitura:\n %s", buffer);
}

int main(int argc, char **argv) {
    int nExecutions = NUMBER_EXECUTIONS;

    FILE* fd = fopen(FILE_NAME, "a+");

    if(argc > 1){
        flockfile(fd);
    }

    while(nExecutions--){
        write_file(fd);
        read_file(fd);
    }

    if(argc > 1){
        funlockfile(fd);
    }

    fclose(fd);

    return 0;
}