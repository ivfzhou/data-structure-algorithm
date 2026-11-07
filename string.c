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
#include <stdlib.h>
#include <string.h>

#include "string.h"

static void genNext(const char* p, size_t len, int next[]) {
    size_t i = 0;
    int j = -1;
    next[0] = -1;
    while (i < len - 1) {
        if (j == -1 || p[i] == p[j]) {
            ++i, ++j;
            // next[i] = j;
            if (p[i] != p[j])
                next[i] = j;
            else
                next[i] = next[j];
        } else
            j = next[j];
    }
}

String* String_Alloc(const char* c) {
    String* s = malloc(sizeof(String));
    s->length = strlen(c);
    if (s->length) {
        s->chars = malloc(sizeof(char) * s->length);
        memcpy(s->chars, c, sizeof(char) * s->length);
    } else
        s->chars = NULL;
    return s;
}

String* String_Concat(const String* s1, const String* s2) {
    String* s = malloc(sizeof(String));
    s->length = s1->length + s2->length;
    if (s->length) {
        s->chars = malloc(sizeof(char) * s->length);
    } else {
        s->chars = NULL;
    }
    if (s1->length) memcpy(s->chars, s1->chars, s1->length * sizeof(char));
    if (s2->length) memcpy(s->chars + s1->length, s2->chars, s2->length * sizeof(char));
    return s;
}

size_t String_Len(const String* s) { return s->length; }

long long String_Index(const String* s, const String* sub) {
    if (!sub->length) return 0;
    int next[sub->length];
    genNext(sub->chars, sub->length, next);
    unsigned long long i = 0;
    unsigned long long j = 0;
    while (i < s->length && j < sub->length) {
        if (s->chars[i] == sub->chars[j]) {
            i++, j++;
        } else
            j = next[j];
    }
    if (j >= sub->length) return (long long)(i - sub->length);
    return -1;
}

String* String_Sub(const String* s, long long begin, long long end) {
    if (begin > (long long)s->length - 1 || end > (long long)s->length) return NULL;
    if (begin < -(long long)s->length) return NULL;
    if (end < -(long long)s->length) return NULL;
    if (begin < 0) {
        begin += (long long)s->length + 1;
    }
    if (end < 0) {
        end += (long long)s->length + 1;
    }

    if (end < begin) return NULL;

    String* sub = malloc(sizeof(String));
    sub->length = end - begin ? end - begin : 1;
    if (sub->length > 0) {
        sub->chars = malloc(sizeof(char) * sub->length);
        memcpy(sub->chars, s->chars + begin, sub->length * sizeof(char));
    } else
        sub->chars = NULL;
    return sub;
}

void String_Free(String* s) {
    free(s->chars);
    free(s);
}

int String_Compare(const String* s1, const String* s2) {
    for (unsigned long long i = 0; i < s1->length && i < s2->length; i++) {
        if (s1->chars[i] != s2->chars[i]) return s1->chars[i] - s2->chars[i];
    }
    return s1->length > s2->length ? 1 : s1->length == s2->length ? 0 : -1;
}

int String_FPrint(const String* s, FILE* f) {
    for (unsigned long long i = 0; i < s->length; i++) fputc(s->chars[i], f);
    return 0;
}
