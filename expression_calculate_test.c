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

// 算术表达式运算。

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

static _Bool isOperator(char c) {
    const static char operators[] = "+-*/()";
    int i = 0;
    char o;
    while ((o = operators[i++]))
        if (c == o) return 1;
    return 0;
}

static int isPrecede(char s1, char s2) {
    if (!s1) return -1;
    switch (s1) {
    case '+':
    case '-':
        switch (s2) {
        case '+':
        case '-':
        case ')': return 1;
        case '/':
        case '(':
        case '*': return -1;
        }
        break;
    case '/':
    case '*':
        switch (s2) {
        case '+':
        case '-':
        case ')': return 1;
        case '(':
        case '/':
        case '*': return -1;
        }
        break;
    case '(':
        switch (s2) {
        case ')': return 0;
        default: return -1;
        }
    case ')': return 1;
    }
    raise(SIGABRT);
    return 0;
}

static long double calculate(long double x, char optr, long double y) {
    switch (optr) {
    case '+': return x + y;
    case '-': return x - y;
    case '/': return x / y;
    case '*': return x * y;
    }
    raise(SIGABRT);
    return 0;
}

long double expressionCalculate(const char* expr) {
    Stack* operator = Stack_Alloc(sizeof(char), 1024);
    Stack* operand = Stack_Alloc(sizeof(long double), 1024);

    size_t len = strlen(expr);
    for (int i = 0; i < len; i++) {
        char c = expr[i];
        if (!isOperator(c)) {
            char tmp[] = {c, '\0'};
            long double num = strtold(tmp, NULL);
            Stack_Push(operand, &num);
        } else {
            char optr;
            if (Stack_PeekTop(operator, &optr)) optr = '\0';
            switch (isPrecede(optr, c)) {
            case 1:
                Stack_Pop(operator, &optr);
                long double x, y;
                Stack_Pop(operand, &x);
                Stack_Pop(operand, &y);
                long double res = calculate(y, optr, x);

                // 去除括号
                if (c == ')') {
                    Stack_Pop(operator, &optr);
                    if (optr != '(') {
                        fprintf(stderr, "括号不匹配");
                        raise(SIGABRT);
                    }
                }

                Stack_Push(operand, &res);
                break;
            case -1: Stack_Push(operator, &c); break;
            case 0: Stack_Pop(operator, &optr); break;
            }
        }
    }

    while (!Stack_IsEmpty(operator)) {
        char optr;
        Stack_Pop(operator, &optr);
        long double x, y;
        Stack_Pop(operand, &x);
        Stack_Pop(operand, &y);
        long double res = calculate(y, optr, x);
        Stack_Push(operand, &res);
    }

    long double count = 0;
    Stack_Pop(operand, &count);

    if (!Stack_IsEmpty(operator) || !Stack_IsEmpty(operand)) {
        fprintf(stderr, "算式非法");
        raise(SIGABRT);
    }

    Stack_Free(operand);
    Stack_Free(operator);
    return count;
}

int main(void) {
    assert(expressionCalculate("1+1") == 2);
    assert(expressionCalculate("1-1") == 0);
    assert(expressionCalculate("9/3") == 3);
    assert(expressionCalculate("3*3") == 9);
    assert(expressionCalculate("3+3/3") == 4);
    assert(expressionCalculate("(1+3)*4") == 16);
    assert(expressionCalculate("((1+3)/2)*4") == 8);
    assert(expressionCalculate("((1+3)/2)*(4-2)") == 4);
}
