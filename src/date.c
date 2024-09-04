#include <time.h>
#include "newtime.h"

// Nanoseconds since epoch
// Integral percision loss does not occur until 2^112 (2**29 * 2**64 -> 2**93)

date_t fromtime_t(time_t t) { return t*1E9; }
time_t   totime_t(date_t t) { return t/1E9; }

struct timespec totimespec(date_t t)
{
	return (struct timespec){.tv_sec = t / 1E9, .tv_nsec = (long long)(t) % 1000000000};
}

date_t fromtimespec(struct timespec t)
{
	return ((long double)t.tv_nsec)+(((long double)t.tv_sec)*1E9);
}

// date_t: Floating point type: Nanoseconds since epoch

date_t date(void)
{
	struct timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	return fromtimespec(t);
}

