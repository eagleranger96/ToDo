#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "bool.h"
#include "datetime.h"
#include "task.h"

typedef struct {
	Task regularTasks[30];
	Task todaysTasks[30];
	int rt_size, tt_size;
} TaskManager;

void saveTasks(TaskManager *taskManager) {
	FILE *taskFile;
	int i;

	taskFile = fopen("taskFile.dat","w");
	if(taskFile != NULL) {
		for(i=0;i<taskManager->rt_size;i++) {
			fwrite(&taskManager->regularTasks[i], sizeof(Task), 1, taskFile);
		}

		for(i=0;i<taskManager->tt_size;i++) {
			fwrite(&taskManager->todaysTasks[i], sizeof(Task), 1, taskFile);
		}

		fclose(taskFile);
	} else {
		printf("Unable to save todo tasks\n");
	}
}

void loadTasks(TaskManager *taskManager) {
	FILE *taskFile;
	int i,j;
	Task tempTask;
	DateTime currentTime;

	taskManager->rt_size = taskManager->tt_size = 0;

	taskFile = fopen("taskFile.dat","r");
	if(taskFile != NULL) {
		i = j = 0;
		while(fread(&tempTask, sizeof(Task), 1, taskFile)) {
			if(tempTask.taskType == regular) {
				getCurrentDateTime(&currentTime);
				if(isDiffDay(&tempTask.dateTime, &currentTime)) {
					tempTask.done = false;
					tempTask.dateTime = currentTime;
				}
				
				taskManager->regularTasks[i] = tempTask;
				i++;
			} else {
				getCurrentDateTime(&currentTime);
				if(!isDiffDay(&tempTask.dateTime, &currentTime) || !tempTask.done) {
					taskManager->todaysTasks[j] = tempTask;
					j++;
				}
			}
		}
		taskManager->rt_size = i;
		taskManager->tt_size = j;

		fclose(taskFile);
		saveTasks(taskManager);
	} else {
		// load file not found
	}
}

void displayTasks(TaskManager *taskManager) {
	int i=1, j;
	if(taskManager->rt_size > 0) {
		printf("Regular Tasks\n");
		printf("%-10s%-50s%-20s\n", "S.No.", "Task", "Done Today ?");
		for(j=0;j<taskManager->rt_size;j++) {
			printf("%s%d%-8s", "(", i, ")");
			displayTask(&taskManager->regularTasks[j]);
			i++;
		}
		printf("\n");
	}

	if(taskManager->tt_size > 0) {
		printf("Today\'s Tasks\n");
		printf("%-10s%-50s%-20s\n", "S.No.", "Task", "Done ?");
		for(j=0;j<taskManager->tt_size;j++) {
			printf("%s%d%-8s", "(", i, ")");
			displayTask(&taskManager->todaysTasks[j]);
			i++;
		}
		printf("\n");
	}
}

#endif