/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hw_pka.c
  * @author  GPM WBL Application Team
  * @brief   This file implements utility functions for PKA on stm32wb09
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x.h"
#include "pka_manager.h"
#include "stm32wb0x_ll_pka.h"
#include "hw_pka.h"

/** @defgroup PKA_Manager  PKA Manager
* @{
*/

#if defined(STM32WB09) || defined(STM32WB05)
/** @defgroup PKA_Manager_TypesDefinitions Private Type Definitions
* @{
*/
/* Internal state*/
typedef enum
{
  HW_PKA_STEP_0 = 0x0,
  HW_PKA_STEP_1,
  HW_PKA_STEP_2,
  HW_PKA_STEP_3,
  HW_PKA_STEP_4,
  HW_PKA_STEP_5,
  HW_PKA_STEP_6,
  HW_PKA_STEP_7,
  HW_PKA_STEP_8,
  HW_PKA_STEP_9,
  HW_PKA_STEP_10,
  HW_PKA_STEP_11,
  HW_PKA_STEP_12,
  HW_PKA_STEP_13,
  HW_PKA_STEP_END_SUCCESS
} StateMachine_Step;

typedef enum
{
  HW_PKA_OPERATION_NONE     =  0,
  HW_PKA_OPERATION_P256
} StateMachine_operation;

/**
* @}
*/
#endif /* STM32WB09 STM32WB05 */

/** @defgroup PKA_Manager_Private_Macros Private Macros
* @{
*/
static uint32_t ret[24] = {0};

#ifdef STM32WB05
static uint32_t T[4][8] = {0};
#endif /* STM32WB05 */

#if defined(STM32WB06) || defined(STM32WB07)
/* 0b0000 00XY. X: PKA_DATA_PCX error Y: PKA_DATA_PCY error */
static uint8_t PKA_SetDataError = 0x00;

#define HW_PKA_RAM_ECC_ADDR_KP_ERROR   (PKA_RAM_BASE)
#define HW_PKA_RAM_ECC_ADDR_K          (PKA_RAM_BASE + 0x6C)
#define HW_PKA_RAM_ECC_ADDR_PX         (PKA_RAM_BASE + 0x90)
#define HW_PKA_RAM_ECC_ADDR_PY         (PKA_RAM_BASE + 0xB4)

#define HW_PKA_DATA_SK                  0x01  /* PKA select data for K value */
#define HW_PKA_DATA_PCX                 0x02  /* PKA select data for Point X coordinate value */
#define HW_PKA_DATA_PCY                 0x03  /* PKA select data for Point Y coordinate value */
#endif /* STM32WB06 STM32WB07 */

#if defined(STM32WB09) || defined(STM32WB05)
static volatile uint32_t internalStateMachine_Operation = HW_PKA_OPERATION_NONE;
static volatile uint32_t internalStateMachine_Step = 0;

static volatile uint32_t bufferSecretKey[8] = {0};
static volatile uint32_t bufferPublicKey[16] = {0};

#define VERIFY_ECC_SCALAR_MUL_RESULT 1

static const uint32_t HW_PKA_oplen[2] = {
0x100,
0x0
};

static const uint32_t HW_PKA_nbits_k[2] = {
0x100,
0x0
};

static const uint32_t HW_PKA_nbits_m[2] = {
0x100,
0x0
};

static const uint32_t HW_PKA_a_coeff_sign[2] = {
0x1,
0x0
};

static const uint32_t HW_PKA_P256_gfp[8] =
{
  0xFFFFFFFF, /* LSB */
  0xFFFFFFFF,
  0xFFFFFFFF,
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000001,
  0xFFFFFFFF,
};

static const uint32_t HW_PKA_P256_r2[8] =
{
  0x00000002, /* LSB */
  0x00000005,
  0x00000003,
  0xFFFFFFFE,
  0xFFFFFFF9,
  0xFFFFFFFB,
  0xFFFFFFFC,
  0xFFFFFFFC,
};

static const uint32_t HW_PKA_P256_a[8] =
{
  0x00000003, /* LSB */
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000000,
};

static const uint32_t HW_PKA_P256_b[8] =
{
  0x27D2604B, /* LSB */
  0x3BCE3C3E,
  0xCC53B0F6,
  0x651D06B0,
  0x769886BC,
  0xB3EBBD55,
  0xAA3A93E7,
  0x5AC635D8,
};

/**
* @}
*/
#endif /* STM32WB09 STM32WB05 */

/** @defgroup PKA_Manager_External_Variables External Variables
* @{
*/

extern PKA_HandleTypeDef hpka;

/**
* @}
*/

