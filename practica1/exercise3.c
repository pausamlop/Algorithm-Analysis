/**************************************************/
/* Programa: ejercicio3       Fecha:              */
/* Autores:                                       */
/*                                                */
/* Programa que genera permutaciones N            */
/* aleatorias de M elementos                      */
/*                                                */
/* Entrada: Linea de comandos                     */
/* -size: numero elementos permutacion         */
/* -numP: numero de permutaciones                 */
/* Salida: 0: OK, -1: ERR                         */
/**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

int main(int argc, char** argv)
{
  int i;
  unsigned int n_perms, size, j, k;
  int** perms = NULL;

  srand(time(NULL));

  if (argc != 5) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -size <int> -numP <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -size : numero elementos permutacion.\n");
    fprintf(stderr, " -numP : numero de permutaciones.\n");
    exit(-1);
  }

  printf("Practica numero 1, apartado 3\n");
  printf("Realizada por: Paula and Laura\n");
  printf("Grupo: 125\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-size") == 0) {
      size = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      n_perms = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  perms = generate_permutations(n_perms, size);

  if (perms == NULL) { /* error */
    printf("Error: No hay memoria\n");
    exit(-1);
  } else {
    for(j = 0; j < n_perms; j++) { /* para cada permutacion */
      for(k = 0; k < size; k++) {
        printf("%d ", perms[j][k]); /* imprimimos cada elemento */
      }
      printf("\n");
      free(perms[j]); /* liberamos la permutacion */
    }

    free(perms); /* liberamos el array de permutaciones */
  }

  return 0;
}
