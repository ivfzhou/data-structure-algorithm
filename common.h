#ifndef CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_COMMON_H
#define CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_COMMON_H

/**
 * @file common.h
 * @brief 放置公共代码定义。
 */

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>

#define is_unsigned_type(T) ((T)(-1) > 0)

#define is_float_type(T) _Generic((T)0, float: 1, double: 1, long double: 1, default: 0)

#define get_type_minimal(T)                 \
    _Generic((T)0,                          \
        _Bool: (intmax_t)0,                 \
        char: (intmax_t)CHAR_MIN,           \
        signed char: (intmax_t)SCHAR_MIN,   \
        short: (intmax_t)SHRT_MIN,          \
        int: (intmax_t)INT_MIN,             \
        long: (intmax_t)LONG_MIN,           \
        long long: (intmax_t)LLONG_MIN,     \
        float: (long double)FLT_MIN,        \
        double: (long double)DBL_MIN,       \
        long double: (long double)LDBL_MIN, \
        default: (intmax_t)0)

#define get_type_maximal(T)                        \
    _Generic((T)0,                                 \
        _Bool: (uintmax_t)1,                       \
        char: (uintmax_t)CHAR_MAX,                 \
        unsigned char: (uintmax_t)UCHAR_MAX,       \
        unsigned short: (uintmax_t)USHRT_MAX,      \
        unsigned int: (uintmax_t)UINT_MAX,         \
        unsigned long: (uintmax_t)ULONG_MAX,       \
        unsigned long long: (uintmax_t)ULLONG_MAX, \
        signed char: (uintmax_t)SCHAR_MAX,         \
        short: (uintmax_t)SHRT_MAX,                \
        int: (uintmax_t)INT_MAX,                   \
        long: (uintmax_t)LONG_MAX,                 \
        long long: (uintmax_t)LLONG_MAX,           \
        float: (long double)FLT_MAX,               \
        double: (long double)DBL_MAX,              \
        long double: (long double)LDBL_MAX)

#define check_type_range_fitness_u2u(T, U) (get_type_maximal(T) <= get_type_maximal(U))

#define check_type_range_fitness_u2s(T, U) (get_type_maximal(T) <= get_type_maximal(U))

#define check_type_range_fitness_s2s(T, U) \
    (get_type_minimal(T) >= get_type_minimal(U) && get_type_maximal(T) <= get_type_maximal(U))

#define check_type_range_fitness_s2u(T, U) 0

#define check_type_range_fitness(T, U)                                                                     \
    (is_unsigned_type(T)                                                                                   \
         ? (is_unsigned_type(U) ? check_type_range_fitness_u2u(T, U) : check_type_range_fitness_u2s(T, U)) \
         : (is_unsigned_type(U) ? check_type_range_fitness_s2u(T, U) : check_type_range_fitness_s2s(T, U)))

#define check_cast_change_u2u(v, T, U) ((T)(U)(v) != (T)(v))

#define check_cast_change_u2s(v, T, U) ((T)(U)(v) != (T)(v))

#define check_cast_change_s2s(v, T, U) ((T)(U)(v) != (T)(v))

#define check_cast_change_s2u(v, T, U) (!((v) >= 0 && (T)(U)(v) == (T)(v)))

/* 浮点 → 浮点：NaN 视为不变；否则回环比较检测精度损失或溢出。 */
#define check_cast_change_f2f(v, T, U) (!(isnan((long double)(v)) || (T)(U)(v) == (T)(v)))

/* 浮点 → 整型：NaN、无穷、越界或有小数部分都视为改变。 */
#define check_cast_change_f2i(v, T, U)                                                                         \
    (isnan((long double)(v)) || isinf((long double)(v)) || (long double)(v) < (long double)get_type_minimal(U) \
     || (long double)(v) > (long double)get_type_maximal(U) || (T)(U)(v) != (T)(v))

