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

#include <assert.h>
#include <stdio.h>

#include "circle_queue.h"

int main(void) {
    CircleQueue* queue = CircleQueueAlloc(sizeof(int), 10);
    int elem;
    for (int i = 0; i < 10; i++) {
        elem = i + 1;
        assert(!CircleQueueInto(queue, &elem));
        assert(CircleQueueLen(queue) == i + 1);
    }
    assert(CircleQueueInto(queue, &elem) == 1);

    for (int i = 0; i < 10; i++) {
        assert(!CircleQueueExit(queue, &elem));
        assert(elem == 1 + i);
        assert(CircleQueueLen(queue) == 9 - i);
    }
    assert(CircleQueueExit(queue, &elem) == 1);
    CircleQueueFree(queue);
}
