#ifndef CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_COMMON_H
#define CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_COMMON_H

/**
 * @file common.h
 * @brief 放置公共代码定义。
 */

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief 判断类型 T 是否为无符号类型。常量表达式。
 * @param[in] T 整数类型。
 * @retval 1 T 是无符号。
 * @retval 0 T 是有符号。
 */
#define IS_UNSIGNED_TYPE(T) ((T)(-1) > 0)

/**
 * @brief 类型 T 的最小值，以 intmax_t 表示；无符号类型最小值为 0。
 * @param[in] T 整数类型。
 * @return intmax_t 类型的数值。
 */
#define GET_TYPE_MINIMAL(T)               \
    _Generic((T)0,                        \
        _Bool: (intmax_t)0,               \
        char: (intmax_t)CHAR_MIN,         \
        signed char: (intmax_t)SCHAR_MIN, \
        short: (intmax_t)SHRT_MIN,        \
        int: (intmax_t)INT_MIN,           \
        long: (intmax_t)LONG_MIN,         \
        long long: (intmax_t)LLONG_MIN,   \
        default: (intmax_t)0)

/**
 * @brief 类型 T 的最大值，以 uintmax_t 表示。
 * @param T 整数类型。
 * @return uintmax_t 类型的数值。
 */
#define GET_TYPE_MAXIMAL(T)                        \
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
        long long: (uintmax_t)LLONG_MAX)

/**
 * @brief 判断无符号整型 T 强转成无符号整型 U 时，值域是否包含。
 * @param[in] T 被转的整型类型。
 * @param[in] U 转成的整型类型。
 * @return 若值域包含，返回真。
 */
#define CHECK_TYPE_RANGE_FITNESS_U2U(T, U) (GET_TYPE_MAXIMAL(T) <= GET_TYPE_MAXIMAL(U))

/**
 * @brief 判断无符号整型 T 强转成有符号整型 U 时，值域是否包含。只需比上界。
 * @param[in] T 被转的整型类型。
 * @param[in] U 转成的整型类型。
 * @return 若值域包含，返回真。
 */
#define CHECK_TYPE_RANGE_FITNESS_U2S(T, U) (GET_TYPE_MAXIMAL(T) <= GET_TYPE_MAXIMAL(U))

/**
 * @brief 判断有符号整型 T 强转成有符号整型 U 时，值域是否包含。
 * @param[in] T 被转的整型类型。
 * @param[in] U 转成的整型类型。
 * @return 若值域包含，返回真。
 */
#define CHECK_TYPE_RANGE_FITNESS_S2S(T, U) \
    (GET_TYPE_MINIMAL(T) >= GET_TYPE_MINIMAL(U) && GET_TYPE_MAXIMAL(T) <= GET_TYPE_MAXIMAL(U))

/* 4) 有符号 -> 无符号：有符号必然有负值，永远无法被无符号完全包含 */
/**
 * @brief 判断有符号整型 T 强转成无符号整型 U 时，值域是否包含。有符号必然有负值，永远无法被无符号完全包含。
 * @param[in] T 被转的整型类型。
 * @param[in] U 转成的整型类型。
 * @return 恒返回假。
 */
#define CHECK_TYPE_RANGE_FITNESS_S2U(T, U) 0

/**
 * @brief 判断整型类型强转是否安全。
 * @param[in] T 被转的整型类型。
 * @param[in] U 转成的整型类型。
 */
#define CHECK_TYPE_RANGE_FITNESS(T, U)                                                                         \
    (T_UNSIGNED(T) ? (T_UNSIGNED(U) ? CHECK_TYPE_RANGE_FITNESS_U2U(T, U) : CHECK_TYPE_RANGE_FITNESS_U2S(T, U)) \
                   : (T_UNSIGNED(U) ? CHECK_TYPE_RANGE_FITNESS_S2U(T, U) : CHECK_TYPE_RANGE_FITNESS_S2S(T, U)))

/* 编译期断言：不满足直接编译报错 */
/**
 * @brief 编译器断言，判断整型类型强转是否安全。
 * @param[in] T 被转的整型类型。
 * @param[in] U 转成的整型类型。
 */
#define STATIC_ASSERT_CAST_FITS(T, U) \
    _Static_assert(CHECK_TYPE_RANGE_FITNESS(T, U), "cast truncates value: " #T " -> " #U)

/**
 * @brief 判断无符号整型 T 的数值 v 强转成无符号整型 U 时，是否仍等于原值 v。
 * @param[in] v 整型 v 数值。
 * @param[in] T 整型 v 的类型。
 * @param[in] U 整型 v 被强转的类型。
 * @return 若强转后数字没变，返回真。
 */
#define CHECK_CAST_CHANGE_U2U(v, T, U) ((T)(U)(v) == (T)(v))

/**
 * @brief 判断无符号整型 T 的数值 v 强转成有符号整型 U 时，是否仍等于原值 v。
 * @param[in] v 整型 v 数值。
 * @param[in] T 整型 v 的类型。
 * @param[in] U 整型 v 被强转的类型。
 * @return 若强转后数字没变，返回真。
 */
#define CHECK_CAST_CHANGE_U2S(v, T, U) ((T)(U)(v) == (T)(v))

/**
 * @brief 判断有符号整型 T 的数值 v 强转成有符号整型 U 时，是否仍等于原值 v。
 * @param[in] v 整型 v 数值。
 * @param[in] T 整型 v 的类型。
 * @param[in] U 整型 v 被强转的类型。
 * @return 若强转后数字没变，返回真。
 */
#define CHECK_CAST_CHANGE_S2S(v, T, U) ((T)(U)(v) == (T)(v))

/**
 * @brief 判断有符号整型 T 的数值 v 强转成有符号整型 U 时，是否仍等于原值 v。
 * @details 必须额外加 (v) >= 0 判断：负值转到无符号再转回，在补码平台上位模式不变、会误判为没变。
 * @param[in] v 整型 v 数值。
 * @param[in] T 整型 v 的类型。
 * @param[in] U 整型 v 被强转的类型。
 * @return 若强转后数字没变，返回真。
 */
#define CHECK_CAST_CHANGE_S2U(v, T, U) ((v) >= 0 && (T)(U)(v) == (T)(v))

/**
 * @brief 运行期，判断整型数字强转后是否改变原值。
 * @param[in] v 整型 v 数值。
 * @param[in] T 整型 v 的类型。
 * @param[in] U 整型 v 被强转的类型。
 * @return 若强转后数字没变，返回真。
 */
#define CHECK_CAST_CHANGE(v, T, U)                                                                                 \
    (IS_UNSIGNED_TYPE(T) ? (IS_UNSIGNED_TYPE(U) ? CHECK_CAST_CHANGE_U2U(v, T, U) : CHECK_CAST_CHANGE_U2S(v, T, U)) \
                         : (IS_UNSIGNED_TYPE(U) ? CHECK_CAST_CHANGE_S2U(v, T, U) : CHECK_CAST_CHANGE_S2S(v, T, U)))

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
