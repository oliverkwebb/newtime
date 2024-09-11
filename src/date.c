#include <time.h>
#include "newtime.h"
#include <math.h>

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

