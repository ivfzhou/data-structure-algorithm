/*
 * Copyright (c) 2023 ivfzhou
 * data-structure-algorithm is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */

#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "circle_queue.h"
#include "common.h"

CircleQueue* CircleQueueAlloc(const size_t elemSize, const size_t queueLength) {
    if (queueLength >= ULLONG_MAX) raise(SIGABRT);
    CircleQueue* queue = malloc(sizeof(CircleQueue));
    queue->elemSize = elemSize;
    queue->length = queueLength;
    queue->array = malloc(elemSize * queueLength);
    queue->head = queue->tail = 0;
    return queue;
}

int CircleQueueInto(CircleQueue* queue, const void* elem) {
    if (queue == NULL) return 2;
    if ((queue->head - queue->tail) >= queue->length) return 1;
    memcpy(PointerAdd(queue->array, (queue->head % queue->length) * queue->elemSize), elem, queue->elemSize);
    queue->head++;
    return 0;
}

int CircleQueueExit(CircleQueue* queue, void* elem) {
    if (queue == NULL) return 2;
    if (queue->tail == queue->head) return 1;
    memcpy(elem, PointerAdd(queue->array, (queue->tail % queue->length) * queue->elemSize), queue->elemSize);
    queue->tail++;
    return 0;
}

void CircleQueueFree(CircleQueue* queue) {
    free(queue->array);
    free(queue);
}

size_t CircleQueueLen(const CircleQueue* queue) {
    if (queue == NULL) return 0;
    return queue->head - queue->tail;
}
