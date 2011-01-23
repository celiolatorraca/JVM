#include <stdio.h>
#include <stdlib.h>
#include "jvmerr.h"

/**
 \brief Shows an error on the screen
 \param where Name of the location (function/file)
 \param msg Error msg
 */
void errorMsg(char *where, char *msg)
{
  fprintf(stderr, "%s Error: %s\n\n", where, msg);
}

/**
 \brief Shows an error on the screen and terminates the program
 \param where Name of the location (function/file)
 \param msg Error msg
 */
void fatalErrorMsg(char *where, char *msg)
{
  fprintf(stderr, "%s Error: %s\n\n", where, msg);
  exit(EXIT_FAILURE);
}
