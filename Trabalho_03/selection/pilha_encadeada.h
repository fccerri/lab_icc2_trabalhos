#ifndef PILHA_E
    #define PILHA_E
    #define ERRO -1
    #include <stdbool.h>

    typedef struct pair_ {
        char nome[51];
        int nota;
    }pair;

    typedef struct pilha_ PILHA;

    PILHA* pilha_criar(int tam);
    void pilha_apagar(PILHA** pilha);
    bool pilha_vazia(PILHA* pilha);
    bool pilha_cheia(PILHA* pilha);
    int pilha_tamanho(PILHA* pilha);
    pair pilha_topo(PILHA* pilha);
    bool pilha_empilhar(PILHA* pilha, pair dado);
    pair pilha_desempilhar(PILHA* pilha);
    void pilha_print(PILHA* p);



#endif
