#include "newtime.h"
#include <math.h>
#include <time.h>
#include <limits.h>
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

// This algorithm was originally made by Rich Felker in musl src/time/__secs_to_tm.c
struct cal tocal(date_t d)
{
	struct cal c;
	date_t days;
	unsigned secs;
	dsn(d, &c.nsec, &secs, &days);

	c.hour = secs / 3600;
	c.min  = secs / 60 % 60;
	c.sec  = secs % 60;

	char mdays[] = {31,30,31,30,31,31,30,31,30,31,31,29};
	
	days += 11017;
	date_t qc = truncl(days / 146097);
	int rd = fmodl(days, 146097);
	if (rd < 0) {
		rd += 146097;
		qc--;
	}

	int cen = trunc(rd / (365*100 + 24));
	if (cen == 4) cen--;
	rd -= cen * (365*100 + 24);


	int q = trunc(rd / (365*4 + 1));
	if (q == 25) q--;
	rd -= q * (365*4 + 1);

	int ry = trunc(rd / 365);
	if (ry == 4) ry--;
	rd -= ry * 365;

	c.year = ry + 4*q + 100*cen + 400*qc;
	c.month = 0;
	for (; mdays[c.month] <= rd; c.month++) rd -= mdays[c.month];

	if (c.month >= 10) {
		c.month -= 12;
		c.year++;
	}

	c.month += 2;
	c.day = rd + 1;
	c.year -= 30;
	
	return c;
}
