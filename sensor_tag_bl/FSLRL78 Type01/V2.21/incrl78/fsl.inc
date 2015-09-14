;=================================================================================================
; Project      = Flash self-programming library, MF3 single voltage flash
; Module       = fsl.inc
; Device:      = RL78
; Version      = V2.21
;=================================================================================================
; DISCLAIMER
; This software is supplied by Renesas Electronics Corporation and is only
; intended for use with Renesas products. No other uses are authorized. This
; software is owned by Renesas Electronics Corporation and is protected under
; all applicable laws, including copyright laws.
; THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
; THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
; LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
; AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
; TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
; ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
; FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
; ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
; BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
; Renesas reserves the right, without notice, to make changes to this software
; and to discontinue the availability of this software. By using this software,
; you agree to the additional terms and conditions found by accessing the
; following link:
; http://www.renesas.com/disclaimer
;
; Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
;=================================================================================================
; Purpose:
;              implementation module of low-level flash memory access
;
;=================================================================================================

$IFDEF __FSL_INC_INCLUDED

$ELSE
__FSL_INC_INCLUDED  .SET    1


;*************************************************************************************************
; BEGIN OF CUSTOMIZABLE DECLARATION AREA
;*************************************************************************************************

; Base number prefix/suffix mode selection for Assembler
; Numbers definition within the prefix mode: 0x005
; Numbers definition within the suffix mode: 005H
;
; Prefix mode will be activated in case the symbol __FSL_INC_BASE_NUMBER_SUFFIX is NOT defined.
; Suffix mode will be activated in case the symbol __FSL_INC_BASE_NUMBER_SUFFIX is defined.

;__FSL_INC_BASE_NUMBER_SUFFIX .SET 1

;*************************************************************************************************
; END OF CUSTOMIZABLE DECLARATION AREA
;*************************************************************************************************


;=================================================================================================
; constant definitions
;=================================================================================================

$IFNDEF __FSL_INC_BASE_NUMBER_SUFFIX

;status code definitions returned by the FSL functions
FSL_OK                  .EQU    (0x000) ; no problems
FSL_ERR_PARAMETER       .EQU    (0x005) ; parameter error
FSL_ERR_PROTECTION      .EQU    (0x010) ; protection error (access right conflict)
FSL_ERR_ERASE           .EQU    (0x01A) ; erase error
FSL_ERR_BLANKCHECK      .EQU    (0x01B) ; blankcheck error (MRG11)
FSL_ERR_IVERIFY         .EQU    (0x01B) ; internal verify error (MRG11)
FSL_ERR_WRITE           .EQU    (0x01C) ; write error
FSL_ERR_FLOW            .EQU    (0x01F) ; flow error (wrong timing calling)
FSL_IDLE                .EQU    (0x030) ; idle state (any action is not running)
FSL_SUSPEND             .EQU    (0x043) ; previous flash action is suspended
FSL_BUSY                .EQU    (0x0FF) ; command is being processed

$ELSE

;status code definitions returned by the FSL functions
FSL_OK                  .EQU    (000H)  ; no problems
FSL_ERR_PARAMETER       .EQU    (005H)  ; parameter error
FSL_ERR_PROTECTION      .EQU    (010H)  ; protection error (access right conflict)
FSL_ERR_ERASE           .EQU    (01AH)  ; erase error
FSL_ERR_BLANKCHECK      .EQU    (01BH)  ; blankcheck error (MRG11)
FSL_ERR_IVERIFY         .EQU    (01BH)  ; internal verify error (MRG11)
FSL_ERR_WRITE           .EQU    (01CH)  ; write error
FSL_ERR_FLOW            .EQU    (01FH)  ; flow error (wrong timing calling)
FSL_IDLE                .EQU    (030H)  ; idle state (any action is not running)
FSL_SUSPEND             .EQU    (043H)  ; previous flash action is suspended
FSL_BUSY                .EQU    (0FFH)  ; command is being processed

$ENDIF


;=================================================================================================
; global function prototypes
;=================================================================================================


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      initialization of flash environment                                            
;                                                                                              
; Input:        DE,A - pointer to FSL descriptor                                               
; Output:       -                                                                              
; Returned:     A, status_code                                                                 
;                   = 0x00(FSL_OK), normal and means initialization OK                         
;                   = 0x05(FSL_ERR_PARAMETER), parameter error or HOCO isn't started           
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_Init


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      opens flash environment                                                        
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     -                                                                              
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_Open


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      closes flash environment                                                       
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     -                                                                              
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_Close


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      prepares following functions to be called                                      
;               FSL_BlankCheck, FSL_Erase, FSL_Write, FSL_IVerify, FSL_StatusCheck             
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     -                                                                              
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_PrepareFunctions


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      prepares following functions to be called                                      
;               FSL_Set*ProtectFlag, FSL_InvertBootFlag, FSL_SetFlashShieldWindow,             
;               FSL_SwapBootCluster, FSL_SwapActiveBootCluster                                 
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     -                                                                              
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_PrepareExtFunctions


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      changes all vector addresses to specified address in RAM                       
; Input:        AX - vector address in RAM (Lower 16 bits address)                             
; Output:       -                                                                              
; Returned:     -                                                                              
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_ChangeInterruptTable


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      restores all vector addresses to initial vector addresses                      
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     -                                                                              
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_RestoreInterruptTable


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      checks if specified block is blank                                             
; Input:        AX - block number has to be checked                                            
; Output:       -                                                                              
; Returned:     A, status_code                                                                 
;                   = 0x00(FSL_OK), normal and means "block is blank"                          
;                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 
;                   = 0x1B(FSL_ERR_BLANKCHECK), blank-check error, means "block is not blank"  
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;                   = 0xFF(FSL_BUSY), normal and means "process was started"                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_BlankCheck


