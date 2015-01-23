// inspired from http://www.jera.com/techinfo/jtns/jtn002.html
#ifndef _MINUNIT_H_
#define _MINUNIT_H_

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define MAX_MESSAGE_SIZE 256

char message[MAX_MESSAGE_SIZE];


#define msg_handle(msg) do { sprintf(message, "Function: %s: line:%d %s \n",\
                             __func__, __LINE__, msg);} while (0)

/* file: minunit.h */
#define mu_assert(msg, test) do { msg_handle(msg);\
                                      if (!(test)) return message; } while (0)

#define mu_assert2(msg, test1, test2) do { msg_handle(msg);\
                                              if(!test1) ; \
                                              else if(test1 && !test2) \
                                              return message;} while (0) 

#define mu_run_test(test) do { char *msg = test(); tests_run++; \
                                if (msg) return msg; } while (0)


extern int tests_run;

#endif
