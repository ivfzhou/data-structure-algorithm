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

#include "linked_queue.h"

int main(void) {
    LinkedQueue* queue = LinkedQueue_Alloc(sizeof(int));
    assert(queue);

    for (int i = 100; i > 0; i--) assert(!LinkedQueue_Into(queue, &i));
    assert(LinkedQueue_Len(queue) == 100);
    for (int i = 100; i > 0; i--) {
        int tmp;
        assert(!LinkedQueue_Exit(queue, &tmp));
        assert(tmp == i);
    }

    LinkedQueue_Free(queue);
}
