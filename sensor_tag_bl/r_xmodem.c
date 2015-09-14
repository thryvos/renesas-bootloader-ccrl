/********************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
********************************************************************************/

/********************************************************************************
* File Name    : r_xmodem.c
* Version      : 1.00
* Description  : This file implements the XMODEM communication protocol.
********************************************************************************/

/********************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.12.2012 1.00    First Release
********************************************************************************/

/********************************************************************************
Includes	<System Includes> , "Project Includes"
********************************************************************************/
#include "r_typedefs.h"
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"
#include "r_cg_serial.h"
#include "fsl.h"
#include "fsl_types.h"
    
/********************************************************************************
Macro definitions
********************************************************************************/
// Debug mode
#define FLASH_END_ADDRESS 0x0FBFF   // need to reserve last 512bytes and memory
                                    // per block is 0x400 = 1024 bytes, so,
                                    // 0xFFFF - 0x400  = 0xFC00 - 1 = 0xFBFF
        

// Release mode
//#define FLASH_END_ADDRESS 0x0FFFF



#define FLASH_START_ADDRESS 0x2000 // 0x2000
#define CHECKSUM_ADDRESS    (uint16_t)(FLASH_END_ADDRESS - 3)

/********************************************************************************
Typedef definitions
********************************************************************************/

/********************************************************************************
Exported global variables
********************************************************************************/

/********************************************************************************
Exported global functions
********************************************************************************/

/********************************************************************************
* Function Name : WriteFlash
* Description	: This function initializes the TAU0 Channel 0 module.		
* Parameters	: addr - 
*					start address to write
*				  data[] -
*				  	data buffer to write
*				  len -
*				  	size of data buffer
* Return value  : fsl_u08, status_code                                          
*                   = 0x00(FSL_OK), normal                                      
*                   = 0x05(FSL_ERR_PARAMETER), parameter error                   
*                   = 0x10(FSL_ERR_PROTECTION), protection error                 
*                   = 0x1C(FSL_ERR_WRITE), write error                           
*                   = 0x1F(FSL_ERR_FLOW), last operation has not finished, yet.  
*                                      or violates the precondition.             
*                                      or FSL is suspending.                     
*                   = 0xFF(FSL_BUSY), normal and means "process was started"
********************************************************************************/
fsl_u08 WriteFlash(uint16_t addr, int8_t data[], uint8_t size)
{
	__near fsl_write_t my_fsl_write_str;	
	
	my_fsl_write_str.fsl_data_buffer_p_u08 = (__near fsl_u08 *) data;
	my_fsl_write_str.fsl_word_count_u08 = size/4;
	my_fsl_write_str.fsl_destination_address_u32 = addr;
		
	return FSL_Write((__near fsl_write_t*) &my_fsl_write_str);
}

/********************************************************************************
* Function Name : GetByte
* Description	: This function recieves a byte of UART0 data.		
* Parameters	: timeout -
*					time limit for reception
*				  data -
*				  	data buffer pointer
* Return value  : uint8_t, status
*					TRUE or FALSE
********************************************************************************/
uint8_t GetByte (uint32_t timeout, int8_t *data)
{
	uint32_t tick_count;
	
	tick_count = timeout;
	R_TAU0_Channel0_Start();
	
	/* wait for a byte to arrive */
	while ((SRIF1 == 0) && (tick_count))
	{
		WDTE = 0xac;
		if (TMIF00 == 1)
		{
			TMIF00 = 0;
			R_TAU0_Channel0_Stop();
			if (--tick_count)
			{
				R_TAU0_Channel0_Start();
			}
		}
	}
	
	if (tick_count == 0)
	{
		*data = '0';
		return FALSE;
	}
		
	*data=(uint8_t) RXD1;
	SRIF1 = 0;

	return TRUE;
}

