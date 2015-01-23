#include<string.h>
#include"gol.h"

/*! \def DEBUG 
 * Debug=1 to print debug messages
 * Change it at compile time with -D DEBUG=0
 * */
#ifndef DEBUG
   #define DEBUG 1
#endif


struct map* create_map(size_t lines, size_t columns) {
  //find out the normal size of a liniar vector
  size_t number_of_elements = lines * columns;

  /* Because EXIT_ON_OOM is not redefined, bitvector either is allocated
   * either program closes */

  bitvector v = b_new(number_of_elements);
  struct map* m = (struct map*)malloc(sizeof(struct map));

  if(!m) {
    exit(CGOL_NO_MEMORY);
  } /* exit if not enough memory */

  m-> map = v;
  m->number_of_columns = columns;
  m->number_of_lines = lines;
  m->max_life = 0;

  return m;   
}


/* freee it and set it to NULL */
void free_map(struct map** m) {
  if(m && *m) {
    bitvector b = (*m)->map;
    b_delete(&b);
    free(*m);
    *m = NULL;
  }
}


bool get_value(struct map* m, size_t line, size_t column) {
  if(!m) {
    return false;
  }

  /* calculate the index, index = line * columns + column */
  size_t index = line * m->number_of_columns + column;

  return b_get(m->map, index);   
}


void set_value(struct map* m, size_t line, size_t column, bool value) {
  if(!m) {
    return ;
  }

  /* calculate the index, index = line * columns + column */
  size_t index = line * m->number_of_columns + column;

  b_set(m->map, index, value); 
}


/* checl if index is inside the bounds */
bool check_index(struct map* m, size_t line, size_t column) {
  if(column >= m->number_of_columns || 
     line >= m->number_of_lines) {
    return false;
  } 

  return true;
}


bool get_neighbour(struct map* m, size_t line,
                   size_t column, enum direction d, char mode,
                   char* error) {

  error[0] = '\0'; /* initialize error string*/


  if(!m || !check_index(m, line, column)) {
    strcpy(error, "Invalid index"); /* fill error string if index invalid*/
    return false;
  }

  /* get the neighbour's line */
  switch(d) {
    case N:
    case NE:
    case NV:
      line = line - 1;
      break;
    case S:
    case SE:
    case SV:
      line = line + 1;
      break;
    default:
      break;
  }
  
  /* additional logic if the map is toroidal*/
  if(mode == 'T' && line == m->number_of_lines) {
    line = 0;
  } else if(mode == 'T' && line == -1) {
    line = m->number_of_lines - 1;
  }

  /* get the neighbour's column */
  switch(d) {
    case V:
    case SV:
    case NV:
      column = column - 1;
      break;
    case E:
    case SE:
    case NE:
      column = column + 1;
      break;
    default:
      break;
  }

  /* additional logic if the map is toroidal*/
  if(mode == 'T' && column == m->number_of_columns) {
    column = 0;
  } else if(mode == 'T' && column == -1) {
    column = m->number_of_columns - 1;
  }

  if(check_index(m, line, column)) {
    return get_value(m, line, column);
  } else {
    strcpy(error, "No neighbour"); /* fill error string */
  }


  return false;
}


/* print out the message error if any and DEBUG on*/
static void handle_error(char* m) {
  if(m[0] != '\0' && DEBUG) {
    printf("Error:-%s-\n", m);
  }
}


int get_alive_neighbours(struct map* m, size_t line,
                          size_t column, char mode) {

  if(!m) {
    return 0;
  }
  int count = 0;
  char p[20];
  p[0] = '\0';

  /* add all the live neighbours, also check for errors */
  count += get_neighbour(m, line, column, N, mode, p);
  handle_error(p);p[0] = '\0';
  count += get_neighbour(m, line, column, NE, mode, p);
  handle_error(p);p[0] = '\0';
  count += get_neighbour(m, line, column, E, mode, p);
  handle_error(p);p[0] = '\0';
  count += get_neighbour(m, line, column, SE, mode, p);
  handle_error(p);p[0] = '\0';
  count += get_neighbour(m, line, column, S, mode, p);
  handle_error(p);p[0] = '\0';
  count += get_neighbour(m, line, column, SV, mode, p);
  handle_error(p);p[0] = '\0';
  count += get_neighbour(m, line, column, V, mode, p);
  handle_error(p);p[0] = '\0';
  count += get_neighbour(m, line, column, NV, mode, p);

  return count;
}


/* set each byte to 0 */
static void set_to_zero(struct map* map) {
  size_t i, j;

  for(i = 0; i < map->number_of_lines; ++ i) {
    for(j = 0; j < map->number_of_columns; ++ j) {
      set_value(map, i, j, false);
    }   
  }

}


void do_cycle(struct map* map, struct map* copy, char mode) {
  
  if(!map || !copy) {
    return ; 
  }
  
  unsigned long alive = 0; /* used to determine the number of alive cells */

  /* create the map for the new cycle */
  set_to_zero(copy); 
 
  size_t i, j;
  char error[15]; /* create error string */
  error[0] = '\0';

  /* iterate over each cell and check if it should live */
  for(i = 0; i < map->number_of_lines; ++ i) {
    for(j = 0; j < map->number_of_columns; ++ j) {

      bool should_live = lives(map, i, j, error, mode);
      alive += should_live;
      set_value(copy, i, j, should_live);

      if(error[0] != '\0') {
        fprintf(stderr, "Error: %s\n", error);
      }

      error[0] = '\0'; /* reset error string */   
    }
  } 

  if(alive > map->max_life) {
    map->max_life = alive;
  }

  b_copy(copy->map, map->map); /* update the map */ 
}


void simulate(struct map* map, struct map* copy, size_t cycles, char mode) {
  if(!map) {
    return ;
  }

  size_t i = 0;
  while(i ++ < cycles) {
    do_cycle(map, copy, mode);
  }

}


bool lives(struct map* m, size_t line, size_t column, char* error, char mode) {
  error[0] = '\0';

  if(!m) {
    strcpy(error, "NULL map");
    return false;
  }

  if(!check_index(m, line, column)) {
    strcpy(error, "Invalid index");
    return false;
  }
 
  bool current_state = get_value(m, line, column);
  int alive_neighbours = get_alive_neighbours(m, line, column, mode);

  /* CGOL logic */  
  if(current_state) {
    if(alive_neighbours < 2) {
      return false;
    } else if(alive_neighbours == 2 || alive_neighbours == 3) {
      return true;
    } else if(alive_neighbours > 3) {
      return false;
    }
  } else if(alive_neighbours == 3){
    return true;
  }
  return false;
}


void read_map(struct map* m) {
  if(!m) {
    return ;
  }
  
  unsigned long alive = 0;
  size_t i, j;
  for(i = 0; i < m->number_of_lines; ++ i) {
    for(j = 0; j < m->number_of_columns; ++ j) {
      int value;
      scanf("%d", &value);
      set_value(m, i, j, value);
      alive += value;
    }
  }

  m->max_life = alive;
}


void print_map(struct map* m) {
  if(!m) {
    return ;
  }

  size_t i, j;
  for(i = 0; i < m->number_of_lines; ++ i) {
    for(j = 0; j < m->number_of_columns; ++ j) {
      printf("%d ", get_value(m, i, j)); 
    }
    printf("\n");
  }
}
