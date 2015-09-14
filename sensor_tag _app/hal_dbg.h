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

#ifndef __HAL_DBG_H
#define __HAL_DBG_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*                              Include File                                 */
/*****************************************************************************/
#include "bsp_dbg.h"

/*****************************************************************************/
/*                      Global Macro or Enum Definition	                     */
/*****************************************************************************/


/*****************************************************************************/
/*                   Global Structure or Union Definition     		         */
/*****************************************************************************/
#define hal_dbg_start()         bsp_dbg_start()
#define hal_dbg_write(string)   bsp_dbg_print(string)
#define hal_dbg_wake()          bsp_dbg_start()
#define hal_dbg_sleep()         bsp_dbg_stop()

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TEMPLATE_H */
/* EOF */
