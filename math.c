#include<math.h>
#include<stdio.h>

#define MPI 3.1415926535897932384

int main()
{
	printf("%f\n", sin(3*MPI / 4));
	printf("%f\n", cos(3*MPI / 4));
	printf("%f\n", tan(3*MPI / 4));
	printf("%f\n", atan(1) / MPI);
//	n = (float)2 / (float)3;
	return 0;
}
