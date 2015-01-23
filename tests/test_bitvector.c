#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"minunit.h"
#include"../src/bitvector.h"
int tests_run = 0;

char* test_new_and_delete() {
  bitvector b = b_new(2);
  mu_assert("T1: Cannot create new bitvector", b != NULL);
  mu_assert("T1: Invalid bit size at creation", b->n_bits == 2);
  mu_assert("T1: Invalid byte size at creation", b->n_bytes == 1);
  mu_assert("T1: Invalid bitvector at creation", b->bytes != NULL);

  b_delete(&b);
  mu_assert("Deletion doesn't work", b == NULL);

  return NULL;
}

char* test_new_bitvector_should_have_zeros() {
  bitvector b = b_new(1024013);
  size_t i = 0;

  while(i < 1024013) {
    mu_assert("0 everywhere... ", b_get(b, i) == false);
    ++ i;
  }

  b_delete(&b);
  return NULL;
}

char* test_resize() {
	bitvector b = b_new(1);
	b_resize(&b, 9);
	
  //complete with equaliy test
	mu_assert("T2: Invalid bitvector at resize", b != NULL);
	mu_assert("T2: Invalid bit size at resize", b->n_bits == 9);
	mu_assert("T2: Invalid byte size at resize", b->n_bytes == (2));

	b_delete(&b);
	return NULL;
}

char* test_equal() {
  bitvector a = b_new(1), b = b_new(1);
  char c1 = 123, c2 = 134;

  a->bytes[0] = c1;
  b->bytes[0] = c1;
  //mu_assert("T3: Bitvectors are not equal: ", b_equal(a, b, false));
  b->bytes[0] = c2;
  //mu_assert("T3: Bitvectors are equal: ", !b_equal(a, b, false)); 


  b_delete(&a);
  b_delete(&b);

  return NULL;
}

char* test_set_and_get() {
  bitvector a = b_new(3 * BYTE_SIZE);
  int i, j;
  time_t t;
  srand((unsigned) time(&t));
  for(i = 0; i < 3; ++ i) {
    for(j = 0; j < BYTE_SIZE; ++ j) {
      bool t = rand() % 3 == 0;

      b_set(a, i * BYTE_SIZE + j, t);
      mu_assert("ERROR SET AND GET",
            b_get(a, i * BYTE_SIZE + j) == t);
    }
  }

  b_delete(&a);

  return NULL;
}

char* test_diff() {
  bitvector a = b_new(2 * BYTE_SIZE), b= b_new(3 * BYTE_SIZE);

  size_t i = 0;
  for( ; i < 3 * BYTE_SIZE; ++ i) {
    b_set(a, i, (i % 2 == 0));
    b_set(b, i, (i % 3 == 0));
  } 

  bitvector c = b_diff(a, b);
  
  for( i = 0; i < BYTE_SIZE * 3; ++ i) {
    mu_assert2("DIFF1 FAILED", b_get(a, i) == true &&
                              b_get(b, i) == false,
                              b_get(c, i) == true);

    mu_assert2("DIFF2 FAILED",  b_get(a, i) == true && 
                              b_get(b, i) == true,
                              b_get(c, i) == false); 

    mu_assert2("DIFF3 FAILED",  b_get(a, i) == false, 
                              b_get(c, i) == false);
  }

  b_delete(&a);
  b_delete(&b); 
  b_delete(&c);

  return NULL;
}

char* test_and() {
  bitvector a = b_new(2 * BYTE_SIZE),
            b = b_new(3 * BYTE_SIZE);

  size_t i = 0;
  for( ; i < 3 * BYTE_SIZE; ++ i) {
    b_set(a, i, i % 2 == 0);
    b_set(b, i, i % 3 == 0); 
  }

  bitvector c = b_and(a, b);

  for(i = 0 ; i < 3 * BYTE_SIZE; ++ i) {
    mu_assert("AND not working", b_get(c, i) == 
        (b_get(a, i) & b_get(b, i)));
  }

  b_delete(&a);
  b_delete(&b);
  b_delete(&c);

  return NULL;
}

char* test_or() {
  bitvector a = b_new(2 * BYTE_SIZE),
            b = b_new(3 * BYTE_SIZE);

  size_t i = 0;
  for( ; i < 3 * BYTE_SIZE; ++ i) {
    b_set(a, i, i % 2 == 0);
    b_set(b, i, i % 3 == 0); 
  }

  bitvector c = b_or(a, b);

  for(i = 0 ; i < 3 * BYTE_SIZE; ++ i) {
    mu_assert("OR not working", b_get(c, i) == 
        (b_get(a, i) | b_get(b, i)));
  }

  b_delete(&a);
  b_delete(&b);
  b_delete(&c);

  return NULL;
}

char* test_xor() {
  bitvector a = b_new(2 * BYTE_SIZE),
            b = b_new(3 * BYTE_SIZE);

  size_t i = 0;
  for( ; i < 3 * BYTE_SIZE; ++ i) {
    b_set(a, i, i % 2 == 0);
    b_set(b, i, i % 3 == 0); 
  }

  bitvector c = b_xor(a, b);

  for(i = 0 ; i < 3 * BYTE_SIZE; ++ i) {
    mu_assert("AND not working", b_get(c, i) == 
        (b_get(a, i) ^ b_get(b, i)));
  }

  b_delete(&a);
  b_delete(&b);
  b_delete(&c);

  return NULL;
}

char* run_tests() {
	mu_run_test(test_new_and_delete);
	mu_run_test(test_resize);
  mu_run_test(test_equal);
  mu_run_test(test_set_and_get);
  mu_run_test(test_and);
  mu_run_test(test_or);
  mu_run_test(test_xor);
  mu_run_test(test_diff);  
  mu_run_test(test_new_bitvector_should_have_zeros);

	return NULL;
}

int main() {

	char* result = run_tests();
	if(result) {
		printf("Error: %s\n", result);
	} else {
		printf("Tests(%d) ran succcesfully\n", tests_run);
	}

  return 0;
}


