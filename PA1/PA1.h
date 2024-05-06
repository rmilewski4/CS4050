#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
//Distance struct that will be used by the knn function, storing the original index and distance.
typedef struct _Dist {
    int index;
    float distance;
} Distance;
int cmp(const void *a, const void *b);
Distance  * knn(int *, int * *, int, int);
void loadPoints(char * filename, int** points, int arrsize);
int * * create2DArr(char * filename, int* size);
void freeArr(int * * points, int arrsize);
void freeDist(Distance * d);