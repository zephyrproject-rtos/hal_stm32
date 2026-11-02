/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_ll_flash.h
  * @brief   Header file of LL FLASH driver module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H7PXX_LL_FLASH_H
#define STM32H7PXX_LL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_LL_Driver
  * @{
  */

#if defined (FLASH)
/** @defgroup FLASH_LL FLASH
  * @{
  */

/* Exported Constants ------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Constants LL FLASH Constants
  * @{
  */

/** @defgroup FLASH_Unlock_Keys FLASH Unlock Keys
  * @{
  */
#define LL_FLASH_KEY1 0x45670123U /*!< LL FLASH key1 */
#define LL_FLASH_KEY2 0xCDEF89ABU /*!< LL FLASH key2 */
/**
  * @}
  */

/** @defgroup FLASH_OB_Unlock_Keys FLASH OB Unlock Keys
  * @{
  */
#define LL_FLASH_OB_OPTKEY1 0x08192A3BU /*!< LL FLASH option byte key1 */
#define LL_FLASH_OB_OPTKEY2 0x4C5D6E7FU /*!< LL FLASH option byte key2 */
/**
  * @}
  */

/** @defgroup FLASH_Bank_Selection FLASH Bank Selection
  * @{
  */
#define LL_FLASH_BANK_1 0x0U /*!< LL FLASH bank 1 selection */
#define LL_FLASH_BANK_2 0x1U /*!< LL FLASH bank 2 selection */
/**
  * @}
  */

/** @defgroup FLASH_Status_Flags FLASH Status Flags
  * @{
  */
#define LL_FLASH_FLAG_BUSY         FLASH_ASR_BUSY                 /*!< Busy flag                   */
#define LL_FLASH_FLAG_WBNE         FLASH_ASR_WBNE                 /*!< Write buffer not empty flag */
#define LL_FLASH_FLAG_QW           FLASH_ASR_QW                   /*!< Wait queue flag             */
#define LL_FLASH_FLAG_CRC_BUSY     FLASH_ASR_CRC_BUSY             /*!< CRC busy flag               */
#define LL_FLASH_FLAG_IS_PROGRAM   FLASH_ASR_IS_PROGRAM           /*!< Is a program flag           */
#define LL_FLASH_FLAG_IS_ERASE     FLASH_ASR_IS_ERASE             /*!< Is an erase flag            */
#define LL_FLASH_FLAG_IS_OPTCHANGE FLASH_ASR_IS_OPTCHANGE         /*!< Is an option change flag    */
#define LL_FLASH_FLAG_STATUS_ALL   (LL_FLASH_FLAG_BUSY | LL_FLASH_FLAG_WBNE \
                                    | LL_FLASH_FLAG_QW | LL_FLASH_FLAG_CRC_BUSY \
                                    | LL_FLASH_FLAG_IS_PROGRAM | LL_FLASH_FLAG_IS_ERASE \
                                    | LL_FLASH_FLAG_IS_OPTCHANGE) /*!< All status flags            */

#define LL_FLASH_FLAG_SWAP_BANK    FLASH_ASR_SWAP_BANK            /*!< Swapped bank flag           */
/**
  * @}
  */

/** @defgroup FLASH_Interrupt_Flags FLASH Interrupt Flags
  * @{
  */
#define LL_FLASH_IT_EOP      FLASH_AIER_EOPIE                   /*!< End-of-program interrupt control bit            */
#define LL_FLASH_IT_WRPERR   FLASH_AIER_WRPERRIE                /*!< Write protection error interrupt enable bit     */
#define LL_FLASH_IT_PGSERR   FLASH_AIER_PGSERRIE                /*!< Programming sequence error interrupt enable bit */
#define LL_FLASH_IT_STRBERR  FLASH_AIER_STRBERRIE               /*!< Strobe error interrupt enable bit               */
#define LL_FLASH_IT_OBLERR   FLASH_AIER_OBLERRIE                /*!< Option byte loading error interrupt enable bit  */
#define LL_FLASH_IT_INCERR   FLASH_AIER_INCERRIE                /*!< Inconsistency error interrupt enable bit        */
#define LL_FLASH_IT_RDSERR   FLASH_AIER_RDSERRIE                /*!< Read security error interrupt enable bit        */
#define LL_FLASH_IT_CRCEND   FLASH_AIER_CRCENDIE                /*!< CRC end of calculation interrupt enable bit     */
#define LL_FLASH_IT_CRCRDERR FLASH_AIER_CRCRDERRIE              /*!< CRC read error interrupt enable bit             */
#define LL_FLASH_IT_ALL      (LL_FLASH_IT_EOP | LL_FLASH_IT_WRPERR \
                              | LL_FLASH_IT_PGSERR | LL_FLASH_IT_STRBERR \
                              | LL_FLASH_IT_OBLERR | LL_FLASH_IT_INCERR \
                              | LL_FLASH_IT_RDSERR | LL_FLASH_IT_CRCEND \
                              | LL_FLASH_IT_CRCRDERR)           /*!< All interrupt flags                             */

#define LL_FLASH_IT_SNECCERR FLASH_AIER_SNECCERRIE /*!< ECC single correction error interrupt enable bit */
#define LL_FLASH_IT_DBECCERR FLASH_AIER_DBECCERRIE /*!< ECC double detection error interrupt enable bit  */
#define LL_FLASH_IT_ECC_ALL  (LL_FLASH_IT_SNECCERR | LL_FLASH_IT_DBECCERR) /*!< All ECC error interrupt enable bits */

#define LL_FLASH_IT_OBKERR FLASH_OPTCR_OBKERRIE /*!< Option byte key error interrupt enable bit    */
#define LL_FLASH_IT_OPTERR FLASH_OPTCR_OPTERRIE /*!< Option byte change error interrupt enable bit */
#define LL_FLASH_OB_IT_ALL (LL_FLASH_IT_OBKERR | LL_FLASH_IT_OPTERR)/*!< All OB interrupt flags */
/**
  * @}
  */

/** @defgroup FLASH_Error_Flags FLASH Error Flags
  * @{
  */
#define LL_FLASH_FLAG_WRPERR     FLASH_AISR_WRPERRF         /*!< Write protection error flag     */
#define LL_FLASH_FLAG_PGSERR     FLASH_AISR_PGSERRF         /*!< Programming sequence error flag */
#define LL_FLASH_FLAG_STRBERR    FLASH_AISR_STRBERRF        /*!< Strobe error flag               */
#define LL_FLASH_FLAG_OBLERR     FLASH_AISR_OBLERRF         /*!< Option byte loading error flag  */
#define LL_FLASH_FLAG_INCERR     FLASH_AISR_INCERRF         /*!< Inconsistency error flag        */
#define LL_FLASH_FLAG_RDSERR     FLASH_AISR_RDSERRF         /*!< Read security error flag        */
#define LL_FLASH_FLAG_CRCRDERR   FLASH_AISR_CRCRDERRF       /*!< CRC read error flag             */
#define LL_FLASH_FLAG_ERRORS_ALL (LL_FLASH_FLAG_WRPERR | LL_FLASH_FLAG_PGSERR \
                                  | LL_FLASH_FLAG_STRBERR | LL_FLASH_FLAG_OBLERR \
                                  | LL_FLASH_FLAG_INCERR | LL_FLASH_FLAG_RDSERR \
                                  | LL_FLASH_FLAG_CRCRDERR) /*!< All error flags                 */

#define LL_FLASH_FLAG_SNECCERR FLASH_AISR_SNECCERRF                              /*!< ECC single error flag */
#define LL_FLASH_FLAG_DBECCERR FLASH_AISR_DBECCERRF                              /*!< ECC double error flag */
#define LL_FLASH_FLAG_ECC_ALL  (LL_FLASH_FLAG_SNECCERR | LL_FLASH_FLAG_DBECCERR) /*!< All ECC error flags   */

#define LL_FLASH_FLAG_EOPF    FLASH_AISR_EOPF    /*!< End-of-program flag */
#define LL_FLASH_FLAG_CRCENDF FLASH_AISR_CRCENDF /*!< CRC end flag        */

#define LL_FLASH_FLAG_OBKERR FLASH_OPTISR_OBKERRF /*!< Option byte key error flag    */
#define LL_FLASH_FLAG_OPTERR FLASH_OPTISR_OPTERRF /*!< Option byte change error flag */
/**
  * @}
  */

/** @defgroup FLASH_Write_Protection_Pages FLASH Write Protection Pages
  * @{
  */
#define LL_FLASH_OB_WRP_PAGE_0TO3       FLASH_AWRPSR_WRPSG_0    /*!< Write protection of Pages 0 to 3     */
#define LL_FLASH_OB_WRP_PAGE_4TO7       FLASH_AWRPSR_WRPSG_1    /*!< Write protection of Pages 4 to 7     */
#define LL_FLASH_OB_WRP_PAGE_8TO11      FLASH_AWRPSR_WRPSG_2    /*!< Write protection of Pages 8 to 11    */
#define LL_FLASH_OB_WRP_PAGE_12TO15     FLASH_AWRPSR_WRPSG_3    /*!< Write protection of Pages 12 to 15   */
#define LL_FLASH_OB_WRP_PAGE_16TO19     FLASH_AWRPSR_WRPSG_4    /*!< Write protection of Pages 16 to 19   */
#define LL_FLASH_OB_WRP_PAGE_20TO23     FLASH_AWRPSR_WRPSG_5    /*!< Write protection of Pages 20 to 23   */
#define LL_FLASH_OB_WRP_PAGE_24TO27     FLASH_AWRPSR_WRPSG_6    /*!< Write protection of Pages 24 to 27   */
#define LL_FLASH_OB_WRP_PAGE_28TO31     FLASH_AWRPSR_WRPSG_7    /*!< Write protection of Pages 28 to 31   */
#define LL_FLASH_OB_WRP_PAGE_32TO35     FLASH_AWRPSR_WRPSG_8    /*!< Write protection of Pages 32 to 35   */
#define LL_FLASH_OB_WRP_PAGE_36TO39     FLASH_AWRPSR_WRPSG_9    /*!< Write protection of Pages 36 to 39   */
#define LL_FLASH_OB_WRP_PAGE_40TO43     FLASH_AWRPSR_WRPSG_10   /*!< Write protection of Pages 40 to 43   */
#define LL_FLASH_OB_WRP_PAGE_44TO47     FLASH_AWRPSR_WRPSG_11   /*!< Write protection of Pages 44 to 47   */
#define LL_FLASH_OB_WRP_PAGE_48TO51     FLASH_AWRPSR_WRPSG_12   /*!< Write protection of Pages 48 to 51   */
#define LL_FLASH_OB_WRP_PAGE_52TO55     FLASH_AWRPSR_WRPSG_13   /*!< Write protection of Pages 52 to 55   */
#define LL_FLASH_OB_WRP_PAGE_56TO59     FLASH_AWRPSR_WRPSG_14   /*!< Write protection of Pages 56 to 59   */
#define LL_FLASH_OB_WRP_PAGE_60TO63     FLASH_AWRPSR_WRPSG_15   /*!< Write protection of Pages 60 to 63   */
#define LL_FLASH_OB_WRP_PAGE_64TO67     FLASH_AWRPSR_WRPSG_16   /*!< Write protection of Pages 64 to 67   */
#define LL_FLASH_OB_WRP_PAGE_68TO71     FLASH_AWRPSR_WRPSG_17   /*!< Write protection of Pages 68 to 71   */
#define LL_FLASH_OB_WRP_PAGE_72TO75     FLASH_AWRPSR_WRPSG_18   /*!< Write protection of Pages 72 to 75   */
#define LL_FLASH_OB_WRP_PAGE_76TO79     FLASH_AWRPSR_WRPSG_19   /*!< Write protection of Pages 76 to 79   */
#define LL_FLASH_OB_WRP_PAGE_80TO83     FLASH_AWRPSR_WRPSG_20   /*!< Write protection of Pages 80 to 83   */
#define LL_FLASH_OB_WRP_PAGE_84TO87     FLASH_AWRPSR_WRPSG_21   /*!< Write protection of Pages 84 to 87   */
#define LL_FLASH_OB_WRP_PAGE_88TO91     FLASH_AWRPSR_WRPSG_22   /*!< Write protection of Pages 88 to 91   */
#define LL_FLASH_OB_WRP_PAGE_92TO95     FLASH_AWRPSR_WRPSG_23   /*!< Write protection of Pages 92 to 95   */
#define LL_FLASH_OB_WRP_PAGE_96TO99     FLASH_AWRPSR_WRPSG_24   /*!< Write protection of Pages 96 to 99   */
#define LL_FLASH_OB_WRP_PAGE_100TO103   FLASH_AWRPSR_WRPSG_25   /*!< Write protection of Pages 100 to 103 */
#define LL_FLASH_OB_WRP_PAGE_104TO107   FLASH_AWRPSR_WRPSG_26   /*!< Write protection of Pages 104 to 107 */
#define LL_FLASH_OB_WRP_PAGE_108TO111   FLASH_AWRPSR_WRPSG_27   /*!< Write protection of Pages 108 to 111 */
#define LL_FLASH_OB_WRP_PAGE_112TO115   FLASH_AWRPSR_WRPSG_28   /*!< Write protection of Pages 112 to 115 */
#define LL_FLASH_OB_WRP_PAGE_116TO119   FLASH_AWRPSR_WRPSG_29   /*!< Write protection of Pages 116 to 119 */
#define LL_FLASH_OB_WRP_PAGE_120TO123   FLASH_AWRPSR_WRPSG_30   /*!< Write protection of Pages 120 to 123 */
#define LL_FLASH_OB_WRP_PAGE_124TO127   FLASH_AWRPSR_WRPSG_31   /*!< Write protection of Pages 124 to 127 */
#define LL_FLASH_OB_WRP_PAGE_ALL        FLASH_AWRPSR_WRPSG      /*!< Write protection of all Pages        */
/**
  * @}
  */

/** @defgroup FLASH_OTP_Lock_Blocks FLASH OTP Lock Blocks
  * @{
  */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_0     FLASH_OTPLSR_OTPL_0    /*!< OTP Blocks 0 locked   */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_1     FLASH_OTPLSR_OTPL_1    /*!< OTP Blocks 1 locked   */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_2     FLASH_OTPLSR_OTPL_2    /*!< OTP Blocks 2 locked   */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_3     FLASH_OTPLSR_OTPL_3    /*!< OTP Blocks 3 locked   */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_4     FLASH_OTPLSR_OTPL_4    /*!< OTP Blocks 4 locked   */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_5     FLASH_OTPLSR_OTPL_5    /*!< OTP Blocks 5 locked   */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_6     FLASH_OTPLSR_OTPL_6    /*!< OTP Blocks 6 locked   */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_7     FLASH_OTPLSR_OTPL_7    /*!< OTP Blocks 7 locked   */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_8     FLASH_OTPLSR_OTPL_8    /*!< OTP Blocks 8 locked   */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_9     FLASH_OTPLSR_OTPL_9    /*!< OTP Blocks 9 locked   */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_10    FLASH_OTPLSR_OTPL_10   /*!< OTP Blocks 10 locked  */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_11    FLASH_OTPLSR_OTPL_11   /*!< OTP Blocks 11 locked  */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_12    FLASH_OTPLSR_OTPL_12   /*!< OTP Blocks 12 locked  */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_13    FLASH_OTPLSR_OTPL_13   /*!< OTP Blocks 13 locked  */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_14    FLASH_OTPLSR_OTPL_14   /*!< OTP Blocks 14 locked  */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_15    FLASH_OTPLSR_OTPL_15   /*!< OTP Blocks 15 locked  */
