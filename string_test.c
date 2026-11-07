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

#include <assert.h>
#include <stdio.h>

#include "string.h"

int main(void) {
    String* s = String_Alloc("abcdefj123456");
    assert(s);
    String* s0 = String_Alloc("dlkasj9fhsafbv93");
    assert(s0);
    String* s1 = String_Concat(s, s0);
    assert(s1);
    assert(String_Compare(s, s0) < 0);
    String* s2 = String_Alloc("abcdefj123456dlkasj9fhsafbv93");
    assert(s2);
    assert(String_Compare(s1, s2) == 0);
    // string_fprint(s2, stdout);
    // puts("");
    String* s3 = String_Sub(s2, 0, 13);
    assert(s3);
    assert(String_Len(s3) == 13);
    assert(String_Compare(s3, s) == 0);
    String* s4 = String_Sub(s2, -17, -1);
    assert(s4);
    assert(String_Len(s4) == 16);
    assert(String_Compare(s4, s0) == 0);
    assert(String_Index(s2, s0) == 13);
    String* s5 = String_Alloc("");
    assert(String_Index(s2, s5) == 0);
    String* s6 = String_Alloc("321");
    assert(String_Index(s2, s6) == -1);
    String_Free(s);
    String_Free(s0);
    String_Free(s1);
    String_Free(s2);
    String_Free(s3);
    String_Free(s4);
    String_Free(s5);
    String_Free(s6);

    s = String_Alloc("abccbakkdiur");
    s1 = String_Alloc("cba");
    assert(String_Index(s, s1) == 3);
    String_Free(s);
    String_Free(s1);
}
