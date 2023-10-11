#include <stdio.h>
#include <stdlib.h>

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
int main()
{
    int counter = 0;
    struct list myList;
    printf("allocating two nodes ... \n");
    myList.head = malloc(sizeof(struct node));
    counter++;
    myList.tail = malloc(sizeof(struct node));
    counter++;
    printf("initialising the list ... \n");
    myList.left = myList.head;
    myList.right = myList.tail;
    myList.tail->i = 0;
    myList.head->i = 0;
    myList.head->next = myList.tail;
    myList.head->prev = NULL;
    myList.tail->prev = myList.head;
    myList.tail->next = NULL;
    myList.length = 0;
    printf(" | %d | | %d | \n", myList.head->i, myList.tail->i);
    printf("counter = %d\n", counter);
    printf("freeing the list ... \n");
    free(myList.head);
    counter--;
    free(myList.tail);
    counter--;
    printf("counter = %d\n", counter);
}

