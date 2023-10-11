#include <stdio.h>
#include <stdlib.h>

#define BLOCKSIZE 5

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

void *allocator(int size, int *counter)
{
    void *cur = malloc(size);
    if (cur)
        (*counter)++;
    return cur;
}

void deAllocator(void *p, int *counter)
{
    if (p)
        (*counter)--;
    free(p);
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



void allocateBlock(struct list *pList, int *counter)
{
    int j = 0;
    while (j < BLOCKSIZE)
    {
        struct node *temp = allocator(sizeof(*pList), counter);

        temp->prev = pList->left;
        temp->next = pList->left->next;
        pList->left->next->prev = temp;
        pList->left->next = temp;
        pList->length = pList->length + 1;
        temp->i = -1;
        j = j+1;
        
    }
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
void pushInt(struct list *pList, int *counter, int i)
{
    if (pList->length == 0) {
        allocateBlock(pList, counter);
    }
    if (i % 2 == 0)
    {
        pList->right->prev->i = i;
        pList->right = pList->right->prev;
    }
    else
    {
        pList->left->next->i = i;
        pList->left = pList->left->next;
    }
    pList->length = pList->length -1;
}
void pullInt(struct list *pList, int *counter, int i)
{
    if (i % 2 == 0 && pList->right != pList->tail)
    {
        pList->right->i = -1;
        pList->right = pList->right->next;
        pList->length = pList->length +1;
    }
    else if (i % 2 == 1 && pList->left != pList->head){
    
        pList->left->i = -1;
        pList->left = pList->left->prev;
        pList->length = pList->length +1;
    }
    
    
    if (pList->length >= BLOCKSIZE)
    {
        deAllocateBlock(pList, counter);
    }
}
int main()

{
    int counter = 0;
    struct list myList;
    printf("initialising the list ... \n");
    initialiseList(&myList, &counter);
    printList(&myList, &counter);

    int N = 4;
    int i = 0;
    while (i < N)
    {
        pushInt(&myList, &counter, i * i);
        printList(&myList, &counter);
        i++;
    }
    while (i > 1)
    {
        pullInt(&myList, &counter, i * i + 1);
        printList(&myList, &counter);
        i--;
    }
    while (myList.length != 0)
    {
        pullInt(&myList, &counter, 1);
        pullInt(&myList, &counter, 2);
    }

    printList(&myList, &counter);
    printf("freeing head and tail ... \n");
    removeList(&myList, &counter);
    printList(&myList, &counter);
}
