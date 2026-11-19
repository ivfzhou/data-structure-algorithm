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

// 判断是否需要缩容。
static _Bool needReduce(const ArrayList* list) {
    return list->length > ARRAY_LIST_EXPAND_THRESHOLD && list->length * ARRAY_LIST_REDUCE_FACTOR <= list->capacity;
}

// 判断是否需要扩容。
static _Bool needExpand(const ArrayList* list) { return list->length >= list->capacity; }

// 扩容并插入元素。
static int expandAndInsert(ArrayList* list, const size_t index, const void* elem) {
    // 计算出线性表容量。
    if (list->capacity < ARRAY_LIST_EXPAND_THRESHOLD) {
        list->capacity++;
    } else {
        const size_t newCapacity = (size_t)((long double)list->capacity * array_list_expand_factor);
        if (list->capacity > newCapacity)
            list->capacity++;
        else
            list->capacity = newCapacity;
    }

    // 分配新的内存。
    void* newElems = malloc(list->elemSize * list->capacity);
    if (!newElems) return MEMORY_ALLOCATE_FAILED;

    // 复制表前段元素。
    if (index && list->elems != NULL) memcpy(newElems, list->elems, list->elemSize * index);

    // 复制表后段元素。
    if (list->length - index && list->elems != NULL)
        memcpy(PointerAdd(newElems, (index + 1) * list->elemSize),
               PointerAdd(list->elems, index * list->elemSize),
               list->elemSize * (list->length - index));

    // 设置新元素。
    memcpy(PointerAdd(newElems, index * list->elemSize), elem, list->elemSize);

    // 回收老内存，设置新内存地址。
    free(list->elems);
    list->elems = newElems;
    list->length++;

    return 0;
}

// 缩容并弹出元素。
static int deallocAndPop(ArrayList* list, const size_t index, void* elem) {
    if (elem != NULL) memcpy(elem, PointerAdd(list->elems, index * list->elemSize), list->elemSize);

    // 分配新内存。
    size_t newCapacity = (size_t)((long double)list->length * array_list_expand_factor);
    if (newCapacity < list->length - 1) newCapacity = list->length - 1;
    void* newElems = malloc(list->elemSize * newCapacity);
    if (!newElems) return MEMORY_ALLOCATE_FAILED;

    // 复制前段。
    if (index) memcpy(newElems, list->elems, list->elemSize * index);

    // 复制后段。
    if (list->length - index - 1)
        memcpy(PointerAdd(newElems, index * list->elemSize),
               PointerAdd(list->elems, (index + 1) * list->elemSize),
               list->elemSize * (list->length - index - 1));

    // 回收老内存，设置新内存。
    free(list->elems);
    list->elems = newElems;
    list->capacity = newCapacity;
    list->length--;
    return 0;
}

// 检查 elem 与 list 是否存在内存重叠。
static _Bool checkMemoryOverlap(const ArrayList* list, const void* elem) {
    const uintptr_t elemPtr = (uintptr_t)elem;
    const uintptr_t startPtr = (uintptr_t)list->elems;
    const uintptr_t endPtr = startPtr + list->capacity * list->elemSize;
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

size_t ArrayList_Len(const ArrayList* list) {
    if (!list) return 0;
    return list->length;
}

int ArrayList_Get(const ArrayList* list, const size_t index, void* elem) {
    if (!list) return LIST_IS_NULL;
    if (!elem) return ELEM_IS_NULL;
    if (index >= list->length) return INDEX_OUT_OF_BOUND;
    if (checkMemoryOverlap(list, elem)) return MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST;
    memcpy(elem, PointerAdd(list->elems, index * list->elemSize), list->elemSize);
    return 0;
}

int ArrayList_Insert(ArrayList* list, const size_t index, const void* elem) {
    if (!list) return LIST_IS_NULL;
    if (index > list->length) return INDEX_OUT_OF_BOUND;
    if (!elem) return ELEM_IS_NULL;
    if (checkMemoryOverlap(list, elem)) return MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST;

    // 扩容。
    if (needExpand(list)) return expandAndInsert(list, index, elem);

    // 从 index 往后移动一位。
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
    if (!list) return LIST_IS_NULL;
    if (index >= list->length) return INDEX_OUT_OF_BOUND;

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
    if (!list) return LIST_IS_NULL;
    if (!cmp) return COMPARER_IS_NULL;
    if (!elem) return ELEM_IS_NULL;
    if (!index) return INDEX_IS_NULL;
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(PointerAdd(list->elems, i * list->elemSize), elem)) {
            *index = i;
            return 0;
        }
    }
    return ELEM_NOT_FOUND;
}

