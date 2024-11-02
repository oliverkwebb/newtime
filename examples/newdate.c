#include <newtime.h>

int main(int argc, char **argv)
{
	char *fmt = "%w %M %d %h:%m:%s %z %y\n";
	if (argc > 1) fmt = argv[1];
	printfdate(fmt, date(), mytz());
}
