#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct 
{
    size_t capacity;
    size_t count;
    size_t start_index;

    void** items;
} Ringbuffer;

Ringbuffer *ringbuffer_create();
void ringbuffer_destroy(Ringbuffer*, void(*detroy_element)(void*));

void *ringbuffer_peek(Ringbuffer*);
void *ringbuffer_pull(Ringbuffer*);
void ringbuffer_push(Ringbuffer*, void *);

bool ringbuffer_is_empty(Ringbuffer*);
size_t ringbuffer_count(Ringbuffer*);