int ArrayList_Travel(const ArrayList* list, ListElemVisitor visitor) {
    if (!list) return LIST_IS_NULL;
    if (!visitor) return VISITOR_IS_NULL;
    for (size_t i = 0; i < list->length; i++) visitor(PointerAdd(list->elems, i * list->elemSize));

    return 0;
}

int ArrayList_Clear(ArrayList* list) {
    if (!list) return LIST_IS_NULL;
    free(list->elems);
    list->elems = NULL;
    list->length = list->capacity = 0;
    return 0;
}

int ArrayList_RPop(ArrayList* list, void* elem) { return ArrayList_GetDel(list, list ? list->length - 1 : 0, elem); }

int ArrayList_LPush(ArrayList* list, const void* elem) { return ArrayList_Insert(list, 0, elem); }

int ArrayList_RPush(ArrayList* list, const void* elem) { return ArrayList_Insert(list, list ? list->length : 0, elem); }

int ArrayList_LPop(ArrayList* list, void* elem) { return ArrayList_GetDel(list, 0, elem); }

int ArrayList_Set(ArrayList* list, const size_t index, const void* elem) {
    if (!list) return LIST_IS_NULL;
    if (index >= list->length) return INDEX_OUT_OF_BOUND;
    if (!elem) return ELEM_IS_NULL;
    if (checkMemoryOverlap(list, elem)) return MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST;
    memcpy(PointerAdd(list->elems, index * list->elemSize), elem, list->elemSize);
    return 0;
}

int ArrayList_GetDel(ArrayList* list, const size_t index, void* elem) {
    if (!list) return LIST_IS_NULL;
    if (index >= list->length) return INDEX_OUT_OF_BOUND;
    if (!elem) return ELEM_IS_NULL;
    if (checkMemoryOverlap(list, elem)) return MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST;

    // 缩容。
    if (needReduce(list)) return deallocAndPop(list, index, elem);

    // 设置元素。
    memcpy(elem, PointerAdd(list->elems, index * list->elemSize), list->elemSize);

    // 从 index 往前移动一位。
    if (list->length - 1 - index)
        memmove(PointerAdd(list->elems, index * list->elemSize),
                PointerAdd(list->elems, (index + 1) * list->elemSize),
                (list->length - 1 - index) * list->elemSize);

    list->length--;
    return 0;
}

int ArrayList_GetSet(ArrayList* list, const size_t index, void* elem) {
    if (!list) return LIST_IS_NULL;
    if (index >= list->length) return INDEX_OUT_OF_BOUND;
    if (!elem) return ELEM_IS_NULL;
    if (checkMemoryOverlap(list, elem)) return MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST;

    void* tmp = malloc(list->elemSize);
    if (!tmp) return MEMORY_ALLOCATE_FAILED;
    memcpy(tmp, PointerAdd(list->elems, index * list->elemSize), list->elemSize); // 元素先放临时变量中。
    memcpy(PointerAdd(list->elems, index * list->elemSize), elem, list->elemSize); // 设置元素。
    memcpy(elem, tmp, list->elemSize);
    free(tmp);
    return 0;
}

int ArrayList_FPrint(const ArrayList* list, FILE* out, ListElemToString2 stringify, size_t sizeOfElem) {
    if (!list) return LIST_IS_NULL;
    if (!out) return STREAM_IS_NULL;
    if (!stringify) return STRINGIFY_IS_NULL;

    fprintf(out, "[");
    size_t tmpLen = sizeOfElem > 1
        ? sizeOfElem + 1
        : (ARRAY_LIST_DEFAULT_PRINT_BUFFER_SIZE > 1 ? ARRAY_LIST_DEFAULT_PRINT_BUFFER_SIZE + 1 : 256);
    char* tmp = malloc(tmpLen);
    if (!tmp) return MEMORY_ALLOCATE_FAILED;

    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
        size_t len = stringify(PointerAdd(list->elems, i * list->elemSize), tmp, tmpLen - 1);
        tmp[len] = '\0';
        fprintf(out, "%s, ", tmp);
    }

    if (list->length) {
        const size_t len = stringify(PointerAdd(list->elems, (list->length - 1) * list->elemSize), tmp, tmpLen - 1);
        tmp[len] = '\0';
        fprintf(out, "%s", tmp);
    }
    free(tmp);

    fprintf(out, "]");
    fflush(out);
    return 0;
}
