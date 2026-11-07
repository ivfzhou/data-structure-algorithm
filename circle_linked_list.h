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

#ifndef CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_CircleLinkedList_H
#define CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_CircleLinkedList_H

#include <stdlib.h>

#include "list.h"

// 环链节点。
typedef struct CircleLinkNode {
    void* elem;
    struct CircleLinkNode *next, *prev;
} CircleLinkNode;

// 环链线性表。
typedef struct {
    size_t length, elemSize;
    CircleLinkNode* firstNode;
} CircleLinkedList;

// 新建环链表。
// elemSize：每个元素占用的字节大小。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
CircleLinkedList* CircleLinkedList_Alloc(size_t elemSize);

// 销毁环链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void CircleLinkedList_Free(CircleLinkedList* list);

// 获取环链中表元素个数。
// list：环链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t CircleLinkedList_Len(const CircleLinkedList* list);

// 获取环链表中元素。
// list：环链表。
// index：元素所在位置。
// elem：元素值塞入 elem 中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int CircleLinkedList_Get(const CircleLinkedList* list, size_t index, void* elem);

// 向环链表中插入元素。
// list：环链表。
// index：元素所在位置。
// elem：被插入的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int CircleLinkedList_Insert(CircleLinkedList* list, size_t index, const void* elem);

// 删除环链表中元素。
// list：环链表。
// index：元素所在位置。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int CircleLinkedList_Del(CircleLinkedList* list, size_t index);

// 寻找元素在环链表的位置。
// list：环链表。
// cmp：元素比较函数。
// elem：要寻找的元素。
// index：元素位置塞入index中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 未找到。
int CircleLinkedList_Locate(const CircleLinkedList* list, ListElemComparer cmp, const void* elem, size_t* index);

// 遍历环链表。
// list：环链表。
// visit：遍历函数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int CircleLinkedList_Travel(const CircleLinkedList* list, ListElemVisitor visit);

// 清除环链表中所有元素。
// list：环链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int CircleLinkedList_Clear(CircleLinkedList* list);

// 取出环链表中最右边的元素。
// list：环链表。
// elem：元素值塞入 elem 中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int CircleLinkedList_RPop(CircleLinkedList* list, void* elem);

// 向环链表最左边添加元素。
// list：环链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int CircleLinkedList_LPush(CircleLinkedList* list, const void* elem);

// 向环链表最右边添加元素。
// list：环链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int CircleLinkedList_RPush(CircleLinkedList* list, const void* elem);

// 取出环链表中最左边的元素。
// list：环链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int CircleLinkedList_LPop(CircleLinkedList* list, void* elem);

// 设置环链表中一个位置上的元素。
// list：环链表。
// index：元素位置。
// elem：被设置的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int CircleLinkedList_Set(CircleLinkedList* list, size_t index, const void* elem);

// 获取环链表中元素并从环链表中删除。
// list：环链表。
// index：元素所在位置。
// elem：元素值塞入 elem 中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int CircleLinkedList_GetDel(CircleLinkedList* list, size_t index, void* elem);

// 获取环链表中元素值并设置新元素值。
// list：环链表。
// index：元素所在位置。
// elem：替换元素值。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int CircleLinkedList_GetSet(CircleLinkedList* list, size_t index, void* elem);

// 打印环链表元素。
// list：环链表。
// f：打印输出对象。
// str：元素转字符串表示函数。
// sizeOfElem：每个元素的字符串表示占用的最大字节大小。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int CircleLinkedList_FPrint(const CircleLinkedList* list, FILE* f, ListElemToString str, size_t sizeOfElem);

#endif
