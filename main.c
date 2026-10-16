#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ncurses.h>

#define FILE_ADDR "/todo" // file named todo inside the $HOME dir

FILE* fp = NULL;

char* get_file_address()
{
  const char* home = getenv ("HOME");
  const char* subdir = FILE_ADDR;

  char* file_addr = malloc((strlen(home) + strlen(subdir)) * sizeof(char));
  if (file_addr == NULL) {fprintf (stderr, "ERR: Couldn't allocate memory to file_addr (%d)\n", errno); return NULL;}
  file_addr = strcpy (file_addr, home);
  file_addr = strcat (file_addr, subdir);
  printf ("Complete file address: %s\n", file_addr);
  return file_addr;
}

int open_file()
{
  char* file_addr = get_file_address();
  if (file_addr == NULL) return 1;
  fp = fopen(file_addr, "a+");
  if (fp == NULL) {fprintf (stderr, "ERR: Couldn't open the file. (errno: %d)\n", errno); return errno;}
  return 0;
}

void display()
{
  initscr();
  printw("Hello Everybody, my name is marketpiler!\n");
  refresh();
  getch();
  endwin();
}

int main(int argc, char** argv)
{
  if (argc > 3 || (argc < 3 && argc != 1)) 
  {
    if (argc < 3)  printf ("Too few parameters\n");
    else if (argc > 3)  printf ("Too many parameters\n");
    return 1;
  }

  if (open_file() != 0) return 1;

  if (argc == 1)
  {
    // Display all tasks
    display();
  }
  else if (argc == 3) // command -option file
  {
    // add ();
    // del ( task_number / task_string (case_insensitive));
    // edit ( task_number / task_string (case_insensitive));
  }
  return 0;
}