/** @defgroup PKA_Manager_Private_FunctionPrototypes Private Function Prototypes
* @{
*/
void HW_PKA_ExitWithError(uint32_t errorCode);
void HW_PKA_ProcEnd_StateMachine(void);
void (*HW_PKA_funcCB_LP)(PKAMGR_ResultStatus error_code, void *args_p);
#if defined(STM32WB09) || defined(STM32WB05)
void HW_PKA_Comparison( const uint32_t* opLen, const uint32_t* op1 , const uint32_t* op2 );
void HW_PKA_P256_StartPointCheck( const uint32_t* x, const uint32_t* y );
uint32_t HW_PKA_IsPointCheckOk(void);
uint32_t HW_PKA_IsRangeCheckOk(void);
void HW_PKA_P256_StartEccScalarMul( const uint32_t* k, const uint32_t* pX, const uint32_t* pY );
void HW_PKA_P256_ReadEccScalarMul(uint32_t* pX, uint32_t* pY);
uint32_t HW_PKA_isStartPoint(const uint32_t* p);
#endif /* STM32WB09 STM32WB05 */
#ifdef STM32WB05
void HW_PKA_MontgomeryMultiplication( uint32_t opLen, const uint32_t* op1, const uint32_t* op2, const uint32_t* p);
#endif /* STM32WB05 */
/**
* @}
*/

/** @defgroup PKA_Manager_Private_Functions Private Functions
* @{
*/

#if defined STM32WB09

void HW_PKA_WriteSingleInput( uint32_t index,  int size, const uint32_t* word )
{
  /* Write the single word into PKA RAM */
  for(int i=0; i<size; i++)
  {
    PKA->RAM[index++] = *word++;
  }
}

#elif defined STM32WB05

void HW_PKA_WriteSingleInput( uint32_t index, uint32_t word )
{
  /* Write the single word into PKA RAM */
  PKA->RAM[index] = word;
}

#endif

#if defined STM32WB09

void HW_PKA_WriteOperand( uint32_t index, int size, const uint32_t* in )
  {
  uint32_t* pka_ram = (uint32_t*)&PKA->RAM[index];
  /* Write the input data into PKA RAM */
  for ( ; size > 0; size-- )
  {
    *pka_ram++ = *in++;
  }
  /* Write extra zeros into PKA RAM */
  *pka_ram++ = 0;
  *pka_ram = 0;
}

#elif defined STM32WB05

void HW_PKA_WriteOperand( uint32_t index, int size, const uint32_t* in )
{
  uint32_t* pka_ram = (uint32_t*)&PKA->RAM[index];
  /* Write the input data into PKA RAM */
  for ( ; size > 0; size-- )
  {
    *pka_ram++ = *in++;
  }
  /* Write extra zeros into PKA RAM */
  *pka_ram = 0;
}

#endif

#if defined(STM32WB05) || defined(STM32WB09)
void HW_PKA_ReadResult( uint32_t index, int size, uint32_t* out )
{
  uint32_t* pka_ram = (uint32_t*)&PKA->RAM[index];
  /* Read from PKA RAM */
  for ( ; size > 0; size-- )
  {
    *out++ = *pka_ram++;
  }
}
#endif /* STM32WB05 STM32WB09 */

#if defined STM32WB09

/**
  * @brief
  * @param  index PKA RAM index at 32 bit
  * @param  out   must be 64bit
  *
  */
void HW_PKA_ReadSingleOutput( uint32_t index, uint32_t* out)
{
  HW_PKA_ReadResult(index, 2, out);
}

#elif defined STM32WB05

/**
  * @brief
  * @param
  * @param
  *
  */
uint32_t HW_PKA_ReadSingleOutput( uint32_t index )
{
  /* Read a single word from PKA RAM */
  return PKA_RAM->RAM[index];
}

#endif /* STM32WB09 elif STM32WB05 */

#if defined(STM32WB06) || defined(STM32WB07)

void HAL_PKA_OperationCpltCallback(PKA_HandleTypeDef *hpka)
{
  PKAMGR_Unlock();
  HW_PKA_IRQHandler();
  PKAMGR_IRQCallback();
}

void HAL_PKA_ErrorCallback(PKA_HandleTypeDef *hpka)
{
  PKAMGR_Unlock();
  PKAMGR_IRQCallback();
}

/** @defgroup PKA_SELECT_DATA_VALUE Select Data for PKA operation
  * @{
  */
/**
  * @}
  */

/**
  * @brief  Internal Utility for PKA key range check
  * @param  a: pka key
  *         b: reference key
  *         bufferSize: key size
  * @retval check result
  */
static int rev_memcmp(uint8_t *a, const uint8_t *b, uint8_t  bufferSize)
{
    uint_fast8_t i = bufferSize;
    int retval = 0;

    do
    {
        i--;
        retval = (int)a[i] - (int)b[i];
        if (retval !=0)
        {
            break;
        }
    } while (i != 0U);

   return retval;
}

/**
  * @brief  Write the PKA RAM with the input data.
  * @param  dataType: select the region of PKA RAM to write:
  * @arg HW_PKA_DATA_SK is the K value
  * @arg HW_PKA_DATA_PCX is the point X coordinate
  * @arg HW_PKA_DATA_PCY is the point Y coordinate
  * @param  srcData Source Data
  * @retval ErrorStatus
  */
