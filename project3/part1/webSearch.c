#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "crawler.h"


int main(int argc, char** argv) {

   
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
    srand((int)SEED);

    const int MAXSIZE = 100000;
   
    char buffer[100];
    char url[100];
    int numHops;
    int hopsLimit;
    int numIndexed = 0;
    int isIndexed = 0;

    struct trieNode *pNodes[MAXINDEX];

  
    while(fgets(buffer, 100, openFile) && numIndexed < MAXINDEX) {
        sscanf(buffer, "%s %d", url, &hopsLimit);
        numHops = 0;

       
        while (1) {

           
            for (int i = 0; i < numIndexed; i++) {
                if (strcmp(url, pNodes[i]->address) == 0) {
                    isIndexed = 1;
                }
            }

           
            if (isIndexed == 0) {
                printf("Indexing page: %s\n", url);
                pNodes[numIndexed] = indexPage(url, MAXSIZE);
                if (pNodes[numIndexed] == NULL) {
                    printf("INDEX FAILED.\n");
                    isIndexed = 0;
                    break;
                }
                printtrieContents(pNodes[numIndexed]);
                numIndexed++;
            }
            else if (isIndexed == 1)
            {
                isIndexed = 0;
            }
            numHops++;


           
            if (numHops <= hopsLimit && numIndexed < MAXINDEX) {

                getLink(url, url, 1000);
            }
            else {
                break;
            }
        }
    }


  
    for (int i = 0; i<numIndexed; i++) {
        printf("Indexed page: %.25s...(%d words)\n", pNodes[i]->address, pNodes[i]->wordCount);
        freetrieMemory(pNodes[i]);
    }

    return 0;
}