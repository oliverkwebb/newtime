#include <newtime.h>
#include <stdlib.h>
#include <string.h>

static char *tmptz = NULL;

static void usingtz(char *name)
{
	// Save current timezone value
	char *tz = getenv("TZ");
	if (tz) {
		tmptz = realloc(tmptz, strlen(tz));
		strcpy(tmptz, tz);
	}
	else
		tmptz = NULL;

	if (name)
		setenv("TZ", name, 1);

	tzset();
}

static void unusingtz(void)
{
	if (tmptz)
		setenv("TZ", tmptz, 1);
	else
		unsetenv("TZ");
	tzset();
}

int tzoffat(date_t d, char *tz)
{
	usingtz(tz);
	struct tm tm;
	time_t ttt = (time_t)d;
	localtime_r(&ttt, &tm);
	unusingtz();
	return tm.tm_gmtoff;
}

const char *tznameat(date_t d, char *tz)
{
	usingtz(tz);
	struct tm tm;
	time_t ttt = (time_t)d;
	localtime_r(&ttt, &tm);
	// This is to apease musl
	char *cpy = strdup(tm.tm_zone);
	unusingtz();
	return cpy;
}

const char *mytz(void)
{
	usingtz(NULL);
	return tmptz ? tmptz : "/etc/localtime";
}

date_t intz(date_t d, char *tz) { return d+tzoffat(d, tz);     }
date_t inmytz(date_t d)         { return d+tzoffat(d, mytz()); }
