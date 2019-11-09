 /**
 *
 * Description: Implementation of sorting functions
 *
 * File: sorting.c
 * Author: Laura de Paz & Paula Samper
 * Version: 1.0
 * Data: 27-09-2019
 *
 */


#include "sorting.h"
#include <stdlib.h>
#include <stdio.h>

/*************************************************************/
/* Function: InsertSort    Date:  27-09-2019                 */
/* This function sortes an integer array in ascending order	 */
/*************************************************************/
int InsertSort(int* list, int ip, int iu)
{
  int i, j, a, count = 1;
  if (ip < 0 || iu < 0 || ip > iu || list == NULL) return ERR;

  for (i = ip; i <= iu; i++){
    a = list[i];
    j = i-1;
    while (j >= ip && list[j] > a){
      list[j+1] = list[j];
      count++;
      j--;
    }
    if(j>=ip) count++;
    list[j+1] = a;
  }
  return count;
}


/*************************************************************/
/* Function: InsertSort    Date:  27-09-2019                 */
/* This function sortes an integer array in descending order */
/*************************************************************/
int InsertSortInv(int* list, int ip, int iu)
{
  int i, j, a, count = 0;
  if (ip < 0 || iu < 0 || ip > iu || list == NULL) return ERR;

  for (i = ip; i <= iu; i++){
    a = list[i];
    j = i-1;
    while (j >= ip && list[j] < a){
      list[j+1] = list[j];
      count++;
      j--;
    }
    if(j>=ip) count++;
    list[j+1] = a;
  }
  return count;
}



/************************** MERGESORT ***************************/

/**********************************************************************************/
/* Function: merge    Date:  18-10-2019                                           */
/* This function combines the table that receives and which is divided by imiddle */
/**********************************************************************************/
int merge(int* table, int ip, int iu, int imiddle){
  int i, j, k, counter = 0;
  int *table_aux = NULL;
  if (!table || iu < ip || ip < 0) return ERR;

  /*creates temporary array*/
  table_aux = (int*)malloc((iu-ip+1)*sizeof(int));

  if (!table_aux) return ERR;

  i = ip;
  j = imiddle+1;
  k = 0;

  /*compares the two subarrays and merges them*/
  while (i <= imiddle && j <= iu){
    counter++;
    if (table[i] < table[j]){
      table_aux[k] = table[i];
      i++;
    } else {
      table_aux[k] = table[j];
      j++;
    }
    k++;
  }

  /*copies the remaining elements if there is any*/
  if (i > imiddle){
    while (j <= iu){
      table_aux[k] = table[j];
      j++;
      k++;
    }
  }

  /*copies the remaining elements if there is any*/
  else if (j>iu){
    while (i <= imiddle){
      table_aux[k] = table[i];
      i++;
      k++;
    }
  }

  for(i = 0; i < k; i++){
    table[i+ip] = table_aux[i];
  }

  free(table_aux);
  return counter;

}

/*************************************************************/
/* Function: MergeSort    Date:  18-10-2019                  */
/* This function sortes an integer array in ascending order  */
/*************************************************************/
int MergeSort(int* table, int ip, int iu){
  int m, num_bo1, num_bo2, res;
  if (!table || iu < ip || ip < 0) return ERR;

  if (ip == iu) return OK;

  m = (ip + iu)/2;
  num_bo1 = MergeSort(table, ip, m);
  num_bo2 = MergeSort(table, m+1, iu);
  if (num_bo1 == ERR || num_bo2 == ERR) return ERR;

  res = merge(table, ip, iu, m);
  if (!res) return ERR;
  return num_bo1 + num_bo2 + res;
}



/************************** QUICKSORT ***************************/

/***************************************************************/
/* Function: swap    Date:  25-10-2019                         */
/* This function exchanges the value of x with the value of y  */
/***************************************************************/
static void swap (int *x, int *y) {
  int aux;

  if (!x || !y) return;

  aux = *x;
  *x = *y;
  *y = aux;
}

/*************************************************************/
/* Function: median    Date:  25-10-2019                     */
/* This function returns the index of the pivot              */
/*************************************************************/
int median(int *table, int ip, int iu, int *pos){
  if (!table || iu < ip || ip < 0 || !pos) return ERR;

  *(pos) = ip;
  return 0;
}

/*************************************************************/
/* Function: median_avg    Date:  08-11-2019                     */
/* This function returns the index of the pivot              */
/*************************************************************/
int median_avg(int *table, int ip, int iu, int *pos){
  if (!table || iu < ip || ip < 0 || !pos) return ERR;

  *(pos) = (ip + iu)/2;
  return 0;
}

/*************************************************************/
/* Function: median_stat   Date:  08-11-2019                 */
/* This function returns the index of the pivot              */
/*************************************************************/
int median_stat(int *table, int ip, int iu, int *pos){
  int a, b, c, med, m;
  if (!table || iu < ip || ip < 0 || !pos) return ERR;

  a = table[ip];
  b = table[iu];
  m = (ip + iu)/2;
  c = table[m];

  if (a>b){
    if (b>c){
      med = b;
    } else if (a>c) {
      med = c;
    } else {
      med = a;
    }
  } else {
    if (a>c){
      med = a;
    } else if (b>c){
      med = c;
    } else{
      med = b;
    }
  }

  if (med == a) *(pos) = ip;
  else if (med == b) *(pos) = iu;
  else *(pos) = m;

  return 3;

}

/*********************************************************************************/
/* Function: split    Date:  25-10-2019                                          */
/* This function divides an integer array in two subtables depending on a pivot  */
/*********************************************************************************/
int split (int* table, int ip, int iu, int *pos){
  int i, k, pivot, count = 0;

  if (!table || iu < ip || !pos || ip < 0) return ERR;

  pivot = median(table, ip, iu, pos);
  if (pivot == ERR) return ERR;

  k = table[*pos];
  count += pivot;

  swap(&table[ip], &table[*pos]);
  (*pos) = ip;

  for (i=ip+1; i<=iu; i++){
    count++;
    if (table[i]< k) {
      (*pos)++;
      swap(&table[i], &table[*pos]);
    }
  }
  swap(&table[ip],&table[*pos]);

  return count;
}


/*************************************************************/
/* Function: QuickSort    Date:  25-10-2019                  */
/* This function sortes an integer array in ascending order  */
/*************************************************************/
int QuickSort(int *table, int ip, int iu){
  int count, pos, res = 0;
  if (!table || iu < ip || ip < 0) return ERR;
  if (iu == ip) return OK;

  count = split(table, ip, iu, &pos);
  if (count == ERR)return ERR;
  if (ip < pos-1){
    res = QuickSort(table, ip, pos-1);
    if (res == ERR) return ERR;
    count += res;
  }
  if (pos+1 < iu){
    res = QuickSort(table, pos+1, iu);
    if (res == ERR) return ERR;
    count += res;
  }

  return count;

}
