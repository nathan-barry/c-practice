#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct RingBuffer {
    int* buffer;
    int capacity;
    int size;
    int start;
    int end; // exlusive
} RingBuffer;

RingBuffer* create_buffer(int capacity) {
    RingBuffer* rb = malloc(sizeof(RingBuffer));
    int* buffer = calloc(capacity, sizeof(int));

    rb->buffer = buffer;
    rb->capacity = capacity;
    rb->size = 0;
    rb->start = 0;
    rb->end = 0;

    return rb;
}

bool buffer_put(RingBuffer* rb, int val) {
    if (rb->capacity == rb->size) {
        return false;
    }

    *(rb->buffer + rb->end) = val;
    rb->end = (rb->end + 1) % rb->capacity;
    rb->size++;

    return true;
}

int buffer_get(RingBuffer* rb) {
    if (rb->size == 0) {
        return 0;
    }

    int val = *(rb->buffer + rb->start);
    rb->start = (rb->start + 1) % rb->capacity;
    rb->size--;

    return val;
}

void buffer_print(RingBuffer* rb) {
    printf("[ ");
    for (int i=0; i < rb->capacity; i++) {
        if (rb->start < rb->end) {
            if (i < rb->start || i >= rb->end) {
                printf(". ");
            } else {
                printf("%d ", *(rb->buffer + i));
            }
        } else {
            if (i < rb->start && i >= rb->end) {
                printf(". ");
            } else {
                printf("%d ", *(rb->buffer + i));
            }
        }
    }
    printf("]    size: %d, start: %d, end: %d\n", rb->size, rb->start, rb->end);
}

int main() {
    RingBuffer* rb = create_buffer(8);
    buffer_print(rb);

    for (int i=1; i<6; i++) {
        buffer_put(rb, i);
    }
    buffer_print(rb);

    buffer_get(rb);
    buffer_get(rb);
    buffer_print(rb);

    for (int i=1; i<6; i++) {
        buffer_put(rb, i);
    }
    buffer_print(rb);

    for (int i=0; i<8; i++) {
        buffer_get(rb);
    }
    buffer_print(rb);

    buffer_put(rb, 1);
    buffer_print(rb);
}