/********************************************************************************
* Function Name : XmodemProg
* Description	: This function uses the XModem protocol to recieve data and write data into rom memory.		
* Parameters	: flash_start_address -
*					the start address of rom memory to write
* Return value  : uint8_t, status
					XM_OK, XM_TIMEOUT, XM_ADDRESS_ERROR or XM_PROG_FAIL
********************************************************************************/
uint8_t XmodemProg(uint16_t flash_start_address)
{
	uint16_t		ret;
	uint8_t			expected_blk_num;
	uint8_t			retry_counter;
	uint32_t		rx_byte_count;
	uint8_t			rx_byte_buffer_index;
	uint8_t			status;
	uint8_t			checksum;
	uint8_t			start_condition;
	uint16_t		Address;
	uint8_t			tmp;
	uint16_t		ROM_checksum;
	uint16_t		UART_checksum;
	uint8_t			CHK[4] = {0};
	uint8_t			rx_buffer[XMODEM_BUFFER_SIZE];
	__far int8_t* 	ptr;

	/* first xmodem block number is 1 */
	expected_blk_num = 1;

	start_condition = TRUE;
	
	UART_checksum = 0;
	
	ROM_checksum = 0;

	Address = flash_start_address;	


	while (1)
	{
		/*	initialise Rx attempts */
		retry_counter = 10;
		ret = FALSE;	

		/* decrement Rx attempts counter & get Rx data byte with a 10 sec timeout contdition, and repeat until Rx attempts is 0 */
		while ((retry_counter > 0) && (ret == FALSE)) 
			{
				/*	if this is the start of the xmodem frame */
			if (start_condition == TRUE)
			{
				/*	send a NAK to the transmitter */
				R_UART1_Send_Byte(NAK);							/* Kick off the XModem transfer */
				ret = GetByte(10000, (int8_t*)&rx_buffer[0]);	

			}                             
			else
			{
				 /* wait for all data to be received */
				 /* or EOT */
				ret = GetByte(10000, (int8_t*)&rx_buffer[0]);			
			}
			retry_counter--;
		}

		start_condition = FALSE;
		
		if (ret == FALSE)
		{
			return (XM_TIMEOUT); 
		}
		else			
		{
			/* if first received byte is "end of frame" */
			/* return ACK to sender */
			if (rx_buffer[0] == EOT)
			{
				R_UART1_Send_Byte(ACK);
				for (ptr=(__far int8_t*)flash_start_address; ptr<(__far int8_t*)Address; ptr++)
				{
					tmp = *ptr;
					ROM_checksum += tmp;
				}
				if (ROM_checksum == UART_checksum)
				{
					CHK[0] = (uint8_t)(ROM_checksum & 0x00FF);
					CHK[1] = (uint8_t)((ROM_checksum & 0xFF00)>>8);
					CHK[2] = (uint8_t)(Address & 0x00FF);
					CHK[3] = (uint8_t)((Address & 0xFF00)>>8);

                    if (flash_start_address < FLASH_START_ADDRESS)
					{
						/* Write checksum value into the end of boot area*/
						WriteFlash(0x1FFC, (int8_t*)CHK, 4);
					}
					else
					{
						/* Write checksum value into the end of flash area*/
						WriteFlash(CHECKSUM_ADDRESS, (int8_t*)CHK, 4);
					}
					return (XM_OK);
				}
				else
					return (XM_PROG_FAIL);
				
			}
			else
			{					
				/* initialise counter for incoming Rx data bytes */
				/* block num + (255 - block num) + 128 data bytes + checksum */
				rx_byte_count = 131 ;
				/*	rx_byte_buffer_index is initiales to 1 to ensure correct boundary for the data */
				rx_byte_buffer_index = 1;

				status = XM_OK;

				while (rx_byte_count > 0)
				{
					/* recieve each byte of Rx data with 1 second timeout condition*/
					ret = GetByte(1000, (int8_t*)&rx_buffer[rx_byte_buffer_index++]);                    
					/* if timeout or comms error */
					if (ret == FALSE)
					{
						status = XM_TIMEOUT;
						/* send NAK and loop back to the start of while loop due to timeout*/
						R_UART1_Send_Byte(NAK);
						break;
					}
					else
					{
						rx_byte_count--;
					}
				}
				if (status == XM_TIMEOUT)
					continue;
				checksum = 0;
				for (rx_byte_buffer_index=0; rx_byte_buffer_index<128; rx_byte_buffer_index++)
				{
					checksum += rx_buffer[ rx_byte_buffer_index + 3 ];
					tmp = rx_buffer[ rx_byte_buffer_index + 3 ];
					UART_checksum += tmp;
				}
				
				/* if SOH, blk#, 255 - blk# or checksum not valid */
				if (!((rx_buffer[0] == SOH) && 
					((rx_buffer[1] == expected_blk_num) || (rx_buffer[1] == expected_blk_num - 1)) && 
					(rx_buffer[2] + rx_buffer[1] == 255) && 
					(rx_buffer[131] == checksum)))
				{
					/* send NAK and loop back to the start of while loop */
					R_UART1_Send_Byte(NAK);
				}
				else 
				{
					/* if blk# is expected blk num */
					if (rx_buffer[1] == expected_blk_num)
					{
						if ((Address<= FLASH_END_ADDRESS) && (Address >= flash_start_address))
						{
							status = WriteFlash(Address, (int8_t*)&rx_buffer[3], 128);
						}
						else 
						{
							status = XM_ADDRESS_ERROR;
						}


						if (status == FSL_OK)
						{
							/* if programming routine passed, then increase the flash address */
							Address += 128;
							expected_blk_num++;
							R_UART1_Send_Byte(ACK);
						}
						else
						{
							/* programming failed */
							R_UART1_Send_Byte(NAK);
							/* cancel xmodem download */
							R_UART1_Send_Byte(CAN);

							return (XM_PROG_FAIL);
						}

					}
					else
					{
						/* 	block number is valid but this data block has already been received */
						/*	send ACK to recieve next package */
						R_UART1_Send_Byte(ACK);
					}
				}
			} 
		}
	}	
}