O arquivo RunCodes.c só não passou nos ultimos testes pela complexidade alta do selection,
de qlqr forma é pra enviar o Shell Sort lá.
Lembrando que não precisa usar TAD nem pilha pra fazer o Shell Sort, mas ele pediu 
pra enviar o TAD que utilizamos pra ele, no caso é só colocar no relatório.

Na main eu optei por fazer a logica de remoção do array principal simplesmente 
alterando o valor das notas e do nome marcados como mínimo naquela iteração, 
tbm da pra implementar removendo o elemento e movendo todos os subsequentes
mas achei mais simples dessa forma, se quiser eu posso mudar.

Segue o texto com breve explicação da lógica utilizada no Selection sort e na main

O algoritmo de ordenação por seleção se baseia na ideia de percorrer o vetor a ser 
ordenado, buscando sempre o menor (ou maior) elemento e inserindo-o no início desse 
mesmo vetor ou em uma estrutura de dados auxiliar. Para implementá-lo, utilizamos 
dois loops: o primeiro itera sobre todos os elementos do vetor, armazenando em uma 
pilha o menor deles, o segundo reinicia as iterações até que todos os elementos 
estejam ordenados. Por simplicidade, optamos por marcar um item como “removido” ao 
invés de efetivamente retirá-lo do array principal.
Além disso, como solicitado, a pilha utilizada foi implementada como um tipo 
abstrato de dado (TAD). Optamos por implementá-la de forma sequencial e dinâmica. 
Esse TAD possui as funções básicas de: criar, empilhar, desempilhar, verificar o 
topo da pilha, verificar o tamanho, checar se está cheia ou vazia, imprimi-la e 
apagá-la. Aproveitamos as características de um TAD para evitar vazamentos de 
memória e manipular os dados de forma segura.
