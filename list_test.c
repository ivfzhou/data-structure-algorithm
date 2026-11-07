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
#include <time.h>

#include "list.h"

#define TEST_LENGTH 40000

static void intVisitor(void* p) {
    int i = *(int*)p;
    assert(i > 0);
}

static int intCompare(const void* o1, const void* o2) {
    int* n1 = (int*)o1;
    int* n2 = (int*)o2;
    if (*n1 == *n2) return 0;
    return o1 > o2 ? 1 : -1;
}

static void testListImpl(ListImplType type) {
    List* list = List_Alloc(sizeof(int), type);
    assert(list);

    int elem = 2;
    size_t index = 0;
    assert(!List_Insert(list, index, &elem));

    elem = 1;
    assert(!List_LPush(list, &elem));

    elem = 3;
    assert(!List_RPush(list, &elem));

    assert(!List_Travel(list, intVisitor));

    size_t length = List_Len(list);
    assert(length == 3);

    elem = 4;
    assert(!List_Set(list, index, &elem));

    assert(!List_Get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!List_Locate(list, intCompare, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!List_GetSet(list, index, &elem));
    assert(elem == 3);

    assert(!List_GetDel(list, index, &elem));
    assert(elem == 4);

    assert(!List_LPop(list, &elem));
    assert(elem == 4);

    assert(!List_RPop(list, &elem));
    assert(elem == 2);

    int res = 0;
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = List_Len(list);
        index = rand() % (length + 1u);
        assert(!List_Insert(list, index, &elem));
        assert(!List_Get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = List_Len(list);
        index = rand() % length;
        assert(!List_Del(list, index));
    }

    List_Clear(list);
    List_Free(list);
}

int main(void) {
    time_t now = time(NULL);

    srand(now + 100);
    // time_t begin = time(NULL);
    testListImpl(ARRAY);
    // printf("array list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    testListImpl(DOUBLE_LINKED);
    // printf("double linked list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    testListImpl(CIRCLE_LINKED);
    // printf("circle linked list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    testListImpl(LINKED);
    // printf("linked list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    testListImpl(STATIC_LINKED);
    // printf("static linked list cost %fs\n", difftime(time(NULL), begin));
}
