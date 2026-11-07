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

#include "double_linked_list.h"

static DoubleLinkNode* newNode(size_t size, const void* elem) {
    DoubleLinkNode* newNode = malloc(sizeof(DoubleLinkNode));
    newNode->elem = malloc(size);
    memcpy(newNode->elem, elem, size);
    newNode->next = newNode->prev = NULL;
    return newNode;
}

static DoubleLinkNode* getNode(const DoubleLinkedList* list, size_t index) {
    DoubleLinkNode* node;
    if (index <= (list->length - 1) / 2) {
        node = list->head;
        for (size_t i = 0; i < index; i++) node = node->next;
    } else {
        node = list->tail;
        for (size_t i = list->length - 1; i > index; i--) node = node->prev;
    }
    return node;
}

static DoubleLinkNode* popNode(DoubleLinkedList* list, size_t index) {
    DoubleLinkNode* node;
    if (!index) {
        node = list->head;
        list->head = list->head->next;
        if (list->length == 2) list->tail = list->head->next = NULL;
    } else if (index == (list->length - 1)) {
        node = list->tail;
        if (list->length == 2)
            list->tail = NULL;
        else {
            list->tail = list->tail->prev;
            list->tail->next = NULL;
        }
    } else {
        node = getNode(list, index);
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    node->prev = node->next = NULL;
    list->length--;
    return node;
}

DoubleLinkedList* DoubleLinkedList_Alloc(size_t elemSize) {
    DoubleLinkedList* list = malloc(sizeof(DoubleLinkedList));
    list->elemSize = elemSize;
    list->length = 0;
    list->head = list->tail = NULL;
    return list;
}

void DoubleLinkedList_Free(DoubleLinkedList* list) {
    DoubleLinkNode* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        DoubleLinkNode* tmp = node->next;
        free(node->elem);
        free(node);
        node = tmp;
    }
    list->length = 0;
    list->elemSize = 0;
    list->head = list->tail = NULL;
    free(list);
}

size_t DoubleLinkedList_Len(const DoubleLinkedList* list) { return list->length; }

int DoubleLinkedList_Get(const DoubleLinkedList* list, size_t index, void* elem) {
    if (index >= list->length) return 1;
    DoubleLinkNode* node = getNode(list, index);
    memcpy(elem, node->elem, list->elemSize);
    return 0;
}

int DoubleLinkedList_Insert(DoubleLinkedList* list, size_t index, const void* elem) {
    if (index > list->length) return 1;
    DoubleLinkNode* node = newNode(list->elemSize, elem);

    if (!list->length) {
        // 第一次插入。
        list->head = node;
    } else if (list->length == 1) {
        // 第二次插入。
        if (index) {
            node->prev = list->head;
            list->head->next = node;
            list->tail = node;
        } else {
            node->next = list->head;
            list->head->prev = node;
            list->tail = list->head;
            list->head = node;
        }
    } else if (index == list->length) {
        // 尾部追加。
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    } else if (!index) {
        // 头部追加。
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    } else {
        DoubleLinkNode* indexNode = getNode(list, index);
        node->next = indexNode;
        node->prev = indexNode->prev;
        indexNode->prev->next = node;
        indexNode->prev = node;
    }

    list->length++;
    return 0;
}

int DoubleLinkedList_Del(DoubleLinkedList* list, size_t index) {
    if (index > list->length) return 1;
    DoubleLinkNode* node = popNode(list, index);
    free(node->elem);
    free(node);
    return 0;
}

int DoubleLinkedList_Locate(const DoubleLinkedList* list, ListElemComparer cmp, const void* elem, size_t* index) {
    DoubleLinkNode* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(node->elem, elem)) {
            *index = i;
            return 0;
        }
        node = node->next;
    }
    return 1;
}

int DoubleLinkedList_Travel(const DoubleLinkedList* list, ListElemVisitor visit) {
    DoubleLinkNode* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        visit(node->elem);
        node = node->next;
    }
    return 0;
}

int DoubleLinkedList_Clear(DoubleLinkedList* list) {
    DoubleLinkNode* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        DoubleLinkNode* tmp = node->next;
        free(node->elem);
        free(node);
        node = tmp;
    }
    list->length = 0;
    list->head = list->tail = NULL;
    return 0;
}

int DoubleLinkedList_RPop(DoubleLinkedList* list, void* elem) {
    return DoubleLinkedList_GetDel(list, list->length - 1, elem);
}

int DoubleLinkedList_LPush(DoubleLinkedList* list, const void* elem) { return DoubleLinkedList_Insert(list, 0, elem); }

int DoubleLinkedList_RPush(DoubleLinkedList* list, const void* elem) {
    return DoubleLinkedList_Insert(list, list->length, elem);
}

int DoubleLinkedList_LPop(DoubleLinkedList* list, void* elem) { return DoubleLinkedList_GetDel(list, 0, elem); }

int DoubleLinkedList_Set(DoubleLinkedList* list, size_t index, const void* elem) {
    if (index >= list->length) return 1;
    DoubleLinkNode* node = getNode(list, index);
    memcpy(node->elem, elem, list->elemSize);
    return 0;
}

int DoubleLinkedList_GetDel(DoubleLinkedList* list, size_t index, void* elem) {
    if (index >= list->length) return 1;
    DoubleLinkNode* node = popNode(list, index);
    memcpy(elem, node->elem, list->elemSize);
    free(node->elem);
    free(node);
    return 0;
}

int DoubleLinkedList_GetSet(DoubleLinkedList* list, size_t index, void* elem) {
    if (index >= list->length) return 1;
    DoubleLinkNode* node = getNode(list, index);
    void* tmp = malloc(list->elemSize);
    memcpy(tmp, node->elem, list->elemSize);
    memcpy(node->elem, elem, list->elemSize);
    memcpy(elem, tmp, list->elemSize);
    free(tmp);
    return 0;
}

int DoubleLinkedList_FPrint(const DoubleLinkedList* list, FILE* f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    DoubleLinkNode* node = list->head;
    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
        size_t len = str(node->elem, s);
        s[len] = '\0';
        fprintf(f, "%s, ", s);
        node = node->next;
    }
    if (list->length > 0) {
        size_t len = str(node->elem, s);
        s[len] = '\0';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}
