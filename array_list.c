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

#include <string.h>

#include "array_list.h"
#include "common.h"

// 扩容阈值。
static const int EXPAND_THRESHOLD = 256;

// 扩容系数。
static const long double EXPAND_FACTOR = 1.25L;

// 缩容系数。
static const long double REDUCE_FACTOR = 2L;

// 判断是否需要缩容。
static _Bool needReduce(const ArrayList* list) {
    return list->length > EXPAND_THRESHOLD && (list->length * REDUCE_FACTOR <= list->capacity);
}

// 判断是否需要扩容。
static _Bool needExpand(const ArrayList* list) { return list->length >= list->capacity; }

// 扩容并插入元素。
static int expandAndInsert(ArrayList* list, const size_t index, const void* elem) {
    if (list->capacity < EXPAND_THRESHOLD)
        list->capacity += list->capacity + 1;
    else
        list->capacity = (size_t)(list->capacity * EXPAND_FACTOR);

    void* newElems = malloc(list->elemSize * list->capacity);

    // 复制前段。
    if (index && list->elems != NULL) memcpy(newElems, list->elems, list->elemSize * index);

    // 复制后段。
    if ((list->length - index) && list->elems != NULL)
        memcpy(PointerAdd(newElems, (index + 1) * list->elemSize),
               PointerAdd(list->elems, index * list->elemSize),
               list->elemSize * (list->length - index));

    // 设置新元素。
    memcpy(PointerAdd(newElems, index * list->elemSize), elem, list->elemSize);

    free(list->elems);
    list->elems = newElems;
    list->length++;

    return 0;
}

// 缩容并弹出元素。
static int deallocAndPop(ArrayList* list, const size_t index, void* elem) {
    if (elem != NULL) memcpy(elem, PointerAdd(list->elems, index * list->elemSize), list->elemSize);

    void* newElems = malloc(list->elemSize * (size_t)(list->length * EXPAND_FACTOR));

    // 复制前段。
    if (index) memcpy(newElems, list->elems, list->elemSize * index);

    // 复制后段。
    if (list->length - index)
        memcpy(PointerAdd(newElems, (index + 1) * list->elemSize),
               PointerAdd(list->elems, index * list->elemSize),
               list->elemSize * (list->length - index));

    free(list->elems);
    list->elems = newElems;
    list->length--;
    return 0;
}

// 检查 elem 与 list 是否存在内存重叠。
static _Bool checkMemoryOverlap(const ArrayList* list, const void* elem) {
    const uintptr_t elemPtr = (uintptr_t)elem;
    const uintptr_t startPtr = (uintptr_t)list->elems;
    const size_t elemSize = list->capacity * list->elemSize;

    // 类型强转溢出，保守视为重叠。
    if (!CHECK_CAST_CHANGE(elemSize, size_t, uintptr_t)) return 1;

    // 加法溢出，保守视为重叠。
    if (CHECK_ADD_OVERFLOW(startPtr, (uintptr_t)elemSize)) return 1;

    const uintptr_t endPtr = startPtr + (uintptr_t)elemSize;
    return elemPtr >= startPtr && elemPtr < endPtr;
}

ArrayList* ArrayList_Alloc(const size_t elemSize) {
    if (elemSize <= 0) return NULL;
    ArrayList* list = malloc(sizeof(ArrayList));
    if (!list) return NULL;
    list->elemSize = elemSize;
    list->length = list->capacity = 0;
    list->elems = NULL;
    return list;
}

void ArrayList_Free(ArrayList* list) {
    if (!list) return;
    free(list->elems);
    list->length = list->capacity = 0;
    list->elemSize = 0;
    list->elems = NULL;
    free(list);
}

size_t ArrayList_Len(const ArrayList* list) { return list->length; }

int ArrayList_Get(const ArrayList* list, const size_t index, void* elem) {
    if (!list) return 1;
    if (!elem) return 2;
    if (index >= list->length) return 3;
    if (checkMemoryOverlap(list, elem)) return 4;
    memcpy(elem, PointerAdd(list->elems, index * list->elemSize), list->elemSize);
    return 0;
}

