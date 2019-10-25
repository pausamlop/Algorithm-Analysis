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
  if (ip < 0 || iu < 0 || ip > iu) return ERR;

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
  if (ip < 0 || iu < 0 || ip > iu) return ERR;

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




/*************************************************************/
/* Function: MergeSort    Date:  18-10-2019                  */
/* This function sortes an integer array in ascending order  */
/*************************************************************/
int MergeSort(int* table, int ip, int iu){
  int m, num_bo1, num_bo2, res;
  if (!table || iu < ip) return ERR;

  if (ip == iu) return OK;

  m = (ip + iu)/2;
  num_bo1 = MergeSort(table, ip, m);
  num_bo2 = MergeSort(table, m+1, iu);
  if (num_bo1 == ERR || num_bo2 == ERR) return ERR;

  res = merge(table, ip, iu, m);
  if (!res) return ERR;
  return num_bo1 + num_bo2 + res;
}



/*************************************************************/
/* Function: merge    Date:  18-10-2019                 */
/* - */
/*************************************************************/
int merge(int* table, int ip, int iu, int imiddle){
  int i, j, k, counter = 0;
  int *table_aux = NULL;
  if (!table || iu < ip) return ERR;

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





int quicksort(int *table, int ip, int iu){
  int m, pos;
  if (!table || iu < ip) return ERR;
  if (iu == ip) return OK;

  m = split(table, ip, iu, &pos);
  if (ip < m-1)
    quicksort(table, ip, m-1);
  if (m+1 < iu)
    quicksort(table, m+1, iu);

  return OK;

}


static void swap (int *x, int *y) {
  int aux;

  if (!x || !y) return;

  aux = *x;
  *x = *y;
  *y = aux;
}

int split (int* table, int ip, int iu, int *pos){
  int i, k, m;

  if (!table || iu < ip || !pos) return ERR;

  m = median(table, ip, iu, pos);
  k = table[m];

  swap(&table[ip],&table[iu]);
  m = ip;

  for (i=ip+1; i<=iu; i++){
    if (table[i]<k) {
      m++;
      swap(&table[i], &table[m]);
    }
  }
  swap(&table[ip],&table[m]);

  return m;
}


int median(int *table, int ip, int iu, int *pos){
  if (!table || iu < ip || !pos) return ERR;

  *pos = ip;
  return 0;
}