ErrorStatus HW_PKA_SetData(uint8_t dataType, uint32_t* srcData)
{
  const uint8_t P256_P_LE[32] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xff,0xff,0xff,0xff};
  const uint8_t BLE_P256_ABELIAN_ORDER_R_LE[32] = {0x51,0x25,0x63,0xFC,0xC2,0xCA,0xB9,0xF3,0x84,0x9E,0x17,0xA7,0xAD,0xFA,0xE6,0xBC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
  uint32_t StartAddress;
  uint8_t idx;

  /* Check the parameters */
  assert_param(IS_LL_PKA_CMD(dataType));

  if (dataType == HW_PKA_DATA_SK) {
    if (rev_memcmp((uint8_t *) srcData, (uint8_t *)BLE_P256_ABELIAN_ORDER_R_LE, 32) >= 0) {
      PKA_SetDataError |= 0x04;
      return ERROR;
    }
    else {
      PKA_SetDataError &= ~0x04;
    }
    StartAddress = HW_PKA_RAM_ECC_ADDR_K;
  }

  else if (dataType == HW_PKA_DATA_PCX) {
    if (rev_memcmp((uint8_t *) srcData, (uint8_t *)P256_P_LE, 32) >= 0) {
      PKA_SetDataError |= 0x01;
      return ERROR;
    }
    else {
      PKA_SetDataError &= ~0x01;
    }
    StartAddress = HW_PKA_RAM_ECC_ADDR_PX;

  }

  else if (dataType == HW_PKA_DATA_PCY) {
    if (rev_memcmp((uint8_t *) srcData, (uint8_t *)P256_P_LE, 32) >= 0) {
      PKA_SetDataError |= 0x02;
      return ERROR;
    }
    else {
      PKA_SetDataError &= ~0x02;
    }
    StartAddress = HW_PKA_RAM_ECC_ADDR_PY;
  }
  else
    return ERROR;

  /* Write the source data to target PKA RAM address. */
  for (idx = 0; idx<8; idx++)
  {
    *(uint32_t *)(StartAddress + 4*idx) = srcData[idx];
  }

  /* A 9th word of zeros must be added */
  *(uint32_t *)(StartAddress + 32UL) = 0x00000000;

  return SUCCESS;
}

/**
  * @brief  Get from the PKA RAM the output data.
  * @param  dataType: select the region of PKA RAM to read:
  * @arg HW_PKA_DATA_SK is the K value
  * @arg HW_PKA_DATA_PCX is the point X coordinate
  * @arg HW_PKA_DATA_PCY is the point Y coordinate
  * @param  dataTarget PKA RAM output data
  * @retval ErrorStatus
  */
ErrorStatus HW_PKA_GetData(uint8_t dataType, uint8_t* dataTarget)
{
  uint32_t StartAddress;

  /* Check the parameters */
  assert_param(IS_LL_PKA_CMD(dataType));

  if (dataType == HW_PKA_DATA_SK)
    StartAddress = HW_PKA_RAM_ECC_ADDR_K;
  else if (dataType == HW_PKA_DATA_PCX)
    StartAddress = HW_PKA_RAM_ECC_ADDR_PX;
  else if (dataType == HW_PKA_DATA_PCY)
    StartAddress = HW_PKA_RAM_ECC_ADDR_PY;
  else return ERROR;

  /* Read the data to target PKA RAM address. */
  for(uint8_t i=0;i<32;i++) {
    dataTarget[i] = ((uint8_t *)StartAddress)[i];
  }

  return SUCCESS;
}

#endif /* STM32WB06 STM32WB07 */

void HW_PKA_Init(void)
{
  PKAMGR_Init();
  /* Activate interrupts */
  LL_PKA_EnableIT_ADDRERR(PKA);
  LL_PKA_EnableIT_RAMERR(PKA);
  LL_PKA_EnableIT_PROCEND(PKA);
}

uint8_t HW_PKA_PowerSaveLevelCheck(void)
{
  if(PKAMGR_SleepCheck()==PKAMGR_SUCCESS)
  {
    return POWER_SAVE_LEVEL_STOP;
  }
  else // PKA on going
  {
    return POWER_SAVE_LEVEL_CPU_HALT;
  }
}

/**
  * @brief
  * @param
  * @param
  *
  */
