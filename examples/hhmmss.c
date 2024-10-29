#include <newtime.h>
#include <stdio.h>

int main()
{
	struct cal c = tocal(inmytz(date()));
	printf("%d:%d:%d\n", c.hour, c.min, c.sec);
}
