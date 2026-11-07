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

#ifndef CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_DOUBLE_LINKED_LIST_H
#define CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_DOUBLE_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

// 双向链表节点。
typedef struct DoubleLinkNode {
    void* elem;
    struct DoubleLinkNode *next, *prev;
} DoubleLinkNode;

// 双向链式线性表。
typedef struct {
    size_t elemSize, length;
    DoubleLinkNode *head, *tail;
} DoubleLinkedList;

// 新建双向链表。
// elemSize：每个元素占用的字节大小。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
DoubleLinkedList* DoubleLinkedList_Alloc(size_t elemSize);

// 销毁双向链表。
// list：双向链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void DoubleLinkedList_Free(DoubleLinkedList* list);

// 获取双向链表中元素个数。
// list：双向链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t DoubleLinkedList_Len(const DoubleLinkedList* list);

// 获取双向链表中某位置上的元素。
// list：双向链表。
// index：元素所在位置。
// elem：元素值被塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int DoubleLinkedList_Get(const DoubleLinkedList* list, size_t index, void* elem);

// 向双向链表中插入元素。
// list：双向链表。
// index：元素插入位置。
// elem：被插入的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int DoubleLinkedList_Insert(DoubleLinkedList* list, size_t index, const void* elem);

// 删除双向链表中某个位置上的元素。
// list：双向链表。
// index：被删除元素所在位置。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int DoubleLinkedList_Del(DoubleLinkedList* list, size_t index);

// 寻找元素在双向链表中的位置。
// list：双向链表。
// cmp：元素比较函数。
// elem：要寻找的元素。
// index：元素位置塞入index中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 未找到。
int DoubleLinkedList_Locate(const DoubleLinkedList* list, ListElemComparer cmp, const void* elem, size_t* index);

// 遍历双向链表。
// list：双向链表。
// visit：遍历函数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int DoubleLinkedList_Travel(const DoubleLinkedList* list, ListElemVisitor visit);

// 清空双向链表中元素。
// list：双向链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int DoubleLinkedList_Clear(DoubleLinkedList* list);

// 取出双向链表中最右边的元素。
// list：双向链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int DoubleLinkedList_RPop(DoubleLinkedList* list, void* elem);

// 向双向链表左边添加元素。
// list：双向链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int DoubleLinkedList_LPush(DoubleLinkedList* list, const void* elem);

// 向双向链表右边添加元素。
// list：双向链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int DoubleLinkedList_RPush(DoubleLinkedList* list, const void* elem);

// 取出双向链表中最左边的元素。
// list：双向链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int DoubleLinkedList_LPop(DoubleLinkedList* list, void* elem);

// 设置双向链表中某个位置上的元素。
// list：双向链表。
// index：元素所在位置。
// elem：被设置的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int DoubleLinkedList_Set(DoubleLinkedList* list, size_t index, const void* elem);

// 获取双向链表中元素然后删除它。
// list：双向链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int DoubleLinkedList_GetDel(DoubleLinkedList* list, size_t index, void* elem);

// 获取双向链表中元素然后设置新的值。
// list：双向链表。
// index：元素所在位置。
// elem：元素值设置进表中，然后旧值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int DoubleLinkedList_GetSet(DoubleLinkedList* list, size_t index, void* elem);

// 打印双向链表中元素。
// list：双向链表。
// f：打印输出对象。
// str：元素转字符串表示形式函数。
// sizeOfElem：每个元素转字符串后占用的最大字节数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int DoubleLinkedList_FPrint(const DoubleLinkedList* list, FILE* f, ListElemToString str, size_t sizeOfElem);

#endif
