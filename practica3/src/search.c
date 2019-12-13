/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be
 *				 allocated externally to the function.
 */

/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++)
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order){
  PDICT dic = NULL;

  if (size < 0 || order > 1 || order < 0) return NULL;

  dic = (PDICT)malloc(sizeof(DICT));
  if (!dic) return NULL;

  dic->size = size;
  dic->n_data = 0;
  dic->order = order;
  dic->table = (int *)malloc(size*sizeof(int));
  if (!dic->table){
    free_dictionary(dic);
    return NULL;
  }

  return dic;
}

src
void free_dictionary(PDICT pdict){
  if (!pdict) return;

  if (pdict->table != NULL){
    free(pdict->table);
  }

  free(pdict);
  return;
}


int insert_dictionary(PDICT pdict, int key)
{
  int a, j, counter = 0;
  if (!pdict) return ERR;
  if (pdict->n_data == pdict->size) return ERR;


  if (pdict->order == NOT_SORTED){
    pdict->table[pdict->n_data] =  key;
    pdict->n_data++;
    return counter;
  }

  pdict->table[pdict->n_data] =  key;
  pdict->n_data++;

  a = pdict->table[pdict->n_data - 1];
  j = pdict->n_data - 2;

  while (j >= 0 && pdict->table[j]>a){
    counter ++;
    pdict->table[j+1] = pdict->table[j];
    j--;
  }
  if(j >= 0) counter++;

  pdict->table[j+1] = a;
  return counter;
}

int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys){
  int i, res, counter = 0;
  if (!pdict || !keys || n_keys < 0) return ERR;

  for (i = 0; i < n_keys; i++){
    counter ++;
    res = insert_dictionary(pdict, keys[i]);
    if (res == ERR) return ERR;
  }

  return counter;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method){
  int res;
  if (!pdict || !ppos || !method) return ERR;

  res = method (pdict->table, 0, pdict->n_data - 1, key, ppos);
  if (res == ERR) return ERR;

  return res;
}


/* Search functions of the Dictionary ADT */

int bin_search(int *table,int F,int L,int key, int *ppos){
  int m, counter = 0;
  if (!table || F > L || F < 0 || !ppos) return ERR;

  while (F <= L){
    m = (F+L) / 2;

    counter ++;
    if (table[m] > key){
      L = m - 1;
    }
    else if (table[m] < key){
      F = m + 1;
    }
    else{
      *ppos = m;
      return counter;
    }
  }
  *ppos = NOT_FOUND;
  return counter;
}

int lin_search(int *table,int F,int L,int key, int *ppos){
  int i, counter = 0;
  if (!table || F > L || F < 0 || !ppos) return ERR;

  for (i = F; i <= L; i++){
    counter ++;
    if (table[i] == key){
      *ppos = i;
      return counter;
    }
  }
  *ppos = NOT_FOUND;
  return counter;
}


static void swap (int *x, int *y) {
  int aux;

  if (!x || !y) return;

  aux = *x;
  *x = *y;
  *y = aux;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos){
  int i, counter = 0;
  if (!table || F > L || F < 0 || !ppos) return ERR;

  for (i = F; i <= L; i++){
    counter++;
    if (table[i] == key){
      if (i != F) swap(&table[i], &table[i-1]);
      *ppos = i;
      return counter;
    }
  }
  *ppos = NOT_FOUND;
  return counter;
}
