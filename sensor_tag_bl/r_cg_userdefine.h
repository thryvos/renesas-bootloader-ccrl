/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_userdefine.h
* Version      : CodeGenerator for RL78/G13 V2.03.02.01 [15 May 2015]
* Device(s)    : R5F100BE
* Tool-Chain   : CCRL
* Description  : This file includes user definition.
* Creation Date: 6/9/2015
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */
#define NORMAL_END         (0x00U)          /* Normal end value */
#define ERROR              (0xFFU)          /* Error value */
#define NO_RECEIVE         (0x00U)          /* The state where data is not received */
#define START_CODE         (0x01U)          /* The state which received start code */
#define PACKET_SIZE        (0x02U)          /* The state which received packet size */
#define START              (0x02U)          /* START command */
#define WRITE              (0x03U)          /* WRITE command */
#define END                (0x04U)          /* END command */
#define FULL_SPEED_MODE    (0x00U)          /* Initial setting value ( full-speed mode ) */
#define FREQUENCY_32M      (0x20U)          /* Initial setting value ( frequency ) */
#define INTERNAL_MODE      (0x01U)          /* Initial setting value ( internal mode ) */
#define START_BLOCK_NUM    (0x00U)          /* Block's start number */
#define END_BLOCK_NUM      (0x3FU)          /* Block's end number */
#define BLOCK_SIZE         (0x400U)         /* Size of one block */
#define TXSIZE             (0x01U)          /* Size of send data */
#define RXSIZE             (0x102U)         /* Size of receive buffer */
/* End user code. Do not edit comment generated here */
#endif
