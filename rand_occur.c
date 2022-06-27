#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#define N 1000    //valori di default modificabili
#define K1 0
#define K2 10


//restituisce un intero dall'argomento altrimenti termina con failure
int numberify(const char* s){
   if(s==NULL || strlen(s) == 0){
      puts("NaN");
      exit(EXIT_FAILURE); //NaN
   }
   char* e = NULL; //raccolta caratteri dopo il nr
   errno=0;
   long val = strtol(s, &e, 10);
   if (errno == ERANGE || val > INT_MAX){
      puts("overflow");
      exit(EXIT_FAILURE);    //overflow
   }
   if (e != NULL && *e == (char)0) {
      return (int)val;   // success
   }
   puts("Not a Number");
   exit(EXIT_FAILURE);   //NaN
}

int main(int argc, char* argv[]){
   if(argc>4){
      puts("troppi argomenti");
      return -1;
   }

   int n, k1, k2; //n: nr generazioni, k1 lim inf, k2 lim sup
   //a seconda se l'argomento viene passato da tastiera
   //sceglie se prendere il default o meno
   n = (argc<2 ? N : numberify(argv[1]));
   k1 = (argc<3 ? K1 : numberify(argv[2]));
   k2 = (argc<4 ? K2 : numberify(argv[3]));

   int diff = k2-k1;
   if(diff<0){
      puts("lim superiore non può essere minore di lim inferiore");
      exit(EXIT_FAILURE);
   }
   int *vect = calloc(diff,sizeof(int)); //alloco vettore init a 0
   //vect tiene il conto delle occorrenze di ogni nr generato 

   int tmp;
   unsigned int seed = time(NULL);
   for(int i = 0; i <= n; ++i){ //generazione nr randomici
      tmp = rand_r(&seed) % (diff+1);
     // printf("%d\n", tmp);
      vect[tmp]+=1;
   }

   //stampa percentuale occorrenze in output
   puts("Occorrenze di:");
   float prc;
   for(int i = 0; i <= diff; i++){  
      //printf("%d\n", vect[i]);
      prc = (float)vect[i] * 100 / (float)n; 
      printf("%d : %.2f%%\n", (k1+i), prc);
   }

   free(vect);
   return 0;
}


 