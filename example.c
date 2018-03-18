#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliarg.h"

int main(int argc, char *argv[]) 
{
  char    **error = NULL; // Get the errors
  char     *word  = NULL; // For get the "w" argument
  cliarg_t *args  = NULL; // geted arguments structure
  
  // liste of the expected arguments ("short name + type", "long name", ...)
  char *arglist[] = {
    "v", "verbose",  // no type = bool
    "r.", "#",       // . = int, # = no long name
    "s:+", "size",   // : = string, + = one ore more arguments
    "i.+", "#",
    "w:", "word",
    NULL
  };

  // check and get arguments from cli
  args = Cliarg_check_arguments(arglist, argv, argc, &error);

  // if args = NULL, an argument's error is detected
  if (!args) {
    Cliarg_print_error(stdout, error);      // Print the error
    return -1;
  }
  else {
    Cliarg_show_arguments(args);    // Show the geted arguments list
  }

  // Geting the "w" argument (NULL if not exists)
  word = STRING(Cliarg_get_copy_value(args, 'w', NULL));

  Cliarg_free_error(&error);
  Cliarg_free_arguments(&args);

  if (word) {
    printf("word = \"%s\"\n", word);
    free(word);
  }

  return 0;
}
