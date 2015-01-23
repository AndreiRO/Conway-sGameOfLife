#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"minunit.h"
#include"../src/gol.h"

int tests_run = 0;

char* test_new_and_free() {
  struct map* m = create_map(27, 33);
  mu_assert("Map is null", m);
  mu_assert("Map lines incorrect", m->number_of_lines == 27);
  mu_assert("Map columns incorrect", m->number_of_columns == 33);
  free_map(&m);
  mu_assert("Map is not deleted", m == NULL);  

  return NULL;
}

char* test_a_new_map_should_have_zeros() {
  struct map* m = create_map(21, 14);
  int i = 0, j = 0;

  for(; i < 21; ++ i) {
    for(j = 0; j < 14; ++ j) {
      if(get_value(m, i, j)) {
        return "Value not 0...";
      }
    }
  }
  
  free_map(&m); 

  return NULL;
}

char* test_set_and_get() {
  struct map* m = create_map(21, 13);
  int i = 0, j = 0;

  for(; i < 21; ++ i) {
    for(j = 0; j < 13; ++ j) {
      set_value(m, i, j, (i+j%2 == 0));
      if(get_value(m, i, j) != (i+j % 2 == 0)) {
        return "Set and get don't work..";
      }
    }
  }

  free_map(&m);
  return NULL;
}

char* test_good_index() {
  struct map* m = create_map(123, 12);
  mu_assert("Good index is not good", check_index(m, 120, 1));
  mu_assert("Bad index is good", !check_index(m, 123, 1));
  mu_assert("Bad index is good", !check_index(m, 15, 12));

  free_map(&m);
  return NULL;
}


char* test_alive_neighbours() {
  struct map* m = create_map(3, 3);
  char error[15];

  set_value(m, 1, 1, true);
  set_value(m, 0, 2, true);
  set_value(m, 2, 0, true);

  mu_assert("Invalid map data", get_value(m, 0, 0) == 0);
  mu_assert("Invalid map data", get_value(m, 0, 1) == 0);
  mu_assert("Invalid map data", get_value(m, 1, 0) == 0);
  mu_assert("Invalid map data", get_value(m, 1, 2) == 0);
  mu_assert("Invalid map data", get_value(m, 2, 1) == 0);
  mu_assert("Invalid map data", get_value(m, 2, 2) == 0);
  mu_assert("Invalid map data", get_value(m, 0, 2) == 1);
  mu_assert("Invalid map data", get_value(m, 1, 1) == 1);
  mu_assert("Invalid map data", get_value(m, 2, 0) == 1);

  mu_assert("Alive nieghbours wrong", get_alive_neighbours(m, 1, 1, 'P') == 2);
  mu_assert("Alive nieghbours wrong", get_alive_neighbours(m, 1, 1, 'T') == 2);
  mu_assert("Alive nieghbours wrong", get_alive_neighbours(m, 2, 0, 'P') == 1);
  mu_assert("Alive nieghbours wrong", get_alive_neighbours(m, 0, 0, 'T') == 3);

  mu_assert("Cell should live",lives(m, 1, 1, error, 'P'));
  mu_assert("Cell should live",lives(m, 1, 1, error, 'T'));
  mu_assert("Cell shouldn't live",lives(m, 2, 0, error, 'P') == 0);
  mu_assert("Cell should live",lives(m, 2, 0, error, 'T'));
  mu_assert("Cell should born",lives(m, 0, 0, error, 'T'));
  mu_assert("Cell shouldn't born",lives(m, 0, 0, error, 'P') == 0);

  free_map(&m);
  return NULL;
}

char* run_tests() {
  mu_run_test(test_a_new_map_should_have_zeros); 
  mu_run_test(test_set_and_get);
  mu_run_test(test_new_and_free);
  mu_run_test(test_good_index);
  mu_run_test(test_alive_neighbours);

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


