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

#include "list.h"
#include "array_list.h"
#include "circle_linked_list.h"
#include "double_linked_list.h"
#include "linked_list.h"
#include "static_linked_list.h"

List* List_Alloc(size_t elemSize, ListImplType type) {
    List* list = malloc(sizeof(List));
    switch (type) {
    case ARRAY: list->impl = ArrayList_Alloc(elemSize); break;
    case LINKED: list->impl = LinkedList_Alloc(elemSize); break;
    case DOUBLE_LINKED: list->impl = DoubleLinkedList_Alloc(elemSize); break;
    case STATIC_LINKED: list->impl = StaticLinkedList_Alloc(elemSize); break;
    case CIRCLE_LINKED: list->impl = CircleLinkedList_Alloc(elemSize); break;
    default: return NULL;
    }
    list->type = type;
    if (!list->impl) {
        free(list);
        return NULL;
    }
    return list;
}

void List_Free(List* list) {
    switch (list->type) {
    case ARRAY: ArrayList_Free(list->impl); break;
    case LINKED: LinkedList_Free(list->impl); break;
    case DOUBLE_LINKED: DoubleLinkedList_Free(list->impl); break;
    case STATIC_LINKED: StaticLinkedList_Free(list->impl); break;
    case CIRCLE_LINKED: CircleLinkedList_Free(list->impl); break;
    }
    free(list);
}

size_t List_Len(const List* list) {
    switch (list->type) {
    case ARRAY: return ArrayList_Len(list->impl);
    case LINKED: return LinkedList_Len(list->impl);
    case DOUBLE_LINKED: return DoubleLinkedList_Len(list->impl);
    case STATIC_LINKED: return StaticLinkedList_Len(list->impl);
    case CIRCLE_LINKED: return CircleLinkedList_Len(list->impl);
    default: return 0;
    }
}

int List_Get(const List* list, size_t index, void* elem) {
    switch (list->type) {
    case ARRAY: return ArrayList_Get(list->impl, index, elem);
    case LINKED: return LinkedList_Get(list->impl, index, elem);
    case DOUBLE_LINKED: return DoubleLinkedList_Get(list->impl, index, elem);
    case STATIC_LINKED: return StaticLinkedList_Get(list->impl, index, elem);
    case CIRCLE_LINKED: return CircleLinkedList_Get(list->impl, index, elem);
    default: return 1;
    }
}

int List_Insert(List* list, size_t index, const void* elem) {
    switch (list->type) {
    case ARRAY: return ArrayList_Insert(list->impl, index, elem);
    case LINKED: return LinkedList_Insert(list->impl, index, elem);
    case DOUBLE_LINKED: return DoubleLinkedList_Insert(list->impl, index, elem);
    case STATIC_LINKED: return StaticLinkedList_Insert(list->impl, index, elem);
    case CIRCLE_LINKED: return CircleLinkedList_Insert(list->impl, index, elem);
    default: return 1;
    }
}

int List_Del(List* list, size_t index) {
    switch (list->type) {
    case ARRAY: return ArrayList_Del(list->impl, index);
    case LINKED: return LinkedList_Del(list->impl, index);
    case DOUBLE_LINKED: return DoubleLinkedList_Del(list->impl, index);
    case STATIC_LINKED: return StaticLinkedList_Del(list->impl, index);
    case CIRCLE_LINKED: return CircleLinkedList_Del(list->impl, index);
    default: return 1;
    }
}

int List_Locate(const List* list, ListElemComparer cmp, const void* elem, size_t* index) {
    switch (list->type) {
    case ARRAY: return ArrayList_Locate(list->impl, cmp, elem, index);
    case LINKED: return LinkedList_Locate(list->impl, cmp, elem, index);
    case DOUBLE_LINKED: return DoubleLinkedList_Locate(list->impl, cmp, elem, index);
    case STATIC_LINKED: return StaticLinkedList_Locate(list->impl, cmp, elem, index);
    case CIRCLE_LINKED: return CircleLinkedList_Locate(list->impl, cmp, elem, index);
    default: return 1;
    }
}

int List_Travel(const List* list, ListElemVisitor visit) {
    switch (list->type) {
    case ARRAY: return ArrayList_Travel(list->impl, visit);
    case LINKED: return LinkedList_Travel(list->impl, visit);
    case DOUBLE_LINKED: return DoubleLinkedList_Travel(list->impl, visit);
    case STATIC_LINKED: return StaticLinkedList_Travel(list->impl, visit);
    case CIRCLE_LINKED: return CircleLinkedList_Travel(list->impl, visit);
    default: return 1;
    }
}

