#define /*_NOT*/_GNU_SOURCE // *sigh*
#include <newtime.h>
#include <stdlib.h>
#include <string.h>

static char *tmptz = NULL;
static int   using = 0;

static void usingtz(char *name)
{
	if (!name || !*name) return;
	char *timezone = getenv("TZ");
	using = 0;
	if (timezone && tmptz && strlen(tmptz) != strlen(timezone)) { // Slower to realloc
			tmptz = realloc(tmptz, strlen(timezone));
			strcpy(tmptz, timezone);
	}
	setenv("TZ", name, 1);
	tzset();
}

static void unusingtz(void)
{
	if (!using) return;
	using = 0;
	setenv("TZ", tmptz ? tmptz : "", 1);
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
	unusingtz();
	return tm.tm_zone;
}

const char *mytz(void)          { return getenv("TZ") ? : "/etc/localtime"; }
date_t intz(date_t d, char *tz) { return d+tzoffat(d, tz);     }
date_t inmytz(date_t d)         { return d+tzoffat(d, mytz()); }
