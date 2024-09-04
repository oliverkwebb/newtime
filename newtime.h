#ifndef _NEWTIME_H
#define _NEWTIME_H

#include <time.h>

typedef long double date_t;

struct cal {
	unsigned nsecs; // 0..1E9
	unsigned  secs; // 0..60
	unsigned  mins; // 0..59
	unsigned hours; // 0..23
	unsigned   day; // 0..30
	unsigned   mon; // 0..11
	int       year; // Since Epoch
	int      tzoff; // Seconds east of UTC
};

extern time_t   totime_t(date_t);
extern date_t fromtime_t(time_t);

extern struct timespec      totimespec(date_t);
extern date_t fromtimespec(struct timespec tm);

extern date_t date(void);

#endif
