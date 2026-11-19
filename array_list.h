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

#ifndef ARRAY_LIST_EXPAND_THRESHOLD
    /**
     * @brief 扩容阈值。
     * @details 当线性表长度大于此值时，扩容长度将为原长度乘以 ARRAY_LIST_EXPAND_FACTOR。
     *          否则扩容长度为原长度加一。
     *          若要修改此值，在 include array_list.h 前定义该宏。
     */
    #define ARRAY_LIST_EXPAND_THRESHOLD 256UL
#endif

#ifndef ARRAY_LIST_EXPAND_FACTOR_NUM
    /**
     * @brief 扩容系数的分子。
     * @details 扩容系数 ARRAY_LIST_EXPAND_FACTOR = ARRAY_LIST_EXPAND_FACTOR_NUM / ARRAY_LIST_EXPAND_FACTOR_DEN。
     *          若要修改此值，在 include array_list.h 前定义该宏。
     */
    #define ARRAY_LIST_EXPAND_FACTOR_NUM 5UL
#endif
#ifndef ARRAY_LIST_EXPAND_FACTOR_DEN
    /**
     * @brief 扩容系数的分母。
     * @details 扩容系数 ARRAY_LIST_EXPAND_FACTOR = ARRAY_LIST_EXPAND_FACTOR_NUM / ARRAY_LIST_EXPAND_FACTOR_DEN。
     *          若要修改此值，在 include array_list.h 前定义该宏。
     */
    #define ARRAY_LIST_EXPAND_FACTOR_DEN 4UL
#endif

#ifndef ARRAY_LIST_REDUCE_FACTOR
    /**
     * @brief 缩容系数。
     * @details 判断线性表可以缩容的因素，若线性表长度大于 ARRAY_LIST_EXPAND_THRESHOLD，
     *          且线性表长度与 ARRAY_LIST_REDUCE_FACTOR 乘积不大于线性表容量，就进行缩容操作。
     *          若要修改此值，在 include array_list.h 前定义该宏。
     */
    #define ARRAY_LIST_REDUCE_FACTOR 2UL
#endif

#ifndef ARRAY_LIST_DEFAULT_PRINT_BUFFER_SIZE
    /**
     * @brief 在 ArrayList_FPrint 中，sizeOfElem 为 0 时，临时字符串默认长度。
     * @details 可根据元素字符串化后的长度修改此值。
     *          若要修改此值，在 include array_list.h 前定义该宏。
     */
    #define ARRAY_LIST_DEFAULT_PRINT_BUFFER_SIZE 256UL
#endif

#define array_list_expand_factor ((long double)ARRAY_LIST_EXPAND_FACTOR_NUM / (long double)ARRAY_LIST_EXPAND_FACTOR_DEN)

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
 * @brief 顺序线性表函数的错误码。
 */
enum ArrayList_ErrorCode {
    ELEM_NOT_FOUND = -1,
    LIST_IS_NULL = 1,
    INDEX_OUT_OF_BOUND,
    ELEM_IS_NULL,
    MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST,
    MEMORY_ALLOCATE_FAILED,
    COMPARER_IS_NULL,
    INDEX_IS_NULL,
    VISITOR_IS_NULL,
    STREAM_IS_NULL,
    STRINGIFY_IS_NULL,
};

/**
 * @brief 新建顺序表。
 * @details 时间复杂度 O(1)，空间复杂度 O(1)。
 * @param[in] elemSize 单个元素的字节大小。
 * @return 返回顺序线性表类型指针；当不再需要时，需要调用 ArrayList_Free 回收内存。
 * @retval NULL elemSize 为 0 或发生分配内存失败等错误。
 */
ArrayList* ArrayList_Alloc(size_t elemSize);

/**
 * @brief 销毁顺序表。
 * @details 时间复杂度 O(1)，空间复杂度 O(1)。
 * @param[in] list 顺序线性表类型指针。
 */
void ArrayList_Free(ArrayList* list);

/**
 * @brief 获取顺序表中元素个数。
 * @details 时间复杂度 O(1)，空间复杂度 O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @return 顺序表元素个数。如果 list 为 NULL，返回 0。
 */
size_t ArrayList_Len(const ArrayList* list);

