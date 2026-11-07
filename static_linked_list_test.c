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

#include "static_linked_list.h"

#define TEST_LENGTH 50000

static int intCompare(const void* o1, const void* o2) {
    int* n1 = (int*)o1;
    int* n2 = (int*)o2;
    if (*n1 == *n2) return 0;
    return o1 > o2 ? 1 : -1;
}

static void intVisitor(void* p) {
    static int prev = 1;
    int i = *(int*)p;
    assert(i == prev);
    prev = i + 1;
}

int main(void) {
    StaticLinkedList* list = StaticLinkedList_Alloc(sizeof(int));
    assert(list);

    int elem = 2;
    size_t index = 0;
    assert(!StaticLinkedList_Insert(list, index, &elem));

    elem = 1;
    assert(!StaticLinkedList_LPush(list, &elem));

    elem = 3;
    assert(!StaticLinkedList_RPush(list, &elem));

    assert(!StaticLinkedList_Travel(list, intVisitor));

    size_t length = StaticLinkedList_Len(list);
    assert(length == 3);

    elem = 4;
    assert(!StaticLinkedList_Set(list, index, &elem));

    assert(!StaticLinkedList_Get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!StaticLinkedList_Locate(list, intCompare, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!StaticLinkedList_GetSet(list, index, &elem));
    assert(elem == 3);

    assert(!StaticLinkedList_GetDel(list, index, &elem));
    assert(elem == 4);

    assert(!StaticLinkedList_LPop(list, &elem));
    assert(elem == 4);

    assert(!StaticLinkedList_RPop(list, &elem));
    assert(elem == 2);

    int res = 0;
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = StaticLinkedList_Len(list);
        index = rand() % (length + 1u);
        assert(!StaticLinkedList_Insert(list, index, &elem));
        assert(!StaticLinkedList_Get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = StaticLinkedList_Len(list);
        index = rand() % length;
        assert(!StaticLinkedList_Del(list, index));
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = StaticLinkedList_Len(list);
        index = rand() % (length + 1u);
        assert(!StaticLinkedList_Insert(list, index, &elem));
        assert(!StaticLinkedList_Get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = StaticLinkedList_Len(list);
        index = rand() % length;
        assert(!StaticLinkedList_GetDel(list, index, &elem));
    }

    StaticLinkedList_Clear(list);
    StaticLinkedList_Free(list);
}