#define LL_FLASH_OB_OTP_LOCK_BLOCK_ALL   FLASH_OTPLSR_OTPL      /*!< OTP all Blocks locked */
/**
  * @}
  */

/** @defgroup FLASH_OBK FLASH OBK
  * @{
  */
#define LL_FLASH_OBK_EKEY_0     FLASH_OBKCLR_EKEY0    /*!< OBK Erase key #0   */
#define LL_FLASH_OBK_EKEY_1     FLASH_OBKCLR_EKEY1    /*!< OBK Erase key #1   */
#define LL_FLASH_OBK_EKEY_2     FLASH_OBKCLR_EKEY2    /*!< OBK Erase key #2   */
#define LL_FLASH_OBK_EKEY_3     FLASH_OBKCLR_EKEY3    /*!< OBK Erase key #3   */
#define LL_FLASH_OBK_EKEY_4     FLASH_OBKCLR_EKEY4    /*!< OBK Erase key #4   */
#define LL_FLASH_OBK_EKEY_5     FLASH_OBKCLR_EKEY5    /*!< OBK Erase key #5   */
#define LL_FLASH_OBK_EKEY_6     FLASH_OBKCLR_EKEY6    /*!< OBK Erase key #6   */
#define LL_FLASH_OBK_EKEY_7     FLASH_OBKCLR_EKEY7    /*!< OBK Erase key #7   */
#define LL_FLASH_OBK_EKEY_8     FLASH_OBKCLR_EKEY8    /*!< OBK Erase key #8   */
#define LL_FLASH_OBK_EKEY_9     FLASH_OBKCLR_EKEY9    /*!< OBK Erase key #9   */
#define LL_FLASH_OBK_EKEY_10    FLASH_OBKCLR_EKEY10   /*!< OBK Erase key #10  */
#define LL_FLASH_OBK_EKEY_11    FLASH_OBKCLR_EKEY11   /*!< OBK Erase key #11  */
#define LL_FLASH_OBK_EKEY_12    FLASH_OBKCLR_EKEY12   /*!< OBK Erase key #12  */
#define LL_FLASH_OBK_EKEY_13    FLASH_OBKCLR_EKEY13   /*!< OBK Erase key #13  */
#define LL_FLASH_OBK_EKEY_14    FLASH_OBKCLR_EKEY14   /*!< OBK Erase key #14  */
#define LL_FLASH_OBK_EKEY_15    FLASH_OBKCLR_EKEY15   /*!< OBK Erase key #15  */
#define LL_FLASH_OBK_EKEY_16    FLASH_OBKCLR_EKEY16   /*!< OBK Erase key #16  */
#define LL_FLASH_OBK_EKEY_17    FLASH_OBKCLR_EKEY17   /*!< OBK Erase key #17  */
#define LL_FLASH_OBK_EKEY_18    FLASH_OBKCLR_EKEY18   /*!< OBK Erase key #18  */
#define LL_FLASH_OBK_EKEY_19    FLASH_OBKCLR_EKEY19   /*!< OBK Erase key #19  */
#define LL_FLASH_OBK_EKEY_20    FLASH_OBKCLR_EKEY20   /*!< OBK Erase key #20  */
#define LL_FLASH_OBK_EKEY_21    FLASH_OBKCLR_EKEY21   /*!< OBK Erase key #21  */
#define LL_FLASH_OBK_EKEY_22    FLASH_OBKCLR_EKEY22   /*!< OBK Erase key #22  */
#define LL_FLASH_OBK_EKEY_23    FLASH_OBKCLR_EKEY23   /*!< OBK Erase key #23  */
#define LL_FLASH_OBK_EKEY_24    FLASH_OBKCLR_EKEY24   /*!< OBK Erase key #24  */
#define LL_FLASH_OBK_EKEY_25    FLASH_OBKCLR_EKEY25   /*!< OBK Erase key #25  */
#define LL_FLASH_OBK_EKEY_26    FLASH_OBKCLR_EKEY26   /*!< OBK Erase key #26  */
#define LL_FLASH_OBK_EKEY_27    FLASH_OBKCLR_EKEY27   /*!< OBK Erase key #27  */
#define LL_FLASH_OBK_EKEY_28    FLASH_OBKCLR_EKEY28   /*!< OBK Erase key #28  */
#define LL_FLASH_OBK_EKEY_29    FLASH_OBKCLR_EKEY29   /*!< OBK Erase key #29  */
#define LL_FLASH_OBK_EKEY_30    FLASH_OBKCLR_EKEY30   /*!< OBK Erase key #30  */
#define LL_FLASH_OBK_EKEY_31    FLASH_OBKCLR_EKEY31   /*!< OBK Erase key #31  */
#define LL_FLASH_OBK_EKEY_ALL   (0xFFFFFFFFU)         /*!< All OBK Erase Keys */
/**
  * @}
  */

/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define LL_FLASH_LATENCY_0WS  0x00000000U                                     /*!< 0 wait states */
#define LL_FLASH_LATENCY_1WS  (FLASH_ACCR_LATENCY_0)                          /*!< 1 wait states */
#define LL_FLASH_LATENCY_2WS  (FLASH_ACCR_LATENCY_1)                          /*!< 2 wait states */
#define LL_FLASH_LATENCY_3WS  (FLASH_ACCR_LATENCY_1 | FLASH_ACCR_LATENCY_0)   /*!< 3 wait states */
#define LL_FLASH_LATENCY_4WS  (FLASH_ACCR_LATENCY_2)                          /*!< 4 wait states */
#define LL_FLASH_LATENCY_5WS  (FLASH_ACCR_LATENCY_2 | FLASH_ACCR_LATENCY_0)   /*!< 5 wait states */
#define LL_FLASH_LATENCY_6WS  (FLASH_ACCR_LATENCY_2 | FLASH_ACCR_LATENCY_1)   /*!< 6 wait states */
#define LL_FLASH_LATENCY_7WS  (FLASH_ACCR_LATENCY_2 | FLASH_ACCR_LATENCY_0 \
                               | FLASH_ACCR_LATENCY_1)                        /*!< 7 wait states */
#define LL_FLASH_LATENCY_8WS  (FLASH_ACCR_LATENCY_3)                          /*!< 8 wait states */
#define LL_FLASH_LATENCY_9WS  (FLASH_ACCR_LATENCY_3 | FLASH_ACCR_LATENCY_0)   /*!< 9 wait states */
#define LL_FLASH_LATENCY_10WS (FLASH_ACCR_LATENCY_3 | FLASH_ACCR_LATENCY_1)   /*!< 10 wait states */
#define LL_FLASH_LATENCY_11WS (FLASH_ACCR_LATENCY_3 | FLASH_ACCR_LATENCY_0 \
                               | FLASH_ACCR_LATENCY_1)                        /*!< 11 wait states */
#define LL_FLASH_LATENCY_12WS (FLASH_ACCR_LATENCY_3 | FLASH_ACCR_LATENCY_2)   /*!< 12 wait states */
#define LL_FLASH_LATENCY_13WS (FLASH_ACCR_LATENCY_3 | FLASH_ACCR_LATENCY_0 \
                               | FLASH_ACCR_LATENCY_2)                        /*!< 13 wait states */
#define LL_FLASH_LATENCY_14WS (FLASH_ACCR_LATENCY_3 | FLASH_ACCR_LATENCY_1 \
                               | FLASH_ACCR_LATENCY_2)                        /*!< 14 wait states */
#define LL_FLASH_LATENCY_15WS (FLASH_ACCR_LATENCY_3 | FLASH_ACCR_LATENCY_0 \
                               | FLASH_ACCR_LATENCY_1 | FLASH_ACCR_LATENCY_2) /*!< 15 wait states */
/**
  * @}
  */

/** @defgroup FLASH_Programming_delay FLASH Programming Delay
  * @{
  */
#define LL_FLASH_PROGRAM_DELAY_0   0x00000000U                                         /*!< programming delay range 0 */
#define LL_FLASH_PROGRAM_DELAY_1   (FLASH_ACCR_WRHIGHFREQ_0)                           /*!< programming delay range 1 */
#define LL_FLASH_PROGRAM_DELAY_2   (FLASH_ACCR_WRHIGHFREQ_1)                           /*!< programming delay range 2 */
#define LL_FLASH_PROGRAM_DELAY_3   (FLASH_ACCR_WRHIGHFREQ_1 | FLASH_ACCR_WRHIGHFREQ_0) /*!< programming delay range 3 */
/**
  * @}
  */

/** @defgroup FLASH_Non-volatile_state FLASH Non-volatile State
  * @{
  */
#define LL_FLASH_OB_NVSTATE_OPEN  0xB4U /*!< Open non-volatile state   */
#define LL_FLASH_OB_NVSTATE_CLOSE 0x51U /*!< Closed non-volatile state */
/**
  * @}
  */

/** @defgroup FLASH_OEM_provisioning_state FLASH OEM Provisioning State
  * @{
  */
#define LL_FLASH_OB_OEM_PROVD_ENABLE  0xB4U /*!< Device is in OEM provisioned state                     */
#define LL_FLASH_OB_OEM_PROVD_DEFAULT 0x6AU /*!< Device is not in OEM provisioned state (default value) */
/**
  * @}
  */

/** @defgroup FLASH_Debug_authentication_method FLASH Debug Authentication Method
  * @{
  */
#define LL_FLASH_OB_DBG_AUTH_DEFAULT  0x6FU /*!< Locked device (no debug allowed)                  */
#define LL_FLASH_OB_DBG_AUTH_PASSWORD 0x8AU /*!< Authentication method using password              */
#define LL_FLASH_OB_DBG_AUTH_LOCKED   0xB4U /*!< No authentication method selected (default value) */
/**
  * @}
  */

/** @defgroup FLASH_IWDG_HW_SW_Selection FLASH IWDG HW SW Selection
  * @{
  */
#define LL_FLASH_OB_IWDG_HW 0x00000000U          /*!< IWDH hardware selection */
#define LL_FLASH_OB_IWDG_SW FLASH_OBW1SR_IWDG_HW /*!< IWDG software selection */
/**
  * @}
  */

/** @defgroup FLASH_Reset_Generation_Stop_Mode FLASH Reset Generation Stop Mode
  * @{
  */
#define LL_FLASH_OB_RST_STOP_MODE    0x00000000U            /*!< reset in stop mode    */
#define LL_FLASH_OB_NO_RST_STOP_MODE FLASH_OBW1SR_NRST_STOP /*!< no reset in stop mode */
/**
  * @}
  */

/** @defgroup FLASH_Reset_Generation_Standby_Mode FLASH Reset Generation Standby Mode
  * @{
  */
