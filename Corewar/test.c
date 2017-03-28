#include <stdio.h>

int main(void)
{
	short int jump = 0xFFFB;
	
	printf("sizeof(short int) = %zu --> %hd\n", sizeof(short), jump);

	return (0);
}
