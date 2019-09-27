/**
 *
 * Description: Implementation of time functions
 *
 * File: time.c
 * Author: Laura de Paz & Paula Samper
 * Version: 1.0
 * Data: 27-09-2019
 *
 */

#include "times.h"
#include "sorting.h"

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your comments		                           */
/***************************************************/
short average_sorting_time(pfunc_sort method,
                              int n_perms,
                              int N,
                              PTIME ptime)
{
  clock_t start, end;
  int i, res, min = 0,max = 0,sum = 0;
  int **perms = NULL;

  if (!method || n_perms < 0 || N < 0 || !ptime) return ERR;

  ptime->N = N;
  ptime->n_elems = n_perms;

  perms = generate_permutations(n_perms,N);
  if (!perms) return ERR;

  start = clock();
  for (i = 0; i < n_perms; i++){
    res = method(perms[i],0,N-1);
    if (res == ERR) return ERR;
    if (res < min) min = res;
    if (res > max) max = res;
    sum += res;
  }
  end = clock();

  ptime->time = ((double)(end - start) / CLOCKS_PER_SEC) / n_perms;
  ptime->min_ob = min;
  ptime->max_ob = max;
  ptime->average_ob = sum/n_perms;

  return OK;

}

/***************************************************/
/* Function: generate_sorting_times Date:       	   */
/*                                                 */
/* Your comments		                           */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file,
                                int num_min, int num_max,
                                int incr, int n_perms)
{
  /* your code */
}

/***************************************************/
/* Function: store_time_table Date:            	   */
/*                                                 */
/* Your comments		                           */
/***************************************************/
short store_time_table(char* file, PTIME time, int n_times)
{
  /* your code */
}