#define LL_FLASH_OB_RST_STDBY_MODE    0x00000000U            /*!< reset in standby mode    */
#define LL_FLASH_OB_NO_RST_STDBY_MODE FLASH_OBW1SR_NRST_STBY /*!< no reset in standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_BOR_Level FLASH OB BOR Level
  * @{
  */
#define LL_FLASH_OB_BOR_LEVEL_0 0x0U                   /*!< LL FLASH No Brown-out Reset                               */
#define LL_FLASH_OB_BOR_LEVEL_1 FLASH_OBW1SR_BOR_LEV_0 /*!< LL FLASH Brown-out Reset level 1 threshold is around 2.1V */
#define LL_FLASH_OB_BOR_LEVEL_2 FLASH_OBW1SR_BOR_LEV_1 /*!< LL FLASH Brown-out Reset level 2 threshold is around 2.4V */
#define LL_FLASH_OB_BOR_LEVEL_3 FLASH_OBW1SR_BOR_LEV   /*!< LL FLASH Brown-out Reset level 3 threshold is around 2.7V */
/**
  * @}
  */

/** @defgroup FLASH_Swap_bank FLASH Swap Bank
  * @{
  */
#define LL_FLASH_OB_BANK_NOT_SWAPPED 0x00000000U            /*!< Bank not swapped */
#define LL_FLASH_OB_BANK_SWAPPED     FLASH_OBW1SR_SWAP_BANK /*!< Bank swapped     */
/**
  * @}
  */

/** @defgroup FLASH_OB_BootAddr_Lock FLASH OB Boot Address Lock
  * @{
  */
#define LL_FLASH_OB_BOOTCFG_NOT_LOCKED 0x6AU /*!< LL FLASH Boot OBs not locked  */
#define LL_FLASH_OB_BOOTCFG_LOCKED     0xB4U /*!< LL FLASH Boot OBs locked      */
/**
  * @}
  */

/** @defgroup FLASH_KEY_Level FLASH Option Bytes Key HDPL level
  * @{
  */
#define LL_FLASH_OBK_HDPL_0 0x00000000U          /*!< Key stored for the HDPL indicated in SBS_HDPLSR     */
#define LL_FLASH_OBK_HDPL_1 FLASH_OBKCR_NEXTKL_0 /*!< Key stored for the HDPL indicated in SBS_HDPLSR + 1 */
/**
  * @}
  */

/** @defgroup FLASH_CRC_Burst_Size FLASH CRC Burst Size
  * @{
  */
#define LL_FLASH_CRC_BURST_SIZE_4   0x00000000U              /*!< Every burst has a size of 4 Flash words (64 Bytes)   */
#define LL_FLASH_CRC_BURST_SIZE_16  FLASH_ACRCCR_CRC_BURST_0 /*!< Every burst has a size of 16 Flash words (256 Bytes) */
#define LL_FLASH_CRC_BURST_SIZE_64  FLASH_ACRCCR_CRC_BURST_1 /*!< Every burst has a size of 64 Flash words (1 kByte)   */
#define LL_FLASH_CRC_BURST_SIZE_256 FLASH_ACRCCR_CRC_BURST   /*!< Every burst has a size of 256 Flash words (4 kBytes) */
/**
  * @}
  */

/** @defgroup FLASH_HDP_ExtensionState FLASH HDP Extension State
  * @{
  */
#define LL_FLASH_HDP_NO_ACCESS_PROTECTION        0xA3U /*!< HDP extension is not active and can be configured with HDPEXT */
#define LL_FLASH_HDP_ONLY_AREA_ACCESS_PROTECTION 0x5CU /*!< HDP extension is active and can only be increased with HDPEXT */
#define LL_FLASH_HDP_ALL_ACCESS_PROTECTION       0xFFU /*!< HDP extension is active and its configuration is locked until reset */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Macros LL FLASH Macros
  * @{
  */

/**
  * @brief  Write a value in FLASH register.
  * @param  instance FLASH instance.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  */
#define LL_FLASH_WRITE_REG(instance, reg, value) STM32_WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in FLASH register.
  * @param  instance FLASH instance.
  * @param  reg      Register to be read
  * @retval Register value
  */
#define LL_FLASH_READ_REG(instance, reg) STM32_READ_REG((instance)->reg)

/**
  * @brief  Read a bits value in FLASH register.
  * @param  instance FLASH instance.
  * @param  reg      Register to be read
  * @param  msk      Mask to be read
  * @retval Register value
  */
#define LL_FLASH_READ_BIT(instance, reg, msk) STM32_READ_REG((instance)->reg & msk)
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Functions LL FLASH Functions
  * @{
  */

/**
  * @brief Set the flash latency.
  * @rmtoll
  *  ACCR    LATENCY    LL_FLASH_SetLatency
  * @param  flashx FLASH instance.
  * @param  latency
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0WS
  *         @arg @ref LL_FLASH_LATENCY_1WS
  *         @arg @ref LL_FLASH_LATENCY_2WS
  *         @arg @ref LL_FLASH_LATENCY_3WS
  *         @arg @ref LL_FLASH_LATENCY_4WS
  *         @arg @ref LL_FLASH_LATENCY_5WS
  *         @arg @ref LL_FLASH_LATENCY_6WS
  *         @arg @ref LL_FLASH_LATENCY_7WS
  *         @arg @ref LL_FLASH_LATENCY_8WS
  *         @arg @ref LL_FLASH_LATENCY_9WS
  *         @arg @ref LL_FLASH_LATENCY_10WS
  *         @arg @ref LL_FLASH_LATENCY_11WS
  *         @arg @ref LL_FLASH_LATENCY_12WS
  *         @arg @ref LL_FLASH_LATENCY_13WS
  *         @arg @ref LL_FLASH_LATENCY_14WS
  *         @arg @ref LL_FLASH_LATENCY_15WS
  */
__STATIC_INLINE void LL_FLASH_SetLatency(FLASH_TypeDef *flashx, uint32_t latency)
{
  STM32_MODIFY_REG(flashx->ACCR, FLASH_ACCR_LATENCY, latency);
}

/**
  * @brief Get the flash latency.
  * @rmtoll
  *  ACCR    LATENCY    LL_FLASH_GetLatency
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0WS
  *         @arg @ref LL_FLASH_LATENCY_1WS
  *         @arg @ref LL_FLASH_LATENCY_2WS
  *         @arg @ref LL_FLASH_LATENCY_3WS
  *         @arg @ref LL_FLASH_LATENCY_4WS
  *         @arg @ref LL_FLASH_LATENCY_5WS
  *         @arg @ref LL_FLASH_LATENCY_6WS
  *         @arg @ref LL_FLASH_LATENCY_7WS
  *         @arg @ref LL_FLASH_LATENCY_8WS
  *         @arg @ref LL_FLASH_LATENCY_9WS
  *         @arg @ref LL_FLASH_LATENCY_10WS
  *         @arg @ref LL_FLASH_LATENCY_11WS
  *         @arg @ref LL_FLASH_LATENCY_12WS
  *         @arg @ref LL_FLASH_LATENCY_13WS
  *         @arg @ref LL_FLASH_LATENCY_14WS
  *         @arg @ref LL_FLASH_LATENCY_15WS
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->ACCR, FLASH_ACCR_LATENCY));
}

/**
  * @brief Set the flash programming delay.
  * @rmtoll
  *  ACCR    WRHIGHFREQ    LL_FLASH_SetProgrammingDelay
  * @param  flashx FLASH instance.
  * @param  programming_delay
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_PROGRAMMING_DELAY_0
  *         @arg @ref LL_FLASH_PROGRAMMING_DELAY_1
  *         @arg @ref LL_FLASH_PROGRAMMING_DELAY_2
  *         @arg @ref LL_FLASH_PROGRAMMING_DELAY_3
  */
__STATIC_INLINE void LL_FLASH_SetProgrammingDelay(FLASH_TypeDef *flashx, uint32_t programming_delay)
{
  STM32_MODIFY_REG(flashx->ACCR, FLASH_ACCR_WRHIGHFREQ, programming_delay);
}

/**
  * @brief Get the flash programming delay.
  * @rmtoll
  *  ACCR    WRHIGHFREQ    LL_FLASH_GetProgrammingDelay
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_PROGRAMMING_DELAY_0
  *         @arg @ref LL_FLASH_PROGRAMMING_DELAY_1
  *         @arg @ref LL_FLASH_PROGRAMMING_DELAY_2
  *         @arg @ref LL_FLASH_PROGRAMMING_DELAY_3
  */
__STATIC_INLINE uint32_t LL_FLASH_GetProgrammingDelay(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->ACCR, FLASH_ACCR_WRHIGHFREQ));
}

/**
  * @brief Set the flash unlock key for the selected bank.
  * @rmtoll
  *  AKEYR    CUKEY    LL_FLASH_SetUnlockKey \n
  *  BKEYR    CUKEY    LL_FLASH_SetUnlockKey
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  key
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_KEY1
  *         @arg @ref LL_FLASH_KEY2
  */
__STATIC_INLINE void LL_FLASH_SetUnlockKey(FLASH_TypeDef *flashx, uint32_t bank, uint32_t key)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AKEYR : &flashx->BKEYR;
  STM32_WRITE_REG(*reg_addr, key);
}

/**
  * @brief Set the flash unlock key.
  * @rmtoll
  *  OPTKEYR    OCUKEY    LL_FLASH_OB_SetUnlockKey
  * @param  flashx FLASH instance.
  * @param  key
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_OPTKEY1
  *         @arg @ref LL_FLASH_OB_OPTKEY2
  */
__STATIC_INLINE void LL_FLASH_OB_SetUnlockKey(FLASH_TypeDef *flashx, uint32_t key)
{
  STM32_WRITE_REG(flashx->OPTKEYR, key);
}

/**
  * @brief Enable the flash control access registers lock bit for the selected bank.
  * @rmtoll
  *  ACR    LOCK    LL_FLASH_Lock \n
  *  BCR    LOCK    LL_FLASH_Lock
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_Lock(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACR_LOCK);
}

/**
  * @brief Check the state of the flash control access registers lock bit for the selected bank.
  * @rmtoll
  *  ACR    LOCK    LL_FLASH_IsLocked \n
  *  BCR    LOCK    LL_FLASH_IsLocked
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash control access registers lock bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsLocked(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ACR_LOCK) == FLASH_ACR_LOCK) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash option bytes control access registers lock bit.
  * @rmtoll
  *  OPTCR    OPTLOCK    LL_FLASH_OB_Lock
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_Lock(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTCR, FLASH_OPTCR_OPTLOCK);
}

/**
  * @brief Check the state of the flash option bytes control access registers lock bit.
  * @rmtoll
  *  OPTCR    OPTLOCK    LL_FLASH_OB_IsLocked
  * @param  flashx FLASH instance.
  * @retval State of flash option bytes control access registers lock bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsLocked(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTCR, FLASH_OPTCR_OPTLOCK) == FLASH_OPTCR_OPTLOCK) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash programming bit for the selected bank.
  * @rmtoll
  *  ACR|BCR    PG    LL_FLASH_EnableProgramming
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2

  */
__STATIC_INLINE void LL_FLASH_EnableProgramming(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACR_PG);
}

/**
  * @brief Disable the flash programming bit for the selected bank.
  * @rmtoll
  *  ACR|BCR    PG    LL_FLASH_DisableProgramming
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableProgramming(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_CLEAR_BIT(*reg_addr, FLASH_ACR_PG);
}

/**
  * @brief Check the state of the flash programming bit for the selected bank.
  * @rmtoll
  *  ACR    PG    LL_FLASH_IsEnabledProgramming \n
  *  BCR    PG    LL_FLASH_IsEnabledProgramming
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash programming bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledProgramming(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ACR_PG) == FLASH_ACR_PG) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash page erase bit for the selected bank.
  * @rmtoll
  *  ACR    SER    LL_FLASH_EnablePageErase \n
  *  BCR    SER    LL_FLASH_EnablePageErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnablePageErase(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACR_SER);
}

/**
  * @brief Disable the flash page erase bit for the selected bank.
  * @rmtoll
  *  ACR    SER    LL_FLASH_DisablePageErase \n
  *  BCR    SER    LL_FLASH_DisablePageErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisablePageErase(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_CLEAR_BIT(*reg_addr, FLASH_ACR_SER);
}

/**
  * @brief Check the state of the flash page erase bit for the selected bank.
  * @rmtoll
  *  ACR    SER    LL_FLASH_IsEnabledPageErase \n
  *  BCR    SER    LL_FLASH_IsEnabledPageErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash page erase bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageErase(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ACR_SER) == FLASH_ACR_SER) ? 1UL : 0UL);
}

/**
  * @brief  Start the flash erase bank.
  * @rmtoll
  *  ACR          BER          LL_FLASH_StartEraseBank \n
  *  ACR          START        LL_FLASH_StartEraseBank \n
  *  BCR          BER          LL_FLASH_StartEraseBank \n
  *  BCR          START        LL_FLASH_StartEraseBank
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_StartEraseBank(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_SET_BIT(*reg_addr, (FLASH_ACR_BER | FLASH_ACR_START));
}

/**
  * @brief Enable the flash bank erase bit for the selected bank.
  * @rmtoll
  *  ACR    BER    LL_FLASH_EnableBankErase \n
  *  BCR    BER    LL_FLASH_EnableBankErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableBankErase(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACR_BER);
}

/**
  * @brief Disable the flash bank erase bit for the selected bank.
  * @rmtoll
  *  ACR    BER    LL_FLASH_DisableBankErase \n
  *  BCR    BER    LL_FLASH_DisableBankErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableBankErase(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_CLEAR_BIT(*reg_addr, FLASH_ACR_BER);
}

/**
  * @brief Check the state of the flash bank erase bit for the selected bank.
  * @rmtoll
  *  ACR    BER    LL_FLASH_IsEnabledBankErase \n
  *  BCR    BER    LL_FLASH_IsEnabledBankErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash bank erase bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledBankErase(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ACR_BER) == FLASH_ACR_BER) ? 1UL : 0UL);
}

/**
  * @brief  Disable all flash operation.
  * @rmtoll
  *  ACR           PG           LL_FLASH_DisableAllOperation \n
  *  ACR           BER          LL_FLASH_DisableAllOperation \n
  *  ACR           SER          LL_FLASH_DisableAllOperation \n
  *  BCR           PG           LL_FLASH_DisableAllOperation \n
  *  BCR           BER          LL_FLASH_DisableAllOperation \n
  *  BCR           SER          LL_FLASH_DisableAllOperation
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableAllOperation(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_CLEAR_BIT(*reg_addr, FLASH_ACR_SER | FLASH_ACR_BER | FLASH_ACR_PG);
}

/**
  * @brief Enable the flash force write bit for the selected bank.
  * @rmtoll
  *  ACR    FW    LL_FLASH_EnableForceWrite \n
  *  BCR    FW    LL_FLASH_EnableForceWrite
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableForceWrite(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACR_FW);
}

/**
  * @brief Enable the flash start erase operation bit for the selected bank.
  * @rmtoll
  *  ACR    START    LL_FLASH_StartEraseOperation \n
  *  BCR    START    LL_FLASH_StartEraseOperation
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_StartEraseOperation(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACR_START);
}

/**
  * @brief Set the flash page erase index for the selected bank.
  * @rmtoll
  *  ACR    SSN    LL_FLASH_SetPageEraseIndex \n
  *  BCR    SSN    LL_FLASH_SetPageEraseIndex
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page #warning "Fill param description"
  */
__STATIC_INLINE void LL_FLASH_SetPageEraseIndex(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_MODIFY_REG(*reg_addr, FLASH_ACR_SSN, page << FLASH_ACR_SSN_Pos);
}

/**
  * @brief  Start the flash erase page.
  * @rmtoll
  *  ACR          START          LL_FLASH_StartErasePage \n
  *  ACR          SSN            LL_FLASH_StartErasePage \n
  *  ACR          SER            LL_FLASH_StartErasePage \n
  *  BCR          START          LL_FLASH_StartErasePage \n
  *  BCR          SSN            LL_FLASH_StartErasePage \n
  *  BCR          SER            LL_FLASH_StartErasePage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page This parameter can take any value in [0:31]
  */
__STATIC_INLINE void LL_FLASH_StartErasePage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_MODIFY_REG(*reg_addr, (FLASH_ACR_SSN | FLASH_ACR_SER | FLASH_ACR_START),
                   ((page << FLASH_ACR_SSN_Pos) | FLASH_ACR_SER | FLASH_ACR_START));
}

/**
  * @brief Enable the flash OTP programming bit for the selected bank.
  * @rmtoll
  *  ACR    PG_OTP    LL_FLASH_EnableOTPProgramming \n
  *  BCR    PG_OTP    LL_FLASH_EnableOTPProgramming
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableOTPProgramming(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACR_PG_OTP);
}

/**
  * @brief Disable the flash OTP programming bit for the selected bank.
  * @rmtoll
  *  ACR    PG_OTP    LL_FLASH_DisableOTPProgramming \n
  *  BCR    PG_OTP    LL_FLASH_DisableOTPProgramming
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableOTPProgramming(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_CLEAR_BIT(*reg_addr, FLASH_ACR_PG_OTP);
}

/**
  * @brief Check the state of the flash OTP programming bit for the selected bank.
  * @rmtoll
  *  ACR    PG_OTP    LL_FLASH_IsEnabledOTPProgramming \n
  *  BCR    PG_OTP    LL_FLASH_IsEnabledOTPProgramming
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash OTP programming bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledOTPProgramming(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ACR_PG_OTP) == FLASH_ACR_PG_OTP) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash option bytes modification bit.
  * @rmtoll
  *  OPTCR    OPTSTART    LL_FLASH_OB_StartModification
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_StartModification(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTCR, FLASH_OPTCR_OPTSTART);
}

/**
  * @brief Enable the flash CRC bit for the selected bank.
  * @rmtoll
  *  ACR    CRC_EN    LL_FLASH_EnableCRC \n
  *  BCR    CRC_EN    LL_FLASH_EnableCRC
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableCRC(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACR_CRC_EN);
}

/**
  * @brief Disable the flash CRC bit for the selected bank.
  * @rmtoll
  *  ACR    CRC_EN    LL_FLASH_DisableCRC \n
  *  BCR    CRC_EN    LL_FLASH_DisableCRC
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableCRC(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  STM32_CLEAR_BIT(*reg_addr, FLASH_ACR_CRC_EN);
}

/**
  * @brief Check the state of the flash CRC bit for the selected bank.
  * @rmtoll
  *  ACR    CRC_EN    LL_FLASH_IsEnabledCRC \n
  *  BCR    CRC_EN    LL_FLASH_IsEnabledCRC
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash CRC bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledCRC(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACR : &flashx->BCR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ACR_CRC_EN) == FLASH_ACR_CRC_EN) ? 1UL : 0UL);
}

/**
  * @brief Set the flash CRC page for the selected bank.
  * @rmtoll
  *  ACRCCR    CRC_SECT    LL_FLASH_SetCRCPage \n
  *  BCRCCR    CRC_SECT    LL_FLASH_SetCRCPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  crc_sect #warning "Fill param description"
  */
