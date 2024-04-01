#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define P20 1048576
//#define P24 16777216
//#define P30 1073741824

float randFloat() {
	return ((float)(rand() - rand())) / ((float)(rand() + rand()));
}

void randFloats(int n, float* arr) {
	int i;
	for (i = 0; i < n; i++) {
		arr[i] = ((float)(rand() * rand())) / ((float)(rand() + rand()));
	}
}

void initArray(int n, float* arr) {
	int i;
	for (i = 0; i < n; i++) {
		arr[i] = 0;
	}
}

void cSaxpy(int n, float a, float* x, float* y, float* z) {
	int i;
	for (i = 0; i < n; i++) {
		z[i] = a * x[i] + y[i];
	}
}

extern void aSaxpy(int n, float* z, float* x, float* y, float a);


void printArray(int n, float* arr) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%f \n", arr[i]);
	}
}

int main() {
	// Seed Rand
	srand(time(0));

	/* TEST: 10 Array Elements*/

	//Declare Variables
	float x10[10];
	float y10[10];
	float cz10[10];
	float az10[10];
	float aVal = randFloat();

	//Generate Values
	randFloats(10, x10);
	randFloats(10, y10);
	initArray(10, az10);

	//Get SAXPY
	cSaxpy(10, aVal, x10, y10, cz10);			// C SAXPY
	aSaxpy(10, az10, x10, y10, aVal);		// Assembly SAXPY

	//Print Results
	printf("N = 10, A = %f \n", aVal);
	printf("Array X: \n");
	printArray(10, x10);
	printf("\n\nArray Y: \n");
	printArray(10, y10);
	printf("\n\nC SAXPY: \n");
	printArray(10, cz10);
	printf("\n\nAssembly SAXPY: \n");
	printArray(10, az10);

	/* TEST: 2^20 */


	/* TEST: 2^24 */


	/* TEST: 2^30 */


	return 0;
}