/**
 * @brief 获取顺序表元素。
 * @details 时间复杂度 O(1)，空间复杂度 O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] index 元素所在位置。0 代表第一个元素，一次类推。
 * @param[out] elem 填充元素到指针下。
 * @return 操作结果，非零表示失败。
 * @retval 0 操作成功。
 * @retval LIST_IS_NULL 顺序线性表类型指针 list 为 NULL。
 * @retval ELEM_IS_NULL 元素 elem 为 NULL。
 * @retval INDEX_OUT_OF_BOUND index 越界。
 * @retval MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST elem 地址与 list 元素地址存在重叠。
 */
int ArrayList_Get(const ArrayList* list, size_t index, void* elem);

/**
 * @brief 向顺序表中插入元素。
 * @details 时间复杂度：O(1)，空间复杂度：O(1)。
 *          不会删除覆盖元素，而是被插入位开始的元素向后挪一位。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] index 元素插入位置。从 0 开始计数，最大值可以是线性表长度，否则报错越界。
 * @param[in] elem 将被插入到线性表中的元素指针。
 * @retval 0 操作成功。
 * @retval LIST_IS_NULL list 为 NULL。
 * @retval INDEX_OUT_OF_BOUND index 越界。
 * @retval ELEM_IS_NULL elem 为 NULL。
 * @retval MEMORY_ALLOCATE_FAILED 内存分配错误。
 * @retval MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST elem 与 list 存在内存重叠。
 */
int ArrayList_Insert(ArrayList* list, size_t index, const void* elem);

/**
 * @brief 删除顺序表中一个元素。
 * @details 时间复杂度：O(1)，空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] index 被删除元素下标。从 0 开始计数，最大值可以是线性表长度，否则报错越界。
 * @retval 0 操作成功。
 * @retval LIST_IS_NULL list 为 NULL。
 * @retval INDEX_OUT_OF_BOUND index 越界。
 * @retval MEMORY_ALLOCATE_FAILED 内存分配错误。
 */
int ArrayList_Del(ArrayList* list, size_t index);

/**
 * @brief 获取一个元素在顺序表中的位置。
 * @details 时间复杂度：O(n)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] cmp 元素大小比较函数。
 * @param[in] elem 要寻找的元素的指针。
 * @param[out] index 元素 elem 在线性表中的位置。下标从 0 开始计算。
 * @return 操作结果，0 表示操作成功。
 * @retval LIST_IS_NULL list 是 NULL。
 * @retval COMPARER_IS_NULL cmp 是 NULL。
 * @retval ELEM_IS_NULL elem 是 NULL。
 * @retval INDEX_IS_NULL index 是 NULL。
 * @retval ELEM_NOT_FOUND 线性表中不存在 elem 元素。
 * @retval MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST elem 与 list 存在内存重叠。
 */
int ArrayList_Locate(const ArrayList* list, ListElemComparer cmp, const void* elem, size_t* index);

/**
 * @brief 遍历顺序表。
 * @details 时间复杂度：O(n)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] visitor 遍历元素的函数。
 * @return 操作结果，0 表示正常遍历完所有元素。
 * @retval LIST_IS_NULL list 是 NULL。
 * @retval VISITOR_IS_NULL visitor 是 NULL。
 */
int ArrayList_Travel(const ArrayList* list, ListElemVisitor visitor);

/**
 * @brief 清除顺序表中所有元素。
 * @details 时间复杂度：O(1)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @return 操作结果，0 表示操作成功。
 * @retval LIST_IS_NULL list 是 NULL。
 */
int ArrayList_Clear(ArrayList* list);

/**
 * @brief 取出顺序表中的最右边的元素。
 * @details 时间复杂度：O(1)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[out] elem 元素值将填充进 elem。
 * @return 操作结果，0 表示操作成功。
 * @retval LIST_IS_NULL list 是 NULL。
 * @retval ELEM_IS_NULL elem 是 NULL。
 * @retval MEMORY_ALLOCATE_FAILED 内存分配错误。
 * @retval MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST elem 与 list 存在内存重叠。
 */
int ArrayList_RPop(ArrayList* list, void* elem);

/**
 * @brief 在顺序表中的最左边位置添加元素。
 * @details 时间复杂度：O(1)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] elem 添加进线性表的元素的指针。
 * @return 操作结果，0 表示操作成功。
 * @retval LIST_IS_NULL list 为 NULL。
 * @retval ELEM_IS_NULL elem 为 NULL。
 * @retval MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST elem 与 list 存在内存重叠。
 * @retval MEMORY_ALLOCATE_FAILED 内存分配错误。
 */
