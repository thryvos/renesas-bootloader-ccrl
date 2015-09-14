/******************************************************************************
*
* @file    $Name$
* @version $Revision$
* @date    $LastChangedDate$
*
* @Copyright 2015 - JIM.
*  This material is protected by copyright law. It is unlawful
*  to copy it.
*
* This document contains confidential information. It is not to be
* disclosed or used except in accordance with applicable contracts
* or agreements. This document must be rendered illegible when
* being discarded.
* 
* @remarks
* Modification History
* -------------------------
* See Version Control System History.
*
* @file This file contains the template class.
*
******************************************************************************/

#ifndef __TYPEDEF_H
#define __TYPEDEF_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*                              Include File                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                      Global Macro or Enum Definition                      */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* General data types                                                        */
/*---------------------------------------------------------------------------*/
/* Read & Write */
typedef char                                char_t;
typedef signed char        					s8_t;
typedef signed short                        s16_t;
typedef signed long              			s32_t;
typedef unsigned char               		u8_t;
typedef unsigned short            			u16_t;
typedef unsigned long               		u32_t;
typedef float                     			float32_t;
typedef double                      		double64_t;

/*
 * Read or Write but prevent the (pseudo)compiler from applying any
 * optimizations on the code that assume values of variables cannot
 * change "on their own."
 */
typedef volatile signed char                sv8_t;
typedef volatile signed short          		sv16_t;
typedef volatile signed long                sv32_t;
typedef volatile unsigned char				uv8_t;
typedef volatile unsigned short				uv16_t;
typedef volatile unsigned long				uv32_t;
typedef volatile float						vfloat32_t;
typedef volatile double						vdouble64_t;

/* Read Only */
typedef signed char const					sc8_t;
typedef signed short const 					sc16_t;
typedef signed long const					sc32_t;
typedef unsigned char const					uc8_t;
typedef unsigned short const                uc16_t;
typedef unsigned long const					uc32_t;
typedef float const							cfloat32_t;
typedef double const                        cdouble64_t;

/* Read Only */
typedef volatile signed char const			svc8_t;
typedef volatile signed short const			svc16_t;
typedef volatile signed long const			svc32_t;
//typedef volatile signed long long const		sintvc64_t;
typedef volatile unsigned char const        uvc8_t;
typedef volatile unsigned short const		uvc16_t;
typedef volatile unsigned long const        uvc32_t;
//typedef volatile unsigned long long const	uintvc64_t;
typedef volatile float const				vcfloat32_t;
typedef volatile double const				vcdouble64_t;

typedef enum {FALSE = 0, TRUE = !FALSE} bool_t;

typedef void (*func_t)(void);

/*---------------------------------------------------------------------------*/
/*     Assert                                                        		 */
/*---------------------------------------------------------------------------*/

#ifdef USE_FULL_ASSERT

  #define ASSERT(x)   ((x) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))

#else
  #define ASSERT(x) ((void)0)  
#endif

/*---------------------------------------------------------------------------*/
/*     Debug                                                       			 */
/*---------------------------------------------------------------------------*/
#if 0
#ifdef DBG_PRINT_USE
#define DBG_PRINT(x)    printf(x)
#else
#define DBG_PRINT(x)    ((void)0)
#endif
#endif

/*---------------------------------------------------------------------------*/
/*     General Macro                                              			 */
/*---------------------------------------------------------------------------*/
#define NULL    	0

#define EXPORT
#define IMPORT		extern
#define LOCAL  		static
#define CONST    	const
#define VOID     	void

//#define NOP()   	Nop()

#define U8_MAX     	((U8)255)
#define S8_MAX     	((S8)127)
#define S8_MIN     	((S8)-128)
#define U16_MAX    	((U16)65535u)
#define S16_MAX    	((S16)32767)
#define S16_MIN    	((S16)-32768)
#define U32_MAX   	((U32)4294967295uL)
#define S32_MAX    	((S32)2147483647)
#define S32_MIN    	((S32)-2147483648)

/*****************************************************************************/
/*					 Global Structure or Union Definition					 */
/*****************************************************************************/
typedef union
{
    u16_t       val;
    u8_t        u8[2];

    struct
    {
        u8_t    hi;
        u8_t    lo;
    } byte;
} u16u_t;

typedef union
{
    s16_t       val;
    s8_t        s8[2];

    struct
    {
        s8_t    hi;
        s8_t    lo;
    } byte;
} s16u_t;

typedef union
{
    u32_t		val;
    u16_t   	u16[2];
    u8_t  		u8[4];

    struct
    {
      u16_t     lo;
      u16_t     hi;
    } word;

    struct
    {
      u8_t    	lo;
      u8_t    	hi;
      u8_t    	up;
      u8_t    	mo;
    } byte;

} u32u_t;

/*****************************************************************************/
/*						 Global Variable Declaration  						 */
/*****************************************************************************/


/*****************************************************************************/
/*						    Configuration Checking 							 */
/*****************************************************************************/


/*****************************************************************************/
/*						 Global Function Declaration 						 */
/*****************************************************************************/
/******************************************************************************
 * @brief   :
 *
 * @param   :   None.
 * @return  :	None.
 * @remarks :	None.
 *****************************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TYPEDEF_H */
/* EOF */