PKAMGR_ResultStatus HW_PKA_StartP256DHkeyGeneration(const uint32_t* secretKey, const uint32_t* publicKey, PKAMGR_funcCB funcCB)
{
  /* Set the PKA internal state to busy */
  if(PKAMGR_Lock()!=PKAMGR_SUCCESS)
    return PKAMGR_ERR_BUSY;

  HW_PKA_funcCB_LP = funcCB;
#if defined(STM32WB09) || defined(STM32WB05)
  /* Save input data */
  for(int i=0;i<8;i++)
    bufferSecretKey[i] = secretKey[i];
  for(int i=0;i<16;i++)
    bufferPublicKey[i] = publicKey[i];

  if(HW_PKA_isStartPoint(publicKey))
  {
    /* p256 public key generation */
    internalStateMachine_Step = HW_PKA_STEP_3;
    internalStateMachine_Operation = HW_PKA_OPERATION_P256;
    HW_PKA_P256_StartEccScalarMul( secretKey, (uint32_t *)&publicKey[0], (uint32_t *)&publicKey[8] );
  }
  else
  {
    /* p256 dhkey generation */
    internalStateMachine_Step = HW_PKA_STEP_0;
    internalStateMachine_Operation = HW_PKA_OPERATION_P256;
    /* Call the PKA range check operation for public key X coordinate */
    HW_PKA_Comparison(HW_PKA_oplen, (uint32_t *)&publicKey[0], HW_PKA_P256_gfp);

#if !defined(ASYNC_MODE)
    // blocking mode (initial check steps interval time: 0.476ms)
    while(internalStateMachine_Step!=HW_PKA_STEP_1);

    /* Test result of range check operation for public key X coordinate */
    if( !HW_PKA_IsRangeCheckOk() )
    {
      internalStateMachine_Operation = HW_PKA_OPERATION_NONE;
      internalStateMachine_Step = HW_PKA_STEP_0;
      PKAMGR_Unlock();
      return PKAMGR_ERR_PARAM;
    }
    else
    {
      /* Call the PKA range check operation for public key Y coordinate */
      HW_PKA_Comparison(HW_PKA_oplen, (uint32_t *)&bufferPublicKey[8], HW_PKA_P256_gfp);
    }

    while(internalStateMachine_Step!=HW_PKA_STEP_2);

    /* Test result of range check operation for public key X coordinate */
    if( !HW_PKA_IsRangeCheckOk() )
    {
      internalStateMachine_Operation = HW_PKA_OPERATION_NONE;
      internalStateMachine_Step = HW_PKA_STEP_0;
      PKAMGR_Unlock();
      return PKAMGR_ERR_PARAM;
    }
    else
    {
      /* Call the PKA point check operation for remote public key */
      HW_PKA_P256_StartPointCheck( (uint32_t *)&bufferPublicKey[0], (uint32_t *)&bufferPublicKey[8] );
    }

    while(internalStateMachine_Step!=HW_PKA_STEP_3);

    /* Test result of point check operation for remote public key */
    if ( !HW_PKA_IsPointCheckOk() )
    {
      internalStateMachine_Operation = HW_PKA_OPERATION_NONE;
      internalStateMachine_Step = HW_PKA_STEP_0;
      PKAMGR_Unlock();
      return PKAMGR_ERR_PARAM;
    }
    else
    {
      /* Call the PKA scalar multiplication with the local private key
         as k and the remote public key as starting point,
         in order to compute the DH key */
      HW_PKA_P256_StartEccScalarMul( (uint32_t *)&bufferSecretKey[0], (uint32_t *)&bufferPublicKey[0], (uint32_t *)&bufferPublicKey[8] );
    }

#endif /* !defined(ASYNC_MODE) */
  }
#endif /* STM32WB09 STM32WB05 */

#if defined(STM32WB06) || defined(STM32WB07)
  /* ***** PROCEDURE FOR NewPoint ***** */

  /* Insert the random K for NewPoint */
  if(HW_PKA_SetData(HW_PKA_DATA_SK, (uint32_t*) secretKey) == ERROR)
  {
    PKAMGR_Unlock();
    return PKAMGR_ERR_PARAM;
  }

  /* Insert the initial starting point coordinates */
  if(HW_PKA_SetData(HW_PKA_DATA_PCX, (uint32_t *)&publicKey[0]) == ERROR)
  {
    PKAMGR_Unlock();
    return PKAMGR_ERR_PARAM;
  }

  if( HW_PKA_SetData(HW_PKA_DATA_PCY, (uint32_t *)&publicKey[8]) == ERROR)
  {
    PKAMGR_Unlock();
    return PKAMGR_ERR_PARAM;
  }

  /* Launch the computation in interrupt mode */
  LL_PKA_Start(PKA);
#endif /* STM32WB06 STM32WB07 */

  return PKAMGR_SUCCESS;
}

#if defined(STM32WB09) || defined(STM32WB05)
/**
  * @brief
  * @param
  * @param
  *
  */
void HW_PKA_ExitWithError(uint32_t errorCode)
{
  internalStateMachine_Operation = 0;
  internalStateMachine_Step = 0;
  PKAMGR_Unlock();
  ret[0]=errorCode;
  for(int i=0; i<8; i++)
  {
    ret[i+16] = bufferSecretKey[i];
  }
  HW_PKA_funcCB_LP(PKAMGR_ERROR, ret);
}

/**
  * @brief
  * @param
  * @param
  *
  */
