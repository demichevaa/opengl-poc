#ifndef OPENGL_POC_COLLECTIONS_H
#define OPENGL_POC_COLLECTIONS_H

#include <stdio.h>
#include <stdlib.h>

struct LinkedListNode {
    void *value;
    struct LinkedListNode *next;
};

struct LinkedList {
    struct LinkedListNode *head;
    struct LinkedListNode *tail;
    struct LinkedListNode *currentIterator;
};

struct LinkedList* llInitialize();
void * llGetNext(struct LinkedList *p_ll);
int llAppend(struct LinkedList *p_ll, void *value);
int llFree(struct LinkedList *p_ll);


#endif //OPENGL_POC_COLLECTIONS_H
