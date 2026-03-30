#include <stdio.h>

int main(void)
{
	int x, y;

	x = 1;
	printf("수식결과: %d\n", x + 1);
	printf("수식결과: %d\n", y = x + 1);
	printf("y의 변수값: %d\n", y );
	printf("수식의 결과: %d\n", y = 10 + (x = 2+7));
	printf("x 변수값: %d\n", x);
	printf("x++ 변수값: %d\n", x++);
	printf("x 변수값: %d\n", ++x);
	return 0;

}
