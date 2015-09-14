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

#ifndef __BSP_DBG_H
#define __BSP_DBG_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*                              Include File                                 */
/*****************************************************************************/
#include "typedef.h"

/*****************************************************************************/
/*                      Global Macro or Enum Definition	                     */
/*****************************************************************************/
#define bsp_dbg_start() R_UART1_Start()
#define bsp_dbg_stop()  R_UART1_Stop()

/*****************************************************************************/
/*                   Global Structure or Union Definition     		     */
/*****************************************************************************/


/*****************************************************************************/
/*                       Global Variable Declaration                         */
/*****************************************************************************/


/*****************************************************************************/
/*                         Configuration Checking                            */
/*****************************************************************************/


/*****************************************************************************/
/*                       Global Function Declaration                         */
/*****************************************************************************/
/******************************************************************************
 * @brief   :
 *
 * @param   :   None.
 * @return  :	None.
 * @remarks :	None.
 *****************************************************************************/
extern bool_t bsp_dbg_print(char_t *string);


/******************************************************************************
 * @brief   :
 *
 * @param   :   None.
 * @return  :	None.
 * @remarks :	None.
 *****************************************************************************/
extern void bsp_dbg_tx_done_set(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TEMPLATE_H */
/* EOF */
