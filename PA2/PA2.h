#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <float.h>
//Distance struct that will be used by the knn function, storing the original index and distance.
typedef struct _Dist {
    int index;
    float distance;
    struct _Dist* left;
    struct _Dist* right;
    int height;
} Distance;
typedef struct _Tree {
    int size;
    Distance* root;   
} Tree;
void printTree(Distance* root);
void freeTree(Distance* root);
Tree* knn(int *, int * *, int, int);
void loadPoints(char * filename, int** points, int arrsize);
int * * create2DArr(char * filename, int* size);
void freeArr(int * * points, int arrsize);
void freeDist(Distance * d);

Distance* avlInsert(Distance* root, Distance* node);
int getBalance(Distance* node);
Distance* rightRotate(Distance* node);
Distance* leftRotate(Distance* node);
int getMax(int x, int y);
int getHeight(Distance* node);
Distance* deletefromAVL(Distance* rootk, float distance);
float getMaxDist(Distance* root);