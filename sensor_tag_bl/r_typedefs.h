/********************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
********************************************************************************/

/********************************************************************************
* File Name    : r_typedefs.h
* Version      : 1.00
* Description  : This file implements general head file.
********************************************************************************/

/********************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.12.2012 1.00    First Release
********************************************************************************/
#ifndef DEFINE_H
#define DEFINE_H



/********************************************************************************
Pragma directive
********************************************************************************/
/********************************************************************************
Macro definitions
********************************************************************************/


/* Xmodem communication definitions. */
#define SOH		(0x01)
#define EOT		(0x04)
#define ACK		(0x06)
#define	NAK		(0x15)
#define CAN		(0x18)

/* Xmodem programming definitions. */
#define XM_OK				(0x00)
#define XM_ADDRESS_ERROR	(0x01)
#define XM_COMMS_ERROR		(0x02)
#define XM_TIMEOUT			(0x04)
#define XM_PROG_FAIL		(0x08)
#define	XMODEM_BUFFER_SIZE	(132)

/* TRUE and FALSE definitions */
#define FALSE	(0)
#define TRUE	(1)

/********************************************************************************
Typedef definitions
********************************************************************************/
#if 0
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed long int32_t;
typedef unsigned long uint32_t;
#endif

#endif
