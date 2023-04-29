#ifndef CRAWLER_H_
#define CRAWLER_H_

char globalString[25];


struct trieNode{
    int numOf;
    struct trieNode *children[26];
    char *address;
    int wordCount;
};

extern struct trieNode *pNode;

struct trieNode* indexPage(const char* url, int MAXSIZE);

int addWordOccurrence(const char* word, const int wordLength, struct trieNode *pNode);

void printtrieContents(struct trieNode *pNode);

int freetrieMemory(struct trieNode *rootnode);

int findWordCount(char* word, struct trieNode *pNode);

int getText(const char* srcAddr, char* buffer, const int bufSize);

int getLink(const char* srcAddr, char* link, const int maxLinkLength);

#endif