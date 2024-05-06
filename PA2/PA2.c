#include "PA2.h"

//Implementing psuedocode algorithm , because we are using C, we have to pass an extra parameter of the array size so we can parse through the entire array.
Tree * knn(int * query, int * * points, int k, int arrsize) {
    //Create our tree that will store the various nodes
    Tree* h = malloc(sizeof(Tree));
    h->size = 0;
    h->root = NULL;
    //Create max distance variable that will store the max dist
    float maxDist = FLT_MIN;
    //Counter to keep track of max distance
    int count = 0;
    //creating our resultant where the data will be stored based on the defined struct
    Distance* result = calloc(1, sizeof(Distance));
    //The EuclidianDistance Portion of psuedocod, with z being equal to our indicies into the array to allow for parsing the entire array
    for(int z = 0; z < arrsize; z++) {
        //get temporary 12-d point array to do the math on, and set a sum variable equal to 0 to store the results.
        int * x = points[z];
        float sum = 0.0;
        for(int i = 0; i < 12; i++) {
            //Inner for loop of psuedocode, parsing through each point of the distance and finding the square of the query minus the known point, and squaring that result and then finally adding that to our sum.
            sum += pow((query[i] - x[i]),2);
        }
        //After we do this, we add the element into our result array of distance. We offset the index by 1 as required by the specification, and finally take the square root of the sum to get the final distance between the points.
        result->index = z+1;
        result->distance = sqrt(sum);
        //If one of first k elements, we add to tree
        if(count < k) {
            //Create node to store the distance
            Distance* node = malloc(sizeof(Distance));
            h->size += 1;
            node->left = NULL;
            node->right = NULL;
            node->index = result->index;
            node->height = 1;
            node->distance = result->distance;
            //Insert into tree
            h->root = avlInsert(h->root,node);
            count++;
            //Update maxdist
            if(node->distance > maxDist) {
                maxDist = node->distance;
            }
        }
        //If not one of first k nodes, only update tree if it finds a new max distance
        else if(result->distance < maxDist) {
            //If true, delete current maxDistance
            h->root = deletefromAVL((h->root),maxDist);
            //Create new node to store the new max distance
            Distance* node = malloc(sizeof(Distance));
            node->left = NULL;
            node->right = NULL;
            node->index = result->index;
            node->height = 1;
            node->distance = result->distance;
            //Add new node to tree
            h->root = avlInsert(h->root,node);
            //Update max distance by using max Dist function
            maxDist = getMaxDist(h->root);
        }
    }

    //Free original result since all relevant data (k elements) are now stored in the heap
    freeDist(result);
    printTree(h->root);
    return h;
}
//Function that will get the max distance off the AVL tree by doing DFS down the right side of the tree
float getMaxDist(Distance* root) {
    while(root->right != NULL) {
        root = root->right;
    }
    return root->distance;
}
//Delete function for AVL Tree
Distance* deletefromAVL(Distance* root, float distance) {
    //Perform regular deletion
    if(root == NULL )  {
        return root;
    }
    if(distance < root->distance) {
        root->left = deletefromAVL(root->left,distance);
    }
    else if(distance > root->distance) {
        root->right = deletefromAVL(root->right,distance);
    }//This case necessary for our uses since we have duplicates that we need to possibly check for
    else if(distance == root->distance && root->right != NULL) {
        root->right = deletefromAVL(root->right,distance);
    }
    else {
            //If node has one child or no children (will always be the case with max)
            if (root->left == NULL || root->right == NULL) {
                Distance *temp = root->left ? root->left : root->right;
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else {
                    *root = *temp;
                }
                free(temp);
            }
    }
    //Begin to fixup after deletion
    if(root == NULL) {
        return root;
    }
    //Update height after deletion
    root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);
    //Fixup tree structure by checking the various cases
    //Left left case, so rotate right
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    //left right case, have to perform both rotations
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    //right right case, rotate left
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    //right left case, have to perform both rotations
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
//Function to insert into tree
Distance* avlInsert(Distance* root, Distance* node){
    //Do regular BST insertion
    if(root == NULL) {
        return node;
    }
    if(node->distance < root->distance) {
        root->left = avlInsert(root->left,node);
    } //Put duplciates on right side of tree
    else if(node->distance >= root->distance) {
        root->right = avlInsert(root->right, node);
    }
    //Update height of current node
    root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);
    //Update AVL tree if various cases need fixing up
    //Left left case, so rotate right
    if(balance > 1 && node->distance < root->left->distance) {
        return rightRotate(root);
    }
    //right right case, rotate left
    if(balance < -1 && node->distance > root->right->distance) {
        return leftRotate(root);
    }
    //left right case, have to perform both rotations
    if(balance > 1 && node->distance > root->left->distance) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //right left case, have to perform both rotations
    if(balance < -1 && node->distance < root->right->distance) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
//Helper function for balance of given node
int getBalance(Distance* node) {
    if(node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}
//Rotation function that will actually fixup AVL tree by rotating the given tree/node right
Distance* rightRotate(Distance* node) {
    Distance* l = node->left;
    Distance* r = l->right;

    l->right = node;
    node->left = r;
    //Update heights after rotation
    node->height = getMax(getHeight(node->left),getHeight(node->right)) + 1;
    l->height = getMax(getHeight(l->left), getHeight(l->right)) + 1;

    return l;
}
Distance* leftRotate(Distance* node) {
    Distance* r = node->right;
    Distance* l = r->left;

    r->left = node;
    node->right = l;
    //Update heights after rotation
    node->height = getMax(getHeight(node->left),getHeight(node->right)) + 1;
    r->height = getMax(getHeight(r->left), getHeight(r->right)) + 1;

    return r;
}
//Helper function to compare x and y and return whichever is greater
int getMax(int x, int y) {
    if(x > y) {
        return x;
    }
    return y;
}
//helper function to return given node's height
int getHeight(Distance* node) {
    if(node == NULL) {
        return 0;
    }
    return node->height;
}

//Function to print tree by doing in-order traversal
void printTree(Distance* root) {
    if(root == NULL) {
        return;
    }
    printTree(root->left);
    printf("%d %f\n",root->index,root->distance);
    printTree(root->right);

}
//Function to free tree by doing traversal of each node
void freeTree(Distance* r) {
    if(r == NULL) {
        return;
    }
    freeTree(r->left);
    freeTree(r->right);
    free(r);
    r = NULL;
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