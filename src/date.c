#include <time.h>
#include "newtime.h"
#include <math.h>

int isleap(long y)
{
	if (y > 1582)
		return ((!(y % 4)) ? ((!(y % 100)) ? !(y % 400) : 1) : 0);
	else
		return !(y % 4) ? 1 : 0;
}

struct timespec totimespec(date_t t)
{
	return (struct timespec){.tv_sec = t, .tv_nsec = (t - floorl(t))*1E9};
}

date_t fromtimespec(struct timespec t)
{
	return ((long double)t.tv_nsec/1E9)+(((long double)t.tv_sec));
}

date_t date(void)
{
	struct timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	return fromtimespec(t);
}

date_t sleepf(date_t d)
{
	struct timespec t = totimespec(d);
	nanosleep(&t, &t);
	return fromtimespec(t);
}

static void dsn(date_t d, int *nsecs, int *secs, date_t *days)
{
	*days = floorl(d / 86400);
	*secs = floorl(fmodl(d, 86400));
	if (*secs < 0) {
		*secs += 86400;
		(*days)--;
	}
	*nsecs = (d-floorl(d))*1E9;
}

int wdayof(date_t d)
{
	 date_t days; int dummy;
	 dsn(d, &dummy, &dummy, &days);

	 int wday = fmodl(days+4, 7);
	 if (wday < 0) wday += 7;
	 return wday;
}