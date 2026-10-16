#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define FILE_ADDR "/notes"

void get_file_address()
{
  const char* home = getenv ("HOME");
  const char* subdir = FILE_ADDR;

  char* file_addr = malloc((strlen(home) + strlen(subdir)) * sizeof(char));
  if (file_addr == NULL) {fprintf (stderr, "ERR: Couldn't allocate memory to file_addr (%d)\n", errno);}
  file_addr = strcpy (file_addr, home);
  file_addr = strcat (file_addr, subdir);
  printf ("Complete file address: %s\n", file_addr);
}

void open_file()
{
  get_file_address();
}

int main(int argc, char** argv)
{
  if (argc > 3 || (argc < 3 && argc != 1)) 
  {
    if (argc < 3)  printf ("Too few parameters\n");
    else if (argc > 3)  printf ("Too many parameters\n");
    return 1;
  }
  open_file();

  if (argc == 1)
  {
    // Display all tasks
  }
  else if (argc == 3) // command -option file
  {
    // add ();
    // del ( task_number / task_string (case_insensitive));
    // edit ( task_number / task_string (case_insensitive));
  }
  return 0;
}