/* 整型 → 浮点：回环比较检测精度损失。 */
#define check_cast_change_i2f(v, T, U)                                                                                \
    ((long double)(U)(v) < (long double)get_type_minimal(T) || (long double)(U)(v) > (long double)get_type_maximal(T) \
     || (T)(U)(v) != (T)(v))

/* 整型 → 整型：原有逻辑。 */
#define check_cast_change_i2i(v, T, U)                                                                             \
    (is_unsigned_type(T) ? (is_unsigned_type(U) ? check_cast_change_u2u(v, T, U) : check_cast_change_u2s(v, T, U)) \
                         : (is_unsigned_type(U) ? check_cast_change_s2u(v, T, U) : check_cast_change_s2s(v, T, U)))

#define add_overflow_u(a, b, T) ((a) > (T)get_type_maximal(T) - (b))

#define subtract_overflow_u(a, b, T) ((a) < (b))

#define multiply_overflow_u(a, b, T) ((a) != 0 && (b) > (T)get_type_maximal(T) / (a))

#define divide_overflow_u(a, b, T) ((b) == 0)

#define add_overflow_s(a, b, T) \
    (((b) > 0 && (a) > (T)get_type_maximal(T) - (b)) || ((b) < 0 && (a) < (T)get_type_minimal(T) - (b)))

#define subtract_overflow_s(a, b, T) \
    (((b) < 0 && (a) > (T)get_type_maximal(T) + (b)) || ((b) > 0 && (a) < (T)get_type_minimal(T) + (b)))

#define multiply_overflow_s(a, b, T)                               \
    (((a) > 0 && (b) > 0 && (a) > (T)get_type_maximal(T) / (b))    \
     || ((a) > 0 && (b) < 0 && (b) < (T)get_type_minimal(T) / (a)) \
     || ((a) < 0 && (b) > 0 && (a) < (T)get_type_minimal(T) / (b)) \
     || ((a) < 0 && (b) < 0 && (a) < (T)get_type_maximal(T) / (b)))

#define divide_overflow_s(a, b, T) ((b) == 0 || ((a) == (T)get_type_minimal(T) && (b) == (T) - 1))

#define add_overflow_f(a, b, T) (!isfinite((a) + (b)))

#define subtract_overflow_f(a, b, T) (!isfinite((a) - (b)))

#define multiply_overflow_f(a, b, T) (!isfinite((a) * (b)))

#define divide_overflow_f(a, b, T) ((b) == 0 || !isfinite((a) / (b)))

/**
 * @brief 编译器断言，判断类型强转是否安全（按数值范围，不保证精度）。
 * @param[in] T 被转的类型（整型或浮点）。
 * @param[in] U 转成的类型（整型或浮点）。
 */
