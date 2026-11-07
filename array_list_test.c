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

#include "array_list.h"

#define TEST_LENGTH 500000

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
    ArrayList* list = ArrayList_Alloc(sizeof(int));
    assert(list);

    int elem = 2;
    size_t index = 0;
    assert(!ArrayList_Insert(list, index, &elem));
    // arrayList_fprint(list, stdout, intToString, 1); // [2]
    // puts("");

    elem = 1;
    assert(!ArrayList_LPush(list, &elem));
    // arrayList_fprint(list, stdout, intToString, 1); // [1, 2]
    // puts("");

    elem = 3;
    assert(!ArrayList_RPush(list, &elem));
    // arrayList_fprint(list, stdout, intToString, 1); // [1, 2, 3]
    // puts("");

    assert(!ArrayList_Travel(list, intVisitor));

    size_t length = ArrayList_Len(list);
    assert(length == 3);

    elem = 4;
    assert(!ArrayList_Set(list, index, &elem));
    // arrayList_fprint(list, stdout, intToString, 1); // [4, 2, 3]
    // puts("");

    assert(!ArrayList_Get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!ArrayList_Locate(list, intCompare, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!ArrayList_GetSet(list, index, &elem));
    assert(elem == 3);
    // arrayList_fprint(list, stdout, intToString, 1); // [4, 2, 4]
    // puts("");

    assert(!ArrayList_GetDel(list, index, &elem));
    assert(elem == 4);
    // arrayList_fprint(list, stdout, intToString, 1); // [4, 2]
    // puts("");

    assert(!ArrayList_LPop(list, &elem));
    assert(elem == 4);
    // arrayList_fprint(list, stdout, intToString, 1); // [2]
    // puts("");

    assert(!ArrayList_RPop(list, &elem));
    assert(elem == 2);
    // arrayList_fprint(list, stdout, intToString, 1); // []
    // puts("");

    srand(time(NULL) + 100);
    int res = 0;
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = ArrayList_Len(list);
        index = rand() % (length + 1u);
        assert(!ArrayList_Insert(list, index, &elem));
        assert(!ArrayList_Get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = ArrayList_Len(list);
        index = rand() % length;
        assert(!ArrayList_Del(list, index));
    }

    assert(!ArrayList_Clear(list));

    ArrayList_Free(list);
}
