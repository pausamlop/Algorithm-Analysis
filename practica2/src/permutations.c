 /**
 *
 * Description: Implementation of functions for permutation generation
 *
 * File: permutations.c
 * Author: Laura de Paz & Paula Samper
 * Version: 1.0
 * Data: 20-09-2019
 *
 */


#include "permutations.h"

/***************************************************/
/* Function: random_num Date:  20/09/19            */
/* Authors: Paula Samper & Laura de Paz            */
/*                                                 */
/* Rutine that generates random numbers	    		   */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: inferior limit                         */
/* int sup: superior limit       	                 */
/* Output:                                         */
/* int: random number	                             */
/***************************************************/

/*pruebaaa*/

int random_num(int inf, int sup)
{
  if (inf>sup) return ERR;
  return (int)((sup - inf + 1) * (double)rand() / ((double)RAND_MAX + 1)) + inf;
}

/***************************************************/
/* Function: genera_perm Date:                     */
/* Authors:  Laura e Paz & Paula Samper            */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                               	         */
/* int n: Number of permutation elements           */
/* Output:                                         */
/* int *: punter to an integer array that 		     */
/* contains the permutation            			       */
/* or NULL if error		                             */
/***************************************************/
static void swap (int *x, int *y) {
  int aux;

  if (!x || !y) return;

  aux = *x;
  *x = *y;
  *y = aux;
}


int* generate_perm(int N)
{
  int *perm = NULL;
  int i;

  if (N<0) return NULL;

  perm = (int *)malloc(N*sizeof(int));
  if (!perm) return NULL;


  for (i=0; i<N; i++){
    perm[i] = i+1;
  }

  for (i=0; i<N; i++){
    swap (&perm[i], &perm[random_num(i, N-1)]);
  }

  return perm;
}

/***************************************************/
/* Function: genera_permutaciones Date:            */
/* Authors: Paula Samper & Laura de Paz            */
/*                                                 */
/* Funcion that generates n_perms random		       */
/* permutations of N elements                 	   */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements of each permutation   */
/* Output:                                         */
/* int**: Array of integer pointers that point 	   */
/* to each of the permutations 		                 */
/* NULL if error          		                     */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int **perm, i;

  if (n_perms <= 0 || N <= 0) return NULL;

  perm = (int **)malloc(n_perms*sizeof(int *));
  if (!perm) return NULL;

  for (i = 0; i < n_perms; i++){
    perm[i] = generate_perm(N);
    if (!perm[i]) return NULL; //eliminar perm??
  }

  return perm;
}
