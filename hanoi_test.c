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

#include <stdio.h>

#include "stack.h"

static void move(Stack* from, Stack* to) {
    int disk;
    Stack_Pop(from, &disk);
    Stack_Push(to, &disk);
}

void hanoi(int disks, Stack* from, Stack* to, Stack* tmp) {
    if (disks == 1) {
        move(from, to);
        return;
    }
    hanoi(disks - 1, from, tmp, to);
    move(from, to);
    hanoi(disks - 1, tmp, to, from);
}

int main(void) {
    const int disks = 6;
    Stack* from = Stack_Alloc(sizeof(int), 256);
    Stack* to = Stack_Alloc(sizeof(int), 256);
    Stack* tmp = Stack_Alloc(sizeof(int), 256);
    for (int i = disks; i > 0; i--) {
        Stack_Push(from, &i);
    }
    hanoi(disks, from, to, tmp);

    int disk;
    for (int i = 0; i < disks; i++) {
        Stack_Pop(to, &disk);
        // printf("%d ", disk);
    }
    // puts("");

    Stack_Free(from);
    Stack_Free(to);
    Stack_Free(tmp);
}
