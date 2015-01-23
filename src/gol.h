/*! \file gol.h
 * Contains all the necessary function
 * declarations to simulate Conway's Game
 * of life.
 * */
#ifndef _GOL_H_
#define _GOL_H_
 
#include<stdio.h>
#include"bitvector.h"

/*! 
 * \def CGOL_NO_MEMORY
 *  error code when there isn't enough memory to
 *  allocate a map.
 * */
#define CGOL_NO_MEMORY -1


/*!
 * \enum direction
 * Used to identify easier a neighbour
 * */
enum direction {
  N,
  NE,
  E,
  SE,
  S,
  SV,
  V,
  NV
};


/*!
 * \struct map
 * Holds the map of cells.
 * */
struct map {
  bitvector map; /**< the actual bitvector */
  size_t number_of_columns; /**< the number of columns */
  size_t number_of_lines;   /**< number of lines */
  unsigned long max_life;   /**< the maximum number of alive cells */
};
 

/*!
 * \fn struct map* create_map(size_t lines, size_t columns);
 * \param lines the number of lines
 * \param columns the number of columns
 * \return struct map* variable containing the map
 * */
struct map* create_map(size_t lines, size_t columns);

 
/*!
 * \fn void free_map(struct map**);
 * \param m the map to be freed.
 * */
void free_map(struct map** m);
 
 /*!
 * \fn bool get_value(struct map* m, size_t line, size_t column);
 * \param m the map
 * \param line the line of the cell
 * \param column the column of the cell
 * \return true if alive, false otherwise.
 * */
bool get_value(struct map* m, size_t line, size_t column);
 

/*!
 * \fn void set_value(struct map* m, size_t line, size_t column, bool value);
 * \param m the map.
 * \param line the line of the cell.
 * \param column the column of the cell.
 * \param value the value to be set.
 * Sets a cell to a given value.
 * */
void set_value(struct map* m, size_t line, size_t column, bool value);
 

/*!
 * \fn bool check_index(struct map* m, size_t line, size_t column);
 * \param m the map.
 * \param line the line of the cell.
 * \param column the column of the cell.
 * \return true if it is a valid index, false otherwise.
 * Checks if the index isn't out of bounds.
 * */
bool check_index(struct map* m, size_t line, size_t column);


/*!
 * \fn bool get_neighbour(struct map* m, size_t line, size_t column,\
 *                        enum direction d, char mode, char* error);
 * \param m the map.
 * \param line the line of the cell.
 * \param column the column of the cell.
 * \param d the direction where to search for the neighbour.
 * \param error the error string.
 * \param mode 'T' for toroidal, 'P' for plane.
 * \return true if the specified neighbour is alive, false if he doesn't exist
 *  or he is dead.
 * */
bool get_neighbour(struct map* m, size_t line, size_t column,
                  enum direction d, char mode, char* error);


/*!
 * \fn int get_alive_neighbours(struct map* m, size_t line, size_t column, char mode);
 * \param m the map.
 * \param line the line of the cell.
 * \param column the column of the cell.
 * \param mode 'T' for toroidal, 'P' for plane.
 * \return the number of alive neighbours.
 * Calculates the number of alive neighbours.
 * */
int get_alive_neighbours(struct map* m, size_t line, size_t column, char mode);
 

 /*!
 * \fn void do_cycle(struct map* map, struct map* copy, char mode);
 * Updates the map after a cycle.
 * \param map the map.
 * \param copy the map used to turn to the new state.
 * \param mode 'T' for toroidal, 'P' for plane.
 * */
void do_cycle(struct map* map, struct map* copy, char mode);


/*!
 * \fn void simulate(struct map* map, struct map* copy, size_t cycles, char mode);
 * Simulates the number of cycles using CGOL's rules. 
 * \param map the map.
 * \param copy the map used to turn to the new state.
 * \param cycles the number of cyles to be run.
 * \param mode 'T' for toroidal, 'P' for plane.
 * */
void simulate(struct map* map, struct map* copy, size_t cycles, char mode);
 

 /*!
 * \fn bool lives(struct map* m, size_t line, size_t column, char* error, char mode);
 *  Used to determine whether a cell should live/die or born.
 * \param m the map.
 * \param line the line of the cell.
 * \param column the column of the cell.
 * \param error the error string.
 * \param mode 'T' for toroidal, 'P' for plane.
 * \return true if the cell would be alive, false otherwise.
 * */
bool lives(struct map* m, size_t line, size_t column, char* error, char mode);
 

/*!
 * \fn void read_map(struct map* m);
 * \param m the map.
 * Reads the map from stdin.
 * */
void read_map(struct map* m);

 
/*!
 * \fn void print_map(struct map* m);
 * Prints the map from stdout.
 * \param m the map.
 * */
void print_map(struct map* m);

#endif