__STATIC_INLINE void LL_FLASH_SetCRCPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t crc_sect)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  STM32_MODIFY_REG(*reg_addr, FLASH_ACRCCR_CRC_SECT, crc_sect << FLASH_ACRCCR_CRC_SECT_Pos);
}

/**
  * @brief Get the flash CRC page for the selected bank.
  * @rmtoll
  *  ACRCCR    CRC_SECT    LL_FLASH_GetCRCPage \n
  *  BCRCCR    CRC_SECT    LL_FLASH_GetCRCPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and #warning "Specify maximum value"
  */
__STATIC_INLINE uint32_t LL_FLASH_GetCRCPage(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ACRCCR_CRC_SECT)) >> FLASH_ACRCCR_CRC_SECT_Pos);
}

/**
  * @brief Enable the flash CRC computation by page bit for the selected bank.
  * @rmtoll
  *  ACRCCR    CRC_BY_SECT    LL_FLASH_EnableCRCByPage \n
  *  BCRCCR    CRC_BY_SECT    LL_FLASH_EnableCRCByPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableCRCByPage(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACRCCR_CRC_BY_SECT);
}

/**
  * @brief Disable the flash CRC computation by page bit for the selected bank.
  * @rmtoll
  *  ACRCCR    CRC_BY_SECT    LL_FLASH_DisableCRCByPage \n
  *  BCRCCR    CRC_BY_SECT    LL_FLASH_DisableCRCByPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableCRCByPage(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  STM32_CLEAR_BIT(*reg_addr, FLASH_ACRCCR_CRC_BY_SECT);
}

/**
  * @brief Check the state of the flash CRC computation by page bit for the selected bank.
  * @rmtoll
  *  ACRCCR    CRC_BY_SECT    LL_FLASH_IsEnabledCRCByPage \n
  *  BCRCCR    CRC_BY_SECT    LL_FLASH_IsEnabledCRCByPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash CRC computation by page bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledCRCByPage(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ACRCCR_CRC_BY_SECT) == FLASH_ACRCCR_CRC_BY_SECT) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash CRC page to list bit for the selected bank.
  * @rmtoll
  *  ACRCCR    ADD_SECT    LL_FLASH_AddCRCPageToList \n
  *  BCRCCR    ADD_SECT    LL_FLASH_AddCRCPageToList
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_AddCRCPageToList(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACRCCR_ADD_SECT);
}

/**
  * @brief Clear the flash CRC page list for the selected bank.
  * @rmtoll
  *  ACRCCR    CLEAN_SECT    LL_FLASH_ClearCRCPageList \n
  *  BCRCCR    CLEAN_SECT    LL_FLASH_ClearCRCPageList
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearCRCPageList(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACRCCR_CLEAN_SECT);
}

/**
  * @brief Enable the flash start CRC computation bit for the selected bank.
  * @rmtoll
  *  ACRCCR    START_CRC    LL_FLASH_StartCRCComputation \n
  *  BCRCCR    START_CRC    LL_FLASH_StartCRCComputation
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_StartCRCComputation(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACRCCR_START_CRC);
}

/**
  * @brief Clear the flash CRC data for the selected bank.
  * @rmtoll
  *  ACRCCR    CLEAN_CRC    LL_FLASH_ClearCRCData \n
  *  BCRCCR    CLEAN_CRC    LL_FLASH_ClearCRCData
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearCRCData(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACRCCR_CLEAN_CRC);
}

/**
  * @brief Set the flash CRC burst size for the selected bank.
  * @rmtoll
  *  ACRCCR    CRC_BURST    LL_FLASH_SetCRCBurstSize \n
  *  BCRCCR    CRC_BURST    LL_FLASH_SetCRCBurstSize
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  crc_burst
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_CRC_BURST_SIZE_4
  *         @arg @ref LL_FLASH_CRC_BURST_SIZE_16
  *         @arg @ref LL_FLASH_CRC_BURST_SIZE_64
  *         @arg @ref LL_FLASH_CRC_BURST_SIZE_256
  */
__STATIC_INLINE void LL_FLASH_SetCRCBurstSize(FLASH_TypeDef *flashx, uint32_t bank, uint32_t crc_burst)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  STM32_MODIFY_REG(*reg_addr, FLASH_ACRCCR_CRC_BURST, crc_burst);
}

/**
  * @brief Get the flash CRC burst size for the selected bank.
  * @rmtoll
  *  ACRCCR    CRC_BURST    LL_FLASH_GetCRCBurstSize \n
  *  BCRCCR    CRC_BURST    LL_FLASH_GetCRCBurstSize
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_CRC_BURST_SIZE_4
  *         @arg @ref LL_FLASH_CRC_BURST_SIZE_16
  *         @arg @ref LL_FLASH_CRC_BURST_SIZE_64
  *         @arg @ref LL_FLASH_CRC_BURST_SIZE_256
  */
__STATIC_INLINE uint32_t LL_FLASH_GetCRCBurstSize(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  return STM32_READ_BIT(*reg_addr, FLASH_ACRCCR_CRC_BURST);
}

/**
  * @brief Enable the flash CRC computation on the entire bank bit for the selected bank.
  * @rmtoll
  *  ACRCCR    ALL_BANK    LL_FLASH_EnableCRCAllBank \n
  *  BCRCCR    ALL_BANK    LL_FLASH_EnableCRCAllBank
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableCRCAllBank(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCCR : &flashx->BCRCCR;
  STM32_SET_BIT(*reg_addr, FLASH_ACRCCR_ALL_BANK);
}

/**
  * @brief Set the flash CRC start address for the selected bank.
  * @rmtoll
  *  ACRCSADDR    CRC_START_ADDR    LL_FLASH_SetCRCStartAddr \n
  *  BCRCSADDR    CRC_START_ADDR    LL_FLASH_SetCRCStartAddr
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  crc_start_addr
  *         This parameter can be a value between 0x00000U and 0x3FFFFU.
  */
__STATIC_INLINE void LL_FLASH_SetCRCStartAddr(FLASH_TypeDef *flashx, uint32_t bank, uint32_t crc_start_addr)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCSADDR : &flashx->BCRCSADDR;
  STM32_MODIFY_REG(*reg_addr, FLASH_ACRCSADDR_CRC_START_ADDR, crc_start_addr);
}

/**
  * @brief Get the flash CRC start address for the selected bank.
  * @rmtoll
  *  ACRCSADDR    CRC_START_ADDR    LL_FLASH_GetCRCStartAddr \n
  *  BCRCSADDR    CRC_START_ADDR    LL_FLASH_GetCRCStartAddr
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00000U and 0x3FFFFU.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetCRCStartAddr(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCSADDR : &flashx->BCRCSADDR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ACRCSADDR_CRC_START_ADDR)) >> FLASH_ACRCSADDR_CRC_START_ADDR_Pos);
}

/**
  * @brief Set the flash CRC end address for the selected bank.
  * @rmtoll
  *  ACRCEADDR    CRC_END_ADDR    LL_FLASH_SetCRCEndAddr \n
  *  BCRCEADDR    CRC_END_ADDR    LL_FLASH_SetCRCEndAddr
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  crc_end_addr
  *         This parameter can be a value between 0x00000U and 0x3FFFFU.
  */
__STATIC_INLINE void LL_FLASH_SetCRCEndAddr(FLASH_TypeDef *flashx, uint32_t bank, uint32_t crc_end_addr)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCEADDR : &flashx->BCRCEADDR;
  STM32_MODIFY_REG(*reg_addr, FLASH_ACRCEADDR_CRC_END_ADDR, crc_end_addr);
}

/**
  * @brief Get the flash CRC end address for the selected bank.
  * @rmtoll
  *  ACRCEADDR    CRC_END_ADDR    LL_FLASH_GetCRCEndAddr \n
  *  BCRCEADDR    CRC_END_ADDR    LL_FLASH_GetCRCEndAddr
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00000U and 0x3FFFFU.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetCRCEndAddr(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ACRCEADDR : &flashx->BCRCEADDR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ACRCEADDR_CRC_END_ADDR)) >> FLASH_ACRCEADDR_CRC_END_ADDR_Pos);
}

/**
  * @brief  Get the flash CRC data.
  * @rmtoll
  *  CRCDATAR    CRCDATAR    LL_FLASH_GetCRCData
  * @param  flashx FLASH instance.
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU
  */
__STATIC_INLINE uint32_t LL_FLASH_GetCRCData(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_REG(flashx->CRCDATAR));
}

/**
  * @brief Check the state of the flash specified status flags for the selected bank.
  * @rmtoll
  *  ASR    Group    LL_FLASH_IsActiveFlag \n
  *  BSR    Group    LL_FLASH_IsActiveFlag
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  flags
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_BUSY
  *         @arg @ref LL_FLASH_FLAG_WBNE
  *         @arg @ref LL_FLASH_FLAG_QW
  *         @arg @ref LL_FLASH_FLAG_CRC_BUSY
  *         @arg @ref LL_FLASH_FLAG_IS_PROGRAM
  *         @arg @ref LL_FLASH_FLAG_IS_ERASE
  *         @arg @ref LL_FLASH_FLAG_IS_OPTCHANGE
  *         @arg @ref LL_FLASH_FLAG_SWAP_BANK
  *         @arg @ref LL_FLASH_FLAG_STATUS_ALL
  * @retval State of flash specified status flags (1 if at least one is active / 0 if none are active)
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag(const FLASH_TypeDef *flashx, uint32_t bank, uint32_t flags)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ASR : &flashx->BSR;
  return ((STM32_READ_BIT(*reg_addr, flags) != 0U) ? 1UL : 0UL);
}

/**
  * @brief Check the state of the flash Busy flag for the selected bank.
  * @rmtoll
  *  ASR    BUSY    LL_FLASH_IsActiveFlag_BUSY \n
  *  BSR    BUSY    LL_FLASH_IsActiveFlag_BUSY
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Busy flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_BUSY(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ASR : &flashx->BSR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ASR_BUSY) == FLASH_ASR_BUSY) ? 1UL : 0UL);
}

/**
  * @brief Check the state of the flash Write buffer not empty flag for the selected bank.
  * @rmtoll
  *  ASR    WBNE    LL_FLASH_IsActiveFlag_WBNE \n
  *  BSR    WBNE    LL_FLASH_IsActiveFlag_WBNE
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Write buffer not empty flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_WBNE(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ASR : &flashx->BSR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ASR_WBNE) == FLASH_ASR_WBNE) ? 1UL : 0UL);
}

/**
  * @brief Check the state of the flash Wait queue flag for the selected bank.
  * @rmtoll
  *  ASR    QW    LL_FLASH_IsActiveFlag_QW \n
  *  BSR    QW    LL_FLASH_IsActiveFlag_QW
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Wait queue flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_QW(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ASR : &flashx->BSR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ASR_QW) == FLASH_ASR_QW) ? 1UL : 0UL);
}

/**
  * @brief Check the state of the flash CRC busy flag for the selected bank.
  * @rmtoll
  *  ASR    CRC_BUSY    LL_FLASH_IsActiveFlag_CRC_BUSY \n
  *  BSR    CRC_BUSY    LL_FLASH_IsActiveFlag_CRC_BUSY
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash CRC busy flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_CRC_BUSY(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ASR : &flashx->BSR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ASR_CRC_BUSY) == FLASH_ASR_CRC_BUSY) ? 1UL : 0UL);
}

/**
  * @brief Check the state of the flash is a program operation flag for the selected bank.
  * @rmtoll
  *  ASR    IS_PROGRAM    LL_FLASH_IsActiveFlag_IS_PROGRAM \n
  *  BSR    IS_PROGRAM    LL_FLASH_IsActiveFlag_IS_PROGRAM
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash is a program operation flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_IS_PROGRAM(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ASR : &flashx->BSR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ASR_IS_PROGRAM) == FLASH_ASR_IS_PROGRAM) ? 1UL : 0UL);
}

/**
  * @brief Check the state of the flash is an erase operation flag for the selected bank.
  * @rmtoll
  *  ASR    IS_ERASE    LL_FLASH_IsActiveFlag_IS_ERASE \n
  *  BSR    IS_ERASE    LL_FLASH_IsActiveFlag_IS_ERASE
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash is an erase operation flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_IS_ERASE(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ASR : &flashx->BSR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ASR_IS_ERASE) == FLASH_ASR_IS_ERASE) ? 1UL : 0UL);
}

/**
  * @brief Check the state of the flash is an option change operation flag for the selected bank.
  * @rmtoll
  *  ASR    IS_OPTCHANGE    LL_FLASH_IsActiveFlag_IS_OPTCHANGE \n
  *  BSR    IS_OPTCHANGE    LL_FLASH_IsActiveFlag_IS_OPTCHANGE
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash is an option change operation flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_IS_OPTCHANGE(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ASR : &flashx->BSR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ASR_IS_OPTCHANGE) == FLASH_ASR_IS_OPTCHANGE) ? 1UL : 0UL);
}

/**
  * @brief Check the state of the flash Swapped bank for the selected bank.
  * @rmtoll
  *  ASR    SWAP_BANK    LL_FLASH_IsActiveFlag_SWAP_BANK \n
  *  BSR    SWAP_BANK    LL_FLASH_IsActiveFlag_SWAP_BANK
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Swapped bank (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_SWAP_BANK(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->ASR : &flashx->BSR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_ASR_SWAP_BANK) == FLASH_ASR_SWAP_BANK) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash Interrupt enable flags bit for the selected bank.
  * @rmtoll
  *  AIER    Group    LL_FLASH_EnableIT \n
  *  BIER    Group    LL_FLASH_EnableIT
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  interrupts
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_WRPERR
  *         @arg @ref LL_FLASH_IT_PGSERR
  *         @arg @ref LL_FLASH_IT_STRBERR
  *         @arg @ref LL_FLASH_IT_OBLERR
  *         @arg @ref LL_FLASH_IT_INCERR
  *         @arg @ref LL_FLASH_IT_RDSERR
  *         @arg @ref LL_FLASH_IT_SNECCERR
  *         @arg @ref LL_FLASH_IT_DBECCERR
  *         @arg @ref LL_FLASH_IT_CRCEND
  *         @arg @ref LL_FLASH_IT_CRCRDERR
  *         @arg @ref LL_FLASH_IT_OBKERR
  *         @arg @ref LL_FLASH_IT_OPTERR
  *         @arg @ref LL_FLASH_IT_ALL
  */
__STATIC_INLINE void LL_FLASH_EnableIT(FLASH_TypeDef *flashx, uint32_t bank, uint32_t interrupts)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, interrupts);
}

