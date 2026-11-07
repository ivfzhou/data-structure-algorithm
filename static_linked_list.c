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

#include "common.h"
#include "static_linked_list.h"

// 扩容阈值。
const static int EXPAND_THRESHOLD = 256;

// 扩容系数。
const static long double EXPAND_FACTOR = 1.25L;

// 缩容系数。
const static long double REDUCE_FACTOR = 2L;

static _Bool needReduce(StaticLinkedList* list) {
    return list->length > EXPAND_THRESHOLD && (list->length * REDUCE_FACTOR <= list->capacity);
}

static _Bool needExpand(StaticLinkedList* list) { return list->length >= list->capacity; }

static int expandAndInsert(StaticLinkedList* list, size_t index, const void* elem) {
    if (list->capacity < EXPAND_THRESHOLD)
        list->capacity += list->capacity + 1;
    else
        list->capacity = (size_t)(list->capacity * EXPAND_FACTOR);

    void* newElems = malloc(list->elem_size * list->capacity);
    unsigned* newIndexed = malloc(sizeof(unsigned) * list->capacity);

    // 复制元素。
    if (list->length && list->elems != NULL) memcpy(newElems, list->elems, list->length * list->elem_size);

    // 新元素添加到尾部。
    memcpy(PointerAdd(newElems, list->length * list->elem_size), elem, list->elem_size);

    if (index && list->indexes != NULL) memcpy(newIndexed, list->indexes, index * sizeof(unsigned));
    newIndexed[index] = list->length;
    if (list->length - index)
        memcpy(newIndexed + index + 1, list->indexes + index, (list->length - index) * sizeof(unsigned));

    free(list->elems);
    free(list->indexes);
    list->elems = newElems;
    list->indexes = newIndexed;
    list->length++;

    return 0;
}

static int reduceAndPop(StaticLinkedList* list, size_t index, void* elem) {
    unsigned elemIndex = list->indexes[index];
    if (elem != NULL) memcpy(elem, PointerAdd(list->elems, elemIndex * list->elem_size), list->elem_size);
    list->capacity = (size_t)(list->length * EXPAND_FACTOR);

    void* newElems = malloc(list->elem_size * list->capacity);
    unsigned* newIndexed = malloc(sizeof(unsigned) * list->capacity);

    if (elemIndex > 1) memcpy(newElems, list->elems, list->elem_size * (elemIndex - 1));
    if (list->length - elemIndex > 1)
        memcpy(PointerAdd(newElems, elemIndex * list->elem_size),
               PointerAdd(list->elems, (elemIndex + 1) * list->elem_size),
               (list->length - elemIndex - 1) * list->elem_size);

    if (index) memcpy(newIndexed, list->indexes, index * sizeof(unsigned));
    if (list->length - index > 1)
        memcpy(newIndexed + index, list->indexes + index + 1, (list->length - index - 1) * sizeof(unsigned));

    free(list->elems);
    free(list->indexes);
    list->indexes = newIndexed;
    list->elems = newElems;
    list->length--;

    for (size_t i = 0; i < list->length; i++)
        if (list->indexes[i] > elemIndex) list->indexes[i]--;

    return 0;
}

StaticLinkedList* StaticLinkedList_Alloc(size_t elem_size) {
    StaticLinkedList* list = malloc(sizeof(StaticLinkedList));
    list->elem_size = elem_size;
    list->indexes = list->elems = NULL;
    list->length = list->capacity = 0;
    return list;
}

void StaticLinkedList_Free(StaticLinkedList* list) {
    free(list->elems);
    free(list->indexes);
    list->indexes = list->elems = NULL;
    list->length = list->capacity = 0;
    free(list);
}

size_t StaticLinkedList_Len(const StaticLinkedList* list) { return list->length; }

int StaticLinkedList_Get(const StaticLinkedList* list, size_t index, void* elem) {
    if (index >= list->length) return 1;
    memcpy(elem, PointerAdd(list->elems, list->indexes[index] * list->elem_size), list->elem_size);
    return 0;
}

int StaticLinkedList_Insert(StaticLinkedList* list, size_t index, const void* elem) {
    if (index > list->length) return 1;

    // 扩容
    if (needExpand(list)) return expandAndInsert(list, index, elem);

    // 新元素加入到尾部。
    memcpy(PointerAdd(list->elems, list->length * list->elem_size), elem, list->elem_size);

    // 移动索引。
    if (list->length - index > 0)
        memmove(list->indexes + index + 1, list->indexes + index, (list->length - index) * sizeof(unsigned));
    list->indexes[index] = list->length;

    list->length++;
    return 0;
}

