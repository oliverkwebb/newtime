#include <newtime.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char *zones[] = {
		"GMT",
		"America/Denver",
		"Asia/Kolkata",
		"Asia/Riyadh",
		"Europe/Berlin",
		"GMT-9",
		"GMT+4"
	};

	for (int i = 1; i < argc; i++) {
		date_t arg = strtold(argv[i], NULL);
		for (int j = 0; j < 7; j++)
			printf("%Lf, %Lf, %s\n", arg, intz(arg, zones[j]), tznameat(arg, zones[j]));
	}
}
