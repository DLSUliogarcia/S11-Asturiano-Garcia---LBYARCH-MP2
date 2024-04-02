#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define E20 1048576
#define E21 2097152
#define E22 4194304
#define E23 8388608
#define E24 16777216
#define E28 268435456
#define E30 1073741824

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

void initDoubleArray(int n,double* arr) {
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

extern void aSaxpy(float a, float* Z, float* X, float* Y, int n);

void checkEqual(long unsigned int n, float* x, float* y, float* c, float* a) {
	long unsigned int i;
	long unsigned int ctr = 0;
	printf("|-------X Vector--------|--------Y Vector-------|----C SAXPY Results----|----ASM SAXPY Results----|\n");
	printf("|-----------------------|-----------------------|-----------------------|-------------------------|\n");
	for (i = 0; i < n; i++) {
		if (c[i] != a[i]) ctr++;
		if (i < 10) printf("| \t%f\t|\t%f\t|\t%f\t|\t%f\t  |\n", x[i], y[i], c[i], a[i]);
	}
	printf("---------------------------------------------------------------------------------------------------\n");
	printf("Total Mismatch: %d", ctr);
}

double getAveTime(int n, double* arr) {
	int i;
	double sum = 0;
	for (i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum / n;
}

void run(int arrSize, double *timesA, double *timesC, int index) {
	printf("Generating arrays of size %d...\n\n", arrSize);

	//Declare Variables
	float* x = (float*)malloc(arrSize * sizeof(float));
	float* y = (float*)malloc(arrSize * sizeof(float));
	float* cz = (float*)malloc(arrSize * sizeof(float));
	float* az = (float*)malloc(arrSize * sizeof(float));
	float aVal = randFloat();

	clock_t start_timeC, start_timeA, end_timeC, end_timeA;
	double timeC, timeA;

	//Generate Values
	randFloats(arrSize, x);
	randFloats(arrSize, y);

	//Get SAXPY
	start_timeC = clock();
	cSaxpy(arrSize, aVal, x, y, cz);			// C SAXPY
	end_timeC = clock();
	start_timeA = clock();
	aSaxpy(aVal, az, x, y, arrSize);		// Assembly SAXPY
	end_timeA = clock();

	//Get Times
	timeC = ((double)(end_timeC - start_timeC)) / CLOCKS_PER_SEC;
	timeA = ((double)(end_timeA - start_timeA)) / CLOCKS_PER_SEC;

	//Store Times
	timesC[index] = timeC;
	timesA[index] = timeA;

	//Print Results
	printf("Test #%d: A = %f \n", index, aVal);
	checkEqual(arrSize, x, y, cz, az);

	printf("\n\nTime Results:\n");
	printf("+-------------------+---------------+\n");
	printf("| Language          | Time (seconds)|\n");
	printf("+-------------------+---------------+\n");
	printf("| C                 | %-14.8lf|\n", timeC);
	printf("| Assembly          | %-14.8lf|\n", timeA);
	printf("+-------------------+---------------+\n\n\n\n");

	free(x);
	free(y);
	free(cz);
	free(az);
}

int main() {
	// Seed Rand
	srand(time(0));

	//Time Arrays
	double* cSaxpyTimes = (double*)malloc(30 * sizeof(double));
	double* aSaxpyTimes = (double*)malloc(30 * sizeof(double));

	//Initialize Arrays
	initDoubleArray(30, cSaxpyTimes);
	initDoubleArray(30, aSaxpyTimes);

	//Loop: 2^20
	int i = 0, j=0;
	for (i = 0; i < 30; i++) {
		run(E20, aSaxpyTimes, cSaxpyTimes, i);
	}
	double cAveTime = getAveTime(30, cSaxpyTimes);
	double aAveTime = getAveTime(30, aSaxpyTimes);

	//Print Results
	printf("Time Results (Seconds):\n");
	printf("+-------------------+---------------+\n");
	printf("| C                 |    Assembly   |\n");
	printf("+-------------------+---------------+\n");
	for (int j = 0; j < 30; j++) {
		printf("| %-14.8lf    | %-14.8lf|\n", cSaxpyTimes[j], aSaxpyTimes[j]);
	}
	printf("+-------------------+---------------+\n");
	printf("|  Average Time Results (Seconds)   |\n");
	printf("+-------------------+---------------+\n");
	printf("| C                 | %-14.8lf|\n", cAveTime);
	printf("| Assembly          | %-14.8lf|\n", aAveTime);
	printf("+-------------------+---------------+\n\n\n\n");

	//Clear Arrays
	free(cSaxpyTimes);
	free(aSaxpyTimes);

	return 0;
}
