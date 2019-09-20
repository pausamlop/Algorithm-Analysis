/********************************************************/
/* Programa: ejercicio2      Fecha:                     */
/* Autores:                                             */
/*                                                      */
/* Programa que genera permutaciones                    */
/* aleatorias                                           */
/*                                                      */
/* Entrada: Linea de comandos                           */
/* -size: numero elementos permutacion               */
/* -numP: numero de permutaciones                       */
/* Salida: 0: OK, -1: ERR                               */
/********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

int main(int argc, char** argv)
{
  int i;
  unsigned int num, size, j, k;
  int* perm = NULL;

  srand(time(NULL));

  if (argc != 5) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -size <int> -numP <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -size : numero elementos de la permutacion.\n");
    fprintf(stderr, " -numP : numero de permutaciones.\n");
    exit(-1);
  }

  printf("Practica numero 1, apartado 2\n");
  printf("Realizada por: Paula Samper & Laura de Paz\n");
  printf("Grupo: 125\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-size") == 0) {
      size = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  /* imprimimos el resultado */
  for(j = 0; j < num; j++) {
    perm = generate_perm(size);
    if (perm == NULL) { /* error */
      printf("Error: No hay memoria\n");
      exit(-1);
    } else {
      for(k = 0; k < size; k++) { /* imprimimos cada elemento */
        printf("%d ", perm[k]);
      }
      printf("\n");
      free(perm); /* liberamos la permutacion */
    }
  }

  return 0;
}