int ArrayList_LPush(ArrayList* list, const void* elem);

/**
 * @brief 在顺序表中的最右边位置添加元素。
 * @details 时间复杂度：O(1)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] elem 添加进入线性表的元素的指针。
 * @return 操作结果，0 表示操作成功。
 * @retval LIST_IS_NULL list 为 NULL。
 * @retval ELEM_IS_NULL elem 为 NULL。
 * @retval MEMORY_ALLOCATE_FAILED 内存分配错误。
 * @retval MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST elem 与 list 存在内存重叠。
 */
int ArrayList_RPush(ArrayList* list, const void* elem);

/**
 * @brief 取出顺序表中的最左边的元素。
 * @details 时间复杂度：O(1)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] elem 插入线性表中的元素的指针。
 * @return 操作结果，0 表示弹出元素成功。
 * @retval LIST_IS_NULL list 为 NULL。
 * @retval ELEM_IS_NULL elem 为 NULL。
 * @retval MEMORY_ALLOCATE_FAILED 内存分配错误。
 * @retval MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST elem 与 list 在内存中存在重叠。
 */
int ArrayList_LPop(ArrayList* list, void* elem);

/**
 * @brief 设置顺序表的一个位置上的元素。
 * @details 时间复杂度：O(1)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] index 被设置元素的下标。
 * @param[in] elem 添加进线性表的元素的指针。
 * @return 操作结果，0 表示操作成功。
 * @retval LIST_IS_NULL list 为 NULL。
 * @retval INDEX_OUT_OF_BOUND index 越界。
 * @retval ELEM_IS_NULL elem 为 NULL。
 * @retval MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST elem 与 list 在内存中存在重叠。
 */
int ArrayList_Set(ArrayList* list, size_t index, const void* elem);

/**
 * @brief 删除并且取出顺序表中的元素。
 * @details 时间复杂度：O(1)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] index 获取的元素下标。
 * @param[out] elem 线性表元素添加进 elem 中。
 * @return 操作结果，0 表示成功。
 * @retval LIST_IS_NULL list 为 NULL。
 * @retval INDEX_OUT_OF_BOUND index 越界。
 * @retval ELEM_IS_NULL elem 为 NULL。
 * @retval MEMORY_ALLOCATE_FAILED 内存分配错误。
 * @retval MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST elem 与 list 在内存中存在重叠。
 */
int ArrayList_GetDel(ArrayList* list, size_t index, void* elem);

/**
 * @brief 取出顺序表中的元素并在同一位置设置新元素。
 * @details 时间复杂度：O(1)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] index 获取和设置元素的下标。
 * @param[in] elem 与线性表交换元素值的指针。
 * @return 操作结果，0 表示成功。
 * @retval LIST_IS_NULL list 为 NULL。
 * @retval INDEX_OUT_OF_BOUND index 越界。
 * @retval ELEM_IS_NULL elem 为 NULL。
 * @retval MEMORY_ALLOCATE_FAILED 内存分配错误。
 * @retval MEMORY_OVERLAPPING_BETWEEN_ELEM_AND_LIST elem 与 list 在内存中存在重叠。
 */
int ArrayList_GetSet(ArrayList* list, size_t index, void* elem);

/**
 * @brief 打印顺序表中的元素。
 * @details 时间复杂度：O(n)。空间复杂度：O(1)。
 * @param[in] list 顺序线性表类型指针。
 * @param[in] out 字符串输出流，元素打印输出流。
 * @param[in] stringify 将元素变换成字符串的函数。
 * @param[in] sizeOfElem 每个元素的字符串表示形式所占用的最大字节大小。
 * @return 操作结果，0 表示成功。
 * @retval LIST_IS_NULL list 为 NULL。
 * @retval STREAM_IS_NULL out 为 NULL。
 * @retval STRINGIFY_IS_NULL stringify 为 NULL。
 * @retval MEMORY_ALLOCATE_FAILED 内存分配错误。
 */
int ArrayList_FPrint(const ArrayList* list, FILE* out, ListElemToString2 stringify, size_t sizeOfElem);

#endif
