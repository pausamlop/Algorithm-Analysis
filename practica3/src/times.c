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
/* Function: average_search_time Date:            */
/*                                                 */
/* Your comments		                               */
/***************************************************/
short average_search_time(pfunc_search method, pfunc_key_generator generator,
                            char order, int N, int n_times, PTIME ptime){
  clock_t start, end;
  PDICT d = NULL;
  int *perms = NULL, *keys = NULL, i, res, pos, min = 0, max = 0;
  double sum = 0;

  if (!method || !generator || !ptime || n_times<=0 || N <= 0 || order > 1 || order < 0 ) return ERR;

  ptime->N = N;
  ptime->n_elems = n_times;

  d = init_dictionary (N, order);
  if(!d)return ERR;

  perms = generate_perm(N);
  if(!perms){
    free_dictionary(d);
    return ERR;
  }

  if (massive_insertion_dictionary (d, perms, N) == ERR) {
    free_dictionary(d);
    free(perms);
    return ERR;
  }

  keys = (int*)malloc(n_times * N * sizeof(int));
  if (!keys){
    free_dictionary(d);
    free(perms);
    return ERR;
  }

  generator(keys, N*n_times, N);

  start = clock();

  for (i = 0; i < n_times * N; i++){
    res = search_dictionary(d, keys[i], &pos, method);
    if (res == ERR){
      free_dictionary(d);
      free(perms);
      free(keys);
      return ERR;
    }
    if (min == 0) min = res;
    else if (res < min) min = res;
    if (res > max) max = res;
    sum += (double)res/(double)(N*n_times);
  }

  end = clock();

  ptime->time = ((double)(end - start) / (double)CLOCKS_PER_SEC) * 1000 / (double)(N*n_times);
  ptime->min_ob = min;
  ptime->max_ob = max;
  ptime->average_ob = sum;

  free_dictionary(d);
  free(keys);
  free(perms);

  return OK;
}

/***************************************************/
/* Function: generate_search_times Date:            */
/*                                                 */
/* Your comments		                               */
/***************************************************/
short generate_search_times(pfunc_search method, pfunc_key_generator generator,
                            char order, char* file, int num_min, int num_max,
                            int incr, int n_times){
  int i_max, result, i;
  PTIME array_times = NULL;
  if (!method ||  !generator || !file || num_min>num_max || order > 1 || order < 0 || num_min<0 || incr<=0 ||n_times<=0) return ERR;

  i_max = (num_max - num_min)/incr + 1;
  array_times = (PTIME)malloc(i_max*sizeof(TIME));

  if(!array_times) return ERR;

  for (i = 0; i < i_max; i++){
    result = average_search_time(method, generator, order, num_min + incr*i, n_times, &array_times[i]);
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
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your comments		                               */
/***************************************************/
short average_sorting_time(pfunc_sort method,
                              int n_perms,
                              int N,
                              PTIME ptime)
{
  clock_t start, end;
  int i, j, res, min = 0,max = 0;
  double sum = 0;
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
    sum += (double)res/(double)n_perms;
  }

  end = clock();

  ptime->time = ((double)(end - start) / (double)CLOCKS_PER_SEC) * 1000 / (double)n_perms;
  ptime->min_ob = min;
  ptime->max_ob = max;
  ptime->average_ob = sum;

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

  if (!method || !file || num_min>num_max || num_min<0 || incr<=0 ||n_perms<=0) return ERR;

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

  if(store_time_table(file, array_times, i_max) == ERR){
    free(array_times);
    return ERR;
  }

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
    if(!fprintf (f1, "%i %f %f %i %i\n", time[i].N, time[i].time, time[i].average_ob, time[i].max_ob, time[i].min_ob)){
      fclose(f1);
      return ERR;
    }
  }

  fclose(f1);
  return OK;

}
