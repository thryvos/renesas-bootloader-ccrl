/*==============================================================================================*/
/* Project      = Flash self-programming library, MF3 single voltage flash                      */
/* Module       = fsl.h                                                                         */
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
/*              constant and function prototype definitions used by the FSL                     */
/*                                                                                              */
/*==============================================================================================*/

#ifndef __FSL_H_INCLUDED
#define __FSL_H_INCLUDED


/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
#include "fsl_types.h"


/*==============================================================================================*/
/* constant definitions                                                                         */
/*==============================================================================================*/

/*status code definitions returned by the FSL functions                                         */
#define   FSL_OK                    0x00      /* no problems                                    */
#define   FSL_ERR_PARAMETER         0x05      /* parameter error                                */
#define   FSL_ERR_PROTECTION        0x10      /* protection error (access right conflict)       */
#define   FSL_ERR_ERASE             0x1A      /* erase error                                    */
#define   FSL_ERR_BLANKCHECK        0x1B      /* blankcheck error (MRG11)                       */
#define   FSL_ERR_IVERIFY           0x1B      /* internal verify error (MRG11)                  */
#define   FSL_ERR_WRITE             0x1C      /* write error                                    */
#define   FSL_ERR_FLOW              0x1F      /* flow error (wrong timing calling)              */
#define   FSL_IDLE                  0x30      /* idle state (any action is not running)         */
#define   FSL_SUSPEND               0x43      /* previous flash action is suspended             */
#define   FSL_BUSY                  0xFF      /* command is being processed                     */


