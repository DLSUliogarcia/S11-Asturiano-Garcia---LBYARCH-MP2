# Introduction
Welcome to the Github Repository of Christian Asturiano and Aurelio Garcia of LBYARCH S11 of the College of Computer Studies, De Lasalle University of Manila
This project is an x86-64 to C Interface that calculates the SAXPY result of two vectors and a scalar variable.
_Z[i] = A*X[i] + Y[i]_

#  How It Works
Constants for various powers of 2 were defined in the code, as shown in the image below:

![image](https://github.com/DLSUliogarcia/S11-Asturiano-Garcia---LBYARCH-MP2/assets/129931296/093d0bdf-62d6-4f97-acfc-3dce143913be)

To alter the number of vector elements, simply change the value of "arrSize" to another constant or any other positive whole number:

![image](https://github.com/DLSUliogarcia/S11-Asturiano-Garcia---LBYARCH-MP2/assets/129931296/a9dbf0e6-2eda-4ab0-96a9-f43ae38b9503)

The SAXPY results are calculated both by a C function and an assembly function called in the C program.
The values of both SAXPY calculations are compared by checkEqual(long unsigned int n)

![Screenshot 2024-04-02 192511](https://github.com/DLSUliogarcia/S11-Asturiano-Garcia---LBYARCH-MP2/assets/129931296/b1bc23ee-7111-4a86-aa9b-bb6635d0b7e0)

When a mismatch is detected, the mismatched pair is printed out with a signal

The program performs 30 tests for every SAXPY calculation, both for the C and the Assembly functions, to gain an accurate average calculation time.
The time is only taken before and after either the C or Assembly function runs

![image](https://github.com/DLSUliogarcia/S11-Asturiano-Garcia---LBYARCH-MP2/assets/129931296/b0b3201a-b7c1-4604-88a8-7a5de796853b)


#  Debug Version Test Results
The following images are the test results of the Debug version of the program, at vector sizes of 2^20, 2^24, and 2^30.
### Vector Size = 2^20

![image](https://github.com/DLSUliogarcia/S11-Asturiano-Garcia---LBYARCH-MP2/assets/129931296/a4bf2039-cacf-493a-b656-37aff5bc0f41)

### Vector Size = 2^24

![image](https://github.com/DLSUliogarcia/S11-Asturiano-Garcia---LBYARCH-MP2/assets/129931296/03081029-1dcf-4ecf-a25a-b12e48023c82)

### Vector Size = 2^30

![image](https://github.com/DLSUliogarcia/S11-Asturiano-Garcia---LBYARCH-MP2/assets/129931296/374a3a6f-ca92-44f0-95b2-ba0877546274)

#  Release Version Test Results
The following images are the test results of the Release version of the program, at vector sizes of 2^20, 2^24, and 2^30.
### Vector Size = 2^20

![image](https://github.com/DLSUliogarcia/S11-Asturiano-Garcia---LBYARCH-MP2/assets/129931296/acf69667-4a6b-47c4-a486-a9020e10ed8f)

### Vector Size = 2^24

![image](https://github.com/DLSUliogarcia/S11-Asturiano-Garcia---LBYARCH-MP2/assets/129931296/e6447ea3-9597-4836-a6f2-eb1214b4bc5e)

### Vector Size = 2^30

![image](https://github.com/DLSUliogarcia/S11-Asturiano-Garcia---LBYARCH-MP2/assets/129931296/58872518-c4ef-4789-80ce-b3f62e0a0e40)

# Comparing Versions
### Debug Mode Summary
|             | Average Execution Time for C (in seconds) | Average Execution Time for Assembly (in seconds) |  Fastest | Time difference (in seconds)|
|:-----------:|:-----------------------------------------:|:-------------------------------------------------:|:--------:|:---------------:|
|    2<sup>20</sup>     |                 0.003633                  |                      0.001567                     | Assembly |     0.002066    |
|    2<sup>24</sup>   |                 0.039167                  |                      0.013567                     | Assembly |     0.025600      |
|    2<sup>30</sup>  |                 2.534233                  |                      0.846000                     | Assembly |     1.688233    |

### Release Mode Summary
|             | Average Execution Time for C (in seconds) | Average Execution Time for Assembly (in seconds) | Fastest | Time difference (in seconds) |
|:-----------:|:-----------------------------------------:|:-------------------------------------------------:|:-------:|:-------------------------:|
|    2<sup>20</sup>    |                  0.001133                 |                      0.001200                     |    C    |           0.000067      |
|   2<sup>24</sup>   |                  0.014400                 |                      0.015333                     |    C    |           0.000933      |
|    2<sup>30</sup>    |                  0.724233                 |                      0.839367                     |C        |           0.115134        |

Across all tests, even vector sizes as large as 1 billion (approximately 2^30) can be processed swiftly by either the C or assembly version of the SAXPY function. 

Notably, in debug mode, assembly outperforms C in terms of speed, while in release mode, the situation is reversed. Despite these differences, the execution times for the assembly implementation remain consistently stable across both modes. However, the C implementation experiences a substantial performance boost in release mode, demonstrating a significant 70% increase in speed compared to debug mode. 

This is because, by default, [optimization is turned off in the Debug mode of a C/C++ program and turned on in the Release mode](https://learn.microsoft.com/en-us/visualstudio/debugger/how-to-debug-optimized-code?view=vs-2022).
