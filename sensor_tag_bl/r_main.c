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
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G13 V2.03.02.01 [15 May 2015]
* Device(s)    : R5F100BE
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 6/9/2015
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
/***********************************************************************************************************************
* Device Configuration
* --------------------
* DBG_COM @ 115200bps
* BT @ 115200bps
*
* TODO:
* -----
*
*
*
*
*
***********************************************************************************************************************/
#include "typedef.h"
#include "bsp_do.h"
#include "bsp_di.h"
#include "r_typedefs.h"
//#include "r_cg_timer.h"
//#include "r_cg_serial.h"
#include "fsl.h"
#include "fsl_types.h"
#include "r_xmodem.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#define PRODUCTION_PROGRAM_REV_MAJOR   0
#define PRODUCTION_PROGRAM_REV_MINOR   1

typedef enum
{
	FSL_INIT,
	FSL_ERASE,
	FSL_WRITE,
	FSL_INVERTBOOTFLAG
} error_handler_case;

#define BOOT_AREA               0x1000
#define	FLASH_AREA              0x2000
#define FLASH_BYTE_PER_BLOCK    0x400
#define ROM_ADDRESS             (uint16_t)((FLASH_END_BLOCK*FLASH_BYTE_PER_BLOCK)-2)
#define CHECKSUM_ADDRESS        (uint16_t)((FLASH_END_BLOCK*FLASH_BYTE_PER_BLOCK)-4)

// Debug mode
#define FLASH_END_BLOCK         63

// Release mode
//#define FLASH_END_BLOCK         64

void ErrorHandler(uint8_t case_num);

/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    uint16_t 			i = 0;
    int8_t 				selection;
    int8_t 				reselect = 1;
    fsl_u08 			fsl_status;
    __far fsl_descriptor_t 	fsl_descr;


    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */  
    
    /****************/
    /* Boot Program */
    /****************/
    /* Determine to access bootloader program */
    if (bsp_di_is_hi(BSP_DI_DEV_ID_BUTTON) == FALSE)
    {        
        R_UART1_Start();
                
    	/* initialize self-programming environment */
    	fsl_descr.fsl_flash_voltage_u08 = 0x00;
    	fsl_descr.fsl_frequency_u08 = 0x08;
    	fsl_descr.fsl_auto_status_check_u08 = 0x01;
    	
    	fsl_status = FSL_Init(&fsl_descr);
    	
    	if(fsl_status != FSL_OK)
    	{
    		ErrorHandler(FSL_INVERTBOOTFLAG);
    	}
    	
    	FSL_Open();
    	FSL_PrepareFunctions();
    	FSL_PrepareExtFunctions();

    	/* Print operation menu */
    	R_UART1_Send_String((__far int8_t*)"\f*************************\n\r");
    	R_UART1_Send_String((__far int8_t*)"***   FW Ver.: 1.5    ***\n\r");
    	R_UART1_Send_String((__far int8_t*)"*************************\n\r");

    	while (1){
    		R_UART1_Send_String((__far int8_t*)"\n\rChoose actions:(1)Update Boot area (2)Update Flash area (3) Run Application\n\r");
    		while (1){
    			WDTE = 0xAC;
    			if (GetByte(1000, &selection)) break;
    		}
    		switch (selection){
    			case '1':
    				R_UART1_Send_String((__far int8_t*)"\n\rSelect file to write into boot area.");
    				for (i = 4; i < 8; i++)
    				{
    					fsl_status = FSL_Erase(i);
    					if (fsl_status != FSL_OK)
    					{
    						ErrorHandler(FSL_ERASE);
    					}
    				}
    				fsl_status = XmodemProg(BOOT_AREA);

    				if(fsl_status == XM_OK)
    				{
    					fsl_status = FSL_InvertBootFlag();
    					if (fsl_status != FSL_OK)
    					{
    						ErrorHandler(FSL_INVERTBOOTFLAG);
    					}
    					R_UART1_Send_String((__far int8_t*)"\n\rUpdate flash area: Success");
    				}
    				else
    				{
    					R_UART1_Send_String((__far int8_t*)"\n\rUpdate flash area: Failed");
    					while (1)
    					{
    						WDTE = 0xAC;
    					}
    				}
    				R_UART1_Send_String((__far int8_t*)"\n\rReset");
    				FSL_ForceReset();
    				
    				
    				break;
    			case '2':
    				R_UART1_Send_String((__far int8_t*)"\n\rSelect file to write into flash area.");
                                        
    				for (i = FLASH_AREA/FLASH_BYTE_PER_BLOCK; i < FLASH_END_BLOCK; i++) 
    				{
    					fsl_status = FSL_Erase(i);
    					if (fsl_status != FSL_OK)
    					{
    						ErrorHandler(FSL_ERASE);
    					}
    				}
    				
    				fsl_status = XmodemProg(FLASH_AREA);

    				if(fsl_status == XM_OK)
    				{

    					R_UART1_Send_String((__far int8_t*)"\n\rUpdate flash area: Success");
    					R_UART1_Send_String((__far int8_t*)"\n\rGoto application program.\n\r");
    					reselect = 0;
    				}
    				else
    				{
    					R_UART1_Send_String((__far int8_t*)"\n\rUpdate flash area: Failed");
    					while (1)
    					{
    						WDTE = 0xAC;
    					}
    				}
    				break;
    			case '3':
    				R_UART1_Send_String((__far int8_t*)"\n\rGoto application program.\n\r");
    				reselect = 0;
    				break;
    			default:
    				R_UART1_Send_String((__far int8_t*)"\n\rPlease select again.\n\r");
    				reselect = 1;
    				break;
    		}
    		if(reselect == 0)
    			break;
    	}
    	
    	fsl_status = FSL_BlankCheck(FLASH_AREA/FLASH_BYTE_PER_BLOCK);
    	if (fsl_status == FSL_OK)
    	{
    		R_UART1_Send_String((__far int8_t*)"\n\rThe user program is empty.");
    		delay(3000);
    		FSL_ForceReset();
    	}
    }    

    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    DI();

    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/*******************************************************************************
* Function Name : ErrorHandler
* Description	: This function handles the error behavior.	
* Parameters	: case_num -
*                    error case number
* Return value  : none
*******************************************************************************/
void ErrorHandler(uint8_t case_num)
{
	switch (case_num)
	{
		case FSL_INIT:
			R_UART1_Send_String((__far int8_t*)"\n\r FSL_Init failed");
			break;
		case FSL_ERASE:
			R_UART1_Send_String((__far int8_t*)"\n\r FSL_Erase failed");
			break;
		case FSL_WRITE:
			R_UART1_Send_String((__far int8_t*)"\n\r FSL_Write failed");
			break;
		case FSL_INVERTBOOTFLAG:
			R_UART1_Send_String((__far int8_t*)"\n\r FSL_InvertBootFlag failed");
			break;
	}
	
	while (1)
	{
		WDTE = 0xAC;
	}
}

/* End user code. Do not edit comment generated here */
