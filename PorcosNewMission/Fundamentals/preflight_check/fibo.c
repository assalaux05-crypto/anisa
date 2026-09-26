#include "fibo.h"

int fibo(int n)
{
    if (n < 2)
        return n;

    int prev = 0;
    int cur = 1;
    for (int i = 2; i <= n; i++)
    {
        int next = prev + cur;
        prev = cur;
        cur = next;
    }

    return cur;
}
