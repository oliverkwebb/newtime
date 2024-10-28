#include <newtime.h>
#include <stdio.h>

int main()
{
	struct cal x[] = {
		{0, 30, 15, 12, 27, 2, 52},
		{5E8, 30, 15, 12, 27, 2, 52},
		{0, 0, 0, 0, 0, 0, 0},
	};

	for (int i = 0; i < (sizeof(x)/sizeof(x[0])); i++)
		printf("%Lf\n", fromcal(x[i]));
}
