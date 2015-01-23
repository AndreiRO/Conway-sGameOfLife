/*! \file bitvector.h
 * Contains all the necessary function
 * declarations for a bitvector.
 * */

#ifndef _BITVECTOR_H_
#define _BITVECTOR_H_
#include<stdlib.h>

/*!
 * \typedef bool
 * represent a bool variable, 
 * char is the smallest type.
 * */
typedef char bool;

/*!
 * \typedef byte
 * represent a byte variable, 
 * */
typedef char byte;

/*!
 * \def EXIT_ON_OOM
 * \brief Exit on out of memory
 * If there isn't enough memory to allocate 
 * the bitvector and EXIT_ON_OOM == 1,
 * the program terminates, else it returns NULL.
 * */
#ifndef EXIT_ON_OOM
  #define EXIT_ON_OOM 1
#endif

/*!
 * \typedef true
 * substitute true with 1 
 * */
#define true 1

/*!
 * \typedef false
 * substitute false with 0 
 * */
#define false 0

/*!
 * \def BYTE_SIZE
 * a byte has 8 bits.
 * */
#define BYTE_SIZE 8

/*!
 * \def BITVECTOR_OUT_OF_MEMORY
 * error code when no more memory is available.
 * */
#define BITVECTOR_OUT_OF_MEMORY 1


/*!
 * \struct _bitvector
 * Struct to represent a bitvector.
 * */
struct _bitvector {
  size_t n_bits;  /**< the number of bits in the vector */
  size_t n_bytes; /**< the number of bytes allocated */
  byte* bytes;    /**< the actual bitvector */
};

/*!
 * \typedef bitvector
 * use struct _bitvector* easier.
 * */
typedef struct _bitvector* bitvector;


/*!
 *  \fn bitvector b_new(size_t);
 * Constructs a new bitvector with the given size;
 * \param bits the number of bits to store.
 * \return NULL if not enough memory, else a
 * bitvector variable.
 * \warning if EXIT_ON_OOM is not redefined with the value 0,
 * the program will exit if there isn't enough memory. Redefine
 * with -D EXIT_ON_OOM=0 if necessary.
 * */
bitvector b_new(size_t bits);


/*!
 *  \fn void b_delete(bitvector* b);
 *  frees an allocated bitvector.
 * */
void b_delete(bitvector* b);


/*!
 *  \fn void b_resize(bitvector*, size_t);
 *  resize a bitvector to the given size.
 *  \param b the bitvector to resize.
 *  \param size the number of bits to be.
 * */
void b_resize(bitvector* b, size_t size);


/*!
 *  \fn void b_copy(bitvector a, bitvector b);
 *  copy the content of a to b
 *  \param a is the source
 *  \param b is the destination
 * */
void b_copy(bitvector a, bitvector b);


/*!
 *  \fn void b_set(bitvector, size_t, bool);
 *  set the value in the bitvector, at the specifed index.
 *  \param a is the bitvector.
 *  \param index is the index of the bit to be changed.
 *  \param value is the value to be put.
 * */
void b_set(bitvector a, size_t index, bool value);


/*!
 *  \fn bool b_get(bitvector, size_t);
 *  Get the value of the specified bit.
 *  \param a is the bitvector.
 *  \param index is the index of the bit.
 * */
bool b_get(bitvector a, size_t index);


/*!
 *  \fn bitvector b_cmpl(bitvector a);
 *  Creates a bitvector whose value is that of
 *  a complemented.
 *  \param a is the bitvector to complement.
 * */
bitvector b_cmpl(bitvector a);


/*!
 *  \fn bitvector b_or(bitvector a, bitvector b); 
 *  Creates a bitvector whose value is that of
 *  a | b (at bits level).
 *  \param a is a bitvector.
 *  \param b is a bitvector
 * */
bitvector b_or(bitvector a, bitvector b);


/*!
 *  \fn bitvector b_and(bitvector a, bitvector b); 
 *  Creates a bitvector whose value is that of
 *  a & b (at bits level).
 *  \param a is a bitvector.
 *  \param b is a bitvector
 * */
bitvector b_and(bitvector a, bitvector b);


/*!
 *  \fn bitvector b_xor(bitvector a, bitvector b); 
 *  Creates a bitvector whose value is that of
 *  a ^ b (at bits level).
 *  \param a is a bitvector.
 *  \param b is a bitvector
 * */
bitvector b_xor(bitvector a, bitvector b);


/*!
 *  \fn bitvector b_diff(bitvector a, bitvector b); 
 *  Creates a bitvector whose value is that of
 *  a \ b (at bits level).
 *  \param a is a bitvector.
 *  \param b is a bitvector
 * */
bitvector b_diff(bitvector a, bitvector b);


/*!
 *  \fn bool b_equal(bitvector a, bitvector b);
 *  Checks if the bitvectors are equal 
 *  \return true if they are equal, false else
 *  \param a is a bitvector.
 *  \param b is a bitvector
 * */
bool b_equal(bitvector a, bitvector b);

#endif
