all: pilha_encadeada.o main.o
	gcc *.o -o selection -std=c99 -Wall

pilha_encadeada.o:
	gcc -c pilha_encadeada.c

main.o:
	gcc -c main.c

clean:
	rm selection *.o *.zip

zip:
	zip selection makefile *.c *.h README.txt

run:
	./selection