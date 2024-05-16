#include <stdio.h>
#include <stdlib.h>


void printArray(int** arr, int n){
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (j==n-1){
                printf("%d", arr[i][j]); 
            }else{
                printf("%d\t", arr[i][j]); 
            }
        }
        printf("\n");
    }
}

void freeArray(int** arr, int n){
    for(int i =0; i<n; i++){
        free(arr[i]);
    }
    free(arr);
}

void copyArray(int** arr,int** copyArr, int n){
        for(int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                arr[i][j] = copyArr[i][j];
             }
    }
    
}

void clearArray(int**arr, int n){
    for(int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                arr[i][j] = 0;
             }
    }
}

int** matrixSquareTest(int** arr,int n, int exponent){
    int** resultArr = malloc(n*sizeof(int*));
    int** tempResultArr = malloc(n*sizeof(int*));
    for (int i =0; i<n; i++){
            tempResultArr[i] = malloc(n*sizeof(int));
        }
    for (int i =0; i<n; i++){
            resultArr[i] = malloc(n*sizeof(int));
        }
    copyArray(resultArr,arr,n);

    for (int exp=2; exp<=exponent; exp++){
        clearArray(tempResultArr,n);
        for (int i =0; i<n; i++){
            for (int j=0; j<n; j++){
                for (int k =0; k<n; k++){
                    tempResultArr[i][j] += arr[i][k] * resultArr[k][j];
                }
            }
        }

        copyArray(resultArr,tempResultArr,n); 
    }
    freeArray(tempResultArr, n);
    return resultArr;

}




int main(int argc, char** argv){
    if (argc <2){
        printf("Enter the input arguments\n");
        exit(EXIT_SUCCESS);
    }
    
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("unable to open input file \n");
        exit(EXIT_SUCCESS);
    } 

    int n;
    fscanf(fp,"%d",&n);

    int** arr2d = malloc(n*sizeof(int*));
    for (int i =0; i<n; i++){
        arr2d[i] = malloc(n*sizeof(int));
    }
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++){
        int num;
        fscanf(fp, "%d", &arr2d[i][j]);
        }
    }

    int exponent;
    fscanf(fp, "%d", &exponent);

    
    int** result = matrixSquareTest(arr2d,n,exponent);
    printArray(result, n);

    freeArray(result, n);
    freeArray(arr2d, n);
    fclose(fp);
    

    return EXIT_SUCCESS;
}