/**
  * @brief Disable the flash Interrupt enable flags bit for the selected bank.
  * @rmtoll
  *  AIER    Group    LL_FLASH_DisableIT \n
  *  BIER    Group    LL_FLASH_DisableIT
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  interrupts
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_WRPERR
  *         @arg @ref LL_FLASH_IT_PGSERR
  *         @arg @ref LL_FLASH_IT_STRBERR
  *         @arg @ref LL_FLASH_IT_OBLERR
  *         @arg @ref LL_FLASH_IT_INCERR
  *         @arg @ref LL_FLASH_IT_RDSERR
  *         @arg @ref LL_FLASH_IT_SNECCERR
  *         @arg @ref LL_FLASH_IT_DBECCERR
  *         @arg @ref LL_FLASH_IT_CRCEND
  *         @arg @ref LL_FLASH_IT_CRCRDERR
  *         @arg @ref LL_FLASH_IT_OBKERR
  *         @arg @ref LL_FLASH_IT_OPTERR
  *         @arg @ref LL_FLASH_IT_ALL
  */
__STATIC_INLINE void LL_FLASH_DisableIT(FLASH_TypeDef *flashx, uint32_t bank, uint32_t interrupts)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, interrupts);
}

/**
  * @brief Check the state of the flash Interrupt enable flags bit for the selected bank.
  * @rmtoll
  *  AIER    Group    LL_FLASH_IsEnabledIT \n
  *  BIER    Group    LL_FLASH_IsEnabledIT
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  interrupts
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_WRPERR
  *         @arg @ref LL_FLASH_IT_PGSERR
  *         @arg @ref LL_FLASH_IT_STRBERR
  *         @arg @ref LL_FLASH_IT_OBLERR
  *         @arg @ref LL_FLASH_IT_INCERR
  *         @arg @ref LL_FLASH_IT_RDSERR
  *         @arg @ref LL_FLASH_IT_SNECCERR
  *         @arg @ref LL_FLASH_IT_DBECCERR
  *         @arg @ref LL_FLASH_IT_CRCEND
  *         @arg @ref LL_FLASH_IT_CRCRDERR
  *         @arg @ref LL_FLASH_IT_ALL
  * @retval #warning "Specify return Value"
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT(const FLASH_TypeDef *flashx, uint32_t bank, uint32_t interrupts)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, interrupts) != 0U) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash End-of-program interrupt control bit for the selected bank.
  * @rmtoll
  *  AIER    EOPIE    LL_FLASH_EnableIT_EOP \n
  *  BIER    EOPIE    LL_FLASH_EnableIT_EOP
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_EOP(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_EOPIE);
}

/**
  * @brief Disable the flash End-of-program interrupt control bit for the selected bank.
  * @rmtoll
  *  AIER    EOPIE    LL_FLASH_DisableIT_EOP \n
  *  BIER    EOPIE    LL_FLASH_DisableIT_EOP
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_EOP(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_EOPIE);
}

/**
  * @brief Check the state of the flash End-of-program interrupt control bit for the selected bank.
  * @rmtoll
  *  AIER    EOPIE    LL_FLASH_IsEnabledIT_EOP \n
  *  BIER    EOPIE    LL_FLASH_IsEnabledIT_EOP
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash End-of-program interrupt control bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_EOP(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_EOPIE) == FLASH_AIER_EOPIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash Write protection error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    WRPERRIE    LL_FLASH_EnableIT_WRPERR \n
  *  BIER    WRPERRIE    LL_FLASH_EnableIT_WRPERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_WRPERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_WRPERRIE);
}

/**
  * @brief Disable the flash Write protection error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    WRPERRIE    LL_FLASH_DisableIT_WRPERR \n
  *  BIER    WRPERRIE    LL_FLASH_DisableIT_WRPERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_WRPERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_WRPERRIE);
}

/**
  * @brief Check the state of the flash Write protection error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    WRPERRIE    LL_FLASH_IsEnabledIT_WRPERR \n
  *  BIER    WRPERRIE    LL_FLASH_IsEnabledIT_WRPERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Write protection error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_WRPERR(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_WRPERRIE) == FLASH_AIER_WRPERRIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash Programming sequence error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    PGSERRIE    LL_FLASH_EnableIT_PGSERR \n
  *  BIER    PGSERRIE    LL_FLASH_EnableIT_PGSERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_PGSERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_PGSERRIE);
}

/**
  * @brief Disable the flash Programming sequence error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    PGSERRIE    LL_FLASH_DisableIT_PGSERR \n
  *  BIER    PGSERRIE    LL_FLASH_DisableIT_PGSERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_PGSERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_PGSERRIE);
}

/**
  * @brief Check the state of the flash Programming sequence error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    PGSERRIE    LL_FLASH_IsEnabledIT_PGSERR \n
  *  BIER    PGSERRIE    LL_FLASH_IsEnabledIT_PGSERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Programming sequence error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_PGSERR(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_PGSERRIE) == FLASH_AIER_PGSERRIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash Strobe error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    STRBERRIE    LL_FLASH_EnableIT_STRBERR \n
  *  BIER    STRBERRIE    LL_FLASH_EnableIT_STRBERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_STRBERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_STRBERRIE);
}

/**
  * @brief Disable the flash Strobe error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    STRBERRIE    LL_FLASH_DisableIT_STRBERR \n
  *  BIER    STRBERRIE    LL_FLASH_DisableIT_STRBERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_STRBERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_STRBERRIE);
}

/**
  * @brief Check the state of the flash Strobe error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    STRBERRIE    LL_FLASH_IsEnabledIT_STRBERR \n
  *  BIER    STRBERRIE    LL_FLASH_IsEnabledIT_STRBERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Strobe error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_STRBERR(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_STRBERRIE) == FLASH_AIER_STRBERRIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash Option byte loading error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    OBLERRIE    LL_FLASH_EnableIT_OBLERR \n
  *  BIER    OBLERRIE    LL_FLASH_EnableIT_OBLERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_OBLERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_OBLERRIE);
}

/**
  * @brief Disable the flash Option byte loading error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    OBLERRIE    LL_FLASH_DisableIT_OBLERR \n
  *  BIER    OBLERRIE    LL_FLASH_DisableIT_OBLERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_OBLERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_OBLERRIE);
}

/**
  * @brief Check the state of the flash Option byte loading error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    OBLERRIE    LL_FLASH_IsEnabledIT_OBLERR \n
  *  BIER    OBLERRIE    LL_FLASH_IsEnabledIT_OBLERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Option byte loading error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_OBLERR(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_OBLERRIE) == FLASH_AIER_OBLERRIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash Inconsistency error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    INCERRIE    LL_FLASH_EnableIT_INCERR \n
  *  BIER    INCERRIE    LL_FLASH_EnableIT_INCERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_INCERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_INCERRIE);
}

/**
  * @brief Disable the flash Inconsistency error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    INCERRIE    LL_FLASH_DisableIT_INCERR \n
  *  BIER    INCERRIE    LL_FLASH_DisableIT_INCERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_INCERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_INCERRIE);
}

/**
  * @brief Check the state of the flash Inconsistency error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    INCERRIE    LL_FLASH_IsEnabledIT_INCERR \n
  *  BIER    INCERRIE    LL_FLASH_IsEnabledIT_INCERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Inconsistency error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_INCERR(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_INCERRIE) == FLASH_AIER_INCERRIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash Read security error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    RDSERRIE    LL_FLASH_EnableIT_RDSERR \n
  *  BIER    RDSERRIE    LL_FLASH_EnableIT_RDSERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_RDSERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_RDSERRIE);
}

/**
  * @brief Disable the flash Read security error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    RDSERRIE    LL_FLASH_DisableIT_RDSERR \n
  *  BIER    RDSERRIE    LL_FLASH_DisableIT_RDSERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_RDSERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_RDSERRIE);
}

/**
  * @brief Check the state of the flash Read security error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    RDSERRIE    LL_FLASH_IsEnabledIT_RDSERR \n
  *  BIER    RDSERRIE    LL_FLASH_IsEnabledIT_RDSERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Read security error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_RDSERR(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_RDSERRIE) == FLASH_AIER_RDSERRIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash ECC single correction error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    SNECCERRIE    LL_FLASH_EnableIT_SNECCERR \n
  *  BIER    SNECCERRIE    LL_FLASH_EnableIT_SNECCERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_SNECCERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_SNECCERRIE);
}

/**
  * @brief Disable the flash ECC single correction error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    SNECCERRIE    LL_FLASH_DisableIT_SNECCERR \n
  *  BIER    SNECCERRIE    LL_FLASH_DisableIT_SNECCERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_SNECCERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_SNECCERRIE);
}

/**
  * @brief Check the state of the flash ECC single correction error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    SNECCERRIE    LL_FLASH_IsEnabledIT_SNECCERR \n
  *  BIER    SNECCERRIE    LL_FLASH_IsEnabledIT_SNECCERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash ECC single correction error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_SNECCERR(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_SNECCERRIE) == FLASH_AIER_SNECCERRIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash ECC double detection error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    DBECCERRIE    LL_FLASH_EnableIT_DBECCERR \n
  *  BIER    DBECCERRIE    LL_FLASH_EnableIT_DBECCERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_DBECCERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_DBECCERRIE);
}

/**
  * @brief Disable the flash ECC double detection error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    DBECCERRIE    LL_FLASH_DisableIT_DBECCERR \n
  *  BIER    DBECCERRIE    LL_FLASH_DisableIT_DBECCERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_DBECCERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_DBECCERRIE);
}

/**
  * @brief Check the state of the flash ECC double detection error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    DBECCERRIE    LL_FLASH_IsEnabledIT_DBECCERR \n
  *  BIER    DBECCERRIE    LL_FLASH_IsEnabledIT_DBECCERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash ECC double detection error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_DBECCERR(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_DBECCERRIE) == FLASH_AIER_DBECCERRIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash CRC end of calculation interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    CRCENDIE    LL_FLASH_EnableIT_CRCEND \n
  *  BIER    CRCENDIE    LL_FLASH_EnableIT_CRCEND
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_CRCEND(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_CRCENDIE);
}

/**
  * @brief Disable the flash CRC end of calculation interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    CRCENDIE    LL_FLASH_DisableIT_CRCEND \n
  *  BIER    CRCENDIE    LL_FLASH_DisableIT_CRCEND
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_CRCEND(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_CRCENDIE);
}

/**
  * @brief Check the state of the flash CRC end of calculation interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    CRCENDIE    LL_FLASH_IsEnabledIT_CRCEND \n
  *  BIER    CRCENDIE    LL_FLASH_IsEnabledIT_CRCEND
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash CRC end of calculation interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_CRCEND(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_CRCENDIE) == FLASH_AIER_CRCENDIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash CRC read error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    CRCRDERRIE    LL_FLASH_EnableIT_CRCRDERR \n
  *  BIER    CRCRDERRIE    LL_FLASH_EnableIT_CRCRDERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableIT_CRCRDERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_SET_BIT(*reg_addr, FLASH_AIER_CRCRDERRIE);
}

/**
  * @brief Disable the flash CRC read error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    CRCRDERRIE    LL_FLASH_DisableIT_CRCRDERR \n
  *  BIER    CRCRDERRIE    LL_FLASH_DisableIT_CRCRDERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableIT_CRCRDERR(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  STM32_CLEAR_BIT(*reg_addr, FLASH_AIER_CRCRDERRIE);
}

/**
  * @brief Check the state of the flash CRC read error interrupt enable bit for the selected bank.
  * @rmtoll
  *  AIER    CRCRDERRIE    LL_FLASH_IsEnabledIT_CRCRDERR \n
  *  BIER    CRCRDERRIE    LL_FLASH_IsEnabledIT_CRCRDERR
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash CRC read error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_CRCRDERR(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AIER : &flashx->BIER;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AIER_CRCRDERRIE) == FLASH_AIER_CRCRDERRIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash Option byte key error interrupt enable bit.
  * @rmtoll
  *  OPTCR    OBKERRIE    LL_FLASH_EnableIT_OBKERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_OBKERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTCR, FLASH_OPTCR_OBKERRIE);
}

/**
  * @brief Disable the flash Option byte key error interrupt enable bit.
  * @rmtoll
  *  OPTCR    OBKERRIE    LL_FLASH_DisableIT_OBKERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_OBKERR(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OPTCR, FLASH_OPTCR_OBKERRIE);
}

/**
  * @brief Check the state of the flash Option byte key error interrupt enable bit.
  * @rmtoll OPTCR    OBKERRIE    LL_FLASH_IsEnabledIT_OBKERR
  * @param  flashx FLASH instance.
  * @retval State of flash Option byte key error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_OBKERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTCR, FLASH_OPTCR_OBKERRIE) == FLASH_OPTCR_OBKERRIE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash Option byte change error interrupt enable bit.
  * @rmtoll
  *  OPTCR    OPTERRIE    LL_FLASH_EnableIT_OPTERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_OPTERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTCR, FLASH_OPTCR_OPTERRIE);
}

/**
  * @brief Disable the flash Option byte change error interrupt enable bit.
  * @rmtoll
  *  OPTCR    OPTERRIE    LL_FLASH_DisableIT_OPTERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_OPTERR(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OPTCR, FLASH_OPTCR_OPTERRIE);
}

/**
  * @brief Check the state of the flash Option byte change error interrupt enable bit.
  * @rmtoll
  *  OPTCR    OPTERRIE    LL_FLASH_IsEnabledIT_OPTERR
  * @param  flashx FLASH instance.
  * @retval State of flash Option byte change error interrupt enable bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_OPTERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTCR, FLASH_OPTCR_OPTERRIE) == FLASH_OPTCR_OPTERRIE) ? 1UL : 0UL);
}

/**
  * @brief Get the flash Error flags for the selected bank.
  * @rmtoll
  *  AISR    Group    LL_FLASH_ReadFlag \n
  *  BISR    Group    LL_FLASH_ReadFlag
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  flags
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EOPF
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_STRBERR
  *         @arg @ref LL_FLASH_FLAG_OBLERR
  *         @arg @ref LL_FLASH_FLAG_INCERR
  *         @arg @ref LL_FLASH_FLAG_RDSERR
  *         @arg @ref LL_FLASH_FLAG_SNECCERR
  *         @arg @ref LL_FLASH_FLAG_DBECCERR
  *         @arg @ref LL_FLASH_FLAG_CRCENDF
  *         @arg @ref LL_FLASH_FLAG_CRCRDERR
  *         @arg @ref LL_FLASH_FLAG_OBKERR
  *         @arg @ref LL_FLASH_FLAG_OPTERR
  *         @arg @ref LL_FLASH_FLAG_ERRORS_ALL
  * @retval Returned value can be one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EOPF
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_STRBERR
  *         @arg @ref LL_FLASH_FLAG_OBLERR
  *         @arg @ref LL_FLASH_FLAG_INCERR
  *         @arg @ref LL_FLASH_FLAG_RDSERR
  *         @arg @ref LL_FLASH_FLAG_SNECCERR
  *         @arg @ref LL_FLASH_FLAG_DBECCERR
  *         @arg @ref LL_FLASH_FLAG_CRCENDF
  *         @arg @ref LL_FLASH_FLAG_CRCRDERR
  *         @arg @ref LL_FLASH_FLAG_OBKERR
  *         @arg @ref LL_FLASH_FLAG_OPTERR
  *         @arg @ref LL_FLASH_FLAG_ERRORS_ALL
  */
