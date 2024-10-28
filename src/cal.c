#include "newtime.h"
#include <math.h>
#include <time.h>
#include <stdio.h>

int isleap(long y)
{
	if (y > 1582)
		return ((!(y % 4)) ? ((!(y % 100)) ? !(y % 400) : 1) : 0);
	else
		return !(y % 4) ? 1 : 0;
}

int wdayof(date_t d)
{
	// TODO: Prevent INT_MAX overflow headaches
	time_t gmt = d;
	struct tm tm;
	gmtime_r(&gmt, &tm);
	return tm.tm_wday;
}

int ydayof(date_t d)
{
	// TODO: Prevent INT_MAX overflow headaches
	time_t gmt = d;
	struct tm tm;
	gmtime_r(&gmt, &tm);
	return tm.tm_yday;
}

struct cal tocal(date_t d)
{
	struct cal c;
	c.nsec = ((d-truncl(d))*1E9);

	// TODO: Prevent INT_MAX overflow headaches
	time_t gmt = d;
	struct tm tm;
	gmtime_r(&gmt, &tm);
	c.sec  = tm.tm_sec;
	c.min  = tm.tm_min;
	c.hour = tm.tm_hour;
	c.day  = tm.tm_mday - 1;
	c.month= tm.tm_mon;
	c.year = tm.tm_year - 70;
	
	return c;
}

date_t fromcal(struct cal cal)
{
	struct tm tm;
	tm.tm_sec  = cal.sec;
	tm.tm_min  = cal.min;
	tm.tm_hour = cal.hour;
	tm.tm_mday = cal.day + 1;
	tm.tm_mon  = cal.month;
	tm.tm_year = cal.year + 70;

	date_t seconds = timegm(&tm);
	return seconds + (cal.nsec/1E9);
}
