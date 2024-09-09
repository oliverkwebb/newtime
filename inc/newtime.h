#ifndef _NEWTIME_H
#define _NEWTIME_H

typedef long double date_t;

struct tz {
	int tzoff; // Seconds east of UTC
	const char *tzname;
};

struct cal {
	unsigned  nsec; // 0..1E9
	unsigned   sec; // 0..60
	unsigned   min; // 0..59
	unsigned  hour; // 0..23
	unsigned   day; // 0..30
	unsigned month; // 0..11
	long      year; // Since Epoch
};

extern struct timespec totimespec(date_t);
extern date_t        fromtimespec(struct timespec);

extern date_t date(void);
extern date_t sleepf(date_t);

extern struct cal tocal(date_t);
extern int wdayof(date_t);

#endif
