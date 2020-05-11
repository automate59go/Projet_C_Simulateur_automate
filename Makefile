CC = gcc
POINTH = automateFunc.h readFile.h

automate:  readFile.o automateFunc.o automate.o 
	$(CC) -o automate readFile.o automateFunc.o automate.o

readfile.o: readFile.c reaFile.h automateFunc.h
	$(CC) -c -o readFile.o readFile.c

automateFunc.o: automateFunc.c automateFunc.h readFile.h
	$(CC) -c  -o automateFunc.o automateFunc.c

automate.o: automate.c $(POINTH)
	$(CC) -c -o automate.o automate.c