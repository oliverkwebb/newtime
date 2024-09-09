#include <time.h>
#include "newtime.h"

int main()
{
	return time(0) != (time_t)date();
}
