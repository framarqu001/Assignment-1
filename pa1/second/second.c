#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct node {
    int value;
    struct node* next;
};

struct node* allocate_node(int value){
    struct node* temp = malloc(sizeof(struct node));
    temp->value = value;
    temp->next = NULL;
    return temp;
}


void insert(struct node** head, int value, int *count){ 
    if(*count==0){ //Creating head node
        *head = allocate_node(value);
        (*count)++;
        return;
    }
    struct node* current = *head;
    while(current!=NULL){
        if (current->value == value) return; // Same value so return
        else if(current->value > value && current == *head){
            struct node* newNode = allocate_node(value);
            newNode->next = current;
            *head = newNode;
            (*count)++;
            return;
        }
        else if(current->next ==NULL){
            struct node* newNode = allocate_node(value);
            current->next = newNode;
            (*count)++;
            return;
        }else if (current->value < value && value < current->next->value){
            struct node* newNode = allocate_node(value);
            struct node* temp = current->next;
            current->next = newNode;
            newNode->next = temp;
            (*count)++;
            return;
        }
        
        current = current->next;
    }
    
}

void delete(struct node** head, int value, int *count){
    if (*count==0){
        return;
    }
    struct node* current = *head;
    if (current->value == value){
        if(*count==1){
            free(current);
            (*count)--;
            *head = NULL;
            return;
        }else{
            *head = current->next;
            free(current);
            (*count)--;
            return;
        }
    }
    struct node* previous = current;
    current = current->next;

    while(current!=NULL){
        if (current->value == value && current->next == NULL){ //deleting at tail
            free(current);
            previous->next = NULL;
            (*count)--;
            return;
        }else if(current->value == value){ //deleting in middle
            struct node* temp = current->next;
            previous->next = temp;
            free(current);
            (*count)--;
            return;
        }
        previous = current;
        current = current->next;
    }

}

void printList(struct node* current, int count){
    if (count ==0){
        printf("EMPTY");
        return;
    }

    if (count>0){
        printf("%d", current->value);
        current = current->next;
        while(current!=NULL){
            printf(" %d", current->value);
            current = current->next;
        }
    }

}

void freeList(struct node* current){
    while(current!=NULL){
        struct node* temp = current->next;
        free(current);
        current = temp;
    }
}



int main(int argc, char** argv){

    if(argc < 2){
    printf("enter the input arguments\n");
    exit(EXIT_SUCCESS);
    }
    
    FILE* fp = fopen(argv[1], "r"); // change back to input from command line

    if(fp == NULL){
        printf("unable to open input file \n");
        exit(EXIT_SUCCESS);
    }

    
    
    int count = 0;
    char command[7];
    int value;
    struct node* head =NULL;
    while(fscanf(fp,"%s %d", command, &value) != EOF){
        if (!strcmp(command,"INSERT")){ 
            insert(&head, value, &count);
        }else if(!strcmp(command,"DELETE")){
            delete(&head, value, &count);
        }
        printList(head, count);
        printf("\n");


        
    }

    fclose(fp);
    freeList(head);
    return EXIT_SUCCESS;
}