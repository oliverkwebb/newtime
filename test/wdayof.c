#include "newtime.h"
#include <stdio.h>

int main()
{
	for (int i = 0; i < 5; i++) {
	printf("%d\n", wdayof((int []){2, 86560, 12312321, 1312312, 3242}[i]));
	}
}
