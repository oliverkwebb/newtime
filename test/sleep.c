#include "newtime.h"

int main()
{
	date_t then = date();
	sleepf(1);
	date_t now  = date();
	return (now)-(then+1);
}
