#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* str;
    unsigned priority; // 0 is highest
    struct Node* next;
} Node;

typedef struct Heap {
    Node* head;
} Heap;

Node* create_node(char* str, unsigned priority) {
    Node* node = malloc(sizeof(Node));
    node->str = str;
    node->priority = priority;
    node->next = NULL;
    return node;
}

Heap* create_heap() {
    Heap* h = malloc(sizeof(Heap));
    Node* dummy_head = create_node("", 0);
    h->head = dummy_head;
    return h;
}

void free_heap(Heap* h) {
    Node* prev = h->head;
    Node* cur = h->head->next;

    while (cur) {
        free(prev);
        prev = cur;
        cur = cur->next;
    }
    free(cur);
    free(h);
}

void heap_append(Heap* h, char* str, unsigned priority) {
    Node* node = create_node(str, priority);

    Node* prev = h->head;
    Node* cur = h->head->next;

    while (cur) {
        if (priority < cur->priority) {
            prev->next = node;
            node->next = cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }

    prev->next = node;
}

char* heap_pop(Heap* h) {
    if (!h->head->next) {
        return NULL;
    }
    Node* node = h->head->next;
    h->head->next = h->head->next->next;

    char* ret = node->str;

    return node->str;
}

void heap_print(Heap* h) {
    Node* cur = h->head->next;

    if (!cur) {
        printf("[ ]\n");
        return;
    }

    printf("[ ");
    do {
        printf("(%s, %d) ", cur->str, cur->priority);
        cur = cur->next;
    }
    while (cur);
    printf("]\n");
}

int main() {
    Heap* h = create_heap();

    heap_print(h);

    heap_append(h, "A", 1);
    heap_append(h, "B", 2);
    heap_append(h, "C", 3);

    heap_print(h);

    heap_append(h, "BB", 2);
    heap_append(h, "AA", 1);
    heap_append(h, "Z", 0);

    heap_print(h);

    heap_pop(h);
    heap_pop(h);
    heap_pop(h);

    heap_print(h);

    free_heap(h);
}
