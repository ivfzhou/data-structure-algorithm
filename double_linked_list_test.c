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
#include <string.h>
#include <time.h>

#include "double_linked_list.h"

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

/*static size_t intToString(void *elem, char *s) {
    int x = *(int *) elem;
    char buf[12];
    int len = snprintf(buf, 12, "%d", x);
    strncpy(s, buf, len);
    return len;
}*/

int main(void) {
    DoubleLinkedList* list = DoubleLinkedList_Alloc(sizeof(int));
    assert(list);

    int elem = 2;
    size_t index = 0;
    assert(!DoubleLinkedList_Insert(list, index, &elem));
    // double_linked_list_fprint(list, stdout, intToString, 1); // [2]
    // puts("");

    elem = 1;
    assert(!DoubleLinkedList_LPush(list, &elem));
    // double_linked_list_fprint(list, stdout, intToString, 1); // [1, 2]
    // puts("");

    elem = 3;
    assert(!DoubleLinkedList_RPush(list, &elem));
    // double_linked_list_fprint(list, stdout, intToString, 1); // [1, 2, 3]
    // puts("");

    assert(!DoubleLinkedList_Travel(list, intVisitor));

    size_t length = DoubleLinkedList_Len(list);
    assert(length == 3);

    elem = 4;
    assert(!DoubleLinkedList_Set(list, index, &elem));
    // double_linked_list_fprint(list, stdout, intToString, 1); // [4, 2, 3]
    // puts("");

    assert(!DoubleLinkedList_Get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!DoubleLinkedList_Locate(list, intCompare, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!DoubleLinkedList_GetSet(list, index, &elem));
    assert(elem == 3);
    // double_linked_list_fprint(list, stdout, intToString, 1); // [4, 2, 4]
    // puts("");

    assert(!DoubleLinkedList_GetDel(list, index, &elem));
    assert(elem == 4);
    // double_linked_list_fprint(list, stdout, intToString, 1); // [4, 2]
    // puts("");

    assert(!DoubleLinkedList_LPop(list, &elem));
    assert(elem == 4);
    // double_linked_list_fprint(list, stdout, intToString, 1); // [2]
    // puts("");

    assert(!DoubleLinkedList_RPop(list, &elem));
    assert(elem == 2);
    // double_linked_list_fprint(list, stdout, intToString, 1); // []
    // puts("");

    srand(time(NULL) + 100);
    int res = 0;
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = DoubleLinkedList_Len(list);
        index = rand() % (length + 1u);
        assert(!DoubleLinkedList_Insert(list, index, &elem));
        assert(!DoubleLinkedList_Get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = DoubleLinkedList_Len(list);
        index = rand() % length;
        assert(!DoubleLinkedList_Del(list, index));
    }

    assert(!DoubleLinkedList_Clear(list));

    DoubleLinkedList_Free(list);
}
