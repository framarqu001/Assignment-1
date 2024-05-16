#include<stdlib.h>
#include<stdio.h>
#include<string.h>


struct bNode{
    int value;
    struct bNode* left;
    struct bNode* right;
};

struct bNode* allocate_bNode(int value){
    struct bNode* temp = malloc(sizeof(struct bNode));
    temp->value = value;
    temp->right = NULL;
    temp->left = NULL;
    return temp;
}


void insert(struct bNode** root, int value, int *count){
   
    if (!(*root)){
        *root = allocate_bNode(value);
        (*root)->value = value;
        printf("inserted %d\n", *count);
        return;
    }

    struct bNode* current = *root;

    if (value < current->value){
        (*count)++;
        if (!current->left){ // base case. At left node
            current->left = allocate_bNode(value);
            printf("inserted %d\n", *count);
        }else{
            insert(&(current->left),value, count);
        }
    } else if (value > current->value) {
        (*count)++;
        if (!current->right){ //base case. At right node
            current->right = allocate_bNode(value);
            printf("inserted %d\n", *count);
        }else{
            insert(&(current->right),value, count);
        }
    }else{
        printf("duplicate\n");
    }


}

void search(struct bNode* current, int value, int *count){
    if (current == NULL){
        printf("absent\n");
    }else if (current->value == value){
        printf("present %d\n",*count);
    }else if (current->value > value){
        (*count)++;
        search(current->left, value, count);
    }else{
        (*count)++;
        search(current->right, value, count);
    }
}

void free_list(struct bNode* root){ //post order traversal to free
    if (root == NULL) return;

    free_list(root->left);
    free_list(root->right);
    free(root);
}

int main(int argc, char** argv){

    if (argc <2){
        printf("enter the input arguments\n");
        exit(EXIT_SUCCESS);
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp==NULL){
        printf("File could not be opened");
        return EXIT_SUCCESS;
    }

    char instruct;
    int num;
    struct bNode* root = NULL;
    int count =1;

    while(fscanf(fp,"%c %d", &instruct, &num) != EOF){
        if (instruct == 'i'){
            insert(&root, num, &count);
            count = 1;
        }
        if (instruct == 's'){
            search(root, num, &count);
            count = 1;
        }
    }

    free_list(root);
    fclose(fp);

}