#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nVal 1024
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

void cSaxpy(long unsigned int n, float a, float* x, float* y, float* z) {
	long unsigned int i;
	for (i = 0; i < n; i++) {
		z[i] = a * x[i] + y[i];
	}
}

extern void aSaxpy(long unsigned int n, float* z, float* x, float* y, float a);


void printArray(int n, float* arr) {
	int i;
	for (i = 0; i < n; i++) {
		//if (i == 10) break;
		printf("%f \n", arr[i]);
	}
}

void checkEqual(long unsigned int n, float * x, float *y, float* a1, float* a2) {
	long unsigned int i;
	long unsigned int c = 0;
	printf("----X Vector----|--------Y Vector-------|-----C SAXPY Results----|----ASM SAXPY Results----|\n");
	printf("----------------|-----------------------|------------------------|-------------------------|\n");
	for (i = 0; i < n; i++) {
		if (a1[i] != a2[i]) c++;
		printf("%f\t|\t%f\t|\t%f\t |\t%f\t   |\n", x[i], y[i], a1[i], a2[i]);
	}
	printf("---------------------------------------------------------------------------------------------\n");
	printf("Total Mismatch: %d", c);
}

int main() {
	// Seed Rand
	srand(time(0));

	/* TEST: nVal Array Elements*/

	//Declare Variables
	float x[nVal];
	float y[nVal];
	float cz[nVal];
	float az[nVal];
	float aVal = randFloat();

	//Generate Values
	randFloats(nVal, x);
	randFloats(nVal, y);

	//Get SAXPY
	cSaxpy(nVal, aVal, x, y, cz);			// C SAXPY
	aSaxpy(nVal, az, x, y, aVal);		// Assembly SAXPY

	//Print Results
	printf("N = 10, A = %f \n", aVal);
	checkEqual(nVal, x, y, cz, az);

	return 0;
}