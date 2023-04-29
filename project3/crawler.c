#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    ///////////////////////////////////////////////////////
    if (argc != 4) {
        printf("Usage: ./program FILENAME MAXINDEX SEED\n");
        return -1;
    }

    FILE *openFile;
    openFile = fopen(argv[1], "r");
    if (openFile == NULL) {
        printf("Error. File not found.\n");
        return -1;
    }

    const int MAXINDEX = atoi(argv[2]);

    const long SEED = atoi(argv[3]);
    ///////////////////////////////////////////////////////
    char buffer[100];
    char string[100];
    int hopsInt;

    while(fgets(buffer, 100, openFile)) {
        sscanf(buffer, "%s %d", string, &hopsInt);


        printf("%s %d\n", string, hopsInt);
    }
    
}