__STATIC_INLINE uint32_t LL_FLASH_ReadFlag(const FLASH_TypeDef *flashx, uint32_t bank, uint32_t flags)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return (STM32_READ_BIT(*reg_addr, flags));
}

/**
  * @brief Clear the flash Error flags for the selected bank.
  * @rmtoll
  *  AICR    Group    LL_FLASH_ClearFlag \n
  *  BICR    Group    LL_FLASH_ClearFlag
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  flags
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EOPF
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_STRBERR
  *         @arg @ref LL_FLASH_FLAG_OBLERR
  *         @arg @ref LL_FLASH_FLAG_INCERR
  *         @arg @ref LL_FLASH_FLAG_RDSERR
  *         @arg @ref LL_FLASH_FLAG_SNECCERR
  *         @arg @ref LL_FLASH_FLAG_DBECCERR
  *         @arg @ref LL_FLASH_FLAG_CRCENDF
  *         @arg @ref LL_FLASH_FLAG_CRCRDERR
  *         @arg @ref LL_FLASH_FLAG_OBKERR
  *         @arg @ref LL_FLASH_FLAG_OPTERR
  *         @arg @ref LL_FLASH_FLAG_ERRORS_ALL
  */
__STATIC_INLINE void LL_FLASH_ClearFlag(FLASH_TypeDef *flashx, uint32_t bank, uint32_t flags)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, flags);
}

/**
  * @brief Check the state of the flash End-of-program flag for the selected bank.
  * @rmtoll
  *  AISR    EOPF    LL_FLASH_IsActiveFlag_EOPF \n
  *  BISR    EOPF    LL_FLASH_IsActiveFlag_EOPF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash End-of-program flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_EOPF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_EOPF) == FLASH_AISR_EOPF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash End-of-program flag for the selected bank.
  * @rmtoll
  *  AICR    EOPF    LL_FLASH_ClearFlag_EOPF \n
  *  BICR    EOPF    LL_FLASH_ClearFlag_EOPF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_EOPF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_EOPF);
}

/**
  * @brief Check the state of the flash Write protection error flag for the selected bank.
  * @rmtoll
  *  AISR    WRPERRF    LL_FLASH_IsActiveFlag_WRPERRF \n
  *  BISR    WRPERRF    LL_FLASH_IsActiveFlag_WRPERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Write protection error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_WRPERRF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_WRPERRF) == FLASH_AISR_WRPERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash Write protection error flag for the selected bank.
  * @rmtoll
  *  AICR    WRPERRF    LL_FLASH_ClearFlag_WRPERRF \n
  *  BICR    WRPERRF    LL_FLASH_ClearFlag_WRPERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_WRPERRF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_WRPERRF);
}

/**
  * @brief Check the state of the flash Programming sequence error flag for the selected bank.
  * @rmtoll
  *  AISR    PGSERRF    LL_FLASH_IsActiveFlag_PGSERRF \n
  *  BISR    PGSERRF    LL_FLASH_IsActiveFlag_PGSERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Programming sequence error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_PGSERRF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_PGSERRF) == FLASH_AISR_PGSERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash Programming sequence error flag for the selected bank.
  * @rmtoll
  *  AICR    PGSERRF    LL_FLASH_ClearFlag_PGSERRF \n
  *  BICR    PGSERRF    LL_FLASH_ClearFlag_PGSERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_PGSERRF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_PGSERRF);
}

/**
  * @brief Check the state of the flash Strobe error flag for the selected bank.
  * @rmtoll
  *  AISR    STRBERRF    LL_FLASH_IsActiveFlag_STRBERRF \n
  *  BISR    STRBERRF    LL_FLASH_IsActiveFlag_STRBERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Strobe error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_STRBERRF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_STRBERRF) == FLASH_AISR_STRBERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash Strobe error flag for the selected bank.
  * @rmtoll
  *  AICR    STRBERRF    LL_FLASH_ClearFlag_STRBERRF \n
  *  BICR    STRBERRF    LL_FLASH_ClearFlag_STRBERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_STRBERRF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_STRBERRF);
}

/**
  * @brief Check the state of the flash Option byte loading error flag for the selected bank.
  * @rmtoll
  *  AISR    OBLERRF    LL_FLASH_IsActiveFlag_OBLERRF \n
  *  BISR    OBLERRF    LL_FLASH_IsActiveFlag_OBLERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Option byte loading error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OBLERRF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_OBLERRF) == FLASH_AISR_OBLERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash Option byte loading error flag for the selected bank.
  * @rmtoll
  *  AICR    OBLERRF    LL_FLASH_ClearFlag_OBLERRF \n
  *  BICR    OBLERRF    LL_FLASH_ClearFlag_OBLERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OBLERRF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_OBLERRF);
}

/**
  * @brief Check the state of the flash Inconsistency error flag for the selected bank.
  * @rmtoll
  *  AISR    INCERRF    LL_FLASH_IsActiveFlag_INCERRF \n
  *  BISR    INCERRF    LL_FLASH_IsActiveFlag_INCERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Inconsistency error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_INCERRF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_INCERRF) == FLASH_AISR_INCERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash Inconsistency error flag for the selected bank.
  * @rmtoll
  *  AICR    INCERRF    LL_FLASH_ClearFlag_INCERRF \n
  *  BICR    INCERRF    LL_FLASH_ClearFlag_INCERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_INCERRF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_INCERRF);
}

/**
  * @brief Check the state of the flash Read security error flag for the selected bank.
  * @rmtoll
  *  AISR    RDSERRF    LL_FLASH_IsActiveFlag_RDSERRF \n
  *  BISR    RDSERRF    LL_FLASH_IsActiveFlag_RDSERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash Read security error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_RDSERRF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_RDSERRF) == FLASH_AISR_RDSERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash Read security error flag for the selected bank.
  * @rmtoll
  *  AICR    RDSERRF    LL_FLASH_ClearFlag_RDSERRF \n
  *  BICR    RDSERRF    LL_FLASH_ClearFlag_RDSERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_RDSERRF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_RDSERRF);
}

/**
  * @brief Check the state of the flash ECC single error flag for the selected bank.
  * @rmtoll
  *  AISR    SNECCERRF    LL_FLASH_IsActiveFlag_SNECCERRF \n
  *  BISR    SNECCERRF    LL_FLASH_IsActiveFlag_SNECCERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash ECC single error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_SNECCERRF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_SNECCERRF) == FLASH_AISR_SNECCERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash ECC single error flag for the selected bank.
  * @rmtoll
  *  AICR    SNECCERRF    LL_FLASH_ClearFlag_SNECCERRF \n
  *  BICR    SNECCERRF    LL_FLASH_ClearFlag_SNECCERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_SNECCERRF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_SNECCERRF);
}

/**
  * @brief Check the state of the flash ECC double error flag for the selected bank.
  * @rmtoll
  *  AISR    DBECCERRF    LL_FLASH_IsActiveFlag_DBECCERRF \n
  *  BISR    DBECCERRF    LL_FLASH_IsActiveFlag_DBECCERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash ECC double error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_DBECCERRF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_DBECCERRF) == FLASH_AISR_DBECCERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash ECC double error flag for the selected bank.
  * @rmtoll
  *  AICR    DBECCERRF    LL_FLASH_ClearFlag_DBECCERRF \n
  *  BICR    DBECCERRF    LL_FLASH_ClearFlag_DBECCERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_DBECCERRF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_DBECCERRF);
}

/**
  * @brief Check the state of the flash CRC end flag for the selected bank.
  * @rmtoll
  *  AISR    CRCENDF    LL_FLASH_IsActiveFlag_CRCENDF \n
  *  BISR    CRCENDF    LL_FLASH_IsActiveFlag_CRCENDF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash CRC end flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_CRCENDF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_CRCENDF) == FLASH_AISR_CRCENDF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash CRC end flag for the selected bank.
  * @rmtoll
  *  AICR    CRCENDF    LL_FLASH_ClearFlag_CRCENDF \n
  *  BICR    CRCENDF    LL_FLASH_ClearFlag_CRCENDF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_CRCENDF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_CRCENDF);
}

/**
  * @brief Check the state of the flash CRC read error flag for the selected bank.
  * @rmtoll
  *  AISR    CRCRDERRF    LL_FLASH_IsActiveFlag_CRCRDERRF \n
  *  BISR    CRCRDERRF    LL_FLASH_IsActiveFlag_CRCRDERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash CRC read error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_CRCRDERRF(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AISR : &flashx->BISR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AISR_CRCRDERRF) == FLASH_AISR_CRCRDERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash CRC read error flag for the selected bank.
  * @rmtoll
  *  AICR    CRCRDERRF    LL_FLASH_ClearFlag_CRCRDERRF \n
  *  BICR    CRCRDERRF    LL_FLASH_ClearFlag_CRCRDERRF
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_CRCRDERRF(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AICR : &flashx->BICR;
  STM32_SET_BIT(*reg_addr, FLASH_AICR_CRCRDERRF);
}

/**
  * @brief Check the state of the flash Option byte key error flag.
  * @rmtoll
  *  OPTISR    OBKERRF    LL_FLASH_IsActiveFlag_OBKERRF
  * @param  flashx FLASH instance.
  * @retval State of flash Option byte key error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OBKERRF(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTISR, FLASH_OPTISR_OBKERRF) == FLASH_OPTISR_OBKERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash Option byte key error flag.
  * @rmtoll
  *  OPTICR    OBKERRF    LL_FLASH_ClearFlag_OBKERRF
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OBKERRF(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTICR, FLASH_OPTICR_OBKERRF);
}

/**
  * @brief Check the state of the flash Option byte change error flag.
  * @rmtoll
  *  OPTISR    OPTERRF    LL_FLASH_IsActiveFlag_OPTERRF
  * @param  flashx FLASH instance.
  * @retval State of flash Option byte change error flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OPTERRF(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTISR, FLASH_OPTISR_OPTERRF) == FLASH_OPTISR_OPTERRF) ? 1UL : 0UL);
}

/**
  * @brief Clear the flash Option byte change error flag.
  * @rmtoll
  *  OPTICR    OPTERRF    LL_FLASH_ClearFlag_OPTERRF
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OPTERRF(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTICR, FLASH_OPTICR_OPTERRF);
}

/**
  * @brief Get the flash ECCC fail address for the selected bank.
  * @rmtoll
  *  AECCSFADDR    SEC_FADD    LL_FLASH_GetECCCFailAddress \n
  *  BECCSFADDR    SEC_FADD    LL_FLASH_GetECCCFailAddress
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU
  */
__STATIC_INLINE uint32_t LL_FLASH_GetECCCFailAddress(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AECCSFADDR : &flashx->BECCSFADDR;
  return (STM32_READ_REG(*reg_addr));
}

/**
  * @brief Get the flash ECCD fail address for the selected bank.
  * @rmtoll
  *  AECCDFADDR    DED_FADD    LL_FLASH_GetECCDFailAddress \n
  *  BECCDFADDR    DED_FADD    LL_FLASH_GetECCDFailAddress
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU
  */
__STATIC_INLINE uint32_t LL_FLASH_GetECCDFailAddress(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AECCDFADDR : &flashx->BECCDFADDR;
  return (STM32_READ_REG(*reg_addr));
}

/**
  * @brief Disable the flash write protection for the selected pages  for the selected bank.
  * @rmtoll
  *  AWRPSRP    WRPSG    LL_FLASH_OB_EnablePageWRP \n
  *  BWRPSRP    WRPSG    LL_FLASH_OB_EnablePageWRP
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page
  *         This parameter can be any combination of @ref LL_FLASH_OB_Write_Protection_Pages possible values.
  */
__STATIC_INLINE void LL_FLASH_OB_EnablePageWRP(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AWRPSRP : &flashx->BWRPSRP;
  STM32_CLEAR_BIT(*reg_addr, (FLASH_AWRPSRP_WRPSG & page));
}

/**
  * @brief Enable the flash write protection for the selected pages  for the selected bank.
  * @rmtoll
  *  AWRPSRP    WRPSG    LL_FLASH_OB_DisablePageWRP \n
  *  BWRPSRP    WRPSG    LL_FLASH_OB_DisablePageWRP
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page
  *         This parameter can be any combination of @ref LL_FLASH_OB_Write_Protection_Pages possible values.
  */
__STATIC_INLINE void LL_FLASH_OB_DisablePageWRP(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AWRPSRP : &flashx->BWRPSRP;
  STM32_SET_BIT(*reg_addr, (FLASH_AWRPSRP_WRPSG & page));
}

/**
  * @brief Check the state of the flash write protection for the selected pages  for the selected bank.
  * @rmtoll
  *  AWRPSR    WRPSG    LL_FLASH_OB_IsEnabledPageWRP \n
  *  BWRPSR    WRPSG    LL_FLASH_OB_IsEnabledPageWRP
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page
  *         This parameter can be any combination of @ref LL_FLASH_OB_Write_Protection_Pages possible values.
  * @retval 1 if all pages specified by the page parameter are write protected, 0 otherwise.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledPageWRP(const FLASH_TypeDef *flashx, uint32_t bank, uint32_t page)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AWRPSR : &flashx->BWRPSR;
  return ((STM32_READ_BIT(*reg_addr, (FLASH_AWRPSR_WRPSG & page)) == 0U) ? 1UL : 0UL);
}

/**
  * @brief Set the flash HDP area start block for the selected bank.
  * @rmtoll
  *  AHDPSRP    HDP_AREA_START    LL_FLASH_OB_SetHDPAreaStartBlock \n
  *  BHDPSRP    HDP_AREA_START    LL_FLASH_OB_SetHDPAreaStartBlock
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  hdp_area_start
  *         This parameter can be a value between 0x00U and the maximum number of blocks by bank.
  */
__STATIC_INLINE void LL_FLASH_OB_SetHDPAreaStartBlock(FLASH_TypeDef *flashx, uint32_t bank, uint32_t hdp_area_start)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AHDPSRP : &flashx->BHDPSRP;
  STM32_MODIFY_REG(*reg_addr, FLASH_AHDPSRP_HDP_AREA_START, hdp_area_start << FLASH_AHDPSRP_HDP_AREA_START_Pos);
}

