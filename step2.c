#include <stdio.h>
#include <stdlib.h>

#define BLOCKSIZE 5

void *allocator(int size, int *counter)
{
    void *cur = malloc(size);
    if (cur)
        (*counter)++;
    return cur;
}
struct list
{
    struct node *head;
    struct node *tail;
    struct node *right;
    struct node *left;
    int length;
};
struct node
{
    int i;
    struct node *next;
    struct node *prev;
};
void deAllocator(void *p, int *counter)
{
    if (p)
        (*counter)--;
    free(p);
}

void allocateBlock(struct list *pList, int *counter)
{
    int j = 0;
    while (j<BLOCKSIZE) {
        struct node *temp = allocator(sizeof(*pList), counter);
        
        temp->prev = pList->left;
        temp->next = pList->left->next;
        pList->left->next->prev = temp;
        pList->left->next = temp;
        pList->length = pList->length+1;
        temp->i = -1;
        j = j+1;
    }
}
void deAllocateBlock(struct list *pList, int *counter)
{
    int i = 0;
    while (i < BLOCKSIZE)
    {
        struct node *temp = pList->left->next;
        pList->left->next->next->prev = pList->left;
        pList->left->next = pList->left->next->next;
        deAllocator(temp, counter);
        pList->length = pList->length - 1;
        i++;
    }
}
void printList(struct list *pList, int *counter)
{
    if (pList->head)
    {
        struct node *cur = pList->head;
        while (cur)
        {
            printf(" | %d | ", cur->i);
            cur = cur->next;
        }
        printf("\n");
    }
    printf("counter = %d\n", *counter);
}
void removeList(struct list *pList, int *counter)
{
    deAllocator(pList->head, counter);
    deAllocator(pList->tail, counter);
    pList->head = NULL;
    pList->tail = NULL;
    pList->length = 0;
    pList->left = NULL;
    pList->right = NULL;
}
void initialiseList(struct list *pList, int *counter)
{
    pList->head = allocator(sizeof(*pList), counter);
    pList->tail = allocator(sizeof(*pList), counter);
    pList->left = pList->head;
    pList->right = pList->tail;
    pList->tail->i =0;
    pList->head->i = 0;
    pList->head->next = pList->tail;
    pList->head->prev = NULL;
    pList->tail->next = pList->head;
    pList->tail->next = NULL;
    

    pList->length = 0;
}
int main() {
int counter = 0;
struct list myList;
printf("initialising the list ... \n");
initialiseList(&myList, &counter);
printList(&myList, &counter);
printf("allocating %d free nodes ... \n", BLOCKSIZE);
allocateBlock(&myList, &counter);
printList(&myList, &counter);
printf("freeing %d free nodes ... \n", BLOCKSIZE);
deAllocateBlock(&myList, &counter);
printList(&myList, &counter);
printf("freeing head and tail ... \n");
removeList(&myList, &counter);
printList(&myList, &counter);
} 
