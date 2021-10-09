#include <stdio.h>
#include <stdlib.h>

#define FINDNUM	100

int main(void)
{
	int i,j;

	for (i = 2; i <= FINDNUM; i++) {
		for (j = 2; j <= i / 2; j++) {
			if (i % j == 0) break;
		}
		if (j > i / 2) printf(" %d", i);
	}
	exit(0);
}