#include "PA3.h"

long FibRecurse(int n, long* acc) {
    if(n < 2) {
        return n;
    }
    *acc = *acc + 1;
    return (FibRecurse(n-1, acc) + FibRecurse(n-2,acc));
}
long FibDynamic(int n, long* acc) {
    long* fib = malloc(sizeof(long) * (n+1));
    fib[0] = 0;
    fib[1] = 1;
    int i = 2;
    do{
        fib[i] = fib[i-1] + fib[i-2];
        *acc = *acc + 1;
        i++;
    }while(i<=n);
    long result = fib[n];
    free(fib);
    return result;
}