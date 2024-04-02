#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nVal 268435456
//#define P19 524288
//#define P20 1048576
//#define P24 16777216
//#define P28 268435456
//#define P29 536870912


float randFloat() {
	return ((float)(rand() - rand())) / ((float)(rand() + rand()));
}

void randFloats(long unsigned int n, float* arr) {
	long unsigned int i;
	for (i = 0; i < n; i++) {
		arr[i] = ((float)(rand() * rand())) / ((float)(rand() + rand()));
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
		if (i <= 100) printf("%f\t|\t%f\t|\t%f\t |\t%f\t   |\n", x[i], y[i], a1[i], a2[i]);
	}
	printf("---------------------------------------------------------------------------------------------\n");
	printf("Total Mismatch: %d", c);
}

int main() {
	// Seed Rand
	srand(time(0));

	/* TEST: nVal Array Elements*/

	//Declare Variables
	float* x = (float*)malloc(nVal * sizeof(float));
	float* y = (float*)malloc(nVal * sizeof(float));
	float* cz = (float*)malloc(nVal * sizeof(float));
	float* az = (float*)malloc(nVal * sizeof(float));
	float aVal = randFloat();

	//Generate Values
	randFloats(nVal, x);
	randFloats(nVal, y);

	//Setup Timers
	clock_t start_timeC, start_timeA, end_timeC, end_timeA;
	double timeC, timeA;

	//C SAXPY
	start_timeC = clock();
	cSaxpy(nVal, aVal, x, y, cz);		// C SAXPY
	end_timeC = clock();

	//Assembly SAXPY
	start_timeA = clock();
	aSaxpy(nVal, az, x, y, aVal);		// Assembly SAXPY
	end_timeA = clock();

	//Get Time
	timeC = ((double)(end_timeC - start_timeC)) / CLOCKS_PER_SEC;	//C Time
	timeA = ((double)(end_timeA - start_timeA)) / CLOCKS_PER_SEC;	//Assembly Time

	//Print Results
	printf("N = %d, A = %f \n", nVal, aVal);
	checkEqual(nVal, x, y, cz, az);
	printf("\n\nTime Results:\n");
	printf("+-------------------+---------------+\n");
	printf("| Language          | Time (seconds)|\n");
	printf("+-------------------+---------------+\n");
	printf("| C                 | %-14.6f|\n", timeC);
	printf("| Assembly          | %-14.6f|\n", timeA);
	printf("+-------------------+---------------+\n\n\n\n");

	free(x);
	free(y);
	free(cz);
	free(az);

	return 0;
}