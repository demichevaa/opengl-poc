#include "collections.h"



struct LinkedList* llInitialize() {
        struct LinkedList *ll = malloc(sizeof(struct LinkedList));
        ll->head = NULL;
        ll->tail = NULL;
        ll->currentIterator = NULL;

        return ll;
}

void * llGetNext(struct LinkedList *p_ll) {
        if (p_ll == NULL) {
                return NULL;
        }

        if (p_ll->currentIterator == NULL) {
                p_ll->currentIterator = p_ll->head;
                return p_ll->currentIterator ? p_ll->currentIterator->value : NULL;
        }

        if (p_ll->currentIterator->next != NULL) {
                p_ll->currentIterator = p_ll->currentIterator->next;
                return  p_ll->currentIterator->value;
        }

        return NULL;
}

int llAppend(struct LinkedList *p_ll, void *value) {
        if (p_ll == NULL) {
                return EXIT_FAILURE;
        }

        struct LinkedListNode *n = malloc(sizeof(struct LinkedList));
        n->value = value;

        if (p_ll->head == NULL) {
                p_ll->head = n;
                p_ll->tail = n;
                return EXIT_SUCCESS;
        }

        p_ll->tail->next = n;
        p_ll->tail = n;

        return EXIT_SUCCESS;
}

int llFree(struct LinkedList *p_ll) {
        if (p_ll == NULL) {
                return EXIT_FAILURE;
        }

        struct LinkedListNode *current = p_ll->head;
        struct LinkedListNode *next;

        while (current != NULL) {
                next = current->next;
                free(current);
                current = next;
        }

        free(p_ll);
        return EXIT_SUCCESS;
}

//int main(void) {
//        struct LinkedList *ill = llInitialize();
//        unsigned int value1 = 1;
//        unsigned int value2 = 2;
//
//
//        llAppend(ill, (void *) &value1);
//        llAppend(ill, (void *) &value2);
//
//        unsigned int *p_value;
//        while ((p_value = llGetNext(ill)) != NULL) {
//                printf("%d\n", *(unsigned int*)p_value);
//        }
//
//        llFree(ill);
//        return 0;
//}