void HW_PKA_ProcEnd_StateMachine(void)
{
  if(internalStateMachine_Operation == HW_PKA_OPERATION_P256)
  {
    switch(internalStateMachine_Step)
    {
      case HW_PKA_STEP_0:
        internalStateMachine_Step = HW_PKA_STEP_1;

      break;
      case HW_PKA_STEP_1:
        internalStateMachine_Step = HW_PKA_STEP_2;
        break;
      case HW_PKA_STEP_2:
          internalStateMachine_Step = HW_PKA_STEP_3;
          break;
      case HW_PKA_STEP_3:
            /* Read the PKA scalar multiplication result which is the DH key */
            for(int i=0;i<8;i++)
              ret[i] = bufferSecretKey[i];
            HW_PKA_P256_ReadEccScalarMul( (uint32_t *)&ret[8], (uint32_t *)&ret[16] );
#ifdef STM32WB09
            internalStateMachine_Step = HW_PKA_STEP_END_SUCCESS;
            HW_PKA_ProcEnd_StateMachine();
#endif /* STM32WB09 */

#ifdef STM32WB05
            if( VERIFY_ECC_SCALAR_MUL_RESULT )
            {
              internalStateMachine_Step = HW_PKA_STEP_4;
              HW_PKA_ReadResult( 739, 8, &ret[0] );
              HW_PKA_MontgomeryMultiplication( 256, &ret[0], &ret[0], HW_PKA_P256_gfp);
            }
            else
            {
            internalStateMachine_Step = HW_PKA_STEP_END_SUCCESS;
            HW_PKA_ProcEnd_StateMachine();
            }
          break;
       case HW_PKA_STEP_4:
         HW_PKA_ReadResult( 500, 8, &T[0][0] );

         internalStateMachine_Step = HW_PKA_STEP_5;

         /* Set the point coordinate X1 */
         HW_PKA_ReadResult( 634, 8, &ret[0]);
         HW_PKA_MontgomeryMultiplication( 256, &ret[0], &T[0][0], HW_PKA_P256_gfp);

         break;
       case HW_PKA_STEP_5:
         HW_PKA_ReadResult( 500, 8, &T[1][0] );

         internalStateMachine_Step = HW_PKA_STEP_6;
         /* Set the point coordinate Z1 */
         HW_PKA_ReadResult( 676, 8, &ret[0] );
         HW_PKA_MontgomeryMultiplication( 256, &ret[0], &ret[0], HW_PKA_P256_gfp);
         break;
       case HW_PKA_STEP_6:
         HW_PKA_ReadResult( 500, 8, &T[2][0] );

         internalStateMachine_Step = HW_PKA_STEP_7;
         /* Set the point coordinate X2 */
         HW_PKA_ReadResult( 697, 8, &ret[0] );
         HW_PKA_MontgomeryMultiplication( 256, &ret[0], &T[2][0], HW_PKA_P256_gfp);
         break;
       case HW_PKA_STEP_7:
         HW_PKA_ReadResult( 500, 8, &T[3][0] );

         internalStateMachine_Step = HW_PKA_STEP_8;
         HW_PKA_Comparison(HW_PKA_oplen, &T[1][0], &T[3][0]);
         break;
       case HW_PKA_STEP_8:
         internalStateMachine_Step = HW_PKA_STEP_9;
         if(HW_PKA_ReadSingleOutput(500)!=0)
         {
            HW_PKA_ExitWithError(0xFF00+HW_PKA_STEP_8);
         }
         else
         {
           /* Set the point coordinate Z2 */
           HW_PKA_ReadResult( 739, 8, &ret[0] );
           HW_PKA_MontgomeryMultiplication( 256, &ret[0], &T[0][0], HW_PKA_P256_gfp);
         }
         break;
       case HW_PKA_STEP_9:
         HW_PKA_ReadResult( 500, 8, &T[3][0] );

         internalStateMachine_Step = HW_PKA_STEP_10;
         /* Set the point coordinate Y1 */
         HW_PKA_ReadResult( 655, 8, &ret[0] );
         HW_PKA_MontgomeryMultiplication( 256, &ret[0], &T[3][0], HW_PKA_P256_gfp);
         break;
       case HW_PKA_STEP_10:
         HW_PKA_ReadResult( 500, 8, &T[0][0] );

         internalStateMachine_Step = HW_PKA_STEP_11;
         /* Set the point coordinate Z1 */
         HW_PKA_ReadResult( 676, 8, &ret[0] );
         HW_PKA_MontgomeryMultiplication( 256, &ret[0], &T[2][0], HW_PKA_P256_gfp);
         break;
       case HW_PKA_STEP_11:
         HW_PKA_ReadResult( 500, 8, &T[1][0] );

         internalStateMachine_Step = HW_PKA_STEP_12;
         /* Set the point coordinate Y2 */
         HW_PKA_ReadResult( 718, 8, &ret[0] );
         HW_PKA_MontgomeryMultiplication( 256, &ret[0], &T[1][0], HW_PKA_P256_gfp);
         break;
       case HW_PKA_STEP_12:
         HW_PKA_ReadResult( 500, 8, &T[2][0] );

         internalStateMachine_Step = HW_PKA_STEP_13;
         HW_PKA_Comparison(HW_PKA_oplen, &T[0][0], &T[2][0]);
         break;
       case HW_PKA_STEP_13:
         if(HW_PKA_ReadSingleOutput(500)!=0)
         {
            HW_PKA_ExitWithError(0xFF00+HW_PKA_STEP_13);
         }
         else
         {
           internalStateMachine_Step = HW_PKA_STEP_END_SUCCESS;
           HW_PKA_ProcEnd_StateMachine();
         }
#endif /* STM32WB05 */
          break;
       case HW_PKA_STEP_END_SUCCESS:
          internalStateMachine_Operation = HW_PKA_OPERATION_NONE;
          internalStateMachine_Step = HW_PKA_STEP_0;
          PKAMGR_Unlock();
          for(int i=0;i<8;i++)
            ret[i] = bufferSecretKey[i];
          HW_PKA_funcCB_LP(PKAMGR_SUCCESS, ret);
          break;
       default:
          HW_PKA_ExitWithError(0xA0);
    }
  }
}

