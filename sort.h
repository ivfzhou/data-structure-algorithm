/*
 * Copyright (c) 2025 ivfzhou
 * data-structure-algorithm is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */

#ifndef CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_SORT_H
#define CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_SORT_H

// 冒泡。
void Sort_Bubble(int length, int arr[]);

// 选择。
void Sort_Select(int length, int arr[]);

// 插入。
void Sort_Insert(int length, int arr[]);

// 希尔。
void Sort_Shell(int length, int arr[]);

// 快速。
void Sort_Quick(int length, int arr[]);

// 归并。
void Sort_Merge(int length, int arr[]);

// 基数。
void Sort_Radix(int length, int arr[]);

#endif
