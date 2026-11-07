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

#include "stack.h"

int main(void) {
    Stack* s = Stack_Alloc(sizeof(int), 10);
    assert(s);
    assert(Stack_IsEmpty(s));
    int elem = 1;
    Stack_Push(s, &elem);
    elem = 2;
    Stack_Push(s, &elem);
    Stack_Pop(s, &elem);
    assert(elem == 2);
    assert(!Stack_PeekTop(s, &elem));
    assert(elem == 1);
    Stack_Pop(s, &elem);
    assert(elem == 1);
    assert(Stack_IsEmpty(s));
    Stack_Free(s);
}