int ArrayList_Insert(ArrayList* list, const size_t index, const void* elem) {
    if (index > list->length) return 1;

    // 扩容。
    if (needExpand(list)) return expandAndInsert(list, index, elem);

    // 从index往后移动一位。
    if (list->length - index)
        memmove(PointerAdd(list->elems, (index + 1) * list->elemSize),
                PointerAdd(list->elems, index * list->elemSize),
                list->elemSize * (list->length - index));
    // 设置元素。
    memcpy(PointerAdd(list->elems, index * list->elemSize), elem, list->elemSize);

    list->length++;
    return 0;
}

int ArrayList_Del(ArrayList* list, const size_t index) {
    if (index >= list->length) return 1;

    // 缩容。
    if (needReduce(list)) return deallocAndPop(list, index, NULL);

    // 从index往前移动一位。
    if (list->length - index - 1)
        memmove(PointerAdd(list->elems, index * list->elemSize),
                PointerAdd(list->elems, (index + 1) * list->elemSize),
                (list->length - index - 1) * list->elemSize);

    list->length--;
    return 0;
}

int ArrayList_Locate(const ArrayList* list, ListElemComparer cmp, const void* elem, size_t* index) {
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(PointerAdd(list->elems, i * list->elemSize), elem)) {
            *index = i;
            return 0;
        }
    }
    return 1;
}

int ArrayList_Travel(const ArrayList* list, ListElemVisitor visit) {
    for (size_t i = 0; i < list->length; i++) visit(PointerAdd(list->elems, i * list->elemSize));

    return 0;
}

int ArrayList_Clear(ArrayList* list) {
    free(list->elems);
    list->elems = NULL;
    list->length = list->capacity = 0;
    return 0;
}

int ArrayList_RPop(ArrayList* list, void* elem) { return ArrayList_GetDel(list, list->length - 1, elem); }

int ArrayList_LPush(ArrayList* list, const void* elem) { return ArrayList_Insert(list, 0, elem); }

int ArrayList_RPush(ArrayList* list, const void* elem) { return ArrayList_Insert(list, list->length, elem); }

int ArrayList_LPop(ArrayList* list, void* elem) { return ArrayList_GetDel(list, 0, elem); }

int ArrayList_Set(ArrayList* list, const size_t index, const void* elem) {
    if (index >= list->length) return 1;
    memcpy(PointerAdd(list->elems, index * list->elemSize), elem, list->elemSize);
    return 0;
}

int ArrayList_GetDel(ArrayList* list, const size_t index, void* elem) {
    if (index >= list->length) return 1;

    // 缩容。
    if (needReduce(list)) return deallocAndPop(list, index, elem);

    // 设置元素。
    memcpy(elem, PointerAdd(list->elems, index * list->elemSize), list->elemSize);

    // 从 index 往前移动一位。
    if (list->length - 1 - index)
        memmove(PointerAdd(list->elems, index * list->elemSize),
                PointerAdd(list->elems, (list->length - 1) * list->elemSize),
                list->elemSize);

    list->length--;
    return 0;
}

int ArrayList_GetSet(ArrayList* list, const size_t index, void* elem) {
    if (index >= list->length) return 1;

    void* tmp = malloc(list->elemSize);
    memcpy(tmp, PointerAdd(list->elems, index * list->elemSize), list->elemSize); // 元素先放临时变量中。
    memcpy(PointerAdd(list->elems, index * list->elemSize), elem, list->elemSize); // 设置元素。
    memcpy(elem, tmp, list->elemSize);
    free(tmp);
    return 0;
}

int ArrayList_FPrint(const ArrayList* list, FILE* f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
        const size_t len = str(PointerAdd(list->elems, i * list->elemSize), s);
        s[len] = '\0';
        fprintf(f, "%s, ", s);
    }
    if (list->length) {
        const size_t len = str(PointerAdd(list->elems, (list->length - 1) * list->elemSize), s);
        s[len] = '\0';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}
