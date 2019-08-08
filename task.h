#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "bool.h"
#include "datetime.h"

typedef enum {
	regular,
	today
} TaskType;

typedef struct {
	TaskType taskType;
	char task[50];
	DateTime dateTime;
	bool done;
} Task;

void acceptTask(Task *task) {
	char ch_type;
	char *pos;
		
	printf("Enter task\n");
	fgets(task->task, 50, stdin);

	pos = strchr(task->task,'\n');
	if(pos != NULL) {
		*pos='\0';
	}
	
	printf("Choose task type\tRegular (R)\tToday (T)\n");
	ch_type = getch();
	ch_type = tolower(ch_type);

	if(ch_type=='r') {
		task->taskType = regular;
	} else {
		task->taskType = today;
	}

	getCurrentDateTime(&task->dateTime);
	task->done = false;
}

void displayTask(Task *task) {
	char done[10];
	if(task->done) {
		strcpy(done, "done");
	} else {
		strcpy(done, "not done");
	}
	printf("%-50s%-20s\n",task->task, done);
}

#endif