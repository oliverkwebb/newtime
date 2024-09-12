#include "newtime.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) {
		struct cal c = tocal(strtold(argv[i], 0));
		printf("%u\n", c.month);
	}
}
