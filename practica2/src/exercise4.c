/**************************************************/
/* Programa: ejercicio4       Fecha:              */
/* Autores:                                       */
/*                                                */
/* Programa que Comprueba SelectSort              */
/*                                                */
/* Entrada: Linea de comandos                     */
/* -size: numero elementos permutacion         */
/* Salida: 0: OK, -1: ERR                         */
/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"
#include "sorting.h"

int main(int argc, char** argv)
{
  int tamano, i, j, ret;
  int* perm = NULL;

  srand(time(NULL));

  if (argc != 3) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -size <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -size : numero elementos permutacion.\n");
    return 0;
  }
  printf("Practica numero 1, apartado 4\n");
  printf("Realizada por: Paula and Laura\n");
  printf("Grupo: 125\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-size") == 0) {
      tamano = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  perm = generate_perm(tamano);

  if (perm == NULL) { /* error */
    printf("Error: No hay memoria\n");
    exit(-1);
  }

  ret = InsertSort(perm, 0, tamano-1);
  /*ret = InsertSortInv(perm, 0, tamano-1);*/

  if (ret == ERR) {
    printf("Error: Error en BubbleSort\n");
    free(perm);
    exit(-1);
  }

  for(j = 0; j < tamano; j++) {
    printf("%d \t", perm[j]);
  }
  printf("\n");

  free(perm);

  return 0;
}
