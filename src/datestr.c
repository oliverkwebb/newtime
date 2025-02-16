#include <newtime.h>
#include <langinfo.h>
#include <string.h>
#include <stdio.h>

/* TODO:
zone off fmt +-hhmm  - fz
zone off fmt +-hh:mm - :z
*/

static void writedatestr(int (*submit)(const char *fmt, ...), const char *fmt, date_t d, const char *zone)
{
	date_t zone_corr = intz(d, zone);
	struct cal c = tocal(zone_corr);
	for (int i = 0; i < strlen(fmt); i++) {
		if (fmt[i] != '%') submit("%c", fmt[i]);
		else switch (fmt[++i]) {
		case  '%': // FALLTHROUGH
		case '\0': submit("%%"); break;

		case 'h': submit("%02u", c.hour); break;
		case 'm': submit("%02u", c.min); break;
		case 's': submit("%02u", c.sec); break;

		case 'w': submit("%s", nl_langinfo(DAY_1+wdayof(zone_corr))); break;
		case 'd': submit("%02u", c.day); break;
		case 'M': submit("%s", nl_langinfo(MON_1+c.month)); break;
		case 'y': submit("%.0Lf", c.year+1970); break;
		case 'z': submit("%s", tznameat(d, zone)); break;
		default:
			if (!strncmp(fmt+i, "Ns", 2))
				submit("%u", c.nsec);
			else if (!strncmp(fmt+i, "Us", 2))
				submit("%u", c.nsec/1000);
			else if (!strncmp(fmt+i, "ch", 2))
				submit("%u", c.hour % 12);
			else if (!strncmp(fmt+i, "ih", 2))
				submit("%s", c.hour % 12 ? "AM" : "PM");
			else if (!strncmp(fmt+i, "Fs", 2))
				submit("%03u", c.nsec/1000000);
			else if (!strncmp(fmt+i, "Es", 2))
				submit("%.0Lf", d);
			else if (!strncmp(fmt+i, "nw", 2))
				submit("%02u", wdayof(zone_corr));
			else if (!strncmp(fmt+i, "aw", 2))
				submit("%s", nl_langinfo(ABDAY_1+wdayof(zone_corr)));
			else if (!strncmp(fmt+i, "nM", 2))
				submit("%02u", c.month+1);
			else if (!strncmp(fmt+i, "aM", 2))
				submit("%s", nl_langinfo(ABMON_1+c.month));
			else if (!strncmp(fmt+i, "Dy", 2))
				submit("%u", wdayof(zone_corr));
			else if (!strncmp(fmt+i, "Cy", 2))
				submit("%.0Lf", (c.year)/100);
			//else if (!strncmp(fmt+i, "Sy", 2))
			//	submit("%.0Lf", (c.year+1970)(long)%100);
			else if (!strncmp(fmt+i, "nz", 2))
				submit("%s", zone);
			else if (!strncmp(fmt+i, "oz", 2))
				submit("%d", tzoffat(d, zone));
			else break;
			i++;
			break;
		}
	}
}

void printfdate(const char * fmt, date_t d, const char *zone)
{
	writedatestr(printf, fmt, d, zone);
}

// TODO
/*
date_t readdate(const char *fmt, char *buf, date_t base, char *tz)
{
	struct cal cbase = tocal(intz(base, tz));

	for (size_t i = 0; i < strlen(fmt); i++) {
		size_t bufidx = 0;
	}
	
	return fromcal(cbase);
}
*/
