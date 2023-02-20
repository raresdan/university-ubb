/* Write a program to read a number of units of length (a float) and print out the
area of a circle with that radius. Assume that the value of pi is 3.14159. After
that, change the type to double and compare the results.*/

#include <stdio.h>
#include <stdlib.h>
#define PI 3.14159

int main() {
	float radius, area, pi;
	printf("Enter radius (float): ");
	scanf("%f", &radius);
	area = radius * radius * PI;
	printf("The area of a circle with a float input radius %.2f is : %f \n", radius, area);
	double darea = (double)area;
	printf("The area of a circle with a float input radius %.2f is : %.15lf \n", radius, darea);
	if (area == darea) {
		printf("They are equal!");
	}
	return 0;
}
