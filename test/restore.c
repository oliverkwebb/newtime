#include <newtime.h>
#include <stdio.h>

int main()
{
	printf("%d\n", tocal(intz(date(), "Europe/Berlin")).hour);
	printf("%s\n",  mytz());
}
