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

/**
 * @file array_list.h
 * @brief 顺序线性表接口声明。
 */

#ifndef CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_ARRAY_LIST_H
#define CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_ARRAY_LIST_H

#include <stdlib.h>

#include "list.h"

/**
 * @brief 顺序线性表类型定义。
 */
typedef struct {
    size_t length; ///< 元素的个数。由内部 API 使用，请勿直接使用。
    size_t capacity; ///< 线性表容量大小。由内部 API 使用，请勿直接使用。
    size_t elemSize; ///< 单个元素的字节大小。由内部 API 使用，请勿直接使用。
    void* elems; ///< 第一个元素的指针。由内部 API 使用，请勿直接使用。
} ArrayList;

/**
 * @brief 新建顺序表。
 * @details 时间复杂度 O(1)，空间复杂度 O(1)。
 * @param[in] elemSize 单个元素的字节大小。
 * @return 返回顺序线性表类型指针；当不再需要时，需要调用 ArrayList_Free 回收内存。
 * @retval NULL elemSize 为 0 或发生分配内存失败等错误。
 */
ArrayList* ArrayList_Alloc(size_t elemSize);

/**
 * @berif 销毁顺序表。
 * @details 时间复杂度 O(1)，空间复杂度 O(1)。
 * @param[in] list 顺序线性表类型指针。
 */
void ArrayList_Free(ArrayList* list);

/**
 * @berif 获取顺序表中元素个数。
 * @details 时间复杂度 O(1)，空间复杂度 O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @return 顺序表元素个数。
 */
size_t ArrayList_Len(const ArrayList* list);

/**
 * @berif 获取顺序表元素。
 * @details 时间复杂度 O(1)，空间复杂度 O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] index 元素所在位置。0 代表第一个元素，一次类推。
 * @param[out] elem 填充元素到指针下。
 * @return 操作结果，非零表示失败。
 * @retval 0 操作成功。
 * @retval 1 顺序线性表类型指针 list 为 NULL。
 * @retval 2 元素 elem 为 NULL。
 * @retval 3 index 越界。
 * @retval 4 elem 地址与 list 元素地址存在重叠。
 */
int ArrayList_Get(const ArrayList* list, size_t index, void* elem);

// 向顺序表中插入元素。
// list：顺序表。
// index：插入元素的位置。
// elem：被插入的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int ArrayList_Insert(ArrayList* list, size_t index, const void* elem);

// 删除顺序表中一个元素。
// list：顺序表。
// index：元素所在位置。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int ArrayList_Del(ArrayList* list, size_t index);

// 获取一个元素在顺序表中的位置。
// list：顺序表。
// cmp：元素比较函数。
// elem：要寻找的函数。
// index：元素位置塞入 index 中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 未找到。
int ArrayList_Locate(const ArrayList* list, ListElemComparer cmp, const void* elem, size_t* index);

// 遍历顺序表。
// list：顺序表。
// visit：遍历函数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int ArrayList_Travel(const ArrayList* list, ListElemVisitor visit);

// 清除顺序表中所有元素。
// list：顺序表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int ArrayList_Clear(ArrayList* list);

// 取出顺序表中的最右边的元素。
// list：顺序表。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int ArrayList_RPop(ArrayList* list, void* elem);

// 在顺序表中的最左边位置添加元素。
// list：顺序表。
// elem：被添加的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int ArrayList_LPush(ArrayList* list, const void* elem);

// 在顺序表中的最右边位置添加元素。
// list：顺序表。
// elem：被添加的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int ArrayList_RPush(ArrayList* list, const void* elem);

// 取出顺序表中的最左边的元素。
// list：顺序表。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int ArrayList_LPop(ArrayList* list, void* elem);

// 设置顺序表的一个位置上的元素。
// list：顺序表。
// index：元素所在位置。
// elem：被设置的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int ArrayList_Set(ArrayList* list, size_t index, const void* elem);

// 删除并且取出顺序表中的元素。
// list：顺序表。
// elem：被删除的元素塞入 elem 中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int ArrayList_GetDel(ArrayList* list, size_t index, void* elem);

// 取出顺序表中的元素并在同一位置设置新元素。
// list：顺序表。
// index：元素所在位置。
// elem：被添加的元素以及取出的元素被塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int ArrayList_GetSet(ArrayList* list, size_t index, void* elem);

// 打印顺序表中的元素。
// list：顺序表。
// f：打印输出对象。
// str：元素转字符串表示函数。
// sizeOfElem：每个元素的字符串表示形式所占用的最大字节大小。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int ArrayList_FPrint(const ArrayList* list, FILE* f, ListElemToString str, size_t sizeOfElem);

#endif
