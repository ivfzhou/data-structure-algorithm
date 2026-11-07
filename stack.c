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

#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

extern void* PointerAdd(void* p, size_t delta);

extern void* PointerMinus(void* p, size_t delta);

extern unsigned long long PointerDiff(void* p1, void* p2);

void Stack_Push(Stack* s, const void* elem) {
    if (Stack_IsFull(s)) raise(SIGABRT);
    memcpy(s->top, elem, s->sizeOfElem);
    s->top = PointerAdd(s->top, s->sizeOfElem);
}

void Stack_Pop(Stack* s, void* elem) {
    if (Stack_IsEmpty(s)) raise(SIGABRT);
    memcpy(elem, PointerMinus(s->top, s->sizeOfElem), s->sizeOfElem);
    s->top = PointerMinus(s->top, s->sizeOfElem);
}

_Bool Stack_IsEmpty(const Stack* s) { return s->bottom == s->top; }

Stack* Stack_Alloc(size_t size_of_elem, size_t max_length) {
    Stack* s = malloc(sizeof(Stack));
    s->sizeOfElem = size_of_elem;
    s->length = max_length;
    s->bottom = s->top = malloc(max_length * size_of_elem);
    return s;
}

void Stack_Free(Stack* s) {
    free(s->bottom);
    free(s);
}

int Stack_PeekTop(const Stack* s, void* elem) {
    if (Stack_IsEmpty(s)) return 1;
    memcpy(elem, PointerMinus(s->top, s->sizeOfElem), s->sizeOfElem);
    return 0;
}

_Bool Stack_IsFull(const Stack* s) { return PointerDiff(s->top, s->bottom) >= s->length; }