#define STATIC_ASSERT_CAST_FITS(T, U) \
    _Static_assert(check_type_range_fitness(T, U), "cast truncates value: " #T " -> " #U)

/**
 * @brief 运行期，判断数字强转后是否改变原值。
 * @param[in] v 数字 v 数值。
 * @param[in] T 数字 v 的类型（整型或浮点）。
 * @param[in] U 数字 v 被强转的类型（整型或浮点）。
 * @return 若强转后数字变了，返回真。
 */
#define CHECK_CAST_CHANGE(v, T, U)                                                                           \
    (is_float_type(T) ? (is_float_type(U) ? check_cast_change_f2f(v, T, U) : check_cast_change_f2i(v, T, U)) \
                      : (is_float_type(U) ? check_cast_change_i2f(v, T, U) : check_cast_change_i2i(v, T, U)))

/**
 * @brief 判断加法 a + b 是否会溢出。
 * @param[in] a 被加数。
 * @param[in] b 加数。
 * @return 1 表示溢出，0 表示安全。
 */
#define CHECK_ADD_OVERFLOW(a, b)                                      \
    _Generic(((a) + (b)),                                             \
        int: add_overflow_s(a, b, int),                               \
        unsigned int: add_overflow_u(a, b, unsigned int),             \
        long: add_overflow_s(a, b, long),                             \
        unsigned long: add_overflow_u(a, b, unsigned long),           \
        long long: add_overflow_s(a, b, long long),                   \
        unsigned long long: add_overflow_u(a, b, unsigned long long), \
        float: add_overflow_f(a, b, float),                           \
        double: add_overflow_f(a, b, double),                         \
        long double: add_overflow_f(a, b, long double))

/**
 * @brief 判断减法 a - b 是否会溢出。
 * @param[in] a 被减数。
 * @param[in] b 减数。
 * @return 1 表示溢出，0 表示安全。
 */
#define CHECK_SUBTRACT_OVERFLOW(a, b)                                      \
    _Generic(((a) - (b)),                                                  \
        int: subtract_overflow_s(a, b, int),                               \
        unsigned int: subtract_overflow_u(a, b, unsigned int),             \
        long: subtract_overflow_s(a, b, long),                             \
        unsigned long: subtract_overflow_u(a, b, unsigned long),           \
        long long: subtract_overflow_s(a, b, long long),                   \
        unsigned long long: subtract_overflow_u(a, b, unsigned long long), \
        float: subtract_overflow_f(a, b, float),                           \
        double: subtract_overflow_f(a, b, double),                         \
        long double: subtract_overflow_f(a, b, long double))

/**
 * @brief 判断乘法 a * b 是否会溢出。
 * @param[in] a 被乘数。
 * @param[in] b 乘数。
 * @return 1 表示溢出，0 表示安全。
 */
#define CHECK_MULTIPLY_OVERFLOW(a, b)                                      \
    _Generic(((a) * (b)),                                                  \
        int: multiply_overflow_s(a, b, int),                               \
        unsigned int: multiply_overflow_u(a, b, unsigned int),             \
        long: multiply_overflow_s(a, b, long),                             \
        unsigned long: multiply_overflow_u(a, b, unsigned long),           \
        long long: multiply_overflow_s(a, b, long long),                   \
        unsigned long long: multiply_overflow_u(a, b, unsigned long long), \
        float: multiply_overflow_f(a, b, float),                           \
        double: multiply_overflow_f(a, b, double),                         \
        long double: multiply_overflow_f(a, b, long double))

/**
 * @brief 判断除法 a / b 是否会溢出（含除数为 0）。
 * @param[in] a 被除数。
 * @param[in] b 除数。
 * @return 1 表示溢出或除数为 0，0 表示安全。
 */
#define CHECK_DIVIDE_OVERFLOW(a, b)                                      \
    _Generic(((a) / (b)),                                                \
        int: divide_overflow_s(a, b, int),                               \
        unsigned int: divide_overflow_u(a, b, unsigned int),             \
        long: divide_overflow_s(a, b, long),                             \
        unsigned long: divide_overflow_u(a, b, unsigned long),           \
        long long: divide_overflow_s(a, b, long long),                   \
        unsigned long long: divide_overflow_u(a, b, unsigned long long), \
        float: divide_overflow_f(a, b, float),                           \
        double: divide_overflow_f(a, b, double),                         \
        long double: divide_overflow_f(a, b, long double))

/**
 * @brief 获取指针值加数值后的指针。
 * @param[in] p 被加数值的指针。
 * @param[in] delta 指针加上的字节数。
 * @return 加上字节数后的指针。
 */
inline void* PointerAdd(const void* p, const size_t delta) { return (void*)((const unsigned char*)p + delta); }

/**
 * @brief 获取指针值减数值后的指针。
 * @param[in] p 被减数值的指针。
 * @param[in] delta 指针减去的字节数。
 * @return 减去字节数后的指针。
 */
inline void* PointerMinus(const void* p, const size_t delta) { return (void*)((const unsigned char*)p - delta); }

/**
 * @brief 获取两个指针之间的字节差。
 * @param[in] p1 被减的指针。
 * @param[in] p2 减去的指针。
 * @return p1 与 p2 之间的字节差。
 */
inline ptrdiff_t PointerDiff(const void* p1, const void* p2) {
    return (const unsigned char*)p1 - (const unsigned char*)p2;
}

#endif
