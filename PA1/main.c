#include "PA1.h"

int main(int argc, char *argv[]) {
    int query[12];
    for(int i = 0; i <12; i++) {
        query[i] = atoi(argv[i+2]);
    }
    int arrsize = 0;
    int** points = create2DArr(argv[1], &arrsize);
    loadPoints(argv[1],points,arrsize);
    double sum = 0;
    Distance* result = NULL;
    result = knn(query,points,25,arrsize);
    for(int count = 0; count < 25; count++) {
        printf("%d %f\n",result[count].index,result[count].distance);
    }
    freeArr(points,arrsize);
    freeDist(result);
}