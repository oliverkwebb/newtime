#include "newtime.h"
#include <math.h>
#include <time.h>
#include <stdio.h>

static void dsn(date_t d, unsigned *nsecs, unsigned *secs, date_t *days)
{
	*days  = truncl(d / 86400);
	*secs  = fmodl(d, 86400);
	if (*secs < 0) {
		*secs += 86400;
		(*days)--;
	}
	*nsecs = (d-truncl(d))*1E9;
}

int wdayof(date_t d)
{
	 date_t days; unsigned dummy;
	 dsn(d, &dummy, &dummy, &days);

	 int wday = fmodl(days+4, 7);
	 if (wday < 0) wday += 7;
	 return wday;
}

int isleap(long y)
{
	if (y > 1582)
		return ((!(y % 4)) ? ((!(y % 100)) ? !(y % 400) : 1) : 0);
	else
		return !(y % 4) ? 1 : 0;
}

struct cal tocal(date_t d)
{
	struct cal c;
	c.nsec = ((d-truncl(d))*1E9);

	// TODO: Prevent INT_MAX overflow headaches
	time_t gmt = d;
	struct tm* tm = gmtime(&gmt);
	c.sec  = tm->tm_sec;
	c.min  = tm->tm_min;
	c.hour = tm->tm_hour;
	c.day  = tm->tm_mday - 1;
	c.month= tm->tm_mon;
	c.year += tm->tm_year - 70;
	
	return c;
}
