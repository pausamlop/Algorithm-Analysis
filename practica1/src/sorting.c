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

/***************************************************/
/* Function: InsertSort    Date:  27-09-2019       */
/* Your comment		                                 */
/***************************************************/
int InsertSort(int* list, int ip, int iu)
{
  int i, j, a, count = 0;
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
    if (j>=ip) count++;
    list[j+1] = a;
  }
  return count;
}
