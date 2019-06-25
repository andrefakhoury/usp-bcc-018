#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** storeImage (const char* file_name, int* height, int* width) { // function that reads and stores the pixels of the image in a matrix
    int** img;
    char* trash = malloc(10 * sizeof(char)); // pointer to the string that stores the useless lines of the file
    FILE* fil = fopen(file_name, "r"); 

    fscanf (fil, "%s", trash);
    free(trash);
    fscanf (fil, "%d", width);
    fscanf (fil, "%d", height);

    img = malloc (*height * sizeof(int*));
    for (int i = 0; i < *height; i++) {
        img[i] = malloc (*width * sizeof(int));
    }
    fscanf (fil, "%d", &img[0][0]);
    for (int i = 0; i < *height; i++) { // for that fills the matrix img
        for (int j = 0; j < *width; j++) {
            fscanf (fil, "%d", &img[i][j]);
        }
    }

    fclose(fil); 
    return img; 
}

void runSearch (int x, int y, int c, int seg_regnum, int height, int width, int** img, int** seg_img, float* avg, int* sum, int* rep) { // function that makes the image segmentation considering the query
    if (*rep == 0) { // conditional that adds the starting position x,y in a segmented region if (x,y) doesn't belong to any other region
        if (seg_img[x][y] == 0) { 
            seg_img[x][y] = seg_regnum; // addition of the pixel[x][y] to the segmented region seg_regnum
            (*rep)++;
            *sum = *sum + img[x][y];
            *avg = (float)img[x][y];
        } else { // if x,y already belongs to another segmented region, the search is stopped
            return;
        }
    } else {
        if (fabs(img[x][y] - (*avg)) <= c) { // conditional that verifies the difference between the value of the pixel (x,y) and the average value of the pixels that belongs to the segmented region and the criterion
            seg_img[x][y] = seg_regnum; // addition of the pixel[x][y] to the segmented region seg_regnum
            *sum = *sum + img[x][y];
            (*rep)++;
            *avg =  (float)(*sum) / ((float)(*rep));
        } else { // conditional tha stops the function and return the search to the previous pixel
            return;
        }
    }

    if (x - 1 >= 0) { // conditional that verifies if there is a neighbor above to be verified
        if (seg_img[x - 1][y] == 0) { // conditional that verifies if the the neighbor above belongs to another segmented region
            runSearch (x - 1, y, c, seg_regnum,height, width, img, seg_img, avg, sum, rep);
        }
    }
    if (y + 1 != width) { // conditional that verifies if there is a neighbor to the right to be verified
        if (seg_img[x][y + 1] == 0) { // conditional that verifies if the the neighbor to the right belongs to another segmented region
            runSearch (x, y + 1, c, seg_regnum,height, width, img, seg_img, avg, sum, rep);
        }
    }
    if (x + 1 != height) { // conditional that verifies if there is a non verified neighbor below
        if (seg_img[x + 1][y] == 0) { // conditional that verifies if the the neighbor below belongs to another segmented region
            runSearch (x + 1, y, c, seg_regnum,height, width, img, seg_img, avg, sum, rep);
        }
    }
    if (y - 1 >= 0) { // conditional that verifies if there is a non verified neighbor to the left
        if (seg_img[x][y - 1] == 0) { // conditional that verifies if the the neighbor to the left belongs to another segmented region
            runSearch (x, y - 1, c, seg_regnum,height, width, img, seg_img, avg, sum, rep);
        }
    } 
}

void verifyEdge (int x, int y, int** seg_img, int height, int width) { // function that verifies whether the pixel (x,y) belongs to the edge of the image and prints it if it's true
    int edge = 0; // variable which value is set to 1 if any of the 4 neighbors doesnt belong to the the same segmented region of the pixel (x,y)

    if (x - 1 >= 0) { // conditional that verifies if there is a neighbor above
        if (seg_img[x - 1][y] != seg_img[x][y]) { // conditional that verifies if the pixel (x,y) and its neighbor above belongs to the same segmented region 
            edge = 1;
        }
    }
    if (y + 1 != width) { // conditional that verifies the neighbor to the right
        if (seg_img[x][y + 1] != seg_img[x][y]) { // conditional that verifies if the pixel (x,y) and its neighbor to the right belongs to the same segmented region 
            edge = 1;
        }
    }
    if (x + 1 != height) { // conditional that verifies the neighbor below
        if (seg_img[x + 1][y] != seg_img[x][y]) { // conditional that verifies if the pixel (x,y) and its neighbor below belongs to the same segmented region 
            edge = 1;
        }
    }
    if (y - 1 >= 0) { // conditional that verifies if there is a neighbor to the left
        if (seg_img[x][y - 1] != seg_img[x][y]) { // conditional that verifies if the pixel (x,y) and its neighbor to the right belongs to the same segmented region 
            edge = 1;
        }
    }

    if (edge == 1) {
        printf("(%d, %d) \n", x, y);
    }
}

void freeMemory (int** img, int** seg_img, char* file_name, int height) {
    for (int i = 0; i < height; i++) {
        free(img[i]);
        free(seg_img[i]);
    }
    free (img);
    free (seg_img);
    free (file_name);
}

int main (void) {

    char* file_name = malloc(15 * sizeof(char));
    scanf("%[^\r\n]s", file_name);
    getc(stdin); // consumes the '\n' or '\r'

    int height, width; // variables for the image height and width
    int** img = storeImage(file_name, &height, &width); // pointer to the matrix that represents the image
    int** seg_img = malloc (height * sizeof(int*)); // pointer to the matrix that represents the segmented image
    for (int i = 0; i < height; i++) {
        seg_img[i] = calloc (width, (sizeof(int)));
    }   
  
    int k; // number of queries to the input image
    scanf("%d ", &k);

    int x, y, crit; // variables that stores the coordinates x,y of the position in which the user touched the image and the query criterion
    int rep, sum; // variable to control the repetition of times that a pixel is conquered and the sum of the pixels values that belongs to the same segmented region in runSearch ()
    float avg; // variable that stores the average value of the pixels that belongs to the same segmented region in runSearch ()

    for (int i = 0; i < k; i++) { // for to input the coordinates and criterion that initializes the search
        scanf("%d %d %d", &x, &y, &crit);
        avg = 0;
        sum = 0;
        rep = 0;
        runSearch (x, y, crit, i + 1, height, width, img, seg_img, &avg, &sum, &rep);
    }

    for (int i = 0; i < height; i++) { // for that prints the edges of the image
        for (int j = 0; j < width; j++) {
            verifyEdge(i, j, seg_img, height, width);
        }
    }

    freeMemory (img, seg_img, file_name, height); 

    return 0;
}