/*==============================================================================================*/
/* global function prototypes                                                                   */
/*==============================================================================================*/


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      initialization of flash environment                                            */
/*                                                                                              */
/* Input:        *descriptor_pstr - FSL descriptor                                              */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status_code                                                           */
/*                   = 0x00(FSL_OK), normal and means initialization OK                         */
/*                   = 0x05(FSL_ERR_PARAMETER), parameter error or HOCO isn't started           */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_Init(const __far fsl_descriptor_t* descriptor_pstr);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      opens flash environment                                                        */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     -                                                                              */
/*----------------------------------------------------------------------------------------------*/
extern void __far  FSL_Open(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      closes flash environment                                                       */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     -                                                                              */
/*----------------------------------------------------------------------------------------------*/
extern void __far  FSL_Close(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      prepares following functions to be called                                      */
/*               FSL_BlankCheck, FSL_Erase, FSL_Write, FSL_IVerify, FSL_StatusCheck             */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     -                                                                              */
/*----------------------------------------------------------------------------------------------*/
extern void __far  FSL_PrepareFunctions(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      prepares following functions to be called                                      */
/*               FSL_Set*ProtectFlag, FSL_InvertBootFlag, FSL_SetFlashShieldWindow,             */
/*               FSL_SwapBootCluster, FSL_SwapActiveBootCluster                                 */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     -                                                                              */
/*----------------------------------------------------------------------------------------------*/
extern void __far  FSL_PrepareExtFunctions(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      changes all vector addresses to specified address in RAM                       */
/* Input:        fsl_interrupt_destination_u16 - vector address in RAM (Lower 16 bits address)  */
/* Output:       -                                                                              */
/* Returned:     -                                                                              */
/*----------------------------------------------------------------------------------------------*/
extern void __far  FSL_ChangeInterruptTable(fsl_u16 fsl_interrupt_destination_u16);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      restores all vector addresses to initial vector addresses                      */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     -                                                                              */
/*----------------------------------------------------------------------------------------------*/
extern void __far  FSL_RestoreInterruptTable(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      checks if specified block is blank                                             */
/* Input:        block_u16 - block number has to be checked                                     */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status_code                                                           */
/*                   = 0x00(FSL_OK), normal and means "block is blank"                          */
/*                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 */
/*                   = 0x1B(FSL_ERR_BLANKCHECK), blank-check error, means "block is not blank"  */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*                   = 0xFF(FSL_BUSY), normal and means "process was started"                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_BlankCheck(fsl_u16 block_u16);


/*----------------------------------------------------------------------------------------------*/
/*  Block type:  FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/*  Purpose:     erase specified block                                                          */
/*  Input:       block_u16 - block number has to be erase                                       */
/*  Output:      -                                                                              */
/*  Returned:    fsl_u08, status_code                                                           */
/*                   = 0x00(FSL_OK), normal and means "block erased successfully"               */
/*                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 */
/*                   = 0x10(FSL_ERR_PROTECTION), protection error                               */
/*                   = 0x1A(FSL_ERR_ERASE), erase error                                         */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*                   = 0xFF(FSL_BUSY), normal and means "process was started"                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_Erase(fsl_u16 block_u16);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      performs internal verify on specified block                                    */
/* Input:        block_u16 - block number has to be verified                                    */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status_code                                                           */
/*                   = 0x00(FSL_OK), normal and means "block is verified"                       */
/*                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 */
/*                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*                   = 0xFF(FSL_BUSY), normal and means "process was started"                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_IVerify(fsl_u16 block_u16);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      writes N words from the data buffer into flash                                 */
/* Input:        *write_pstr - struct fsl_write_t to write                                      */
/* Output:       -                                                                              */
/* Condition:    1) (&fsl_destination_address MOD 4 == 0)                                       */
/*               2) most significant byte (MSB) of fsl_destination_address_u32 has to be 0x00   */
/*                  Means: 0x00abcdef 24 bit flash address allowed                              */
/*               3) (0 < fsl_word_count_u08 <= 64)                                              */
/*               4) (fsl_word_count_u08 <= sizeof(data buffer))                                 */
/*                  NOT CHECKED BY FSL                                                          */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 */
/*                   = 0x10(FSL_ERR_PROTECTION), protection error                               */
/*                   = 0x1C(FSL_ERR_WRITE), write error                                         */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*                   = 0xFF(FSL_BUSY), normal and means "process was started"                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_Write(__near fsl_write_t* write_pstr);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      controls the flash action start/continue/check for the last called function    */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x1A(FSL_ERR_ERASE), erase error                                         */
/*                   = 0x1B(FSL_ERR_BLANKCHECK), blank-check error, means "block not blank"     */
/*                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             */
/*                   = 0x1C(FSL_ERR_WRITE), write error                                         */
/*                   = 0x1F(FSL_ERR_FLOW), violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*                   = 0x30(FSL_IDLE), any action is not running                                */
/*                   = 0xFF(FSL_BUSY), normal and means "process was not finished"              */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_StatusCheck(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      suspends the flash action                                                      */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), previous flash action is OK.                               */
/*                                   And the state is suspended.                                */
/*                   = 0x1A(FSL_ERR_ERASE), previous flash action is Erase error.               */
/*                                   And the state is suspended.                                */
/*                   = 0x1B(FSL_ERR_BLANKCHECK), previous flash action is Blank error.          */
/*                                   And the state is suspended.                                */
/*                   = 0x1B(FSL_ERR_IVERIFY), previous flash action is IVerify error.           */
/*                                   And the state is suspended.                                */
/*                   = 0x1C(FSL_ERR_WRITE), previous flash action is Write error.               */
/*                                   And the state is suspended.                                */
/*                   = 0x1F(FSL_ERR_FLOW), violates the precondition.                           */
/*                                      or has been already suspending.                         */
/*                   = 0x30(FSL_IDLE), any action are not running.                              */
/*                                   And the state is suspended.                                */
/*                   = 0x43(FSL_SUSPEND), OK, previous flash action is suspended.               */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_StandBy(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      resumes the flash action                                                       */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), resumed flash action is OK.                                */
/*                                   And the state is resumed from the suspended state.         */
/*                   = 0x1A(FSL_ERR_ERASE), resumed flash action is Erase error.                */
/*                                   And the state is resumed from the suspended state.         */
/*                   = 0x1F(FSL_ERR_FLOW), violates the precondition.                           */
/*                                      or FSL is not suspending.                               */
/*                   = 0xFF(FSL_BUSY), resumed flash action is BUSY.                            */
/*                                   And the state is resumed from the suspended state.         */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_WakeUp(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      puts the security information into the destination variable                    */
/* Input:        *data_destination_pu08 - destination variable of the security info             */
/*               The format of the security info is: "unsigned char"                            */
/*                                                                                              */
/*               Format of the security info:                                                   */
/*               bit_1 = 0 -> boot-area re-programming disabled, otherwise enabled              */
/*               bit_2 = 0 -> block erase command disabled, otherwise enabled                   */
/*               bit_4 = 0 -> write command disabled, otherwise enabled                         */
/*               other bits = 1                                                                 */
/* Output:       data_destination_pu08 - security info                                          */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_GetSecurityFlags(fsl_u08 __near *data_destination_pu08);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      puts the boot flag into the destination variable                               */
/* Input:        *data_destination_pu08 - destination variable of the boot flag                 */
/*               The format of the boot flag info is: "unsigned char"                           */
/*               The value of the boot info is 0x00 for cluster 0 and 0x01 for cluster 1.       */
/* Output:       data_destination_pu08 - the boot flag info                                     */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_GetBootFlag(fsl_u08 __near *data_destination_pu08);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      puts the state of swap boot clusters into the destination variable             */
/* Input:        *data_destination_pu08 - destination variable of the state of boot info        */
/*               The format of the state of boot info is: "unsigned char"                       */
/*               The value of the state of boot info is 0x00 for cluster 0                      */
/*               and 0x01 for cluster 1.                                                        */
/* Output:       data_destination_pu08 - the state of boot info                                 */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_GetSwapState(fsl_u08 __near *data_destination_pu08);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:     puts the last address of the specified block into fsl_destination_address_u32   */
/* Input:       *getblockendaddr_pstr - struct fsl_getblockendaddr_t to get the last address    */
/* Output:      fsl_destination_address_u32 - the last address                                  */
/* Returned:    fsl_u08, status code                                                            */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_GetBlockEndAddr(__near fsl_getblockendaddr_t* getblockendaddr_pstr);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      puts the information about the protected flash area into fsl_*_block_u16       */
/* Input:        *getfsw_pstr - struct fsl_fsw_t to get FSW                                     */
/* Output:       fsl_start_block_u16 - the start block of FSW                                   */
/*               fsl_end_block_u16 - the end block of FSW                                       */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_GetFlashShieldWindow(__near fsl_fsw_t* getfsw_pstr);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      sets specified security flag by dedicated command-function.                    */
/*                                                                                              */
/*               There are following security levels:                                           */
/*               a) block-erase protection                                                      */
/*               b) write protection                                                            */
/*               c) boot-cluster protection                                                     */
/*                                                                                              */
/*               CAUTION:                                                                       */
/*               Each security flag can be written by the application only once                 */
/*                                                                                              */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x1A(FSL_ERR_ERASE), erase error                                         */
/*                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             */
/*                   = 0x1C(FSL_ERR_WRITE), write error                                         */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*                   = 0xFF(FSL_BUSY), normal and means "process was started"                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_SetBlockEraseProtectFlag(void);
extern fsl_u08 __far  FSL_SetWriteProtectFlag(void);
extern fsl_u08 __far  FSL_SetBootClusterProtectFlag(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      inverts the boot flag.                                                         */
/*                                                                                              */
/*               CAUTION:                                                                       */
/*               After reset, the boot clusters will be switched regarding this boot flag       */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x10(FSL_ERR_PROTECTION), protection error                               */
/*                   = 0x1A(FSL_ERR_ERASE), erase error                                         */
/*                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             */
/*                   = 0x1C(FSL_ERR_WRITE), write error                                         */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*                   = 0xFF(FSL_BUSY), normal and means "process was started"                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_InvertBootFlag(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      defines a new Flash Shield Window inside the flash memory                      */
/* Input:        *setfsw_pstr - struct fsl_fsw_t to set FSW                                     */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 */
/*                   = 0x10(FSL_ERR_PROTECTION), protection error                               */
/*                   = 0x1A(FSL_ERR_ERASE), erase error                                         */
/*                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             */
/*                   = 0x1C(FSL_ERR_WRITE), write error                                         */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*                   = 0xFF(FSL_BUSY), normal and means "process was started"                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_SetFlashShieldWindow(__near fsl_fsw_t* setfsw_pstr);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      swaps boot cluster 0 and boot cluster 1 physically without setting             */
/*               the boot flag. After swap the library jumps to the address of the              */
/*               reset vector.                                                                  */
/*                                                                                              */
/*               CAUTION:                                                                       */
/*               After reset, the boot cluster will be switched regarding the boot flag         */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x10(FSL_ERR_PROTECTION), protection error                               */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_SwapBootCluster(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      inverts the boot flag and swaps boot cluster 0 and boot cluster 1 physically   */
/*                                                                                              */
/*               CAUTION:                                                                       */
/*               After reset, the boot clusters will be switched regarding this boot flag       */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x10(FSL_ERR_PROTECTION), protection error                               */
/*                   = 0x1A(FSL_ERR_ERASE), erase error                                         */
/*                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             */
/*                   = 0x1C(FSL_ERR_WRITE), write error                                         */
/*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                */
/*                                      or violates the precondition.                           */
/*                                      or FSL is suspending.                                   */
/*                   = 0xFF(FSL_BUSY), normal and means "process was started"                   */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08 __far  FSL_SwapActiveBootCluster(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      forces a hardware reset via illegal instruction                                */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     -                                                                              */
/*----------------------------------------------------------------------------------------------*/
extern void __far  FSL_ForceReset(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      gets the internal version information of the used FSL                          */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     pointer to version string                                                      */
/*----------------------------------------------------------------------------------------------*/
extern __far fsl_u08* __far  FSL_GetVersionString(void);


#endif
