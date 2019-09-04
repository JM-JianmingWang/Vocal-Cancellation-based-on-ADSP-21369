/************************************************************************
 *
 * math.h
 *
 * (c) Copyright 2001-2011 Analog Devices, Inc.  All rights reserved.
 * $Revision: 4862 $
 ************************************************************************/

#pragma once
#ifndef __NO_BUILTIN
#pragma system_header /* math.h */
#endif

#ifndef __MATH_DEFINED
#define __MATH_DEFINED

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_5_2:"ADI header will re-use identifiers")
#pragma diag(suppress:misra_rule_5_3:"ADI header will re-use identifiers")
#pragma diag(suppress:misra_rule_5_4:"ADI header will re-use identifiers")
#pragma diag(suppress:misra_rule_5_5:"ADI header will re-use identifiers")
#pragma diag(suppress:misra_rule_5_6:"ADI header will re-use identifiers")
#pragma diag(suppress:misra_rule_5_7:"ADI header will re-use identifiers")
#pragma diag(suppress:misra_rule_6_3:"ADI header allows use of basic types")
#pragma diag(suppress:misra_rule_19_4:"ADI header allows any substitution")
#pragma diag(suppress:misra_rule_19_7:"ADI header allows function macros")
#pragma diag(suppress:misra_rule_20_1:"ADI standard header")
#pragma diag(suppress:misra_rule_20_2:"ADI standard header")
#endif /* _MISRA_RULES */

/* Analog extensions to math.h are located in
 * a platform specific include file.
 * Use the compile option -D__NO_ANSI_EXTENSIONS__
 * to exclude any such extensions.
 */
#if !defined( __NO_ANSI_EXTENSIONS__ )
#if defined ( __ADSP21000__ )

#include <math_21xxx.h>

#endif    /* __ADSP21000__          */
#endif    /* __NO_ANSI_EXTENSIONS__ */


#ifndef HUGE_VAL
#ifdef __DOUBLES_ARE_FLOATS__
#define HUGE_VAL    (3.402823466e+38F)
#else
#define HUGE_VAL    (1.797693134862315708e+308L)
#endif
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* ========== FLOAT - Single Precision Functions ==================== */

       float   acosf(float x);
       float   asinf(float x);
       float   atanf(float x);
       float   atan2f(float x, float y);
       float   cosf(float x);
       float   sinf(float x);
       float   tanf(float x);
       float   coshf(float x);
       float   sinhf(float x);
       float   tanhf(float x);
       float   expf(float x);
       float   ldexpf(float x, int y);
       float   logf(float x);
       float   log10f(float x);

       float   __frexpfD(float x, int __dm *y);
       float   __frexpfP(float x, int __pm *y);