/**
  * Brief   This function handles PKA Instance interrupt request.
  * Param   None
  * Retval  None
  */
void HW_PKA_IRQHandler(void)
{
   /* Manage the PKA RAM error flag */
  if(LL_PKA_IsActiveFlag_RAMERR(PKA) == 1)
  {
    LL_PKA_ClearFlag_RAMERR(PKA);
    HW_PKA_ExitWithError(0xB1);
  }

  /* Manage the Address error flag */
  if(LL_PKA_IsActiveFlag_ADDRERR(PKA) == 1)
  {
    LL_PKA_ClearFlag_ADDRERR(PKA);
    HW_PKA_ExitWithError(0xB2);
  }

  /* Manage the PKA End of Operation flag */
  if(LL_PKA_IsActiveFlag_PROCEND(PKA) == 1)
  {
    LL_PKA_ClearFlag_PROCEND(PKA);
    HW_PKA_ProcEnd_StateMachine();
  }
}

void HAL_PKA_OperationCpltCallback(PKA_HandleTypeDef *hpka)
{
  HW_PKA_ProcEnd_StateMachine();
  PKAMGR_IRQCallback();
}

void HAL_PKA_ErrorCallback(PKA_HandleTypeDef *hpka)
{
  HW_PKA_ExitWithError(hpka->ErrorCode);
  PKAMGR_IRQCallback();
}

/**
  * @brief
  * @param
  * @param
  *
  */
uint32_t HW_PKA_IsPointCheckOk(void)
{
#ifdef STM32WB09
  uint32_t result[2] = {0};
  HW_PKA_ReadResult( PKA_POINT_CHECK_OUT_ERROR, 2, &result[0] );
  return ( result[0] == 0xD60D);
#endif /* STM32WB09 */

#ifdef STM32WB05
  return (HW_PKA_ReadSingleOutput( 0 ) == 0);
#endif /* STM32WB05 */
}

/**
  * @brief
  * @param
  * @param
  *
  */
uint32_t HW_PKA_IsRangeCheckOk(void)
{
#ifdef STM32WB09
  uint32_t result[2] = {0};
  HW_PKA_ReadResult( PKA_COMPARISON_OUT_RESULT, 2, &result[0] );
  return ( result[0] == 0x916A);
#endif /* STM32WB09 */

#ifdef STM32WB05
  return (HW_PKA_ReadSingleOutput( 500 ) == 2);
#endif /* STM32WB05 */
}

/**
  * @brief
  * @param
  * @param
  *
  */
void HW_PKA_P256_StartEccScalarMul( const uint32_t* k, const uint32_t* pX, const uint32_t* pY )
{
  /* Set the configuration */
  LL_PKA_Config( PKA, LL_PKA_MODE_ECC_KP_PRIMITIVE );

  /* Enable the Security level */
  LL_PKA_SetSecurityLevel(PKA, LL_PKA_SECURITY_LEVEL_ENABLE);

#ifdef STM32WB09
  /* Set the scalar multiplier k length */
  HW_PKA_WriteSingleInput( PKA_ECC_SCALAR_MUL_IN_EXP_NB_BITS, 2, HW_PKA_nbits_k);
  /* Set the modulus length */
  HW_PKA_WriteSingleInput( PKA_ECC_SCALAR_MUL_IN_OP_NB_BITS, 2, HW_PKA_nbits_m);
  /* Set the coefficient a sign */
  HW_PKA_WriteSingleInput( PKA_ECC_SCALAR_MUL_IN_A_COEFF_SIGN, 2, HW_PKA_a_coeff_sign);
  /* Set the coefficient |a| */
  HW_PKA_WriteOperand( PKA_ECC_SCALAR_MUL_IN_A_COEFF, 8, HW_PKA_P256_a );
  /* Set the modulus value p */
  HW_PKA_WriteOperand( PKA_ECC_SCALAR_MUL_IN_MOD_GF, 8, HW_PKA_P256_gfp );
  /* Set the Montgomery parameter */
  HW_PKA_WriteOperand( PKA_ECC_SCALAR_MUL_IN_MONTGOMERY_PARAM, 8, HW_PKA_P256_r2 );
  /* Set the scalar multiplier k */
  HW_PKA_WriteOperand( PKA_ECC_SCALAR_MUL_IN_K, 8, k );
  /* Set the point P coordinate x */
  HW_PKA_WriteOperand( PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_X, 8, pX );
  /* Set the point P coordinate y */
  HW_PKA_WriteOperand( PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_Y, 8, pY );
#endif /* STM32WB09 */

#ifdef STM32WB05
  /* Set the scalar multiplier k length */
  HW_PKA_WriteSingleInput( 0, HW_PKA_nbits_k[0] );
  /* Set the modulus length */
  HW_PKA_WriteSingleInput( 1, HW_PKA_nbits_m[0] );
  /* Set the coefficient a sign */
  HW_PKA_WriteSingleInput( 2, HW_PKA_a_coeff_sign[0] );
  /* Set the coefficient |a| */
  HW_PKA_WriteOperand( 3, 8, HW_PKA_P256_a );
  /* Set the modulus value p */
  HW_PKA_WriteOperand( 24, 8, HW_PKA_P256_gfp );
  /* Set the Montgomery parameter */
  HW_PKA_WriteOperand( 45, 8, HW_PKA_P256_r2 );
  /* Set the scalar multiplier k */
  HW_PKA_WriteOperand( 66, 8, k );
  /* Set the point P coordinate x */
  HW_PKA_WriteOperand( 87, 8, pX );
  /* Set the point P coordinate y */
  HW_PKA_WriteOperand( 108, 8, pY );
#endif /* STM32WB05 */

  /* Wait for  PKA busy flag equal to 0 */
  while(LL_PKA_IsActiveFlag_BUSY(PKA));

  /* Start the PKA processing */
  LL_PKA_Start( PKA );
}