;----------------------------------------------------------------------------------------------
;  Block type:  FSL command function                                                           
;----------------------------------------------------------------------------------------------
;  Purpose:     erase specified block                                                          
;  Input:       AX - block number has to be erase                                              
;  Output:      -                                                                              
;  Returned:    A, status_code                                                                 
;                   = 0x00(FSL_OK), normal and means "block erased successfully"               
;                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 
;                   = 0x10(FSL_ERR_PROTECTION), protection error                               
;                   = 0x1A(FSL_ERR_ERASE), erase error                                         
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;                   = 0xFF(FSL_BUSY), normal and means "process was started"                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_Erase


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      performs internal verify on specified block                                    
; Input:        AX - block number has to be verified                                           
; Output:       -                                                                              
; Returned:     A, status_code                                                                 
;                   = 0x00(FSL_OK), normal and means "block is verified"                       
;                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 
;                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;                   = 0xFF(FSL_BUSY), normal and means "process was started"                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_IVerify


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      writes N words from the data buffer into flash                                 
; Input:        AX - pointer to struct fsl_write_str to write                                  
; Output:       -                                                                              
; Condition:    1) (fsl_destination_address_u32 MOD 4 == 0)                                    
;               2) most significant byte (MSB) of fsl_destination_address_u32 has to be 0x00   
;                  Means: 0x00abcdef 24 bit flash address allowed                              
;               3) (0 < fsl_word_count_u08 <= 64)                                              
;               4) (fsl_word_count_u08 <= sizeof(data buffer))                                 
;                  NOT CHECKED BY FSL                                                          
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 
;                   = 0x10(FSL_ERR_PROTECTION), protection error                               
;                   = 0x1C(FSL_ERR_WRITE), write error                                         
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;                   = 0xFF(FSL_BUSY), normal and means "process was started"                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_Write


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      controls the flash action start/continue/check for the last called function    
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x1A(FSL_ERR_ERASE), erase error                                         
;                   = 0x1B(FSL_ERR_BLANKCHECK), blank-check error, means "block not blank"     
;                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             
;                   = 0x1C(FSL_ERR_WRITE), write error                                         
;                   = 0x1F(FSL_ERR_FLOW), violates the precondition.                           
;                                      or FSL is suspending.                                   
;                   = 0x30(FSL_IDLE), any action is not running                                
;                   = 0xFF(FSL_BUSY), normal and means "process was not finished"              
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_StatusCheck


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      susdends the flash action                                                      
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), previous flash action is OK.                               
;                                   And the state is suspended.                                
;                   = 0x1A(FSL_ERR_ERASE), previous flash action is Erase error.               
;                                   And the state is suspended.                                
;                   = 0x1B(FSL_ERR_BLANKCHECK), previous flash action is Blank error.          
;                                   And the state is suspended.                                
;                   = 0x1B(FSL_ERR_IVERIFY), previous flash action is IVerify error.           
;                                   And the state is suspended.                                
;                   = 0x1C(FSL_ERR_WRITE), previous flash action is Write error.               
;                                   And the state is suspended.                                
;                   = 0x1F(FSL_ERR_FLOW), violates the precondition.                           
;                                      or has been already suspending.                         
;                   = 0x30(FSL_IDLE), any action are not running.                              
;                                   And the state is suspended.                                
;                   = 0x43(FSL_SUSPEND), OK, previous flash action is suspended.               
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_StandBy


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      resumes the flash action                                                       
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), resumed flash action is OK.                                
;                                   And the state is resumed from the suspended state.         
;                   = 0x1A(FSL_ERR_ERASE), resumed flash action is Erase error.                
;                                   And the state is resumed from the suspended state.         
;                   = 0x1F(FSL_ERR_FLOW), violates the precondition.                           
;                                      or FSL is not suspending.                               
;                   = 0xFF(FSL_BUSY), resumed flash action is BUSY.                            
;                                   And the state is resumed from the suspended state.         
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_WakeUp


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      puts the security information into the destination address                     
; Input:        AX - destination address of the security info                                  
;               The format of the security info is: "unsigned char"                            
;                                                                                              
;               Format of the security info:                                                   
;               bit_1 = 0 -> boot-area re-programming disabled, otherwise enabled              
;               bit_2 = 0 -> block erase command disabled, otherwise enabled                   
;               bit_4 = 0 -> write command disabled, otherwise enabled                         
;               other bits = 1                                                                 
; Output:       data_destination_pu08 - security info                                          
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_GetSecurityFlags


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      puts the boot flag into the destination address                                
; Input:        AX - destination address of the boot flag                                      
;               The format of the boot flag info is: "unsigned char"                           
;               The value of the boot info is 0x00 for cluster 0 and 0x01 for cluster 1.       
; Output:       data_destination_pu08 - the boot flag info                                     
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_GetBootFlag


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      puts the state of swap boot clusters into the destination address              
; Input:        AX - destination address of the state of boot info                             
;               The format of the state of boot info is: "unsigned char"                       
;               The value of the state of boot info is 0x00 for cluster 0                      
;               and 0x01 for cluster 1.                                                        
; Output:       data_destination_pu08 - the state of boot info                                 
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_GetSwapState


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      puts the last address of the specified block into fsl_destination_address_u32  
; Input:        AX - pointer to struct fsl_getblockendaddr_str to get the last address         
; Output:       fsl_destination_address_u32 - the last address                                 
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                      
;                   = 0x05(FSL_ERR_PARAMETER), parameter error                                  
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_GetBlockEndAddr


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      puts the information about the protected flash area into fsl_*_block_u16       
; Input:        AX - pointer to struct fsl_fsw_str to get FSW                                  
; Output:       fsl_start_block_u16 - the start block of FSW                                   
;               fsl_end_block_u16 - the end block of FSW                                       
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_GetFlashShieldWindow


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      sets specified security flag by dedicated command-function.                    
;                                                                                              
;               There are following security levels:                                           
;               a) block-erase protection                                                      
;               b) write protection                                                            
;               c) boot-cluster protection                                                     
;                                                                                              
;               CAUTION:                                                                       
;               Each security flag can be written by the application only once                 
;                                                                                              
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x1A(FSL_ERR_ERASE), erase error                                         
;                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             
;                   = 0x1C(FSL_ERR_WRITE), write error                                         
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;                   = 0xFF(FSL_BUSY), normal and means "process was started"                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_SetBlockEraseProtectFlag
.EXTERN _FSL_SetWriteProtectFlag
.EXTERN _FSL_SetBootClusterProtectFlag


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      inverts the boot flag.                                                         
;                                                                                              
;               CAUTION:                                                                       
;               After reset, the boot clusters will be switched regarding this boot flag       
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x10(FSL_ERR_PROTECTION), protection error                               
;                   = 0x1A(FSL_ERR_ERASE), erase error                                         
;                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             
;                   = 0x1C(FSL_ERR_WRITE), write error                                         
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;                   = 0xFF(FSL_BUSY), normal and means "process was started"                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_InvertBootFlag


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      defines a new Flash Shield Window inside the flash memory                      
; Input:        AX - pointer struct fsl_fsw_str to set FSW                                     
; Output:       -                                                                              
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x05(FSL_ERR_PARAMETER), parameter error                                 
;                   = 0x10(FSL_ERR_PROTECTION), protection error                               
;                   = 0x1A(FSL_ERR_ERASE), erase error                                         
;                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             
;                   = 0x1C(FSL_ERR_WRITE), write error                                         
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;                   = 0xFF(FSL_BUSY), normal and means "process was started"                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_SetFlashShieldWindow


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      swaps boot cluster 0 and boot cluster 1 physically without setting             
;               the boot flag. After swap the library jumps to the address of the              
;               reset vector.                                                                  
;                                                                                              
;               CAUTION:                                                                       
;               After reset, the boot cluster will be switched regarding the boot flag         
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     A, status code                                                                 
;                   = 0x10(FSL_ERR_PROTECTION), protection error                               
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_SwapBootCluster


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      inverts the boot flag and swaps boot cluster 0 and boot cluster 1 physically   
;                                                                                              
;               CAUTION:                                                                       
;               After reset, the boot clusters will be switched regarding this boot flag       
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     A, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x10(FSL_ERR_PROTECTION), protection error                               
;                   = 0x1A(FSL_ERR_ERASE), erase error                                         
;                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             
;                   = 0x1C(FSL_ERR_WRITE), write error                                         
;                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.                
;                                      or violates the precondition.                           
;                                      or FSL is suspending.                                   
;                   = 0xFF(FSL_BUSY), normal and means "process was started"                   
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_SwapActiveBootCluster


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      forces a hardware reset via illegal instruction                                
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     -                                                                              
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_ForceReset


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      gets the internal version information of the used FSL                          
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     DE, pointer to version string(LW)                                              
;               A, pointer to version string(H)                                                
;----------------------------------------------------------------------------------------------
.EXTERN _FSL_GetVersionString



$ENDIF
