#include<stdio.h>
#include<stdlib.h>

char* productOf(int target, int nProducts, int* arr, int arrSize){
    for (int i =0; i<arrSize; i++){
        for (int j = i+1; j<arrSize;j++){
            int num1 = arr[i];
            int num2 = arr[j];
            if (nProducts == 2 && num1*num2 == target) return "yes";
            if (nProducts !=2) {
                    for(int k = j+1; k<arrSize; k++){
                        int num3 = arr[k];
                        if (num1*num2*num3 ==target) return "yes";
                    }
            }
        }
    }
    return "no";
}


int main(int argc, char** argv){
    if (argc !=2){
        printf("Enter the input arguments\n");
        exit(EXIT_SUCCESS);
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("unable to open input file \n");
        exit(EXIT_SUCCESS);
    } 

    int arrSize;
    fscanf(fp, "%d\n", &arrSize);
    int* inputArr = malloc(arrSize* sizeof(int));
    for(int i=0; i<arrSize; i++){
        fscanf(fp, "%d\n", &inputArr[i]);
    }


    int nQuerry;
    fscanf(fp, "%d\n", &nQuerry);

    for(int i =0; i<nQuerry; i++){
        int target, nProducts;
        fscanf(fp,"%d %d", &target, &nProducts);
        printf("%s\n", productOf(target,nProducts, inputArr, arrSize));
    }

    free(inputArr);
    fclose(fp);


    return EXIT_SUCCESS;
}