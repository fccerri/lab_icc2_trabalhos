all: quick_select_runcodes.c
	gcc -o quick_select_runcodes quick_select_runcodes.c -Wall -Wextra -std=c99	

teste_zip:
	zip Code_Tester -r CasosTeste notaveis.c *.csv 

runcodes_zip:
	zip runcodes makefile only_sort_runcodes.c quick_select_runcodes.c 

clean:
	rm *.zip quick_select_runcodes only_sort_runcodes notaveis

run: quick_select_runcodes
	./quick_select_runcodes
