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

static int intCompare(const void* o1, const void* o2) {
    const int n1 = *(int*)o1;
    const int n2 = *(int*)o2;
    return n1 == n2 ? 0 : n1 > n2 ? 1 : -1;
}

static void intVisitor(void* p) {
    static int prev = 0;
    const int i = *(int*)p;
    assert(i == prev);
    prev = i + 1;
}

static size_t intToString(void* elem, char* s, size_t size) {
    const int x = *(int*)elem;
    return sprintf(s, "%d", x);
}

static void testAllocAndFree(void) {
    ArrayList* list = ArrayList_Alloc(sizeof(int));
    assert(list != NULL);
    ArrayList_Free(list);

    list = ArrayList_Alloc(0);
    assert(list == NULL);
    ArrayList_Free(list);
}

static void testLen(void) {
    ArrayList* list = ArrayList_Alloc(sizeof(int));
    assert(ArrayList_Len(list) == 0);

    srand((unsigned)time(NULL) + 100);
    int count = rand() % 1000;
    for (int i = 0; i < count; i++) {
        ArrayList_RPush(list, &i);
    }
    assert(ArrayList_Len(list) == (size_t)count);

    ArrayList_Free(list);
}

static void testGet(void) {
    ArrayList* list = ArrayList_Alloc(sizeof(int));

    int x;
    int ret = ArrayList_Get(list, 0, &x);
    assert(ret == INDEX_OUT_OF_BOUND);

    srand((unsigned)time(NULL) + 100);
    int count = rand() % 1000;
    for (int i = 0; i < count; i++) {
        ArrayList_RPush(list, &i);
    }
    for (int i = 0; i < count; i++) {
        int y;
        ret = ArrayList_Get(list, i, &y);
        assert(ret == 0);
        assert(y == i);
    }

    ArrayList_Free(list);
}

static void testInsert(void) {
    ArrayList* list = ArrayList_Alloc(sizeof(int));

    srand((unsigned)time(NULL) + 100);
    int count = rand() % 1000;
    for (int i = 0; i < count; i++) {
        size_t index = rand() % (ArrayList_Len(list) + 1);
        int ret = ArrayList_Insert(list, index, &i);
        assert(ret == 0);
    }

    ArrayList_Free(list);
}

static void testDel(void) {
    ArrayList* list = ArrayList_Alloc(sizeof(int));

    int ret = ArrayList_Del(list, 0);
    assert(ret == INDEX_OUT_OF_BOUND);

    srand((unsigned)time(NULL) + 100);
    int count = rand() % 1000;
    for (int i = 0; i < count; i++) {
        ArrayList_RPush(list, &i);
    }
    for (int i = 0; i < count; i++) {
        size_t index = rand() % (ArrayList_Len(list) + 1);
        ArrayList_Del(list, index);
    }

    ArrayList_Free(list);
}

static void testLocate(void) {
    ArrayList* list = ArrayList_Alloc(sizeof(int));
    srand((unsigned)time(NULL) + 100);
    int count = rand() % 1000;
    for (int i = 0; i < count; i++) {
        ArrayList_RPush(list, &i);
    }

    int hit = rand() % count;
    size_t index;
    int ret = ArrayList_Locate(list, intCompare, &hit, &index);
    assert(ret == 0);
    assert(index == (size_t)hit);

    ArrayList_Free(list);
}

static void testTravel(void) {
    ArrayList* list = ArrayList_Alloc(sizeof(int));
    srand((unsigned)time(NULL) + 100);
    int count = rand() % 1000;
    for (int i = 0; i < count; i++) {
        ArrayList_RPush(list, &i);
    }
    int ret = ArrayList_Travel(list, intVisitor);
    assert(ret == 0);
    ArrayList_Free(list);
}

static void testClear(void) {
    ArrayList* list = ArrayList_Alloc(sizeof(int));
    srand((unsigned)time(NULL) + 100);
    int count = rand() % 1000;
    for (int i = 0; i < count; i++) {
        ArrayList_RPush(list, &i);
    }
    int ret = ArrayList_Clear(list);
    assert(ret == 0);
    ArrayList_Free(list);
}

static void testRPop(void) {
    ArrayList* list = ArrayList_Alloc(sizeof(int));
    srand((unsigned)time(NULL) + 100);
    int count = rand() % 1000;
    for (int i = 0; i < count; i++) {
        ArrayList_RPush(list, &i);
    }
    for (int i = count - 1; i > 0; i--) {
        int y;
        int ret = ArrayList_RPop(list, &y);
        assert(ret == 0);
        assert(y == i);
    }
    ArrayList_Free(list);
}

int main(void) {
    testAllocAndFree();
    testLen();
    testGet();
    testInsert();
    testDel();
    testLocate();
    testTravel();
    testClear();
    testRPop();
    /*ArrayList* list = ArrayList_Alloc(sizeof(int));
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

    ArrayList_Free(list);*/
}
