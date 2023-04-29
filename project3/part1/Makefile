CC = gcc
CFLAGS = -g
OBJS = webSearch.o crawler.o helper.o trie.o


webSearch: webSearch.c trie.c helper.c crawler.h
	$(CC) -c webSearch.c -o webSearch.o
	$(CC) -c trie.c -o trie.o
	$(CC) -c helper.c -o helper.o
	$(CC) webSearch.o trie.o helper.o -o webSearch
	
clean:
	rm *.o 