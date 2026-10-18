#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ncurses.h>

#define FILE_ADDR "/todo" // file named todo inside the $HOME dir

FILE* fp = NULL;
char** file_content = NULL;

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

int get_file_length()
{
  fseek (fp, 0, SEEK_END);
  int file_size = ftell (fp);
  fseek (fp, 0, SEEK_SET);

  return file_size;
}

int read_file_by_lines ()
{
  char ch;
  int file_len = get_file_length();
  int lines = 0;
  int i = 0;
  while (i < file_len)
  {
    file_content = realloc(file_content, (lines + 1)*sizeof(char*));
    if (file_content == NULL) {fprintf (stderr, "ERR: Couldn't allocate memory to file_content: %d\n", errno); return 1;}
    int ch_count = 0;
    while ((ch = fgetc(fp)) != '\n')
    {
      file_content[lines] = realloc(file_content[lines], (ch_count+1)*sizeof(char));
      if (file_content[lines] == NULL) {fprintf (stderr, "ERR: Couldn't allocate memory to file_content[%d]: %d\n", lines, errno); return 1;}
      file_content[lines][ch_count] = ch;
      ch_count++;
      i++;
    }
    i++;
    lines++;
  }
  return 0;
}
int print_file ()
{
  if(read_file_by_lines()) return 1;
  printf ("The file content: \n");
  int file_len = get_file_length();
  int lines = 0;
  int i = 0;
  while (i < file_len)
  {
    printf("%s\n", file_content[lines]);
    i += strlen(file_content[lines]) + 1; // + 1 for each newline character
    lines++;
  }
}

void display_tui()
{
  // Will work on this function later.
}

int display_cli()
{
  print_file();
  return 0;
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
    // Display all tasks on a tui -- will work on it later
    //display_tui();
    // Display tasks on the console
    if (display_cli()) return 1;
  }
  else if (argc == 3) // command -option file
  {
    // add ();
    // del ( task_number / task_string (case_insensitive));
    // edit ( task_number / task_string (case_insensitive));
  }
  return 0;
}

