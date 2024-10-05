CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ_NOMES = gerador_nomes.o nomes.o
OBJ_ALUNOS = gerador_aluno_notas.o nomes.o
TARGET_NOMES = gerador_nomes
TARGET_ALUNOS = gerador_aluno_notas

# Alvo para compilar ambos os programas
all: $(TARGET_NOMES) $(TARGET_ALUNOS)

# Alvo para gerar o executável gerador_nomes
$(TARGET_NOMES): $(OBJ_NOMES)
	$(CC) $(CFLAGS) -o $@ $^

# Alvo para gerar o executável gerador_aluno_notas
$(TARGET_ALUNOS): $(OBJ_ALUNOS)
	$(CC) $(CFLAGS) -o $@ $^

# Regras para os arquivos .o
gerador_nomes.o: gerador_nomes.c nomes.h
	$(CC) $(CFLAGS) -c gerador_nomes.c

gerador_aluno_notas.o: gerador_aluno_notas.c nomes.h
	$(CC) $(CFLAGS) -c gerador_aluno_notas.c

nomes.o: nomes.c nomes.h
	$(CC) $(CFLAGS) -c nomes.c

# Alvo para limpar os arquivos .o e os binários gerados
clean:
	rm -f *.o $(TARGET_NOMES) $(TARGET_ALUNOS)

.PHONY: all clean
