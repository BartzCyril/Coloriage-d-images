CFLAGS += -Wall -Wextra
CC = gcc
DOBJ = obj
DBIN = bin

ifeq (TEST,$(MODE)) 

bin/projet : obj/test.o obj/fonctions.o obj/liste.o obj/arbre.o
	$(CC) -g $(CFLAGS) obj/test.o obj/fonctions.o obj/liste.o obj/arbre.o -o bin/projet

obj/test.o : testUnitaire/test.c includes/fonctions.h includes/liste.h includes/arbre.h includes/utils.h
	$(CC) -g $(CFLAGS) -c testUnitaire/test.c 

	mv test.o $(DOBJ)

obj/fonctions.o : src/fonctions.c includes/fonctions.h includes/utils.h
	$(CC) -g $(CFLAGS) -c src/fonctions.c 

	mv fonctions.o $(DOBJ)

obj/liste.o : src/liste.c includes/liste.h includes/fonctions.h includes/utils.h
	$(CC) -g $(CFLAGS) -c src/liste.c

	mv liste.o $(DOBJ)

obj/arbre.o : src/arbre.c includes/arbre.h includes/fonctions.h includes/utils.h
	$(CC) -g $(CFLAGS) -c src/arbre.c 

	mv arbre.o $(DOBJ)

else
bin/projet : obj/main.o obj/fonctions.o obj/liste.o obj/arbre.o
	$(CC) -g $(CFLAGS) obj/main.o obj/fonctions.o obj/liste.o obj/arbre.o -o bin/projet

obj/main.o : src/main.c includes/fonctions.h includes/liste.h includes/arbre.h includes/utils.h
	$(CC) -g $(CFLAGS) -c src/main.c 

	mv main.o $(DOBJ)

obj/fonctions.o : src/fonctions.c includes/fonctions.h includes/utils.h
	$(CC) -g $(CFLAGS) -c src/fonctions.c 

	mv fonctions.o $(DOBJ)

obj/liste.o : src/liste.c includes/liste.h includes/fonctions.h includes/utils.h
	$(CC) -g $(CFLAGS) -c src/liste.c

	mv liste.o $(DOBJ)

obj/arbre.o : src/arbre.c includes/arbre.h includes/fonctions.h includes/utils.h
	$(CC) -g $(CFLAGS) -c src/arbre.c 

	mv arbre.o $(DOBJ)
endif

archive : 
	tar -cf BARTZ.tar.gz main.c fonctions.c fonctions.h liste.c liste.h arbre.c arbre.h Makefile README.md Doxyfile

install : 
	mkdir -p $(DOBJ)
	mkdir -p $(DBIN)
	
doc : 
	mkdir -p doc
	doxygen
	mv html/ doc
	rm -rf latex/
	xdg-open doc/html/index.html

clean : 
	rm -f obj/*.o bin/*
	rm -rf doc/ obj/ bin/


