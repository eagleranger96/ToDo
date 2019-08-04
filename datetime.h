#ifndef DATETIME_H
#define DATETIME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bool.h"

typedef struct {
	int d, M, y, h, m, s;
} DateTime;

void getCurrentDateTime(DateTime *dateTime) {
	time_t rawtime;
	struct tm *timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	dateTime->d = timeinfo->tm_mday;
	dateTime->M = timeinfo->tm_mon + 1;
	dateTime->y = timeinfo->tm_year + 1900;
	dateTime->h = timeinfo->tm_hour;
	dateTime->m = timeinfo->tm_min;
	dateTime->s = timeinfo->tm_sec;
}

bool isDiffDay(DateTime *day1, DateTime *day2) {
	if(day1->d==day2->d && day1->M==day2->M && day1->y==day2->y) {
		return false;
	}
	return true;
}

#endif