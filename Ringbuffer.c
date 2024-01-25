#include "Ringbuffer.p.h"
#include <stdlib.h>

Ringbuffer *ringbuffer_create()
{
    Ringbuffer *ringbuffer = malloc(sizeof(Ringbuffer));

    ringbuffer->capacity = 5;
    ringbuffer->start_index = 0;
    ringbuffer->count = 0;
    ringbuffer->items = malloc(sizeof(void *) * ringbuffer->capacity);

    return ringbuffer;
}

void ringbuffer_destroy(Ringbuffer *self, void (*destroy_element)(void *))
{
    for (size_t i = 0; i < self->count; i++)
    {
        size_t ring_index = (self->start_index + i) % self->capacity;
        void *item = self->items[ring_index];
        free(item);
    }

    free(self->items);
    free(self);
}

void *ringbuffer_peek(Ringbuffer *self)
{
    return self->items[self->start_index];
}

void ringbuffer_maybe_move(Ringbuffer *self)
{
    size_t new_capacity;
    if (self->count * 4 < self->capacity)
    {
        new_capacity = self->capacity / 2;
        if (new_capacity < 5)
        {
            return;
        }
    }
    else if (self->count == self->capacity)
    {
        new_capacity = self->capacity * 2;
    }
    else
    {
        return;
    }

    void **new_array = malloc(new_capacity * sizeof(void *));

    for (size_t i = 0; i < self->count; i++)
    {
        size_t ring_index = (self->start_index + i) % self->capacity;
        void *item = self->items[ring_index];
        new_array[i] = item;
    }

    free(self->items);
    self->items = new_array;
    self->start_index = 0;
    self->capacity = new_capacity;
}

void *ringbuffer_pull(Ringbuffer *self)
{
    void *item = ringbuffer_peek(self);

    self->count--;
    self->start_index++;
    self->start_index %= self->capacity;

    ringbuffer_maybe_move(self);

    return item;
}

void ringbuffer_push(Ringbuffer *self, void *new_item)
{
    ringbuffer_maybe_move(self);

    size_t insert_index = (self->start_index + self->count) % self->capacity;

    self->items[insert_index] = new_item;
}

size_t ringbuffer_count(Ringbuffer *self)
{
    return self->count;
}

bool ringbuffer_is_empty(Ringbuffer *self)
{
    return self->count == 0;
}
