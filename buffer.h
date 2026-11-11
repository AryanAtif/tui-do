#ifndef BUFFER_H
#define BUFFER_H

struct line
{
	char* task;	
	struct lines* next;
};

struct lines** head = NULL;
struct lines** tail = NULL;

int line_count = 0;

void store_to_list (char* line);

#endif
