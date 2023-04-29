#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "crawler.h"



struct trieNode* indexPage(const char* url, int MAXSIZE)
{
    int totalWords = 0;

   
    char *buffer = malloc(MAXSIZE * sizeof(char));

   
    int size = getText(url, buffer, MAXSIZE);

    if (size == 0) {
        return NULL;
    }


    buffer = realloc(buffer, size);

    
    struct trieNode *rootNode = malloc(sizeof(struct trieNode));

   
    char *string = malloc(30 * sizeof(char));
    char tmpString[2];

    
    for (int i=0; i < MAXSIZE; i++) {
       
        if ( (buffer[i] >= 65 && buffer[i] <= 90) || (buffer[i] >= 97 && buffer[i] <= 122) ) {

            
            tmpString[0] = buffer[i];
            tmpString[1] = '\0';
            strcat(string, tmpString);
        }
            
        else if (string[0] != '\0') {
            addWordOccurrence(string, strlen(string), rootNode);
            totalWords++;
            string[0] = '\0';
        }
    }

    free(buffer);
    free(string);

    rootNode->wordCount = totalWords;
    rootNode->address = malloc(strlen(url) + 1);
    rootNode->numOf = 0;
    strcpy(rootNode->address, url);

    return rootNode;
}

int addWordOccurrence(const char* word, const int wordLength, struct trieNode *pNode) {
    
    char firstChar = word[0];
    
    const char *newStr = word+1;

    .
    if (firstChar >= 65 && firstChar <= 90) {
        
        firstChar += 32;
    }


    
    int charABC = firstChar - 97;


    if (pNode->children[charABC] != NULL) {

        
        if (wordLength > 1) {
            addWordOccurrence(newStr, strlen(newStr), pNode->children[charABC]);
        }
        else if (wordLength == 1) {
            pNode->children[charABC]->numOf++;
        }
        return 0;
    }

    
    struct trieNode *newNode = malloc(sizeof(struct trieNode));
    newNode->numOf = 0;

   
    pNode->children[charABC] = newNode;

    
    if (wordLength > 1) {
        addWordOccurrence(newStr, strlen(newStr), newNode);
    }
    else if (wordLength == 1) {
        newNode->numOf++;
    }

    return 0;
}

void printtrieContents(struct trieNode *pNode) {
  
    if (pNode->numOf > 0) {
        printf("  %s - %d\n", globalString, pNode->numOf);
    }

    for (int i = 0; i < 26; i++) {
        if (pNode->children[i] != NULL) {
            globalString[strlen(globalString)] = i + 97;
            printtrieContents(pNode->children[i]);
            globalString[strlen(globalString) - 1] = '\0';
        }
    }
}

int freetrieMemory(struct trieNode *pNode) {

    
    for (int i = 0; i < 26; i++) {
        if (pNode->children[i] != NULL) {
            freetrieMemory(pNode->children[i]);
            
        }
        
    }
    free(pNode);
    return 0;
}


int findWordCount(char* word, struct trieNode *pNode) {
    char firstChar = tolower(word[0]);

    if (pNode->children[firstChar-97] == NULL) {
        return 0;
    }

    if (strlen(word) > 1) {
        return findWordCount(word + 1, pNode->children[firstChar - 97]);
    }
    else if (strlen(word) == 1) {
        return pNode->children[firstChar - 97]->numOf;
    }
    return 0;
}
