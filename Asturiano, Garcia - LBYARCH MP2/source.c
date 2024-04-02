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

double cTime = 0;
double aTime = 0;

float* x;
float* y;
float* cz;
float* az;

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

void cSaxpy(int n, float a, float* X, float* Y, float* Z) {
	int i;
	for (i = 0; i < n; i++) {
		Z[i] = a * X[i] + Y[i];
	}
}

extern void aSaxpy(float a, float* Z, float* X, float* Y, int n);

void checkEqual(long unsigned int n) {
	long unsigned int i;
	long unsigned int ctr = 0;
	printf("|-------X Vector--------|--------Y Vector-------|----C SAXPY Results----|----ASM SAXPY Results----|\n");
	printf("|-----------------------|-----------------------|-----------------------|-------------------------|\n");
	for (i = 0; i < n; i++) {
		if (cz[i] != az[i]) ctr++;
		if (i < 10) printf("| \t%f\t|\t%f\t|\t%f\t|\t%f\t  |\n", x[i], y[i], cz[i], az[i]);
	}
	printf("---------------------------------------------------------------------------------------------------\n");
	printf("Total Mismatch: %d", ctr);
}

void run(int arrSize) {
	printf("Generating arrays of size %d...\n", arrSize);

	//Define Arrays
	x = (float*)malloc(arrSize * sizeof(float));
	y = (float*)malloc(arrSize * sizeof(float));
	cz = (float*)malloc(arrSize * sizeof(float));
	az = (float*)malloc(arrSize * sizeof(float));
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
	cTime += timeC;
	aTime += timeA;

	//Print Results
	printf("A =  %f \n", aVal);
	checkEqual(arrSize);

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
	//double aSaxpyTimes = 0;
	//double cSaxpyTimes = 0;

	//Loop: 2^20
	int i = 0, j=0, n = 30;
	for (i = 0; i < n; i++) {
		printf("Test #%d: ", i+1);
		run(E20);
	}
	double cAveTime = cTime / n;
	double aAveTime = aTime / n;

	//Print Results
	printf("+-------------------+---------------+\n");
	printf("|  Average Time Results (Seconds)   |\n");
	printf("+-------------------+---------------+\n");
	printf("| C                 | %-14.8lf|\n", cAveTime);
	printf("| Assembly          | %-14.8lf|\n", aAveTime);
	printf("+-------------------+---------------+\n\n\n\n");

	return 0;
}
