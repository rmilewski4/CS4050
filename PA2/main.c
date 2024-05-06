#include "PA2.h"

int main(int argc, char *argv[]) {
    //creating query array that will be taken in from command line.
    int query[12];
    //Loop through for all 12 elements on the command line and add them to the query array by converting the string from the command line to an integer.
    for(int i = 0; i <12; i++) {
        query[i] = atoi(argv[i+2]);
    }
    int arrsize = 0;
    //Create our 2d array using specified function and filename taken off the command line.
    int** points = create2DArr(argv[1], &arrsize);
    //Fill array with data from the file
    loadPoints(argv[1],points,arrsize);
    Tree* result = NULL;
    clock_t time;
    double timeTaken = 0;
    double timeAvg = 0;
    //Get our resulting distance array of the top k elements by calling our knn function with the query array, 2-d points array, the specified k, and the array size.
    result = knn(query,points,25,arrsize);
    //Free our given arrays to avoid memory leaks.
    freeArr(points,arrsize);
    freeTree(result->root);
    free(result);
}