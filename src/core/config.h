/* This file contains various preprocessor definitions and macros
 * that can be defined when compiling Malachite to control what is
 * compiled, and enable non-ANSI C features
 */

/* Hint to the compiler to inline the given function */
/* #define MCH_INLINE */
#ifndef MCH_INLINE
#define MCH_INLINE
#endif

/* Hint to the compiler to forcefully inline a function */
/* #define MCH_FORCE_INLINE */

/* If the 'force inline' hint isn't given, define it to be the regular
 * inline hint.
 */
#ifndef MCH_FORCE_INLINE
#define MCH_FORCE_INLINE MCH_INLINE
#endif

/* Hint to the compiler that certain function parameters will not
 * alias.  Could be defined as, for example, the C99 'restrict'
 * keyword
 */
/* #define MCH_RESTRICT */
#ifndef MCH_RESTRICT
#define MCH_RESTRICT
#endif

/* Hint to the compiler that a given branch is likely to be taken.
 * For example, GCC's __builtin_expect.
 */
#define likely(x)   x
#define unlikely(x) x

/* Type representing a basic numerical type */
#define MCH_TY_NUMBER       signed int

/* Type representing a floating-point type */
#define MCH_TY_FLOAT        double


/* Directives controlling what components of Malachite are enabled */
#define MCH_INCLUDE_COMPILER        /* Include compiler */
/* TODO: these aren't used right now */