int StaticLinkedList_Del(StaticLinkedList* list, size_t index) {
    if (index >= list->length) return 1;
    if (needReduce(list)) return reduceAndPop(list, index, NULL);
    unsigned elemIndex = list->indexes[index];
    if (list->length - elemIndex > 1)
        memmove(PointerAdd(list->elems, elemIndex * list->elem_size),
                PointerAdd(list->elems, (elemIndex + 1) * list->elem_size),
                (list->length - elemIndex - 1) * list->elem_size);
    if (list->length - index > 1)
        memmove(list->indexes + index, list->indexes + index + 1, sizeof(unsigned) * (list->length - index - 1));
    list->length--;
    for (int i = 0; i < list->length; i++)
        if (list->indexes[i] > elemIndex) list->indexes[i]--;
    return 0;
}

int StaticLinkedList_Locate(const StaticLinkedList* list, ListElemComparer cmp, const void* elem, size_t* index) {
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(PointerAdd(list->elems, list->indexes[i] * list->elem_size), elem)) {
            *index = (int)i;
            return 0;
        }
    }
    return 1;
}

int StaticLinkedList_Travel(const StaticLinkedList* list, ListElemVisitor visit) {
    for (size_t i = 0; i < list->length; i++) visit(PointerAdd(list->elems, list->indexes[i] * list->elem_size));

    return 0;
}

int StaticLinkedList_Clear(StaticLinkedList* list) {
    free(list->elems);
    free(list->indexes);
    list->length = list->capacity = 0;
    list->indexes = list->elems = NULL;
    return 0;
}

int StaticLinkedList_RPop(StaticLinkedList* list, void* elem) {
    return StaticLinkedList_GetDel(list, list->length - 1, elem);
}

int StaticLinkedList_LPush(StaticLinkedList* list, const void* elem) { return StaticLinkedList_Insert(list, 0, elem); }

int StaticLinkedList_RPush(StaticLinkedList* list, const void* elem) {
    return StaticLinkedList_Insert(list, list->length, elem);
}

int StaticLinkedList_LPop(StaticLinkedList* list, void* elem) { return StaticLinkedList_GetDel(list, 0, elem); }

int StaticLinkedList_Set(StaticLinkedList* list, size_t index, const void* elem) {
    if (index >= list->length) return 1;
    memcpy(PointerAdd(list->elems, list->indexes[index] * list->elem_size), elem, list->elem_size);
    return 0;
}

int StaticLinkedList_GetDel(StaticLinkedList* list, size_t index, void* elem) {
    if (index >= list->length) return 1;
    if (needReduce(list)) return reduceAndPop(list, index, elem);
    unsigned elemIndex = list->indexes[index];
    memcpy(elem, PointerAdd(list->elems, elemIndex * list->elem_size), list->elem_size);
    if (list->length - elemIndex > 1)
        memmove(PointerAdd(list->elems, elemIndex * list->elem_size),
                PointerAdd(list->elems, (elemIndex + 1) * list->elem_size),
                (list->length - elemIndex - 1) * list->elem_size);
    if (list->length - index > 1)
        memmove(list->indexes + index, list->indexes + index + 1, sizeof(unsigned) * (list->length - index - 1));
    list->length--;
    for (size_t i = 0; i < list->length; i++)
        if (list->indexes[i] > elemIndex) list->indexes[i]--;
    return 0;
}

int StaticLinkedList_GetSet(StaticLinkedList* list, size_t index, void* elem) {
    void* tmp = malloc(list->elem_size);
    memcpy(tmp, PointerAdd(list->elems, list->indexes[index] * list->elem_size), list->elem_size);
    memcpy(PointerAdd(list->elems, list->indexes[index] * list->elem_size), elem, list->elem_size);
    memcpy(elem, tmp, list->elem_size);
    free(tmp);
    return 0;
}

int StaticLinkedList_FPrint(const StaticLinkedList* list, FILE* f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
        size_t len = str(PointerAdd(list->elems, list->indexes[i] * list->elem_size), s);
        s[len] = '\0';
        fprintf(f, "%s, ", s);
    }
    if (list->length > 0) {
        size_t len = str(PointerAdd(list->elems, list->indexes[list->length - 1] * list->elem_size), s);
        s[len] = '\0';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}
