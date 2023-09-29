#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * ImprimePalavras( char **palavras, int m ){
    for (int i = m; i >= 1; i--) 
    {
      printf("%s\n", palavras[i]);
      free(palavras[i]); 
}    
    }  
    

void troca( char *lp[], int x, int y ){
   char *aux;
   aux = lp[x];
   lp[x] = lp[y];
   lp[y] = aux;
}

void compara( char *lp[], int pai, int fd, int fs ){
   if(strcmp( lp[fd], lp[pai] ) < 0) troca( lp, pai, fd );
   if(strcmp( lp[fs], lp[pai] ) < 0) troca( lp, pai, fs );
}

void buildHeap( char *lp[] , int m ){
   int p = 1;
   while ( 2*p <= m )
   {
       int pai_d = (2*p)+1;
       int pai_s = 2*p;

      if (2*(pai_d)+1 <= m) 
      {
         compara( lp, pai_d, 2*(pai_d)+1, 2*(pai_d) );
      }
      if (2*(pai_s)+1 <= m){
         compara( lp, pai_s, 2*(pai_s)+1, 2*(pai_s) );
      }
      p += 1;
   }
}

void heapsort( char **lp , int m ){ 
   int pai = 1;
   while(m > 0){
      buildHeap( lp , m );
      compara( lp , pai , 3 , 2 ); 
      troca( lp , pai , m );
      m -= 1;
   }
   troca( lp , pai , 3 );
}


int main(){ 
    char *palavras[1000];
    int m = 1, tam = sizeof( palavras );
    while( !feof( stdin ) ){
      palavras[m] = malloc( sizeof(char) * 10 );
      fgets( palavras[m] , tam , stdin );
      m += 1;
    }  
   heapsort( palavras , m-2 );
   ImprimePalavras( palavras , m-2 );
}

