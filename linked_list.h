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

#ifndef CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_LINKED_LIST_H
#define CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

// 单链表节点。
typedef struct SingleLinkNode {
    void* elem;
    struct SingleLinkNode* next;
} SingleLinkNode;

// 单链线性表。
typedef struct {
    size_t length, elemSize;
    SingleLinkNode* head;
} LinkedList;

// 新建单链表。
// elemSize：每个元素占用的字节数量。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
LinkedList* LinkedList_Alloc(size_t elemSize);

// 销毁单链表。
// list：单链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void LinkedList_Free(LinkedList* list);

// 获取单链表中元素个数。
// list：单链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t LinkedList_Len(const LinkedList* list);

// 获取单链表中某一个位置的元素。
// list：单链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int LinkedList_Get(const LinkedList* list, size_t index, void* elem);

// 向单链表中插入元素。
// list：单链表。
// index：元素插入位置。
// elem：被插入的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int LinkedList_Insert(LinkedList* list, size_t index, const void* elem);

// 删除单链表个某个位置上的元素。
// list：单链表。
// index：元素所在位置。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int LinkedList_Del(LinkedList* list, size_t index);

// 查找元素单链表中的位置。
// list：单链表。
// cmp：元素比较函数。
// elem：寻找的元素。
// index：元素位置塞入index中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 未找到。
int LinkedList_Locate(const LinkedList* list, ListElemComparer cmp, const void* elem, size_t* index);

// 遍历单链表。
// list：单链表。
// visit：遍历函数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int LinkedList_Travel(const LinkedList* list, ListElemVisitor visit);

// 清空单链表。
// list：单链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int LinkedList_Clear(LinkedList* list);

// 取出单链表中右边元素。
// list：单链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int LinkedList_RPop(LinkedList* list, void* elem);

// 向单链表左边添加元素。
// list：单链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int LinkedList_LPush(LinkedList* list, const void* elem);

// 向单链表右边添加元素。
// list：单链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int LinkedList_RPush(LinkedList* list, const void* elem);

// 取出单链表最左边的元素。
// list：单链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int LinkedList_LPop(LinkedList* list, void* elem);

// 设置单链表中某个位置上的元素。
// list：单链表。
// index：元素所在位置。
// elem：被设置的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int LinkedList_Set(LinkedList* list, size_t index, const void* elem);

// 获取单链表中某个位置上的元素然后删除之。
// list：单链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int LinkedList_GetDel(LinkedList* list, size_t index, void* elem);

// 获取单链表中某个位置上的元素然后设置新值。
// list：单链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int LinkedList_GetSet(LinkedList* list, size_t index, void* elem);

// 打印单链表中的元素。
// list：单链表。
// f：打印输出对象。
// str：元素转字符串函数。
// sizeOfElem：每个元素转字符串表示占用的最大字节数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int LinkedList_FPrint(const LinkedList* list, FILE* f, ListElemToString str, size_t sizeOfElem);

#endif
