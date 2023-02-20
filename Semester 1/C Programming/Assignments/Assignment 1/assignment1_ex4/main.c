/* Given as input a floating number of centimeters, print the corresponding number of
feet (integer) and inches (floating, 1 decimal), with the inches given to an
accuracy of one decimal place.
Assume 2.54 centimeters per inch, and 12 inches per foot.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    float num , feet;
    printf("Enter your desired number in cm: ");
    scanf("%f", &num);
    printf("%.2f cm are %1.f feet and %.1f inches!", num, num/2.54/12, num/2.54);
    return 0;
}
