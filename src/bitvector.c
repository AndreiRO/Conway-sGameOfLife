#include"bitvector.h"
#include<stdio.h>

/* get the biggest size in bits*/
size_t __max(bitvector a, bitvector b) {
  return a->n_bits > b->n_bits ? a->n_bits : b->n_bits;
}

size_t __max2(bitvector a, bitvector b) {
  return a->n_bytes > b->n_bytes ? a->n_bytes : b->n_bytes;
}

bitvector b_new(size_t bits) {  
  /* get the number of bytes, add one if necessary */
  size_t bytes = bits / BYTE_SIZE + ((bits % BYTE_SIZE != 0) ? 1 : 0);

  bitvector b = (bitvector)malloc(sizeof(struct _bitvector));
  if(!b) {
    if(EXIT_ON_OOM) {
      exit(BITVECTOR_OUT_OF_MEMORY);
    }

    return NULL;
  } /* handle out of memory events */

  b->bytes = (byte*)calloc(bytes, sizeof(char));
  if(!(b->bytes)) {
    free(b);
    if(EXIT_ON_OOM) {
      exit(BITVECTOR_OUT_OF_MEMORY);
    }

    return NULL;
  }

  b->n_bits = bits;
  b->n_bytes = bytes;
  
  return b;
}


void b_delete(bitvector* b) {
  if(!b) return;
  if((*b)->bytes != NULL) {
    free((*b)->bytes);
  }
    free(*b);
    *b = NULL;
}


void b_resize(bitvector* b, size_t size) {
  if(!b || (*b)->n_bits == size) return;

  bitvector a = b_new(size);
  b_delete(b);
  *b = a;
}


void b_copy(bitvector a, bitvector b) {
  if(!a || !b || !a->bytes || !b->bytes) return ;

  size_t index = 0;
  size_t max_bytes = __max2(a, b);
  size_t max_bits = __max(a, b);
  size_t i, j;

  for(i = 0; i < max_bytes; ++ i) {
    for(j = 0; j < BYTE_SIZE && i * BYTE_SIZE + j < max_bits; ++ j) {
      b_set(b, i * BYTE_SIZE +  j, b_get(a, i * BYTE_SIZE + j));       
    }
  }

}


void b_set(bitvector a, size_t index, bool value) {
  if(!a || a->n_bits <= index) return;

  size_t i = index / BYTE_SIZE,
         j = index % BYTE_SIZE;
  char power = 1;
  power <<= j;

  if(a->bytes[i] & power) {
    /* byte value is true */
    if(value) {
      ;
    } else {
      a->bytes[i] ^= power;
    }
  } else {
    /* byte value is false */
    if(value) {
      a->bytes[i] |= power;
    } else {
      ;
    }
  }
}


bool b_get(bitvector a, size_t index) {
  if(!a || a->n_bits <= index) return false;

  size_t i = index / BYTE_SIZE,
         j = index % BYTE_SIZE;

  char power = 1;
  power <<= j;

  if(a->bytes[i] & power) {
    return true;
  } else {
    return false;
  }

  return false;
}


bool b_equal(bitvector a, bitvector b) {
  if(!a || !b || a->n_bits != b->n_bits)  {
    return false;
  }

  size_t index = 0, max_index = a->n_bits;

  /* iterate over all the values*/
  while(index < max_index / BYTE_SIZE) {
    size_t index2 = 0;

    while(index * BYTE_SIZE + index2 < max_index && index2 < BYTE_SIZE) {
      if(b_get(a, index * BYTE_SIZE + index2) !=
        b_get(b, index * BYTE_SIZE + index2)) {
        return false;
      }
      ++ index2;
    } /* check if a[i][i2]  == b[i][i2] */


    ++ index;
  }

  return true;
}


bitvector b_cmpl(bitvector a) {
  if(!a) return NULL;
  bitvector b = b_new(a->n_bits);

  size_t index = 0;

  /* iterate over all the values*/
  while(index < a->n_bytes) {
    size_t index2 = 0;

    while(index2 < BYTE_SIZE && (index * BYTE_SIZE + index2 < a->n_bits)) { 
      b_set(b, index * BYTE_SIZE + index2, !b_get(b, index * BYTE_SIZE + index2));
      ++ index2;
    } /* set to b[i][i2] the value of ~a[i][i2] */

    ++ index;
  }

  return b;
}


bitvector b_or(bitvector a, bitvector b) {
  if(!a || !b) return NULL;
  size_t sz = __max(a, b);
  bitvector c = b_new(sz);

  size_t index = 0;
  
  /* iterate over all the values*/
  while(index < sz) {
    size_t index2 = 0;
  
    while(index2 < BYTE_SIZE && (index * BYTE_SIZE + index2 < sz)) { 
      b_set(c, index * BYTE_SIZE + index2, 
          b_get(b, index * BYTE_SIZE + index2) | 
          b_get(a, index * BYTE_SIZE + index2));
      ++ index2;
    } /* set to c[i][i2] the value of a[i][i2] | b[i][i2]*/

    ++ index;
  }

  return c;
}


bitvector b_and(bitvector a, bitvector b) {
  if(!a || !b) return NULL;
  size_t sz = __max(a, b);
  bitvector c = b_new(sz);

  size_t index = 0;
  
  /* iterate over all the values*/
  while(index < sz) {
  
    size_t index2 = 0;
    while(index2 < BYTE_SIZE && (index * BYTE_SIZE + index2 < sz)) { 
      b_set(c, index * BYTE_SIZE + index2, 
          b_get(b, index * BYTE_SIZE + index2) & 
          b_get(a, index * BYTE_SIZE + index2));
      ++ index2;
    } /* set to c[i][i2] the value of a[i][i2] & b[i][i2]*/

    ++ index;
  }

  return c;
}


bitvector b_xor(bitvector a, bitvector b) {
  if(!a || !b) return NULL;
  size_t sz = __max(a, b);
  bitvector c = b_new(sz);

  size_t index = 0;
  
  /* iterate over all the values*/
  while(index < sz) {
 
   size_t index2 = 0;
    while(index2 < BYTE_SIZE && (index * BYTE_SIZE + index2 < sz)) { 
      b_set(c, index * BYTE_SIZE + index2, 
          b_get(b, index * BYTE_SIZE + index2) ^ 
          b_get(a, index * BYTE_SIZE + index2));
      ++ index2;
    } /* set to c[i][i2] the value of a[i][i2] ^ b[i][i2]*/
    ++ index;
  }

  return c;
}


bitvector b_diff(bitvector a, bitvector b) {
  if(!a || !b) return NULL;
  size_t sz = __max(a, b);
  bitvector c = b_new(sz);

  size_t index = 0;
  
  /* iterate over all the values*/
  while(index < sz) {
 
   size_t index2 = 0;
    while(index2 < BYTE_SIZE && (index * BYTE_SIZE + index2 < sz)) { 
      if(b_get(a, index * BYTE_SIZE + index2) && 
          !b_get(b, index * BYTE_SIZE + index2)) {
        b_set(c, index * BYTE_SIZE + index2, true);
      }  /* add the element if it is in a and not in b*/ 
      
      ++ index2;
    }
    ++ index;
  }

  return c;
}

