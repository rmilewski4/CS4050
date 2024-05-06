#include "PA1.h"
//Compare function for quicksort, comparing the distances between two structs
int cmp(const void *a, const void *b) {
    //Getting the arguments in the form of distance structs to access the members.
    Distance* arg1 = (Distance *)a;
    Distance* arg2 = (Distance *)b;
    //We know that if the first distance is less than the second, then their subtraction result will be less than 0, so we return a negative to indicate this
    if(arg1->distance -arg2->distance < 0) {
        return -1;
    }
    //On the other hand, we return a positive value to indicate that the first argument is greater than the second.
    if (arg1->distance-arg2->distance > 0) {
        return 1;
    }
    //If neither of those are true, then they must be equal so we return 0.
    return 0;
}
//Implementing psuedocode algorithm , because we are using C, we have to pass an extra parameter of the array size so we can parse through the entire array.
Distance  * knn(int * query, int * * points, int k, int arrsize) {
    //creating our resultant array where the data will be stored/sorted based on the defined struct.
    Distance* result = calloc(arrsize, sizeof(Distance));
    //First line of psuedocode, with z being equal to our indicies into the array to allow for parsing the entire array
    for(int z = 0; z < arrsize; z++) {
        //get temporary 12-d point array to do the math on, and set a sum variable equal to 0 to store the results.
        int * x = points[z];
        float sum = 0.0;
        for(int i = 0; i < 12; i++) {
            //Inner for loop of psuedocode, parsing through each point of the distance and finding the square of the query minus the known point, and squaring that result and then finally adding that to our sum.
            sum += pow((query[i] - x[i]),2);
        }
        //After we do this, we add the element into our result array of distance. We offset the index by 1 as required by the specification, and finally take the square root of the sum to get the final distance between the points.
        result[z].index = z+1;
        result[z].distance = sqrt(sum);
    }
    //Sort the array using the given stdlib qsort function and created compare function.
    qsort(result,arrsize,sizeof(Distance),cmp);
    //Get top k elements by creating an array of that size and then copying the memory of the first k elments into the new array.
    Distance* final = calloc(k,sizeof(Distance));
    memcpy(final,result,k*sizeof(Distance));
    //Free original result array since all relevant data (k elements) are now stored in final
    freeDist(result);
    return final;
}
//Create the 2D array to store the database of points by taking in the filename, size is a return variable that will be modified to say what the size of the array will be.
int * * create2DArr(char * filename, int* size) {
    int arrsize = 0;
    //Use strcmp on the filename to see which dataset is being used to determine how big the array size is.
    //The array size will be set accordingly if any of the known filenames are used, otherwise the arraysize will default to NULL and printout that an error was found.
    if(strcmp(filename, "1k.csv") == 0) {
        arrsize = 1000;
    }
    else if(strcmp(filename, "2k.csv") == 0) {
        arrsize = 2000;
    }
    else if(strcmp(filename, "3k.csv") == 0) {
        arrsize = 3000;
    }
    else if(strcmp(filename, "4k.csv") == 0) {
        arrsize = 4000;
    }
    else if(strcmp(filename, "5k.csv") == 0) {
        arrsize = 5000;
    }
    else if(strcmp(filename, "6k.csv") == 0) {
        arrsize = 6000;
    }
    else if(strcmp(filename, "7k.csv") == 0) {
        arrsize = 7000;
    }
    else if(strcmp(filename, "8k.csv") == 0) {
        arrsize = 8000;
    }
    else if(strcmp(filename, "9k.csv") == 0) {
        arrsize = 9000;
    }
    else if(strcmp(filename, "10k.csv") == 0) {
        arrsize = 10000;
    }
    else {
        printf("Incorrect file type!\n");
    }
    int** points = NULL;
    //Calloc our 2-D points array with the discovered array size
    points = calloc(arrsize,sizeof(int *));
    //Then for each of the 1-d elements, we need to calloc an array of size 12 because we will have 12 query points.
    for(int x = 0; x < arrsize; x++) {
        points[x] = calloc(12, sizeof(int));
    }
    //Finally set our size equal to array size to pass back the array size to the user and return our newly allocated 2d array.
    *size = arrsize;
    return points;
}
//Load in the points from the file by taking in the filename, array size, and created 2-d array from above function.
void loadPoints(char * filename, int** points, int arrsize) {
    //File pointer that will be used to parse through the file.
    FILE * fp = NULL;
    //open file pointer on specified file, set to read mode.
    fp = fopen(filename, "r");
    //If the file pointer returns NULL, it was unable to open the specified file, so it will let the user know that it recieved a bad filename.
    if (fp == NULL) {
        printf("Bad filename!\n");
    }
    //For the entire file:
    for(int i = 0; i < arrsize; i++) {
        //Parse through using fscanf and set the points of the 2-d array accordingly
        fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&points[i][0],&points[i][1],&points[i][2],&points[i][3],&points[i][4],&points[i][5],&points[i][6]
        ,&points[i][7],&points[i][8],&points[i][9],&points[i][10],&points[i][11]);
    }
    //Close the file pointer when we are done with it.
    fclose(fp);
}
//Function to free our created 2-d array
void freeArr(int * * points, int arrsize) {
    //Looping through entire array to free individual 1-d arrays.
    for(int x = 0; x < arrsize; x++) {
        free(points[x]);
        points[x] = NULL;
    }
    //Finally looping the allocated 2-d array itself.
    free(points);
    points = NULL;
}
//Function to free a distance array that was created by the user.
void freeDist(Distance * d) {
    free(d);
    d = NULL;
}