int List_Clear(List* list) {
    switch (list->type) {
    case ARRAY: return ArrayList_Clear(list->impl);
    case LINKED: return LinkedList_Clear(list->impl);
    case DOUBLE_LINKED: return DoubleLinkedList_Clear(list->impl);
    case STATIC_LINKED: return StaticLinkedList_Clear(list->impl);
    case CIRCLE_LINKED: return CircleLinkedList_Clear(list->impl);
    default: return 1;
    }
}

int List_RPop(List* list, void* elem) {
    switch (list->type) {
    case ARRAY: return ArrayList_RPop(list->impl, elem);
    case LINKED: return LinkedList_RPop(list->impl, elem);
    case DOUBLE_LINKED: return DoubleLinkedList_RPop(list->impl, elem);
    case STATIC_LINKED: return StaticLinkedList_RPop(list->impl, elem);
    case CIRCLE_LINKED: return CircleLinkedList_RPop(list->impl, elem);
    default: return 1;
    }
}

int List_LPush(List* list, const void* elem) {
    switch (list->type) {
    case ARRAY: return ArrayList_LPush(list->impl, elem);
    case LINKED: return LinkedList_LPush(list->impl, elem);
    case DOUBLE_LINKED: return DoubleLinkedList_LPush(list->impl, elem);
    case STATIC_LINKED: return StaticLinkedList_LPush(list->impl, elem);
    case CIRCLE_LINKED: return CircleLinkedList_LPush(list->impl, elem);
    default: return 1;
    }
}

int List_RPush(List* list, const void* elem) {
    switch (list->type) {
    case ARRAY: return ArrayList_RPush(list->impl, elem);
    case LINKED: return LinkedList_RPush(list->impl, elem);
    case DOUBLE_LINKED: return DoubleLinkedList_RPush(list->impl, elem);
    case STATIC_LINKED: return StaticLinkedList_RPush(list->impl, elem);
    case CIRCLE_LINKED: return CircleLinkedList_RPush(list->impl, elem);
    default: return 1;
    }
}

int List_LPop(List* list, void* elem) {
    switch (list->type) {
    case ARRAY: return ArrayList_LPop(list->impl, elem);
    case LINKED: return LinkedList_LPop(list->impl, elem);
    case DOUBLE_LINKED: return DoubleLinkedList_LPop(list->impl, elem);
    case STATIC_LINKED: return StaticLinkedList_LPop(list->impl, elem);
    case CIRCLE_LINKED: return CircleLinkedList_LPop(list->impl, elem);
    default: return 1;
    }
}

int List_Set(const List* list, size_t index, const void* elem) {
    switch (list->type) {
    case ARRAY: return ArrayList_Set(list->impl, index, elem);
    case LINKED: return LinkedList_Set(list->impl, index, elem);
    case DOUBLE_LINKED: return DoubleLinkedList_Set(list->impl, index, elem);
    case STATIC_LINKED: return StaticLinkedList_Set(list->impl, index, elem);
    case CIRCLE_LINKED: return CircleLinkedList_Set(list->impl, index, elem);
    default: return 1;
    }
}

int List_GetDel(List* list, size_t index, void* elem) {
    switch (list->type) {
    case ARRAY: return ArrayList_GetDel(list->impl, index, elem);
    case LINKED: return LinkedList_GetDel(list->impl, index, elem);
    case DOUBLE_LINKED: return DoubleLinkedList_GetDel(list->impl, index, elem);
    case STATIC_LINKED: return StaticLinkedList_GetDel(list->impl, index, elem);
    case CIRCLE_LINKED: return CircleLinkedList_GetDel(list->impl, index, elem);
    default: return 1;
    }
}

int List_GetSet(const List* list, size_t index, void* elem) {
    switch (list->type) {
    case ARRAY: return ArrayList_GetSet(list->impl, index, elem);
    case LINKED: return LinkedList_GetSet(list->impl, index, elem);
    case DOUBLE_LINKED: return DoubleLinkedList_GetSet(list->impl, index, elem);
    case STATIC_LINKED: return StaticLinkedList_GetSet(list->impl, index, elem);
    case CIRCLE_LINKED: return CircleLinkedList_GetSet(list->impl, index, elem);
    default: return 1;
    }
}

int List_FPrint(const List* list, FILE* f, ListElemToString str, size_t sizeOfElem) {
    switch (list->type) {
    case ARRAY: return ArrayList_FPrint(list->impl, f, str, sizeOfElem);
    case LINKED: return LinkedList_FPrint(list->impl, f, str, sizeOfElem);
    case DOUBLE_LINKED: return DoubleLinkedList_FPrint(list->impl, f, str, sizeOfElem);
    case STATIC_LINKED: return StaticLinkedList_FPrint(list->impl, f, str, sizeOfElem);
    case CIRCLE_LINKED: return CircleLinkedList_FPrint(list->impl, f, str, sizeOfElem);
    default: return 1;
    }
}