#if defined(__cplusplus)
}   /* extern "C" */
extern "C++" {

       #pragma inline
       #pragma always_inline
       float frexpf(float _a, int __dm * _b)
       {
           return __frexpfD(_a, _b);
       }

       #pragma inline
       #pragma always_inline
       float frexpf(float _a, int __pm * _b)
       {
           return __frexpfP(_a, _b);
       }

}
extern "C" {
#else

       float   frexpf(float x, int *y);
#define        frexpf(_a, _b) __adi_generic("__frexpf", (_b))((_a), (_b))

#endif

       float   __modffD(float x, float __dm *y);
       float   __modffP(float x, float __pm *y);

#if defined(__cplusplus)
}   /* extern "C" */
extern "C++" {

       #pragma inline
       #pragma always_inline
       float modff(float _a, float __dm * _b)
       {
           return  __modffD(_a, _b);
       }

       #pragma inline
       #pragma always_inline
       float modff(float _a, float __pm * _b)
       {
           return  __modffP(_a, _b);
       }
}
extern "C" {
#else

       float   modff(float x, float *y);
#define        modff(_a, _b)  __adi_generic("__modff", (_b))((_a), (_b))

#endif

       float   powf(float x, float y);
       float   sqrtf(float x);
       float   ceilf(float x);

#if !defined(__NO_BUILTIN)
#define fabsf  __builtin_fabsf
#else
       float   fabsf(float x);
#endif

       float   floorf(float x);
       float   fmodf(float x, float y);



/* ========== LONG DOUBLE - Double Precision Functions ============== */

                                  #pragma linkage_name _acos
       long double acosd(long double x);
                                  #pragma linkage_name _asin
       long double asind(long double x);
                                  #pragma linkage_name _atan
       long double atand(long double x);
                                  #pragma linkage_name _atan2
       long double atan2d(long double x, long double y);
                                  #pragma linkage_name _cos
       long double cosd(long double x);
                                  #pragma linkage_name _sin
       long double sind(long double x);
                                  #pragma linkage_name _tan
       long double tand(long double x);
                                  #pragma linkage_name _cosh
       long double coshd(long double x);
                                  #pragma linkage_name _sinh
       long double sinhd(long double x);
                                  #pragma linkage_name _tanh
       long double tanhd(long double x);
                                  #pragma linkage_name _exp
       long double expd(long double x);
                                  #pragma linkage_name _ldexp
       long double ldexpd(long double x, int y);
                                  #pragma linkage_name _log
       long double logd(long double x);
                                  #pragma linkage_name _log10
       long double log10d(long double x);

                                  #pragma linkage_name ___frexpD
       long double __frexpdD(long double x, int __dm *y);
                                  #pragma linkage_name ___frexpP
       long double __frexpdP(long double x, int __pm *y);

#if defined(__cplusplus)
}   /* extern "C" */
extern "C++" {

       #pragma inline
       #pragma always_inline
       long double frexpd(long double _a, int __dm * _b)
       {
           return  __frexpdD(_a, _b);
       }

       #pragma inline
       #pragma always_inline
       long double frexpd(long double _a, int __pm * _b)
       {
           return  __frexpdP(_a, _b);
       }

}
extern "C" {
#else

                                  #pragma linkage_name _frexp
       long double frexpd(long double x, int *y);

#define            frexpd(_a, _b)  __adi_generic("__frexpd", (_b))((_a), (_b))

#endif

                                  #pragma linkage_name ___modfD
       long double __modfdD(long double x, long double __dm *y);
                                  #pragma linkage_name ___modfP
       long double __modfdP(long double x, long double __pm *y);

#if defined(__cplusplus)
}   /* extern "C" */
extern "C++" {

       #pragma inline
       #pragma always_inline
       long double  modfd(long double _a, long double __dm * _b)
       {
           return  __modfdD(_a, _b);
       }
 
       #pragma inline
       #pragma always_inline
       long double  modfd(long double _a, long double __pm * _b)
       {
           return  __modfdP(_a, _b);
       }

}
extern "C" {
#else

                                  #pragma linkage_name _modf
       long double modfd(long double x, long double *y);

#define            modfd(_a, _b)  __adi_generic("__modfd", (_b))((_a), (_b))

#endif

                                  #pragma linkage_name _pow
       long double powd(long double x, long double y);
                                  #pragma linkage_name _sqrt
       long double sqrtd(long double x);
                                  #pragma linkage_name _ceil
       long double ceild(long double x);

#if !defined(__NO_BUILTIN)
#define fabsd  __builtin_fabs
#else
                                  #pragma linkage_name _fabs
       long double fabsd(long double x);
#endif
                                  #pragma linkage_name _floor
       long double floord(long double x);
                                  #pragma linkage_name _fmod
       long double fmodd(long double x, long double y);




/* ========== DOUBLE - Single / Double Precision Functions ========== */

#if !defined(__cplusplus)

#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _acosf
#endif
       double acos(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _asinf
#endif
       double asin(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _atanf
#endif
       double atan(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _atan2f
#endif
       double atan2(double x, double y);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _cosf
#endif
       double cos(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _sinf
#endif
       double sin(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _tanf
#endif
       double tan(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _coshf
#endif
       double cosh(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _sinhf
#endif
       double sinh(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _tanhf
#endif
       double tanh(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _expf
#endif
       double exp(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _ldexpf
#endif
       double ldexp(double x, int y);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _logf
#endif
       double log(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _log10f
#endif
       double log10(double x);

#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _frexpf
       double frexp(double x, int *y);
                 #pragma linkage_name ___frexpfD
       double __frexpD(double x, int __dm *y);
                 #pragma linkage_name ___frexpfP
       double __frexpP(double x, int __pm *y);
#else
       double frexp(double x, int *y);
       double __frexpD(double x, int __dm *y);
       double __frexpP(double x, int __pm *y);
#endif
#define       frexp(_a, _b)  __adi_generic("__frexp", (_b))((_a), (_b))

#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _modff
       double modf(double x, double *y);
                 #pragma linkage_name ___modffD
       double __modfD(double x, double __dm *y);
                 #pragma linkage_name ___modffP
       double __modfP(double x, double __pm *y);
#else
       double modf(double x, double *y);
       double __modfD(double x, double __dm *y);
       double __modfP(double x, double __pm *y);
#endif
#define       modf(_a, _b)  __adi_generic("__modf", (_b))((_a), (_b))

#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _powf
#endif
       double pow(double x, double y);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _sqrtf
#endif
       double sqrt(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _ceilf
#endif
       double ceil(double x);

#if !defined(__cplusplus)
#if defined(__DOUBLES_ARE_FLOATS__)
#if !defined(__NO_BUILTIN)
#define fabs __builtin_fabsf
#else
                 #pragma linkage_name _fabsf
       double fabs(double x);
#endif /*__NO_BUILTIN*/
#else  /*__DOUBLES_ARE_FLOATS__*/
#if !defined(__NO_BUILTIN)
#define fabs __builtin_fabs
#else
       double fabs(double x);
#endif
#endif /*__DOUBLES_ARE_FLOATS__*/
#endif /*__cplusplus*/

#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _floorf
#endif
       double floor(double x);
#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name _fmodf
#endif
       double fmod(double x, double y);


#else      /* defined(__cplusplus) */
}          /* extern "C" */
extern "C++" {

       #pragma inline
       #pragma always_inline
       float acos(float _a)
       {
           return  acosf(_a);
       
       }
       #pragma inline
       #pragma always_inline
       long double  acos(long double _a)
       {
           return  acosd(_a);

       }
       #pragma inline
       #pragma always_inline
       double  acos(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  acosf(_a);
#else
           return  acosd(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float asin(float _a)
       {
           return  asinf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  asin(long double _a)
       {
           return  asind(_a);

       }
       #pragma inline
       #pragma always_inline
       double  asin(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  asinf(_a);
#else
           return  asind(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float atan(float _a)
       {
           return  atanf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  atan(long double _a)
       {
           return  atand(_a);

       }
       #pragma inline
       #pragma always_inline
       double  atan(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  atanf(_a);
#else
           return  atand(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float atan2(float _b, float _a)
       {
           return  atan2f(_b,_a);

       }
       #pragma inline
       #pragma always_inline
       long double  atan2(long double _b, long double _a)
       {
           return  atan2d(_b,_a);

       }
       #pragma inline
       #pragma always_inline
       double  atan2(double _b, double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  atan2f(_b,_a);
#else
           return  atan2d(_b,_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float cos(float _a)
       {
           return  cosf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  cos(long double _a)
       {
           return  cosd(_a);

       }
       #pragma inline
       #pragma always_inline
       double  cos(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  cosf(_a);
#else
           return  cosd(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float sin(float _a)
       {
           return  sinf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  sin(long double _a)
       {
           return  sind(_a);

       }
       #pragma inline
       #pragma always_inline
       double  sin(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  sinf(_a);
#else
           return  sind(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float tan(float _a)
       {
           return  tanf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  tan(long double _a)
       {
           return  tand(_a);

       }
       #pragma inline
       #pragma always_inline
       double  tan(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  tanf(_a);
#else
           return  tand(_a);
#endif
       }
 
       #pragma inline
       #pragma always_inline
       float cosh(float _a)
       {
           return  coshf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  cosh(long double _a)
       {
           return  coshd(_a);

       }
       #pragma inline
       #pragma always_inline
       double  cosh(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  coshf(_a);
#else
           return  coshd(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float sinh(float _a)
       {
           return  sinhf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  sinh(long double _a)
       {
           return  sinhd(_a);

       }
       #pragma inline
       #pragma always_inline
       double  sinh(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  sinhf(_a);
#else
           return  sinhd(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float tanh(float _a)
       {
           return  tanhf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  tanh(long double _a)
       {
           return  tanhd(_a);

       }
       #pragma inline
       #pragma always_inline
       double  tanh(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  tanhf(_a);
#else
           return  tanhd(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float exp(float _a)
       {
           return  expf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  exp(long double _a)
       {
           return  expd(_a);

       }
       #pragma inline
       #pragma always_inline
       double  exp(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  expf(_a);
#else
           return  expd(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float ldexp(float _a, int _b)
       {
           return  ldexpf(_a,_b);

       }
       #pragma inline
       #pragma always_inline
       long double  ldexp(long double _a, int _b)
       {
           return  ldexpd(_a,_b);

       }
       #pragma inline
       #pragma always_inline
       double  ldexp(double _a, int _b)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  ldexpf(_a,_b);
#else
           return  ldexpd(_a,_b);
#endif
       }

       #pragma inline
       #pragma always_inline
       float log(float _a)
       {
           return  logf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  log(long double _a)
       {
           return  logd(_a);

       }
       #pragma inline
       #pragma always_inline
       double  log(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  logf(_a);
#else
           return  logd(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float log10(float _a)
       {
           return  log10f(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  log10(long double _a)
       {
           return  log10d(_a);

       }
       #pragma inline
       #pragma always_inline
       double  log10(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  log10f(_a);
#else
           return  log10d(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float frexp(float _a, int __dm * _b)
       {
           return  __frexpfD(_a, _b);
       }
       #pragma inline
       #pragma always_inline
       float frexp(float _a, int __pm * _b)
       {
           return  __frexpfP(_a, _b);
       }
       #pragma inline
       #pragma always_inline
       long double frexp(long double _a, int __dm * _b)
       {
           return  __frexpdD(_a, _b);
       }
       #pragma inline
       #pragma always_inline
       long double frexp(long double _a, int __pm * _b)
       {
           return  __frexpdP(_a, _b);
       }
       #pragma inline
       #pragma always_inline
       double frexp(double _a, int __dm * _b)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  __frexpfD(_a, _b);
#else
           return  __frexpdD(_a, _b);
#endif
       }
       #pragma inline
       #pragma always_inline
       double frexp(double _a, int __pm * _b)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  __frexpfP(_a, _b);
#else
           return  __frexpdP(_a, _b);
#endif
       }

       #pragma inline
       #pragma always_inline
       float modf(float _a, float __dm * _b)
       {
           return  __modffD(_a, _b);
       }
       #pragma inline
       #pragma always_inline
       float modf(float _a, float __pm * _b)
       {
           return  __modffP(_a, _b);
       }
       #pragma inline
       #pragma always_inline
       long double modf(long double _a, long double __dm * _b)
       {
           return  __modfdD(_a, _b);
       }
       #pragma inline
       #pragma always_inline
       long double modf(long double _a, long double __pm * _b)
       {
           return  __modfdP(_a, _b);
       }

#if defined(__DOUBLES_ARE_FLOATS__)
                 #pragma linkage_name ___modffD
       double __modfD(double, double __dm *);
                 #pragma linkage_name ___modffP
       double __modfP(double, double __pm *);
#else
                 #pragma linkage_name ___modfD
       double __modfD(double, double __dm *);
                 #pragma linkage_name ___modfP
       double __modfP(double, double __pm *);
#endif
       #pragma inline
       #pragma always_inline
       double modf(double _a, double __dm * _b)
       {
           return  __modfD(_a, _b);
       }
       #pragma inline
       #pragma always_inline
       double modf(double _a, double __pm * _b)
       {
           return  __modfP(_a, _b);
       }

       #pragma inline
       #pragma always_inline
       float pow(float _b, float _a)
       {
           return  powf(_b,_a);

       }
       #pragma inline
       #pragma always_inline
       long double  pow(long double _b, long double _a)
       {
           return  powd(_b,_a);

       }
       #pragma inline
       #pragma always_inline
       double  pow(double _b, double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  powf(_b,_a);
#else
           return  powd(_b,_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float sqrt(float _a)
       {
           return  sqrtf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  sqrt(long double _a)
       {
           return  sqrtd(_a);

       }
       #pragma inline
       #pragma always_inline
       double  sqrt(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  sqrtf(_a);
#else
           return  sqrtd(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float ceil(float _a)
       {
           return  ceilf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  ceil(long double _a)
       {
           return  ceild(_a);

       }
       #pragma inline
       #pragma always_inline
       double  ceil(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  ceilf(_a);
#else
           return  ceild(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float abs(float _a)
       {
           return  fabsf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  abs(long double _a)
       {
           return  fabsd(_a);

       }
       #pragma inline
       #pragma always_inline
       double  abs(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  fabsf(_a);
#else
           return  fabsd(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float fabs(float _a)
       {
           return  fabsf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  fabs(long double _a)
       {
           return  fabsd(_a);

       }
       #pragma inline
       #pragma always_inline
       double  fabs(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  fabsf(_a);
#else
           return  fabsd(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float floor(float _a)
       {
           return  floorf(_a);

       }
       #pragma inline
       #pragma always_inline
       long double  floor(long double _a)
       {
           return  floord(_a);

       }
       #pragma inline
       #pragma always_inline
       double  floor(double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  floorf(_a);
#else
           return  floord(_a);
#endif
       }

       #pragma inline
       #pragma always_inline
       float fmod(float _b, float _a)
       {
           return  fmodf(_b,_a);

       }
       #pragma inline
       #pragma always_inline
       long double  fmod(long double _b, long double _a)
       {
           return  fmodd(_b,_a);

       }
       #pragma inline
       #pragma always_inline
       double  fmod(double _b, double _a)
       {
#if defined(__DOUBLES_ARE_FLOATS__)
           return  fmodf(_b,_a);
#else
           return  fmodd(_b,_a);
#endif
       }

}          /* extern "C++" */
#endif     /* defined(__cplusplus) */

#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */

#endif     /* __MATH_DEFINED */
