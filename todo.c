#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include "bool.h"
#include "taskmanager.h"
#include "task.h"

#define esc 27

void clearbuffer() {
	char c;
	do{
		c = getchar();
	}while(c != EOF && c != '\n');
}

int main() {
	TaskManager taskManager;
	Task task;
	DateTime currentTime;
	int tno, i;
	char ch = esc;

	do {
		clrscr();
		loadTasks(&taskManager);
		displayTasks(&taskManager);
		printf("A-Add task\tM-Mark task as done\tR-Remove task\tEsc-Exit\n");

		ch = getch();
		ch = tolower(ch);

		switch(ch) {
			case 'a':
				printf("Add todo task\n");
				acceptTask(&task);
				if(task.taskType == regular) {
					taskManager.regularTasks[taskManager.rt_size] = task;
					taskManager.rt_size++;
				} else {
					taskManager.todaysTasks[taskManager.tt_size] = task;
					taskManager.tt_size++;
				}
				saveTasks(&taskManager);
			break;
			
			case 'm':
				if(taskManager.rt_size==0 && taskManager.tt_size==0) {
					printf("Empty task list\n");
					getch();
					break;
				}
				printf("Enter task number to mark as done\n");
				scanf("%d",&tno);
				clearbuffer();

				if(tno > (taskManager.rt_size + taskManager.tt_size)) {
					printf("Invalid task number");
					getch();
					break;
				} else {
					if(tno<=taskManager.rt_size) {
						taskManager.regularTasks[tno-1].done = true;
						getCurrentDateTime(&currentTime);
						taskManager.regularTasks[tno-1].dateTime = currentTime;
						saveTasks(&taskManager);
					} else {
						tno-=taskManager.rt_size;
						if(tno<=taskManager.tt_size) {
							taskManager.todaysTasks[tno-1].done = true;
							getCurrentDateTime(&currentTime);
							taskManager.todaysTasks[tno-1].dateTime = currentTime;
							saveTasks(&taskManager);
						} else {
							printf("Invalid task number\n");
							getch();
						}
					}
				}
			break;
			
			case 'r':
				if(taskManager.rt_size==0 && taskManager.tt_size==0) {
					printf("Empty task list\n");
					getch();
					break;
				}
				printf("Enter task number to remove\n");
				scanf("%d",&tno);
				clearbuffer();

				if(tno > (taskManager.rt_size + taskManager.tt_size)) {
					printf("Invalid task number");
					getch();
					break;
				} else {
					if(tno<=taskManager.rt_size) {
						for(i=tno;i<taskManager.rt_size;i++) {
							taskManager.regularTasks[i-1] = taskManager.regularTasks[i];
						}
						taskManager.rt_size--;
						saveTasks(&taskManager);
					} else {
						tno-=taskManager.rt_size;
						if(tno<=taskManager.tt_size) {
							for(i=tno;i<taskManager.tt_size;i++) {
								taskManager.todaysTasks[i-1] = taskManager.todaysTasks[i];
							}
							taskManager.tt_size--;
							saveTasks(&taskManager);
						} else {
							printf("Invalid task number\n");
							getch();
						}
					}
				}
			break;
			
			default:
			break;
		}
	}while(ch!=esc);

	return 0;
}