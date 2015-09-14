/******************************************************************************
*
* @file    $Name$
* @version $Revision$
* @date    $LastChangedDate$
*
* @Copyright 2015 - Advance Tech.
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

#ifndef __BSP_DO_H
#define __BSP_DO_H

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
    BSP_DO_DEV_ID_LED = 0,
    BSP_DO_DEV_ID_DGN_1,
    BSP_DO_DEV_ID_DGN_2
} bsp_do_dev_id_t;

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
void bsp_do_set(bsp_do_dev_id_t id);

/******************************************************************************
 * @brief   :
 *
 * @param   :   None.
 * @return  :	None.
 * @remarks :	None.
 *****************************************************************************/
void bsp_do_clear(bsp_do_dev_id_t id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TEMPLATE_H */
/* EOF */