/**
  * @brief
  * @param
  * @param
  *
  */
void HW_PKA_Comparison( const uint32_t* opLen, const uint32_t* op1 , const uint32_t* op2 )
{
  LL_PKA_SetMode(PKA, LL_PKA_MODE_COMPARISON );
#ifdef STM32WB09
  /* Loads the input buffers to PKA RAM */
   /* Set the muber of bits of P */
  HW_PKA_WriteSingleInput( PKA_COMPARISON_NB_BITS, 2, opLen );
  /* Set the op1 */
  HW_PKA_WriteOperand( PKA_COMPARISON_IN_OP1, 8, op1 );
  /* Set the op2 */
  HW_PKA_WriteOperand( PKA_COMPARISON_IN_OP2, 8, op2 );
#endif /* STM32WB09 */

#ifdef STM32WB05
  /* Loads the input buffers to PKA RAM */
  /* Set the muber of bits of P */
  HW_PKA_WriteSingleInput( 1, opLen[0] );
  /* Set the op1 */
  HW_PKA_WriteOperand( 301, 8, op1 );
  /* Set the op2 */
  HW_PKA_WriteOperand( 401, 8, op2 );
#endif /* STM32WB05 */
  /* Wait for  PKA busy flag equal to 0 */
  while(LL_PKA_IsActiveFlag_BUSY(PKA));

  /* Launch the computation in interrupt mode */
  LL_PKA_Start(PKA);
}

void HW_PKA_P256_StartPointCheck( const uint32_t* x, const uint32_t* y )
{
  /* Set the configuration */
  LL_PKA_Config( PKA, LL_PKA_MODE_POINT_CHECK );
#ifdef STM32WB09
  /* Set the muber of bits of p */
  HW_PKA_WriteSingleInput(  PKA_POINT_CHECK_IN_MOD_NB_BITS, 2, HW_PKA_nbits_m);
  /* Set the coefficient a sign */
  HW_PKA_WriteSingleInput( PKA_POINT_CHECK_IN_A_COEFF_SIGN, 2, HW_PKA_a_coeff_sign);
  /* Set the coefficient |a| */
  HW_PKA_WriteOperand( PKA_POINT_CHECK_IN_A_COEFF, 8, HW_PKA_P256_a );
  /* Set the modulus value p */
  HW_PKA_WriteOperand( PKA_POINT_CHECK_IN_MOD_GF, 8, HW_PKA_P256_gfp );
  /* Set the point coordinate x */
  HW_PKA_WriteOperand( PKA_POINT_CHECK_IN_INITIAL_POINT_X, 8, x );
  /* Set the point coordinate y */
  HW_PKA_WriteOperand( PKA_POINT_CHECK_IN_INITIAL_POINT_Y, 8, y );
  /* Set the Montgomery parameter */
  HW_PKA_WriteOperand( PKA_POINT_CHECK_IN_MONTGOMERY, 8, HW_PKA_P256_r2 );
  /* Set the coefficient |b| */
  HW_PKA_WriteOperand( PKA_POINT_CHECK_IN_B_COEFF, 8, HW_PKA_P256_b );
#endif /* STM32WB09 */

#ifdef STM32WB05
  /* Set the muber of bits of p */
  HW_PKA_WriteSingleInput( 1, 256 );
  /* Set the coefficient a sign */
  HW_PKA_WriteSingleInput( 2, 1 );
  /* Set the coefficient |a| */
  HW_PKA_WriteOperand( 3, 8, HW_PKA_P256_a );
  /* Set the modulus value p */
  HW_PKA_WriteOperand( 24, 8, HW_PKA_P256_gfp );
  /* Set the point coordinate x */
  HW_PKA_WriteOperand( 87, 8, x );
  /* Set the point coordinate y */
  HW_PKA_WriteOperand( 108, 8, y );
  /* Set the coefficient |b| */
  HW_PKA_WriteOperand( 255, 8, HW_PKA_P256_b );
#endif /* STM32WB05 */

  /* Wait for  PKA busy flag equal to 0 */
  while(LL_PKA_IsActiveFlag_BUSY(PKA));

  /* Start the PKA processing */
  LL_PKA_Start( PKA );
}

