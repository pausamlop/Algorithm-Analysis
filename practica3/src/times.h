
  /**
 *
 * Description: Header files for time functions
 *
 * File: times.h
 * Author: Laura de Paz & Paula Samper
 * Version: 1.0
 * Data: 20-09-2019
 *
 */

#ifndef TIMES_H
#define TIMES_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

#include <time.h>
#include <stdio.h>
#include "search.h"
#include "sorting.h"
#include "permutations.h"

/* type definitions */
typedef struct time {
  int N;           /* size of the permutation */
  int n_elems;     /* number of elements to average */
  double time;   /* average time */
  double average_ob; /* average number of times that the OB is executed*/
  int min_ob;      /* minimum executions of the OB */
  int max_ob;      /* maximum executions of the OB */
} TIME, *PTIME;

short average_search_time(pfunc_search method, pfunc_key_generator generator, char order, int N, int n_times, PTIME ptime);
short generate_search_times(pfunc_search method, pfunc_key_generator generator, char order, char* file, int num_min, int num_max, int incr, int n_times);

/* Functions */
short average_sorting_time(pfunc_sort method, int n_perms,int N, PTIME ptime);
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms);
short store_time_table(char* file, PTIME time, int n_times);



#endif
