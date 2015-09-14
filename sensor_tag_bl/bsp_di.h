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

#ifndef __BSP_DI_H
#define __BSP_DI_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*                              Include File                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                      Global Macro or Enum Definition	                     */
/*****************************************************************************/
typedef enum
{
    BSP_DI_DEV_ID_BUTTON = 0,
} bsp_di_dev_id_t;

/*****************************************************************************/
/*                   Global Structure or Union Definition     		         */
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
extern bool_t bsp_di_is_hi(bsp_di_dev_id_t id);
 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TEMPLATE_H */
/* EOF */
