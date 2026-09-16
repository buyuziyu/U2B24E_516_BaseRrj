/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "user_canif.h"
#include "r_cg_macrodriver.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define CAN_PASS '1'
#define CAN_FAIL '0'

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/
Can_PduType LddCanPduType;

// uint8 GaaByteArray0[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
// uint8 GaaByteArray1[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

uint8 GaaByteArray0[64] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
                            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 
                            0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 
                            0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 
                            0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 
                            0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 
                            0x60, 0x61, 0x62, 0x63};

uint8 GaaByteArray1[64] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
                            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 
                            0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 
                            0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 
                            0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 
                            0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 
                            0x60, 0x61, 0x62, 0x63};

uint8 GaaByteArray0_read[64] = {0};
uint8 GaaByteArray1_read[64] = {0};

uint8 can_read_test_0[64] = {0};
uint8 can_read_test_1[64] = {0};
uint32 can_read_id = 0;

uint8 GucTestResult[2];

uint32_t l_u32_can3_ackerr_cnt = 0;

/*******************************************************************************
|    code Declaration  
|******************************************************************************/

void CanIf_Init(void)
{
    // Std_ReturnType GenCanReturn;

    // (*(volatile uint32 *)0xffd92134) = 0x03001000u;

    // Can_Init(Can_Config);
    // Can_SetBaudrate(CanConf_CanController_CanController3, 0); 
    // Can_SetBaudrate(CanConf_CanController_CanController4, 0); 
    // GenCanReturn = Can_SetControllerMode(CanConf_CanController_CanController3, CAN_CS_STARTED); 
    // GenCanReturn = Can_SetControllerMode(CanConf_CanController_CanController4, CAN_CS_STARTED); 

    // Can_EnableControllerInterrupts(CanConf_CanController_CanController3);
    // Can_EnableControllerInterrupts(CanConf_CanController_CanController4);

    // Can_SetBaudrate(CanConf_CanController_CanController05, 5);
    // GenCanReturn = Can_SetControllerMode(CanConf_CanController_CanController05, CAN_CS_STARTED); 
    // Can_EnableControllerInterrupts(CanConf_CanController_CanController05);

}


void CanIf_Sample_test(void)
{
    // static uint8_t l_u8_can3_id = 0;
    // static uint8_t l_u8_can4_id = 0;

    // Std_ReturnType GenCanReturn;
    // Can_ControllerStateType LenCanCntlState;
    // uint8 LucHthId; 
    // uint32 LulCount; 

    // Can_ControllerStateType ControllerState;

    // Can_GetControllerMode(CanConf_CanController_CanController05,&ControllerState);
    // if(ControllerState!=CAN_CS_STARTED)
    // {
    //   GenCanReturn = Can_SetControllerMode(CanConf_CanController_CanController05, CAN_CS_STARTED);
    //   // while(1);
    // }

    // LucHthId = 0;
    // LddCanPduType.length = 64;
    // LddCanPduType.swPduHandle = 0x02;
    // LddCanPduType.id = 0x40000377;
    // // LddCanPduType.id = 0x00000123;
    // LddCanPduType.sdu = &GaaByteArray0[0];
    // GenCanReturn = Can_Write(LucHthId, &LddCanPduType);
    // if (E_OK == GenCanReturn)
    // {
    //   GucReturnCount++;
    // }
    // else
    // {
    //   /* No action Required */
    // }

    // LucHthId = 2;
    // LddCanPduType.length = 0x08;
    // LddCanPduType.swPduHandle = 0x02;
    // LddCanPduType.id = 0x40000002;
    // // LddCanPduType.id = 0x00000002;
    // LddCanPduType.sdu = &GaaByteArray1[0];
    // GenCanReturn = Can_Write(LucHthId, &LddCanPduType);
    // if (E_OK == GenCanReturn)
    // {
    //   GucReturnCount++;
    // }
    // else
    // {
    //   /* No action Required */
    // }
    
}

void CanIf_ack_check(void)
{
    // if(RSCFD0.CFDC3ERFL.BIT.AERR)
    // {
    //     RSCFD0.CFDC3ERFL.BIT.AERR = 0;
    //     l_u32_can3_ackerr_cnt++;
    // }
}