/**
  * @brief Get the flash HDP area start block for the selected bank.
  * @rmtoll
  *  AHDPSR    HDP_AREA_START    LL_FLASH_OB_GetHDPAreaStartBlock \n
  *  BHDPSR    HDP_AREA_START    LL_FLASH_OB_GetHDPAreaStartBlock
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of blocks by bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetHDPAreaStartBlock(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AHDPSR : &flashx->BHDPSR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AHDPSR_HDP_AREA_START)) >> FLASH_AHDPSR_HDP_AREA_START_Pos);
}

/**
  * @brief Set the flash HDP area end block for the selected bank.
  * @rmtoll
  *  AHDPSRP    HDP_AREA_END    LL_FLASH_OB_SetHDPAreaEndBlock \n
  *  BHDPSRP    HDP_AREA_END    LL_FLASH_OB_SetHDPAreaEndBlock
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  hdp_area_end
  *         This parameter can be a value between 0x00U and the maximum number of blocks by bank.
  */
__STATIC_INLINE void LL_FLASH_OB_SetHDPAreaEndBlock(FLASH_TypeDef *flashx, uint32_t bank, uint32_t hdp_area_end)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AHDPSRP : &flashx->BHDPSRP;
  STM32_MODIFY_REG(*reg_addr, FLASH_AHDPSRP_HDP_AREA_END, hdp_area_end << FLASH_AHDPSRP_HDP_AREA_END_Pos);
}

/**
  * @brief Get the flash HDP area end block for the selected bank.
  * @rmtoll
  *  AHDPSR    HDP_AREA_END    LL_FLASH_OB_GetHDPAreaEndBlock \n
  *  BHDPSR    HDP_AREA_END    LL_FLASH_OB_GetHDPAreaEndBlock
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of blocks by bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetHDPAreaEndBlock(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AHDPSR : &flashx->BHDPSR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AHDPSR_HDP_AREA_END)) >> FLASH_AHDPSR_HDP_AREA_END_Pos);
}

/**
  * @brief  Configure the flash hide protection area by bank (start and end blocks).
  * @rmtoll
  *  AHDPSRP     HDP_AREA_START     LL_FLASH_OB_ConfigHDPArea \n
  *  AHDPSRP     HDP_AREA_END       LL_FLASH_OB_ConfigHDPArea \n
  *  BHDPSRP     HDP_AREB_START     LL_FLASH_OB_ConfigHDPArea \n
  *  BHDPSRP     HDP_AREB_END       LL_FLASH_OB_ConfigHDPArea
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  start_block
  *         This parameter can be a value between 0x00U and the maximum number of blocks by bank.
  * @param  end_block
  *         This parameter can be a value between 0x00U and the maximum number of blocks by bank.
  */
__STATIC_INLINE void LL_FLASH_OB_ConfigHDPArea(FLASH_TypeDef *flashx, uint32_t bank,
                                               uint32_t start_block,
                                               uint32_t end_block)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AHDPSRP : &flashx->BHDPSRP;
  STM32_MODIFY_REG(*reg_addr, FLASH_AHDPSRP_HDP_AREA_START | FLASH_AHDPSRP_HDP_AREA_END, \
                   (end_block << FLASH_AHDPSRP_HDP_AREA_END_Pos) + (start_block << FLASH_AHDPSRP_HDP_AREA_START_Pos));
}

/**
  * @brief Set the flash HDP ext area for the selected bank.
  * @rmtoll
  *  AHDPEXTR    HDP_AREA_EXT    LL_FLASH_SetHDPExtArea \n
  *  BHDPEXTR    HDP_AREA_EXT    LL_FLASH_SetHDPExtArea
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  hdp_area_ext
  *         This parameter can be a value between 0x00U and 0xFFFU
  */
__STATIC_INLINE void LL_FLASH_SetHDPExtArea(FLASH_TypeDef *flashx, uint32_t bank, uint32_t hdp_area_ext)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AHDPEXTR : &flashx->BHDPEXTR;
  STM32_MODIFY_REG(*reg_addr, FLASH_AHDPEXTR_HDP_AREA_EXT, hdp_area_ext << FLASH_AHDPEXTR_HDP_AREA_EXT_Pos);
}

/**
  * @brief Get the flash HDP ext area for the selected bank.
  * @rmtoll
  *  AHDPEXTR    HDP_AREA_EXT    LL_FLASH_GetHDPExtArea \n
  *  BHDPEXTR    HDP_AREA_EXT    LL_FLASH_GetHDPExtArea
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between between 0x00U and 0xFFFU
  */
__STATIC_INLINE uint32_t LL_FLASH_GetHDPExtArea(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AHDPEXTR : &flashx->BHDPEXTR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AHDPEXTR_HDP_AREA_EXT)) >> FLASH_AHDPEXTR_HDP_AREA_EXT_Pos);
}

/**
  * @brief Set the flash hdpext state for the selected bank.
  * @rmtoll
  *  AHDPEXTR    HDPEXT_ACCDIS    LL_FLASH_SetHDPExtAccessProtection \n
  *  BHDPEXTR    HDPEXT_ACCDIS    LL_FLASH_SetHDPExtAccessProtection
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  hdp_ext_state
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_HDP_NO_ACCESS_PROTECTION
  *         @arg @ref LL_FLASH_HDP_ONLY_AREA_ACCESS_PROTECTION
  *         @arg @ref LL_FLASH_HDP_ALL_ACCESS_PROTECTION
  */
__STATIC_INLINE void LL_FLASH_SetHDPExtAccessProtection(FLASH_TypeDef *flashx, uint32_t bank, uint32_t hdp_ext_state)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AHDPEXTR : &flashx->BHDPEXTR;
  STM32_MODIFY_REG(*reg_addr, FLASH_AHDPEXTR_HDPEXT_ACCDIS, hdp_ext_state << FLASH_AHDPEXTR_HDPEXT_ACCDIS_Pos);
}

/**
  * @brief Get the flash hdpext accdis for the selected bank.
  * @rmtoll
  *  AHDPEXTR    HDPEXT_ACCDIS    LL_FLASH_GetHDPExtAccessProtection \n
  *  BHDPEXTR    HDPEXT_ACCDIS    LL_FLASH_GetHDPExtAccessProtection
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_HDP_NO_ACCESS_PROTECTION
  *         @arg @ref LL_FLASH_HDP_ONLY_AREA_ACCESS_PROTECTION
  *         @arg @ref LL_FLASH_HDP_ALL_ACCESS_PROTECTION
  */
__STATIC_INLINE uint32_t LL_FLASH_GetHDPExtAccessProtection(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->AHDPEXTR : &flashx->BHDPEXTR;
  return ((STM32_READ_BIT(*reg_addr, FLASH_AHDPEXTR_HDPEXT_ACCDIS)) >> FLASH_AHDPEXTR_HDPEXT_ACCDIS_Pos);
}

/**
  * @brief Check the state of the flash OTP block.
  * @rmtoll
  *  OTPLSR    OTPL    LL_FLASH_OB_IsLockedOTPBlock
  * @param  flashx FLASH instance.
  * @param  block
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_0
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_1
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_2
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_3
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_4
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_5
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_6
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_7
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_8
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_9
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_10
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_11
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_12
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_13
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_14
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_15
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_ALL
  * @retval #warning "Specify return Value"
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsLockedOTPBlock(const FLASH_TypeDef *flashx, uint32_t block)
{
  return ((STM32_READ_BIT(flashx->OTPLSR, (FLASH_OTPLSR_OTPL & block)) == (block)) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash OTP block.
  * @rmtoll
  *  OTPLSRP    OTPL    LL_FLASH_OB_LockOTPBlock
  * @param  flashx FLASH instance.
  * @param  block
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_0
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_1
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_2
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_3
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_4
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_5
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_6
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_7
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_8
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_9
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_10
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_11
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_12
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_13
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_14
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_15
  *         @arg @ref LL_FLASH_OB_OTP_LOCK_BLOCK_ALL
  */
__STATIC_INLINE void LL_FLASH_OB_LockOTPBlock(FLASH_TypeDef *flashx, uint32_t block)
{
  STM32_SET_BIT(flashx->OTPLSRP, (FLASH_OTPLSRP_OTPL & block));
}

/**
  * @brief Get the flash non-volatile state.
  * @rmtoll
  *  NVSR    NVSTATE    LL_FLASH_OB_GetNVState
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_NVSTATE_OPEN
  *         @arg @ref LL_FLASH_OB_NVSTATE_CLOSE
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNVState(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->NVSR, FLASH_NVSR_NVSTATE) >> FLASH_NVSR_NVSTATE_Pos);
}

/**
  * @brief Set the flash non-volatile state.
  * @rmtoll
  *  NVSRP    NVSTATE    LL_FLASH_OB_SetNVState
  * @param  flashx FLASH instance.
  * @param  nvstate
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_NVSTATE_OPEN
  *         @arg @ref LL_FLASH_OB_NVSTATE_CLOSE
  */
__STATIC_INLINE void LL_FLASH_OB_SetNVState(FLASH_TypeDef *flashx, uint32_t nvstate)
{
  STM32_MODIFY_REG(flashx->NVSRP, FLASH_NVSRP_NVSTATE, nvstate << FLASH_NVSRP_NVSTATE_Pos);
}

/**
  * @brief Get the flash OEM provisioning state.
  * @rmtoll
  *  ROTSR    OEM_PROVD    LL_FLASH_OB_GetOEMProvisioningState
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_OEM_PROVD_ENABLE
  *         @arg @ref LL_FLASH_OB_OEM_PROVD_DEFAULT
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetOEMProvisioningState(const FLASH_TypeDef *flashx)
{
  return STM32_READ_BIT(flashx->ROTSR, FLASH_ROTSR_OEM_PROVD);
}

/**
  * @brief Get the flash debug authentication method.
  * @rmtoll
  *  ROTSR    DBG_AUTH    LL_FLASH_OB_GetDebugAuthenticationMethod
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_DBG_AUTH_DEFAULT
  *         @arg @ref LL_FLASH_OB_DBG_AUTH_PASSWORD
  *         @arg @ref LL_FLASH_OB_DBG_AUTH_LOCKED
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetDebugAuthenticationMethod(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->ROTSR, FLASH_ROTSR_DBG_AUTH) >> FLASH_ROTSR_DBG_AUTH_Pos);
}

/**
  * @brief Check the state of the flash  boot address lock.
  * @rmtoll
  *  ROTSR    BOOT_LOCK    LL_FLASH_OB_IsLockedBootConfig
  * @param  flashx FLASH instance.
  * @retval State of flash  boot address lock bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsLockedBootConfig(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ROTSR, LL_FLASH_OB_BOOTCFG_LOCKED) == LL_FLASH_OB_BOOTCFG_LOCKED) ? 1UL : 0UL);
}

/**
  * @brief Lock the flash boot address.
  * @rmtoll
  *  ROTSRP    BOOT_LOCK    LL_FLASH_OB_LockBootConfig
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_LockBootConfig(FLASH_TypeDef *flashx)
{
  STM32_MODIFY_REG(flashx->ROTSRP, FLASH_ROTSRP_BOOT_LOCK,
                   ((uint32_t)LL_FLASH_OB_BOOTCFG_LOCKED << FLASH_ROTSRP_BOOT_LOCK_Pos));
}

/**
  * @brief Unlock the flash boot address.
  * @rmtoll
  *  ROTSRP    BOOT_LOCK    LL_FLASH_OB_UnlockBootConfig
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_UnlockBootConfig(FLASH_TypeDef *flashx)
{
  STM32_MODIFY_REG(flashx->ROTSRP, FLASH_ROTSRP_BOOT_LOCK,
                   ((uint32_t)LL_FLASH_OB_BOOTCFG_NOT_LOCKED << FLASH_ROTSRP_BOOT_LOCK_Pos));
}

/**
  * @brief Get the flash Brownout Reset level.
  * @rmtoll
  *  OBW1SR    BOR_LEV    LL_FLASH_OB_GetBORLevel
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_0
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_1
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_2
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_3
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetBORLevel(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OBW1SR, FLASH_OBW1SR_BOR_LEV));
}

/**
  * @brief Set the flash Brownout Reset level.
  * @rmtoll
  *  OBW1SRP    BOR_LEV    LL_FLASH_OB_SetBORLevel
  * @param  flashx FLASH instance.
  * @param  bor_level
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_0
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_1
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_2
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_3
  */
__STATIC_INLINE void LL_FLASH_OB_SetBORLevel(FLASH_TypeDef *flashx, uint32_t bor_level)
{
  STM32_MODIFY_REG(flashx->OBW1SRP, FLASH_OBW1SRP_BOR_LEV, bor_level);
}

/**
  * @brief Get the flash IWDG HW SW Selection.
  * @rmtoll
  *  OBW1SR    IWDG_HW    LL_FLASH_OB_GetIWDGSelection
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_IWDG_HW
  *         @arg @ref LL_FLASH_OB_IWDG_SW
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetIWDGSelection(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OBW1SR, FLASH_OBW1SR_IWDG_HW));
}

/**
  * @brief Set the flash IWDG HW SW Selection.
  * @rmtoll
  *  OBW1SRP    IWDG_HW    LL_FLASH_OB_SetIWDGSelection
  * @param  flashx FLASH instance.
  * @param  hw_sw_selection
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_IWDG_HW
  *         @arg @ref LL_FLASH_OB_IWDG_SW
  */
__STATIC_INLINE void LL_FLASH_OB_SetIWDGSelection(FLASH_TypeDef *flashx, uint32_t hw_sw_selection)
{
  STM32_MODIFY_REG(flashx->OBW1SRP, FLASH_OBW1SRP_IWDG_HW, hw_sw_selection);
}

/**
  * @brief Get the flash Reset Generation Stop Mode.
  * @rmtoll
  *  OBW1SR    NRST_STOP    LL_FLASH_OB_GetNRSTStopMode
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STOP_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STOP_MODE
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNRSTStopMode(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OBW1SR, FLASH_OBW1SR_NRST_STOP));
}

/**
  * @brief Set the flash Reset Generation Stop Mode.
  * @rmtoll
  *  OBW1SRP    NRST_STOP    LL_FLASH_OB_SetNRSTStopMode
  * @param  flashx FLASH instance.
  * @param  rst_generation
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STOP_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STOP_MODE
  */
__STATIC_INLINE void LL_FLASH_OB_SetNRSTStopMode(FLASH_TypeDef *flashx, uint32_t rst_generation)
{
  STM32_MODIFY_REG(flashx->OBW1SRP, FLASH_OBW1SRP_NRST_STOP, rst_generation);
}

/**
  * @brief Get the flash Reset Generation Standby Mode.
  * @rmtoll
  *  OBW1SR    NRST_STBY    LL_FLASH_OB_GetNRSTStandbyMode
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STDBY_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STDBY_MODE
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNRSTStandbyMode(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OBW1SR, FLASH_OBW1SR_NRST_STBY));
}

/**
  * @brief Set the flash Reset Generation Standby Mode.
  * @rmtoll
  *  OBW1SRP    NRST_STBY    LL_FLASH_OB_SetNRSTStandbyMode
  * @param  flashx FLASH instance.
  * @param  rst_generation
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STDBY_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STDBY_MODE
  */
__STATIC_INLINE void LL_FLASH_OB_SetNRSTStandbyMode(FLASH_TypeDef *flashx, uint32_t rst_generation)
{
  STM32_MODIFY_REG(flashx->OBW1SRP, FLASH_OBW1SRP_NRST_STBY, rst_generation);
}

