/*This program uses the concept of greedy algorithms and recursion to 
obtain the maximal quadrants of the respective dimensions*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 256

int Quadrante[1024][2];

void GuardarQuadrante( int filho[4], int n ) {
    int branco = 0;
    int preto = 0;

    int indice = 0;

    while ( n > 2 ) {
        n /= 2;
        indice++;
    }

    for ( int i = 0; i < 4; i++ ) {
        if( filho[i] != -1 ){
            if( filho[i] == 1 ) branco++;
            else preto++;
        }
    }
    Quadrante[indice][0] += branco; 
    Quadrante[indice][1] += preto;
}

void ImprimirMaximais( int n, FILE *saida ) {
    int tam = 1;
    int indice = 0;

    while (tam < n) {
        tam *= 2;
        indice++;
    }

    for ( int i = indice; i >= 0; i-- ) {
        fprintf( saida,"%dx%d %d %d\n", tam, tam, Quadrante[i][0], Quadrante[i][1] );
        tam /= 2;
    }
}

int MaxQuadrant(int** matriz, int n, int k, int linha, int coluna) {

    // Caso base
    if ( n == 1 ) {
        return matriz[linha][coluna];
    }

    int metade = n / 2;
    int valoresFilhos[4];

    for ( int i = 0; i < 2; i++ ) {
        for ( int j = 0; j < 2; j++ ) {
            valoresFilhos[i * 2 + j] = MaxQuadrant( matriz , metade , k , linha + i * metade , coluna + j * metade );
        }
    }

    int mesmaCor = 1;
    int corFilho = valoresFilhos[0];

    for ( int i = 0; i < 4; i++ ) {
        if ( valoresFilhos[i] != corFilho ) {
            mesmaCor = 0;
            break;
        }
    }

    if ( !mesmaCor ) {
        GuardarQuadrante( valoresFilhos , n) ;
        return -1; 
    } else {

        if( n == k ) { //pai máximal 
            int indice = 0;
            while ( n >= 2 ) {
                n /= 2;
                indice++;
            }

            if( corFilho == 1 ) Quadrante[indice][0] = 1;

            else Quadrante[indice][1] = 1;  
        }
        return corFilho; 
    }
}

int main( int argc, char *argv[] ) {
    int n = atoi(argv[1]);
    int **matriz;

    matriz = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matriz[i] = (int *)malloc(n * sizeof(int));
    }

    char filename[MAX_FILENAME] = "";
    strcpy(filename, argv[2]);
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", filename);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char caractere;

            if (fscanf(fp, " %c", &caractere) != 1) {
                fclose(fp);
                return -1;
            }

            matriz[i][j] = (caractere == '1' ? 1 : 0);
        }
    }
    
    FILE *saida = fopen("saida.txt", "w");
    if (saida == NULL) {
        fprintf(stderr, "Não foi possível criar o arquivo de saída.\n");
        return -1;
    }

    int k = n;

    MaxQuadrant(matriz, n, k, 0, 0);

    ImprimirMaximais(n,saida);

    // Libere a memória alocada
    for ( int i = 0; i < n; i++ ) {
        free( matriz[i] );
    }

    free( matriz );

    fclose( fp );
    fclose( saida );

    return 0;
}
