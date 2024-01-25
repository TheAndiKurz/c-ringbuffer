#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct {} Ringbuffer;

Ringbuffer *ringbuffer_create();
void ringbuffer_destroy(Ringbuffer*, void(*detroy_element)(void*));

void *ringbuffer_peek(Ringbuffer*);
void *ringbuffer_pull(Ringbuffer*);
void ringbuffer_push(void *);

bool ringbuffer_is_empty(Ringbuffer*);
size_t ringbuffer_count(Ringbuffer*);
