#include "PA3.h"
int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    long accumlation = 0;
    long result = 0;
    clock_t time;
    time = clock();
    result = FibRecurse(n,&accumlation);
    time = clock() - time;
    double timetaken = ((double)time)/CLOCKS_PER_SEC;
    printf("FibRecurse(%d) = %ld, Addition Operations Performed: %ld\nTime taken: %f seconds\n\n",n,result,accumlation,timetaken);
    accumlation = 0;
    time = clock();
    result = FibDynamic(n,&accumlation);
    time = clock() - time;
    timetaken = ((double)time)/CLOCKS_PER_SEC;
    printf("FibDynamic(%d) = %ld, Addition Operations Performed: %ld\nTime taken: %f seconds\n",n,result,accumlation,timetaken);
}