#include "divisors.h"

#include <stdio.h>

unsigned int count_divisors(unsigned int n)
{
    unsigned int res = 0;

    for (unsigned int i = 1; i <=n/i; i++)
    {
        if (n % i == 0)
        {
            if(i==(n/i))
            {
                res+=1;
            }
            else 
            {
                res+=2;
            }
        }
    }

    return res;
}

unsigned int sum_divisors(unsigned int n)
{
    unsigned int res = 0;

    for (unsigned int i = 1; i <= n; i++)
    {
        res += count_divisors(n);
    }

    return res;
}

int main(void)
{
    unsigned int n = 20000;
    unsigned int result = sum_divisors(n);

    printf("Result: %u\n", result);

    return 0;
}
