#ifndef _NEWTIME_H
#define _NEWTIME_H
#include <time.h>
#include <stdint.h>

typedef long double date_t;
struct cal {
	uint32_t nsec; // 0..1E9
	uint8_t   sec; // 0..60
	uint8_t   min; // 0..59
	uint8_t  hour; // 0..23
	uint8_t   day; // 0..30
	uint8_t month; // 0..11
	date_t   year; // Since Epoch
};

extern date_t date(void);
extern date_t sleepf(date_t time);

extern struct timespec totimespec(date_t d);
extern date_t        fromtimespec(struct timespec);

extern struct cal tocal(date_t d);
extern int wdayof(date_t d);
extern int ydayof(date_t d);
extern date_t   fromcal(struct cal cal);

extern int          tzoffat(date_t d, char *tz); // Seconds EAST of utc, like god intended
extern const char *tznameat(date_t d, char *tz);
extern date_t          intz(date_t d, char *tz); // return d+tzoffat(d, tz);
extern const char     *mytz(void);
extern date_t        inmytz(date_t d);           // return intz(d, mytz());

extern void printfdate(const char *fmt, date_t d, const char *zone);
/*
extern char *tmpdatestr(const char *fmt, date_t d, char *tz); // Realloc on the same array
extern char  *asdatestr(const char *fmt, date_t d, chat *tz); // Malloc on a different array
extern int   *sndatestr(const char *fmt, char *buf, size_t max, date_t d, char *tz) // strftime clone
date_t readdate(const char *fmt, char *buf, date_t base, char *tz) // strptime clone
*/
#endif
