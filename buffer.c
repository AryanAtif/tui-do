#include <stdlib.h>
#include <string.h>

#include "buffer.h"

void store_list (struct line** head, struct line** tail, char* line)
{
	if(*head == NULL) // add the first task 
	{
		*head = malloc (sizeof(struct line));
		(*head)->content = malloc (strlen(task) * sizeof(char));
		(*head)->content = task;
		(*head)->next = NULL;
		*tail = NULL;
	}
	else // add the new task at the end of the file
	{
		struct line* new = malloc (sizeof(struct line));
		new->content = malloc (strlen(task) * sizeof(char));
		new->content = task;
		new->next = NULL;

		*tail->next = new;
		*tail = new;
	}
}

int read_file_by_lines ()
{
	char ch;
	int file_len = get_file_length();
	char* line_read;
	int lines = 0;
	int i = 0;
	while (i < file_len)
	{
		line_read = NULL;
		printf ("reading file...\n");
		int ch_count = 0;
		while ((ch = fgetc(fp)) != '\n')
		{
			line_read = realloc(line_read, (ch_count+1)*sizeof(char));
			if (line_read == NULL) {fprintf (stderr, "ERR: Couldn't allocate memory to file_content[%d]: %d\n", lines, errno); return 1;}
			line_read[ch_count] = ch;
			ch_count++;
		}
		store_to_list(line_read);
		i++;
		lines++;
	}
	return 0;
}
