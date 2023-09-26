/*a. Determine the value x^n, where x is a real number and n is a natural number, by using multiplication and squared operations.
b. Given a vector of numbers, find the longest contiguous subsequence such that any two consecutive elements have contrary signs.*/
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <math.h>

int powerByMultiplication(double x, int n) {
    // computes the value of x^n by repeated multiplications
    double newx = x;
	for (int i = 1; i < n; i++)
		newx = newx * x;
	return (int)newx;
}

int powerBySquaredOperation(double x, int n) {
    // computes the value of x^n by using the c power function
	double newx = pow(x, n);
	return (int)newx;
}

int maximum(int a, int b) {
    // using ternary expression, determines the maximum out of a and b 
	return a > b ? a : b;
}

int longestContiguousSubsequence(int array[], int size) {
    int maximumLength = 1; // initialize the maximum length to 1
    int length = 1; // initialize the current length to 1
    // loop through the array
    for (int i = 1; i < size; i++) {
        // check if the current element has opposite sign to the previous one
        if ((array[i] < 0 && array[i - 1] > 0) || (array[i] > 0 && array[i - 1] < 0)) {
            length++; // increment the current length
            maximumLength = maximum(maximumLength, length); // update the maximum length
        }
        else {
            length = 1; // reset the current length to 1
        }
    }
    return maximumLength;
}

int main()
{
    int choice = -1;
    int size = 0, x, n;
    int array[100];
    printf("\nMenu\n\n");
    printf("1 - Find the longest contiguous subsequence of an array\n");
    printf("2 - Determine the value x^n\n");
    printf("0 - Exit the program\n");
    while (choice != 0) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                while (size <= 0) {
                    printf("Enter the size of the array: ");
                    scanf("%d", &size);
                }
                printf("Enter %d numbers: ", size);
                for (int i = 0; i < size; i++) {
                    scanf("%d", &array[i]);
                }
                if (array == NULL) {
                    printf("Please read an array first.\n");
                    break;
                }
                printf("Array read successfully.\n");
                int subSeqLength = longestContiguousSubsequence(array, size);
                printf("The longest contiguous subsequence with alternating signs has length %d\n", subSeqLength);
                break;
            case 2:
                printf("Enter a base number: ");
                scanf("%d", &x);
                printf("Enter an exponent: ");
                scanf("%d", &n);
                int power1 = powerByMultiplication(x, n);
                int power2 = powerBySquaredOperation(x, n);
                printf("%d raised to the power %d using multiplication: %d\n", x, n, power1);
                printf("%d raised to the power %d using pow function: %d\n", x, n, power2);
                break;
            case 0:
                // exit the program
                printf("Menu exited successfully.\n");
                break;
            default:
                // invalid choice
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
