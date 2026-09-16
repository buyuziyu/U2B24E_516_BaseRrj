/**************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
*
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
***************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_pic.h"
#include "r_pic_reg.h"
/*****************************************************************************
 Macro definitions
 *****************************************************************************/

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global static variables
 *****************************************************************************/

/*****************************************************************************
 Static functions
 *****************************************************************************/

/*****************************************************************************
--------------------- Global functions --------------------------------------
 *****************************************************************************/
/*****************************************************************************
 * Declaration : void R_Drv_PIC2_Init(void)
 * Description : Initialize PIC1B for trigger source for ADCK0SG3
 *               Initialize PIC1B for TSG30 Hi-Z control by ESO3 pin input
 * Parameters  : None
 * Return      : None
 *****************************************************************************/
void R_Drv_PIC2_Init(void)
{
    /* Selects TSG31ADTRG0 signal of TSG31 as the trigger source for ADCK0SG3 */
    R_PIC20ADCK_TSEL(0, 3) = (1 << 7);
    /* Selects TSG31ADTRG0 signal of TSG31 as the trigger source for ADCK1SG3 */
    R_PIC20ADCK_TSEL(1, 3) = (1 << 7);
    /* Selects TSG30ADTRG0 signal of TSG30 as the trigger source for ADCK1SG4 */
    R_PIC20ADCK_TSEL(1, 4) = (1 << 5);
}
/*****************************************************************************
--------------------- Static functions --------------------------------------
 *****************************************************************************/
