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
  int i, j, res, min = 0,max = 0,sum = 0;
  int **perms = NULL;

  if (!method || n_perms < 0 || N < 0 || !ptime) return ERR;

  ptime->N = N;
  ptime->n_elems = n_perms;

  perms = generate_permutations(n_perms,N);
  if (!perms)return ERR;


  start = clock();
  for (i = 0; i < n_perms; i++){
    res = method(perms[i],0,N-1);
    if (res == ERR){
      for (j=0; j<n_perms; j++) free(perms[j]);
      free(perms);
      return ERR;
    }
    if (min == 0) min = res;
    else if (res < min) min = res;
    if (res > max) max = res;
    sum += res;
  }
  end = clock();

  ptime->time = ((double)(end - start) / (double)CLOCKS_PER_SEC) / (double)n_perms;
  ptime->min_ob = min;
  ptime->max_ob = max;
  ptime->average_ob = (double)sum/(double)n_perms;

  for (j=0; j<n_perms; j++) free(perms[j]);
  free(perms);
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

  int i, i_max;
  short result;
  PTIME array_times = NULL;

  i_max = (num_max - num_min)/incr + 1;
  array_times = (PTIME)malloc(i_max*sizeof(TIME));

  if(!array_times) return ERR;

  for (i = 0; i < i_max; i++){
    result = average_sorting_time(method, n_perms, num_min + incr*i, &array_times[i]);
    if (result == ERR){
      free(array_times);
      return ERR;
    }
  }

  store_time_table(file, array_times, i_max);

  free (array_times);
  return OK;
}

/***************************************************/
/* Function: store_time_table Date:            	   */
/*                                                 */
/* Your comments		                           */
/***************************************************/

short store_time_table(char* file, PTIME time, int n_times)
{
  int i = 0;
  FILE *f1 = NULL;

  if (!file || !time || n_times<0 ) return ERR;

  f1 = fopen(file, "w");
  if (!f1) return ERR;

  for (i = 0; i<n_times; i++){
    fprintf (f1, "%i %f %f %i %i\n", time[i].N, time[i].time, time[i].average_ob, time[i].max_ob, time[i].min_ob);
  }

  fclose(f1);
  return OK;

}
