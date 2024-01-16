/*This algorithm uses the concept of greedy algorithms and the heap data 
structure to find the optimal solution to the problem.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numero;
    int duracao;
    int instante;
} Atualizacao;

typedef struct {
    Atualizacao *atualizacoes;
    int tamanho;
} Heap;

void Imprimir(int atualizacoes[], int n, FILE *saida ) {

    fprintf( saida,"%d", n);
    for (int i = 0; i < n; i++) {
        fprintf( saida," %d" , atualizacoes[i] );
    }
}

void trocar( Atualizacao *a, Atualizacao *b ) {
    Atualizacao temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify( Heap *heap, int indice ) {
    int menor = indice;
    int esquerda = 2 * indice + 1;
    int direita = 2 * indice + 2;

    if ( esquerda < heap->tamanho ) {
        if (heap->atualizacoes[esquerda].duracao < heap->atualizacoes[menor].duracao ||
            (heap->atualizacoes[esquerda].duracao == heap->atualizacoes[menor].duracao &&
             heap->atualizacoes[esquerda].numero < heap->atualizacoes[menor].numero)) {
            menor = esquerda;
        }
    }

    if ( direita < heap->tamanho ) {
        if (heap->atualizacoes[direita].duracao < heap->atualizacoes[menor].duracao ||
            (heap->atualizacoes[direita].duracao == heap->atualizacoes[menor].duracao &&
             heap->atualizacoes[direita].numero < heap->atualizacoes[menor].numero)) {
            menor = direita;
        }
    }

    if ( menor != indice ) {
        trocar(&heap->atualizacoes[indice], &heap->atualizacoes[menor]);
        minHeapify(heap, menor);
    }
}

void reconstruirHeap( Heap *heap, int indice ) {
    
    while ( indice > 0 && 
           (heap->atualizacoes[(indice - 1) / 2].duracao > heap->atualizacoes[indice].duracao ||
            (heap->atualizacoes[(indice - 1) / 2].duracao == heap->atualizacoes[indice].duracao &&
             heap->atualizacoes[(indice - 1) / 2].instante > heap->atualizacoes[indice].instante))) {
      
        trocar(&heap->atualizacoes[indice], &heap->atualizacoes[(indice - 1) / 2]);
    
        indice = ( indice - 1 ) / 2;
    }

    minHeapify(heap, indice);
}

Atualizacao encontrarERetirarMenor( Heap *heap ) {
    if ( heap->tamanho == 0 ) {
        Atualizacao valorSentinela = {0, 0, -1};
        return valorSentinela;
    }

    Atualizacao menor = heap->atualizacoes[0];

    trocar(&heap->atualizacoes[0], &heap->atualizacoes[heap->tamanho - 1]);
    
    heap->tamanho--;

    minHeapify(heap, 0);

    return menor;
}

void subirNaHeap( Heap *heap, int indice ) {
    int pai = (indice - 1) / 2;

    while ( indice > 0 && 
           (heap->atualizacoes[pai].duracao > heap->atualizacoes[indice].duracao ||
            (heap->atualizacoes[pai].duracao == heap->atualizacoes[indice].duracao &&
             heap->atualizacoes[pai].instante > heap->atualizacoes[indice].instante))) {
        trocar(&heap->atualizacoes[indice], &heap->atualizacoes[pai]);
        indice = pai;
        pai = (indice - 1) / 2;
    }
}

void adicionarNo( Heap *heap, int numero, int duracao, int instante ) {
    Atualizacao no;
    no.numero = numero;
    no.duracao = duracao;
    no.instante = instante;

    // Adicionar o novo nó na última posição
    int posicao = heap->tamanho;
    heap->atualizacoes[posicao] = no;
    heap->tamanho++;

    subirNaHeap( heap, posicao );
   
}

void inserirAtualizacao( Heap *heap, Atualizacao novaAtualizacao ) {

    int indice = heap->tamanho;
    heap->atualizacoes[indice] = novaAtualizacao;
    heap->tamanho++;

    while ( indice > 0 && 
           (heap->atualizacoes[(indice - 1) / 2].duracao > heap->atualizacoes[indice].duracao ||
            (heap->atualizacoes[(indice - 1) / 2].duracao == heap->atualizacoes[indice].duracao &&
             heap->atualizacoes[(indice - 1) / 2].instante > heap->atualizacoes[indice].instante ))) {
        trocar( &heap->atualizacoes[indice] , &heap->atualizacoes[(indice - 1) / 2] );
        indice = (indice - 1) / 2;
    }
}

void buscarEAtualizar(Heap *heap, int numero, int novaDuracao, int novoInstante) {

    int i;
    for ( i = 0; i < heap->tamanho; i++ ) {
        if (heap->atualizacoes[i].numero == numero) {
            break; 
        }
    }
    if ( i < heap->tamanho ) {
        // Atualizar valores do nó encontrado
        heap->atualizacoes[i].duracao = novaDuracao;
        heap->atualizacoes[i].instante = novoInstante;

    } 
    reconstruirHeap( heap, i );
}

Heap construirHeapInicial( int Qa , int lista_duracoes[] ,int j ) {
    Heap heap;
    heap.tamanho = 0;
    heap.atualizacoes = ( Atualizacao * )malloc(( Qa + j ) * sizeof( Atualizacao ));

    // Inserir elementos da lista no heap
    for ( int i = 0; i < Qa; i++ ) {
    Atualizacao novaAtualizacao;
    novaAtualizacao.numero = i + 1;
    novaAtualizacao.duracao = lista_duracoes[i];
    novaAtualizacao.instante = -1; 
    inserirAtualizacao( &heap, novaAtualizacao );
    }

    int ultimoPai = ( heap.tamanho - 2 ) / 2;
    for ( int i = ultimoPai; i >= 0; i-- ) {
        minHeapify( &heap, i );
    }
    return heap;
}

void selectionSort( int arr[], int indices[], int n ) {

    int i, j, minIndex, temp;

    for (i = 0; i < n - 1; i++) {
        minIndex = i;

        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;

        // Troca o índice correspondente
        temp = indices[minIndex];
        indices[minIndex] = indices[i];
        indices[i] = temp;
    }
}

void CenarioB( int Qa, Heap *heap, int horas,int alteracao[], int inclusao[], int j, int k, FILE *saida) {

    Atualizacao no;
    int total = 0;
    int resultado [Qa+j/3+k/3];
    int nk = 0;
    int nj = 0;
    int soma = 0;

    while( soma < horas ){

    no = encontrarERetirarMenor(heap);
    resultado[total] = no.numero;
    soma+= no.duracao;

    if( soma >= alteracao[nk] && nk < k ){
        buscarEAtualizar( heap, alteracao[nk+1], alteracao[nk+2], alteracao[nk] );
        nk+=3; 
    }

    if( soma >= inclusao[nj] && nj < j ){
        adicionarNo( heap,inclusao[nj+1], inclusao[nj+2], inclusao[nj] );
        nj+=3; 
    }
    total++;
    }
    Imprimir(resultado, total, saida);
    }

void CenarioA(int n, int horas, int arr[], FILE *saida) {
    int sum = 0;
    int total = 0;

    int indices[n];

    for (int i = 0; i < n; i++) {
        indices[i] = i + 1;
    }

    selectionSort(arr, indices, n);

    for (int i = 0; i < n; i++) {
        if (sum + arr[i] <= horas) {
            sum += arr[i];
            total++;
        } else {
            break;
        }
    }

Imprimir(indices,total,saida);
}

int main( int argc, char *argv[] ){
    FILE *arq;
    arq = fopen(argv[3], "r"); 

    int Qa;
    fscanf(arq, "%d", &Qa);

    int lista [Qa];
    
    if ( arq == NULL ) {
        printf("Não foi possível abrir o arq \n");
        exit(-1);      
    } else{

        for (int i = 0; i < Qa; i++) {
            fscanf(arq, "%d", &lista[i]);
        }
        
    switch (atoi(argv[2]))
    {
    case 1: //Cenário 1
    
        FILE *saida1 = fopen( "saida1.txt", "w" );
        if ( saida1 == NULL ) {
        fprintf( stderr, "Não foi possível criar o arquivo de saída 1.\n" );
        return -1;}
        CenarioA( Qa, atoi(argv[1]) ,lista, saida1 );
        break;

    case 2: //Cenário 2

        FILE *saida2 = fopen( "saida2.txt", "w" );
        if ( saida2 == NULL ) {
        fprintf( stderr, "Não foi possível criar o arquivo de saída 2.\n" );
        return -1;}

        char operacao;
        int k = 0; // alterações totais
        int j = 0; // inclusões totais

        int alteracao[100];
        int inclusao[100];
        
        while (fscanf(arq, " %c", &operacao) == 1) {
            if (operacao == 'c') {
                fscanf(arq, " %d %d %d", &alteracao[k], &alteracao[k + 1], &alteracao[k + 2]);
                k += 3;
            } else if (operacao == 'i') {
                fscanf(arq, " %d %d %d", &inclusao[j], &inclusao[j + 1], &inclusao[j + 2]);
                j += 3;
            }
        }

        Heap heap = construirHeapInicial(Qa, lista,j);

        CenarioB(Qa, &heap, atoi(argv[1]),alteracao, inclusao, j, k, saida2);

        free(heap.atualizacoes);

        break;
    default:
        printf("O valor não corresponde a nenhum cenário!\n");
        break;
    }
    fclose(arq);
    return 0;
}
}
