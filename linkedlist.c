#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int val;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

Node* create_node(int val) {
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

LinkedList* create_list() {
    LinkedList* ll = malloc(sizeof(LinkedList));
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

void free_list(LinkedList* ll) {
    if (ll->head == NULL && ll->tail == NULL) {
        free(ll);
    } else if (ll->head == ll->tail) {
        free(ll->head);
        free(ll);
    } else if (ll->head && ll->tail) {
        Node* prev = ll->head;
        Node* cur = prev->next; 
        while (cur) {
            free(prev);
            prev = cur;
            cur = cur->next;
        }
        free(cur);
        free(ll);
    }
}

void list_append(LinkedList* ll, int val) {
    Node* node = create_node(val);

    if (ll->head == NULL && ll->tail == NULL) {
        ll->head = node;
        ll->tail = node;
    } else if (ll->head && ll->tail) {
        node->prev = ll->tail;
        ll->tail->next = node;
        ll->tail = node;
    } else {
        fprintf(stderr, "Error, appending had invalid state");
        exit(1);
    }
    ll->size++;
}

Node* list_pop(LinkedList* ll) {
    if (ll->head == NULL && ll->tail == NULL) {
        return NULL;
    } else if (ll->head == ll->tail && ll->size == 1) {
        // Only one node
        Node* node = ll->tail;
        ll->head = NULL;
        ll->tail = NULL;
        return node;
    } else if (ll->head && ll->tail) {
        Node* node = ll->tail;
        ll->tail->prev->next = NULL;
        ll->tail = ll->tail->prev;
        return node;
    } else {
        fprintf(stderr, "Error, pop had invalid state");
        exit(1);
    }
    ll->size--;
}

void list_print(LinkedList* ll) {
    if (ll->head == NULL && ll->tail == NULL) {
        printf("[]\n");
    } else if (ll->head == ll->tail) {
        printf("[ %d ]\n", ll->head->val);
    } else if (ll->head && ll->tail) {
        Node* cur = ll->head;
        printf("[ ");
        while (cur) {
            printf("%d ", cur->val);
            cur = cur->next;
        }
        printf("]\n");
    } else {
        fprintf(stderr, "Error, print had invalid state");
        exit(1);
    }
}

int main() {
    LinkedList* ll = create_list();
    list_print(ll);

    for (int i=1; i<6; i++) {
        list_append(ll, i);
    }
    list_print(ll);

    list_pop(ll);
    list_pop(ll);
    list_print(ll);

    free_list(ll);
}

