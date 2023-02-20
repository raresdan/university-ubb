#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void SieveOfEratosthenes(int n)
{
    bool prime[n + 1];
    // 'memset' initializes all elements in prime with true
    memset(prime, true, sizeof(prime));
    for (int p = 2; p * p <= n; p++) {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    for (int p = 2; p <= n; p++)
        if (prime[p])
            printf("%d ",p);
}

int main()
{
    int n = 0;
    printf("Give an integer: ");
    scanf("%d", &n);
    printf("Following are the prime numbers smaller than or equal to %d: \n", n);
    SieveOfEratosthenes(n);
    return 0;
}

