CC = gcc
CFLAGS = -g
# OBJS = webSearch.o crawler.o helper.o trie.o


webSearch: webSearch.c trie.c helper.c crawler.h
	$(CC) -c webSearch.c -o webSearch.o -Wall
	$(CC) -c trie.c -o trie.o -Wall
	$(CC) -c helper.c -o helper.o -Wall
	$(CC) webSearch.o trie.o helper.o -o webSearch -Wall
	
clean:
	rm *.o 