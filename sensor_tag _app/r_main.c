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
* Creation Date: 31/8/2015
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
/***********************************************************************************************************************
* Device Configuration
* --------------------
* DBG_COM @ 115200bps
*
* TODO:
* -----
*
*
*
*
*
***********************************************************************************************************************/
#include "hal_dbg.h"
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

void post(void);
void dev_data_init(void);
void delay(u32_t period);

#define TMR_TICK_PRD    100 //100ms

func_t timer_tick_cb;
u32_t tmr_tick_cntr;
bool_t is_tmr_tick_using;

char_t print_buf[256];

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
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */  
   
    /****************/
    /* User Program */
    /****************/
    /* Power Up Self-Test */
    post();
    
    /*******************/
    /* Main  operation */
    /*******************/
    hal_dbg_write("\r\n");
    hal_dbg_write("\r\n**************");
    hal_dbg_write("\r\n* DEBUG INFO *");
    hal_dbg_write("\r\n**************");

    while (1U)
    {   
      
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
/******************************************************************************
 * @brief   :
 *
 * @param   :   None.
 * @return  :	None.
 * @remarks :	None.
 *****************************************************************************/
void post(void)
{
    /* Enable debug module by start function */
    EI();    
 
    hal_dbg_start();
    
    sprintf(print_buf, "\r\n* PC CONSOLE: ver %d.%d *", PRODUCTION_PROGRAM_REV_MAJOR, PRODUCTION_PROGRAM_REV_MINOR);
    
    hal_dbg_write("\r\n****************************");
    hal_dbg_write(print_buf);
    hal_dbg_write("\r\n****************************");
    
    hal_dbg_write("\r\n************");
    hal_dbg_write("\r\n*   POST   *");
    hal_dbg_write("\r\n************");
    
    //TODO:  Test for each module
}


/******************************************************************************
 * @brief   :
 *
 * @param   :   None.
 * @return  :	None.
 * @remarks :	None.
 *****************************************************************************/
void timer_tick_int_cb(void)
{
    tmr_tick_cntr++;
}

/******************************************************************************
 * @brief   :
 *
 * @param   :   None.
 * @return  :	None.
 * @remarks :	None.
 *****************************************************************************/
void timer_tick_start(void)
{
    ASSERT(is_tmr_tick_using == FALSE);
    
    /* 10ms time base */
    R_TAU0_Channel1_Start();
    
    tmr_tick_cntr = 0;
    
    is_tmr_tick_using = TRUE; 
}

/******************************************************************************
 * @brief   :
 *
 * @param   :   None.
 * @return  :	None.
 * @remarks :	None.
 *****************************************************************************/
void timer_tick_stop(void)
{
    ASSERT(is_tmr_tick_using == TRUE);

    R_TAU0_Channel1_Stop();

    is_tmr_tick_using = FALSE; 
}
 
 /******************************************************************************
 * @brief   :
 *
 * @param   :   None.
 * @return  :	None.
 * @remarks :	None.
 *****************************************************************************/
void delay(u32_t period)
{
    period = period/TMR_TICK_PRD;   

    timer_tick_start();

    while (tmr_tick_cntr < period);

    timer_tick_stop();
}
 
/******************************************************************************
 * @brief   :
 *
 * @param   :   None.
 * @return  :	None.
 * @remarks :	None.
 *****************************************************************************/
bool_t is_timer_tick_expired(u32_t period)
{
    period = (period/TMR_TICK_PRD);

    if (tmr_tick_cntr >= period)
    {
     return TRUE;
    }
    else
    {
     return FALSE;
    }
}

/* End user code. Do not edit comment generated here */