/**
  * @brief Check the state of the flash ECC on SRAM bit.
  * @rmtoll
  *  OBW1SR    ECC_ON_SRAM    LL_FLASH_OB_IsEnabledEccOnSram
  * @param  flashx FLASH instance.
  * @retval State of flash ECC on SRAM bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledEccOnSram(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OBW1SR, FLASH_OBW1SR_ECC_ON_SRAM) == FLASH_OBW1SR_ECC_ON_SRAM) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash ECC on SRAM bit.
  * @rmtoll
  *  OBW1SRP    ECC_ON_SRAM    LL_FLASH_OB_EnableEccOnSram
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableEccOnSram(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OBW1SRP, FLASH_OBW1SRP_ECC_ON_SRAM);
}

/**
  * @brief Disable the flash ECC on SRAM bit.
  * @rmtoll
  *  OBW1SRP    ECC_ON_SRAM    LL_FLASH_OB_DisableEccOnSram
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableEccOnSram(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OBW1SRP, FLASH_OBW1SRP_ECC_ON_SRAM);
}

/**
  * @brief Check the state of the flash IWDG counter stop mode bit.
  * @rmtoll
  *  OBW1SR    IWDG_FZ_STOP    LL_FLASH_OB_IsFrozenIWDGStopMode
  * @param  flashx FLASH instance.
  * @retval #warning "Specify return Value"
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsFrozenIWDGStopMode(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OBW1SR, FLASH_OBW1SR_IWDG_FZ_STOP) == FLASH_OBW1SR_IWDG_FZ_STOP) ? 0UL : 1UL);
}

/**
  * @brief Disable the flash IWDG counter stop mode bit.
  * @rmtoll
  *  OBW1SRP    IWDG_FZ_STOP    LL_FLASH_OB_FreezeIWDGStopMode
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_FreezeIWDGStopMode(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OBW1SRP, FLASH_OBW1SRP_IWDG_FZ_STOP);
}

/**
  * @brief Enable the flash IWDG counter stop mode bit.
  * @rmtoll
  *  OBW1SRP    IWDG_FZ_STOP    LL_FLASH_OB_UnfreezeIWDGStopMode
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_UnfreezeIWDGStopMode(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OBW1SRP, FLASH_OBW1SRP_IWDG_FZ_STOP);
}

/**
  * @brief Check the state of the flash IWDG counter standby mode bit.
  * @rmtoll
  *  OBW1SR    IWDG_FZ_STBY    LL_FLASH_OB_IsFrozenIWDGStandbyMode
  * @param  flashx FLASH instance.
  * @retval #warning "Specify return Value"
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsFrozenIWDGStandbyMode(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OBW1SR, FLASH_OBW1SR_IWDG_FZ_STBY) == FLASH_OBW1SR_IWDG_FZ_STBY) ? 0UL : 1UL);
}

/**
  * @brief Disable the flash IWDG counter standby mode bit.
  * @rmtoll
  *  OBW1SRP    IWDG_FZ_STBY    LL_FLASH_OB_FreezeIWDGStandbyMode
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_FreezeIWDGStandbyMode(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OBW1SRP, FLASH_OBW1SRP_IWDG_FZ_STBY);
}

/**
  * @brief Enable the flash IWDG counter standby mode bit.
  * @rmtoll
  *  OBW1SRP    IWDG_FZ_STBY    LL_FLASH_OB_UnfreezeIWDGStandbyMode
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_UnfreezeIWDGStandbyMode(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OBW1SRP, FLASH_OBW1SRP_IWDG_FZ_STBY);
}

/**
  * @brief Check the state of the flash high speed low vdd IO bit.
  * @rmtoll
  *  OBW1SR    VDDIO_HSLV    LL_FLASH_OB_IsEnabledHighSpeedLowVddIO
  * @param  flashx FLASH instance.
  * @retval State of flash high speed low vdd IO bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledHighSpeedLowVddIO(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OBW1SR, FLASH_OBW1SR_VDDIO_HSLV) == FLASH_OBW1SR_VDDIO_HSLV) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash high speed low vdd IO bit.
  * @rmtoll
  *  OBW1SRP    VDDIO_HSLV    LL_FLASH_OB_EnableHighSpeedLowVddIO
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableHighSpeedLowVddIO(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OBW1SRP, FLASH_OBW1SRP_VDDIO_HSLV);
}

/**
  * @brief Disable the flash high speed low vdd IO bit.
  * @rmtoll
  *  OBW1SRP    VDDIO_HSLV    LL_FLASH_OB_DisableHighSpeedLowVddIO
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableHighSpeedLowVddIO(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OBW1SRP, FLASH_OBW1SRP_VDDIO_HSLV);
}

/**
  * @brief  Check the flash option bytes control access registers bank swap state.
  * @rmtoll
  *  ASR           SWAP_BANK           LL_FLASH_OB_IsBankSwapped
  * @param  flashx FLASH instance.
  * @retval State of flash option bytes bank swap (1 swapped / 0 not swapped).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsBankSwapped(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ASR, FLASH_ASR_SWAP_BANK) == (FLASH_ASR_SWAP_BANK)) ? 1UL : 0UL);
}

/**
  * @brief Get the flash swap bank.
  * @rmtoll
  *  OBW1SR    SWAP_BANK    LL_FLASH_OB_GetSwapBank
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_NOT_SWAPPED
  *         @arg @ref LL_FLASH_OB_BANK_SWAPPED
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetSwapBank(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OBW1SR, FLASH_OBW1SR_SWAP_BANK));
}

/**
  * @brief Set the flash swap bank.
  * @rmtoll
  *  OBW1SRP    SWAP_BANK    LL_FLASH_OB_SetSwapBank
  * @param  flashx FLASH instance.
  * @param  swap_bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_NOT_SWAPPED
  *         @arg @ref LL_FLASH_OB_BANK_SWAPPED
  */
__STATIC_INLINE void LL_FLASH_OB_SetSwapBank(FLASH_TypeDef *flashx, uint32_t swap_bank)
{
  STM32_MODIFY_REG(flashx->OBW1SRP, FLASH_OBW1SRP_SWAP_BANK, swap_bank);
}

/**
  * @brief Set the flash OBK index.
  * @rmtoll
  *  OBKCR    OBKINDEX    LL_FLASH_SetOBKIndex
  * @param  flashx FLASH instance.
  * @param  obkindex #warning "Fill param description"
  */
__STATIC_INLINE void LL_FLASH_SetOBKIndex(FLASH_TypeDef *flashx, uint32_t obkindex)
{
  STM32_MODIFY_REG(flashx->OBKCR, FLASH_OBKCR_OBKINDEX, obkindex << FLASH_OBKCR_OBKINDEX_Pos);
}

/**
  * @brief Get the flash OBK index.
  * @rmtoll
  *  OBKCR    OBKINDEX    LL_FLASH_GetOBKIndex
  * @param  flashx FLASH instance.
  * @param  obkindex #warning "Fill param description"
  * @retval Returned value can be a value between 0x00U and #warning "Specify maximum value"
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOBKIndex(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OBKCR, FLASH_OBKCR_OBKINDEX)) >> FLASH_OBKCR_OBKINDEX_Pos);
}

/**
  * @brief Set the flash OB key next HDP level.
  * @rmtoll
  *  OBKCR    NEXTKL    LL_FLASH_SetOBKeyNextHDPLevel
  * @param  flashx FLASH instance.
  * @param  next_key_level #warning "Fill param description"
  */
__STATIC_INLINE void LL_FLASH_SetOBKeyNextHDPLevel(FLASH_TypeDef *flashx, uint32_t next_key_level)
{
  STM32_MODIFY_REG(flashx->OBKCR, FLASH_OBKCR_NEXTKL, next_key_level);
}

/**
  * @brief Get the flash OB key next HDP level.
  * @rmtoll
  *  OBKCR    NEXTKL    LL_FLASH_GetOBKeyNextHDPLevel
  * @param  flashx FLASH instance.
  * @retval Returned value can be a value between 0x00U and #warning "Specify maximum value"
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOBKeyNextHDPLevel(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OBKCR, FLASH_OBKCR_NEXTKL)));
}

/**
  * @brief Enable the flash OB key erase bit.
  * @rmtoll
  *  OBKCR    KEYERASE    LL_FLASH_EnableOBKeyErase
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableOBKeyErase(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OBKCR, FLASH_OBKCR_KEYERASE);
}

/**
  * @brief Disable the flash OB key erase bit.
  * @rmtoll
  *  OBKCR    KEYERASE    LL_FLASH_DisableOBKeyErase
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableOBKeyErase(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OBKCR, FLASH_OBKCR_KEYERASE);
}

/**
  * @brief Check the state of the flash OB key erase bit.
  * @rmtoll
  *  OBKCR    KEYERASE    LL_FLASH_IsEnabledOBKeyErase
  * @param  flashx FLASH instance.
  * @retval State of flash OB key erase bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledOBKeyErase(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OBKCR, FLASH_OBKCR_KEYERASE) == FLASH_OBKCR_KEYERASE) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash OB key programming bit.
  * @rmtoll
  *  OBKCR    KEYPROG    LL_FLASH_EnableOBKeyProgramming
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableOBKeyProgramming(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OBKCR, FLASH_OBKCR_KEYPROG);
}

/**
  * @brief Disable the flash OB key programming bit.
  * @rmtoll
  *  OBKCR    KEYPROG    LL_FLASH_DisableOBKeyProgramming
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableOBKeyProgramming(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OBKCR, FLASH_OBKCR_KEYPROG);
}

/**
  * @brief Check the state of the flash OB key programming bit.
  * @rmtoll
  *  OBKCR    KEYPROG    LL_FLASH_IsEnabledOBKeyProgramming
  * @param  flashx FLASH instance.
  * @retval State of flash OB key programming bit (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledOBKeyProgramming(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OBKCR, FLASH_OBKCR_KEYPROG) == FLASH_OBKCR_KEYPROG) ? 1UL : 0UL);
}

/**
  * @brief Enable the flash OB key operation bit.
  * @rmtoll
  *  OBKCR    KEYSTART    LL_FLASH_StartOBKeyOperation
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_StartOBKeyOperation(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OBKCR, FLASH_OBKCR_KEYSTART);
}

/**
  * @brief Check the state of the flash OB key operation bit.
  * @rmtoll
  *  OBKCR    KEYSTART    LL_FLASH_OB_IsActiveFlag_KEYSTART
  * @param  flashx FLASH instance.
  * @retval State of flash OB key operation flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsActiveFlag_KEYSTART(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OBKCR, FLASH_OBKCR_KEYSTART) == FLASH_OBKCR_KEYSTART) ? 1UL : 0UL);
}

/**
  * @brief Set the flash OB key erase.
  * @rmtoll
  *  OBKCLR    EKEY    LL_FLASH_SetOBKEraseKeyIndex
  * @param  flashx FLASH instance.
  * @param  erase_key
  *         This parameter can be any combination of @ref LL_FLASH_OBK possible values.
  */
__STATIC_INLINE void LL_FLASH_SetOBKEraseKeyIndex(FLASH_TypeDef *flashx, uint32_t erase_key)
{
  STM32_WRITE_REG(flashx->OBKCLR, erase_key);
}

/**
  * @brief Get the flash OB key erase.
  * @rmtoll
  *  OBKCLR    EKEY    LL_FLASH_GetOBKEraseKeyIndex
  * @param  flashx FLASH instance.
  * @param  erase_key
  *         This parameter can be any combination of @ref LL_FLASH_OBK possible values.
  * @retval This parameter can be any combination of @ref LL_FLASH_OBK possible values.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOBKEraseKeyIndex(const FLASH_TypeDef *flashx, uint32_t erase_key)
{
  return (STM32_READ_BIT(flashx->OBKCLR, erase_key));
}

/**
  * @brief Set the flash OBK data.
  * @rmtoll
  *  OBKDR0    OBKDATA    LL_FLASH_SetOBKData0
  * @param  flashx FLASH instance.
  * @param  obk_data #warning "Fill param description"
  */
__STATIC_INLINE void LL_FLASH_SetOBKData0(FLASH_TypeDef *flashx, uint32_t obk_data)
{
  STM32_WRITE_REG(flashx->OBKDR0, obk_data);
}

/**
  * @brief Get the flash OBK data.
  * @rmtoll
  *  OBKDR0    OBKDATA    LL_FLASH_GetOBKData0
  * @param  flashx FLASH instance.
  * @retval Returned value can be a value between 0x00U and #warning "Specify maximum value"
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOBKData0(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_REG(flashx->OBKDR0));
}

/**
  * @brief Set the flash OBK data.
  * @rmtoll
  *  OBKDR1    OBKDATA    LL_FLASH_SetOBKData1
  * @param  flashx FLASH instance.
  * @param  obk_data #warning "Fill param description"
  */
__STATIC_INLINE void LL_FLASH_SetOBKData1(FLASH_TypeDef *flashx, uint32_t obk_data)
{
  STM32_WRITE_REG(flashx->OBKDR1, obk_data);
}

/**
  * @brief Get the flash OBK data.
  * @rmtoll
  *  OBKDR1    OBKDATA    LL_FLASH_GetOBKData1
  * @param  flashx FLASH instance.
  * @retval Returned value can be a value between 0x00U and #warning "Specify maximum value"
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOBKData1(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_REG(flashx->OBKDR1));
}

/**
  * @brief Set the flash OBK data.
  * @rmtoll
  *  OBKDR2    OBKDATA    LL_FLASH_SetOBKData2
  * @param  flashx FLASH instance.
  * @param  obk_data #warning "Fill param description"
  */
__STATIC_INLINE void LL_FLASH_SetOBKData2(FLASH_TypeDef *flashx, uint32_t obk_data)
{
  STM32_WRITE_REG(flashx->OBKDR2, obk_data);
}

/**
  * @brief Get the flash OBK data.
  * @rmtoll
  *  OBKDR2    OBKDATA    LL_FLASH_GetOBKData2
  * @param  flashx FLASH instance.
  * @retval Returned value can be a value between 0x00U and #warning "Specify maximum value"
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOBKData2(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_REG(flashx->OBKDR2));
}

/**
  * @brief Set the flash OBK data.
  * @rmtoll
  *  OBKDR3    OBKDATA    LL_FLASH_SetOBKData3
  * @param  flashx FLASH instance.
  * @param  obk_data #warning "Fill param description"
  */
__STATIC_INLINE void LL_FLASH_SetOBKData3(FLASH_TypeDef *flashx, uint32_t obk_data)
{
  STM32_WRITE_REG(flashx->OBKDR3, obk_data);
}

/**
  * @brief Get the flash OBK data.
  * @rmtoll
  *  OBKDR3    OBKDATA    LL_FLASH_GetOBKData3
  * @param  flashx FLASH instance.
  * @param  obkdata #warning "Fill param description"
  * @retval Returned value can be a value between 0x00U and #warning "Specify maximum value"
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOBKData3(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_REG(flashx->OBKDR3));
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* FLASH */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_LL_FLASH_H */