#ifdef STM32WB05
void HW_PKA_MontgomeryMultiplication( uint32_t opLen, const uint32_t* op1, const uint32_t* op2, const uint32_t* p)
{
  /* Set the configuration */
  LL_PKA_Config( PKA, LL_PKA_MODE_MONTGOMERY_MUL );

  /* Loads the input buffers to PKA RAM */
  /* Set the operand length */
  HW_PKA_WriteSingleInput( 1, opLen);
  /* Set the op1 */
  HW_PKA_WriteOperand( 301, 8, op1);
  /* Set the op2 */
  HW_PKA_WriteOperand( 401, 8, op2);
  /* Set the modulus value p */
  HW_PKA_WriteOperand( 599, 8, p );

  /* Wait for  PKA busy flag equal to 0 */
  while(LL_PKA_IsActiveFlag_BUSY(PKA));

  /* Start the PKA processing */
  LL_PKA_Start( PKA );
}
#endif /* STM32WB05 */

/**
  * @brief
  * @param
  * @param
  *
  */
void HW_PKA_P256_ReadEccScalarMul( uint32_t* pX, uint32_t* pY )
{
#ifdef STM32WB09
  /* Read the output point X */
  if( pX )
  {
    HW_PKA_ReadResult( PKA_ECC_SCALAR_MUL_OUT_RESULT_X, 8, pX );
  }
  /* Read the output point Y as the second half of the result */
  if( pY )
  {
    HW_PKA_ReadResult( PKA_ECC_SCALAR_MUL_OUT_RESULT_Y, 8, pY );
  }
#endif /* STM32WB09 */

#ifdef STM32WB05
  /* Read the output point X */
  if( pX )
  {
    HW_PKA_ReadResult( 87, 8, pX );
  }
  /* Read the output point Y as the second half of the result */
  if( pY )
  {
    HW_PKA_ReadResult( 108, 8, pY );
  }
#endif /* STM32WB05 */
}

/**
  * Brief   This function checks if the param p is equal to the Start Point.
  * Param   Publick key p
  * Retval  1 if p is equal to the Start Point. 0 in other cases.
  */
uint32_t HW_PKA_isStartPoint(const uint32_t* p)
{
  for(int i=0; i<16; i++)
  {
    if(PKAStartPoint[i]!=p[i])
      return 0;
  }
  return 1;
}

/**
* @}
*/

#endif /* STM32WB09 STM32WB05 */

#if defined(STM32WB06) || defined(STM32WB07)

/**
  * @brief  PKA verification of process command.
  * @param  None
  * @retval ErrorStatus
*/
ErrorStatus HW_PKA_VerifyProcess(void)
{
  uint32_t errorCode;

  if(PKA_SetDataError != 0x00)
    return ERROR;

  errorCode = *(uint32_t *)(HW_PKA_RAM_ECC_ADDR_KP_ERROR);

  if (errorCode == 0) {
    return SUCCESS;
  }
  else {
    return ERROR;
  }
}

/**
  * Brief   This function handles PKA Instance interrupt request.
  * Param   None
  * Retval  None
*/
void HW_PKA_IRQHandler(void)
{
    /* Compare to expected results */
    if (HW_PKA_VerifyProcess() == ERROR)
    {
      PKAMGR_Unlock();
      ret[0] = 0x03;
	  HW_PKA_funcCB_LP(PKAMGR_ERR_PROCESS, ret);
    }
    else
    {
      for(int i=0; i<24; i++)
        ret[i] = 0;
      /*  | Secret Key  | Public Key X-coord | Public Key Y-coord | */
      /*  | (32 octets) | (32 octets)        | (32 octets)        | */
      /* Get the new calculated point NewPoint of the ellipse       */
      HW_PKA_GetData(HW_PKA_DATA_SK, (uint8_t *)&ret[0]);
      HW_PKA_GetData(HW_PKA_DATA_PCX, (uint8_t *)&ret[8]);
      HW_PKA_GetData(HW_PKA_DATA_PCY, (uint8_t *)&ret[16]);

      PKAMGR_Unlock();
      HW_PKA_funcCB_LP(PKAMGR_SUCCESS, ret);
    }
}

#endif /* STM32WB06 STM32WB07 */

/**
* @}
*/
