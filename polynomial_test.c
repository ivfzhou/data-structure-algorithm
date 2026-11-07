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

#include <stdarg.h>
#include <stdio.h>

#include "list.h"

// 项。
typedef struct {
    long double coefficient;
    int exponent;
} Item;

// 多项式。
typedef List Polynomial;

static void add(Polynomial* poly, Item* itm) {
    if (itm->coefficient == 0.0) return;
    size_t len = List_Len(poly);

    Item tmp;
    for (int i = 0; i < len; i++) {
        List_Get(poly, i, &tmp);
        if (tmp.exponent == itm->exponent) {
            long double coefficient = tmp.coefficient + itm->coefficient;
            if (coefficient != 0.0) {
                Item newItem = {
                    .coefficient = coefficient,
                    .exponent = tmp.exponent,
                };
                List_Set(poly, i, &newItem);
            } else {
                List_Del(poly, i);
            }
            return;
        } else if (tmp.exponent > itm->exponent) {
            List_Insert(poly, i, itm);
            return;
        }
    }

    List_RPush(poly, itm);
}

// 新建多项式。
Polynomial* Polynomial_New(int num, ...) {
    va_list args;
    va_start(args, num);

    List* newPolynomial = List_Alloc(sizeof(Item), ARRAY);

    for (int i = 0; i < num; i++) {
        Item* itm = va_arg(args, Item*);
        add(newPolynomial, itm);
    }

    va_end(args);
    return newPolynomial;
}

// 销毁多项式。
void Polynomial_Free(Polynomial* poly) { List_Free(poly); }

// 多项式相加。
Polynomial* Polynomial_Add(const Polynomial* x, const Polynomial* y) {
    Polynomial* newPolynomial = List_Alloc(sizeof(Item), ARRAY);

    size_t len = List_Len(x);
    for (int i = 0; i < len; i++) {
        Item item;
        List_Get(x, i, &item);
        add(newPolynomial, &item);
    }

    len = List_Len(y);
    for (int i = 0; i < len; i++) {
        Item item;
        List_Get(y, i, &item);
        add(newPolynomial, &item);
    }

    return newPolynomial;
}

// 多项式相减。
Polynomial* Polynomial_Subtract(const Polynomial* x, const Polynomial* y) {
    Polynomial* newPolynomial = List_Alloc(sizeof(Item), ARRAY);

    size_t len = List_Len(x);
    Item item;
    for (int i = 0; i < len; i++) {
        List_Get(x, i, &item);
        add(newPolynomial, &item);
    }

    len = List_Len(y);
    for (int i = 0; i < len; i++) {
        List_Get(y, i, &item);
        item.coefficient = -item.coefficient;
        add(newPolynomial, &item);
    }

    return newPolynomial;
}

// 多项式相乘。
Polynomial* Polynomial_Multiply(const Polynomial* x, const Polynomial* y) {
    Polynomial* newPolynomial = List_Alloc(sizeof(Item), ARRAY);

    size_t lenX = List_Len(x);
    size_t lenY = List_Len(y);
    Item itemX;
    Item itemY;
    for (int i = 0; i < lenX; i++) {
        List_Get(x, i, &itemX);
        for (int j = 0; j < lenY; j++) {
            List_Get(y, j, &itemY);
            Item newItem = {
                .coefficient = itemX.coefficient * itemY.coefficient,
                .exponent = itemX.exponent * itemY.exponent,
            };
            add(newPolynomial, &newItem);
        }
    }

    return newPolynomial;
}

// 打印多项式。
void Polynomial_FPrint(const Polynomial* poly, FILE* f) {
    size_t len = List_Len(poly);

    for (int i = 0; i < len; i++) {
        Item item;
        List_Get(poly, i, &item);

        if (item.coefficient > 0) {
            if (i != 0)
                fprintf(f, " + %.2Lf", item.coefficient);
            else
                fprintf(f, "%.2Lf", item.coefficient);
        } else {
            if (i == 0)
                fprintf(f, "-%.2Lf", -item.coefficient);
            else
                fprintf(f, " - %.2Lf", -item.coefficient);
        }

        if (item.exponent != 0) {
            fprintf(f, "x");
            int max = 10;
            while (item.exponent / max != 0) max *= 10;
            if (item.exponent < 0) fprintf(f, "⁻");
            // else fprintf(f, "⁺");
            do {
                switch ((item.exponent < 0 ? -item.exponent : item.exponent) / (max / 10) % 10) {
                case 0: fprintf(f, "%s", "⁰"); break;
                case 1: fprintf(f, "%s", "¹"); break;
                case 2: fprintf(f, "%s", "²"); break;
                case 3: fprintf(f, "%s", "³"); break;
                case 4: fprintf(f, "%s", "⁴"); break;
                case 5: fprintf(f, "%s", "⁵"); break;
                case 6: fprintf(f, "%s", "⁶"); break;
                case 7: fprintf(f, "%s", "⁷"); break;
                case 8: fprintf(f, "%s", "⁸"); break;
                case 9: fprintf(f, "%s", "⁹"); break;
                }
            } while ((max /= 10) != 1);
        }
    }
    puts("");
}

int main(void) {
    Polynomial* poly = Polynomial_New(3,
                                      &(Item){
                                          .coefficient = 2,
                                          .exponent = 1,
                                      },
                                      &(Item){
                                          .coefficient = 3,
                                          .exponent = 2,
                                      },
                                      &(Item){
                                          .coefficient = 4,
                                          .exponent = -3,
                                      });
    Polynomial* poly0 = Polynomial_New(3,
                                       &(Item){
                                           .coefficient = 2,
                                           .exponent = 1,
                                       },
                                       &(Item){
                                           .coefficient = -3,
                                           .exponent = 2,
                                       },
                                       &(Item){
                                           .coefficient = 4,
                                           .exponent = -3,
                                       });

    Polynomial* poly1 = Polynomial_Add(poly, poly0);
    // polynomial_fprint(poly1, stdout);

    Polynomial* poly2 = Polynomial_Multiply(poly, poly0);
    // polynomial_fprint(poly2, stdout);

    Polynomial* poly3 = Polynomial_Subtract(poly, poly0);
    // polynomial_fprint(poly3, stdout);

    Polynomial_Free(poly);
    Polynomial_Free(poly0);
    Polynomial_Free(poly1);
    Polynomial_Free(poly2);
    Polynomial_Free(poly3);
}
