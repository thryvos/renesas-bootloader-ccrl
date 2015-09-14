/*==============================================================================================*/
/* Project      = Flash self-programming library, MF3 single voltage flash                      */
/* Module       = fsl_types.h                                                                   */
/* Device:      = RL78                                                                          */
/* Version      = V2.21                                                                         */
/*==============================================================================================*/
/* DISCLAIMER                                                                                   */
/* This software is supplied by Renesas Electronics Corporation and is only                     */
/* intended for use with Renesas products. No other uses are authorized. This                   */
/* software is owned by Renesas Electronics Corporation and is protected under                  */
/* all applicable laws, including copyright laws.                                               */
/* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING                  */
/* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT                      */
/* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE                   */
/* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.                          */
/* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS                       */
/* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE                  */
/* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR                   */
/* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE                  */
/* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.                                             */
/* Renesas reserves the right, without notice, to make changes to this software                 */
/* and to discontinue the availability of this software. By using this software,                */
/* you agree to the additional terms and conditions found by accessing the                      */
/* following link:                                                                              */
/* http://www.renesas.com/disclaimer                                                            */
/*                                                                                              */
/* Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.                     */
/*==============================================================================================*/
/* Purpose:                                                                                     */
/*              definition of types used by the library                                         */
/*                                                                                              */
/*==============================================================================================*/

#ifndef __FSL_TYPES_H_INCLUDED
#define __FSL_TYPES_H_INCLUDED


/*==============================================================================================*/
/* unsigned type definitions                                                                    */
/*==============================================================================================*/
typedef unsigned char                       fsl_u08;
typedef unsigned int                        fsl_u16;
typedef unsigned long int                   fsl_u32;


/*==============================================================================================*/
/* global constant definitions                                                                  */
/*==============================================================================================*/


/*==============================================================================================*/
/* global type definitions                                                                      */
/*==============================================================================================*/

/* FSL descriptor type */
typedef struct
{                                                       /* ---------------------------------------------- */
        fsl_u08         fsl_flash_voltage_u08;          /* 1, setting of flash voltage mode               */
        fsl_u08         fsl_frequency_u08;              /* 1, CPU frequency (MHz)                         */
        fsl_u08         fsl_auto_status_check_u08;      /* 1, setting of status check mode                */
} fsl_descriptor_t;                                     /*------------------------------------------------*/
                                                        /* 3 bytes in total                               */
                                                        /*------------------------------------------------*/


/* FSL write type */
typedef struct
{                                                       /* ---------------------------------------------- */
        fsl_u08 __near  *fsl_data_buffer_p_u08;         /* 2, pointer to data buffer                      */
        fsl_u32         fsl_destination_address_u32;    /* 4, starting address to write data              */
        fsl_u08         fsl_word_count_u08;             /* 1, number of words to write data               */
} fsl_write_t;                                          /*------------------------------------------------*/
                                                        /* 7 bytes in total                               */
                                                        /*------------------------------------------------*/


/* FSL get block end address type */
typedef struct
{                                                       /* ---------------------------------------------- */
        fsl_u32         fsl_destination_address_u32;    /* 4, destination variable for the end address    */
        fsl_u16         fsl_block_u16;                  /* 2, block number                                */
} fsl_getblockendaddr_t;                                /*------------------------------------------------*/
                                                        /* 6 bytes in total                               */
                                                        /*------------------------------------------------*/


/* FSL get and set flash shield window type */
typedef struct
{                                                       /* ---------------------------------------------- */
        fsl_u16         fsl_start_block_u16;            /* 2, start block number of FSW (destination)     */
        fsl_u16         fsl_end_block_u16;              /* 2, end block number of FSW (destination)       */
} fsl_fsw_t;                                            /*------------------------------------------------*/
                                                        /* 4 bytes in total                               */
                                                        /*------------------------------------------------*/


#endif
