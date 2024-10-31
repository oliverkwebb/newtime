#include <newtime.h>
#include <langinfo.h>
#include <string.h>
#include <stdio.h>

void printfdate(const char *fmt, date_t d, const char *zone)
{
	date_t zone_corr = intz(d, zone);
	struct cal c = tocal(zone_corr);
	for (int i = 0; i < strlen(fmt); i++) {
		if (fmt[i] != '%') putchar(fmt[i]);
		else switch (fmt[++i]) {
		case  '%': // FALLTHROUGH
		case '\0': putchar('%'); break;

		case 'm': printf("%d", c.min); break;
		case 'h': printf("%d", c.hour); break;
		case 'y': printf("%.0Lf", c.year+1970); break;
		case 's': printf("%d", c.sec); break;
		case 'w': printf("%s", nl_langinfo(ABDAY_1+wdayof(zone_corr))); break;
		case 'z': printf("%s", tznameat(d, zone)); break;
		}
	}
}
