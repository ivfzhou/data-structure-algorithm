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

#ifndef CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_LIST_H
#define CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_LIST_H

#include <stdio.h>
#include <stdlib.h>

// 线性表实现类型
typedef enum {
    ARRAY, // 数组实现。
    LINKED, // 链表实现。
    DOUBLE_LINKED, // 双向链表实现。
    STATIC_LINKED, // 静态链表实现。
    CIRCLE_LINKED // 环链表实现。
} ListImplType;

// 线性表。
typedef struct {
    ListImplType type; // 线性表类型。
    void* impl; // 线性表实现。
} List;

// 线性表比较器。
// 返回 0 表示相等。
// 返回 -1 表示后者大。
// 返回 1 表示前者大。
typedef int ListElemComparer(const void* e1, const void* e2);

// 线性表元素访问器。
typedef void ListElemVisitor(void* elem);

// 将元素转化成字符串形式表示到 s 并返回长度。
typedef size_t ListElemToString(void* elem, char* s);

// 初始化线性表。
// list：指针地址将被设置为初始化的线性表。
// elem_size：线性表中每个元素占用的空间字节数。
// impl：使用哪种实现。
List* List_Alloc(size_t elemSize, ListImplType type);

// 销毁线性表。
// list：线性表对象。
void List_Free(List* list);

// 获取线性表元素个数。
// list：线性表对象。
// length：将被设置为线性表长度值。
size_t List_Len(const List* list);

// 获取线性表某个位置上的元素。
// list：线性表对象。
// index：元素在线性表的下表值。
// elem：将被设置为元素值。
// 返回1: 越界。
int List_Get(const List* list, size_t index, void* elem);

// 把元素添加到线性表上的某个位置。
// list：线性表对象。
// index：元素在线性表的下表值。
// elem：插入的元素。
// 返回1: 越界。
int List_Insert(List* list, size_t index, const void* elem);

// 删除线性表某个位置上的元素。
// list：线性表对象。
// index：元素在线性表的下表值。
// 返回1: 越界。
int List_Del(List* list, size_t index);

// 找到元素在线性表上的位置。
// list：线性表对象。
// cmp：比较函数。
// elem：要定位的元素。
// index：元素下表将被设置。
// 返回1: 未找到。
int List_Locate(const List* list, ListElemComparer cmp, const void* elem, size_t* index);

// 遍历线性表元素。
// list：线性表对象。
// visit：遍历函数。
int List_Travel(const List* list, ListElemVisitor visit);

// 重置线性表。
// list：操作对象。
int List_Clear(List* list);

// 获取线性表尾部元素并删除。
// list：线性表对象。
// elem：将被设置为元素值。
// 返回1: 越界。
int List_RPop(List* list, void* elem);

// 向线性表首部插入元素。
// list：线性表对象。
// elem：被插入的元素。
int List_LPush(List* list, const void* elem);

// 在线性表尾部插入元素。
// list：线性表对象。
// elem：被插入的元素。
int List_RPush(List* list, const void* elem);

// 弹出线性表首部元素。
// list：线性表对象。
// elem：将被设置为弹出的元素值。
// 返回1: 越界。
int List_LPop(List* list, void* elem);

// 设置线性表上指定位置的元素
// list：线性表对象。
// index：下表。
// elem：元素。
// 返回1: 越界。
int List_Set(const List* list, size_t index, const void* elem);

// 获取线性表上指定位置的元素并从表上删除。
// list：线性表对象。
// index：下表。
// elem：元素。
// 返回1: 越界。
int List_GetDel(List* list, size_t index, void* elem);

// 获取线性表上指定位置的元素并设置新元素。
// list：线性表对象。
// index：下表。
// getElem：获取的元素。
// setElem：设置的元素。
// 返回1: 越界。
int List_GetSet(const List* list, size_t index, void* elem);

// 打印输入线性表元素
// list：线性表对象。
// f：输入对象。
// str：转字符串函数。
// sizeOfElem：元素字符串至少占用的字节数。
int List_FPrint(const List* list, FILE* f, ListElemToString str, size_t sizeOfElem);

#endif
