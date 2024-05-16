#include <stdio.h>
#include <stdlib.h>



int** create2dArray(int n){
    int** arr2d = malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        arr2d[i] = malloc(n*sizeof(int));
    }
    return arr2d;
}

void freeArray(int** arr, int n){
    for(int i =0; i<n; i++){
        free(arr[i]);
    }
    free(arr);
}


int** determinentArray(int** arr, int n, int col){
    int** temp = create2dArray(n-1);
    int rowdiff = 1;
    int coldiff =0;
    for(int i =1; i<n; i++) { // First row is never used. Offset row by 1.
        for(int j = 0; j<n; j++){
            if (j == col ) {
              coldiff = 1; // Skipp this columb. Offset column by 1.
               continue; 
            } 
                temp[i-rowdiff][j-coldiff] = arr[i][j];
            }
        coldiff = 0;
        
    }
    return temp;

}

int determinent(int** arr, int n){
    if (n == 1){
        return arr[0][0];
    }
    if (n == 2){
        return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
    }

    int total =0;
    for(int col = 0; col < n; col++) {
        int i=0;
        if (col % 2 == 0) i=1;
        else i= -1;
        int** newArr = determinentArray(arr,n,col);
        total = total + i*(arr[0][col]* determinent(newArr, n-1));
        freeArray(newArr,n-1);
    }
    return total;
}

int main(int argc, char** argv){
    if (argc<2){
        printf("Please enter file input");
        exit(EXIT_SUCCESS);
    }

    FILE* fp = fopen(argv[1], "r");

    if (fp ==NULL){
        printf("File failed to open");
        exit(EXIT_SUCCESS);
    }

    // n size of 2d array
    int n;
    fscanf(fp,"%d",&n);
    int** arr2d = create2dArray(n);

    // copying file data into 2darray
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++){
        fscanf(fp, "%d", &arr2d[i][j]);
        }
    }

    printf("%d",determinent(arr2d,n));

    freeArray(arr2d,n);
    fclose(fp);

}

