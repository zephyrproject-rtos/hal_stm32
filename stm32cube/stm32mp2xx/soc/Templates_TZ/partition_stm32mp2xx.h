/**
  ******************************************************************************
 * @file     partition_stm32mp2xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32MP2xx Device Initial Setup for Secure / Non-Secure Zones
  *          for ARMCM33 based on CMSIS CORE V5.0.1.
  *
  *          This file contains:
  *           - Initialize Security Attribution Unit (SAU) CTRL register
  *           - Setup behavior of Sleep and Exception Handling
  *           - Setup behavior of Floating Point Unit
  *           - Setup Interrupt Target
  *
  ******************************************************************************
  * @attention
 *
  * <h2><center>&copy; COPYRIGHT(c) 2020 STMicroelectronics</center></h2>
 *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
 *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
  ******************************************************************************
 */

#ifndef PARTITION_STM32MP2XX_H
#define PARTITION_STM32MP2XX_H

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
*/

/*
// <e>Initialize Security Attribution Unit (SAU) CTRL register
*/
#define SAU_INIT_CTRL          1

/*
//   <q> Enable SAU
//   <i> Value for SAU->CTRL register bit ENABLE
*/
#define SAU_INIT_CTRL_ENABLE   0

/*
//   <o> When SAU is disabled
//     <0=> All Memory is Secure
//     <1=> All Memory is Non-Secure
//   <i> Value for SAU->CTRL register bit ALLNS
//   <i> When all Memory is Non-Secure (ALLNS is 1), IDAU can override memory map configuration.
*/
#define SAU_INIT_CTRL_ALLNS  0

/*
// </e>
*/

/*
// <h>Initialize Security Attribution Unit (SAU) Address Regions
// <i>SAU configuration specifies regions to be one of:
// <i> - Secure and Non-Secure Callable
// <i> - Non-Secure
// <i>Note: All memory regions not configured by SAU are Secure
*/
#define SAU_REGIONS_MAX   8                 /* Max. number of SAU regions */

/*
//   <e>Initialize SAU Region 0
//   <i> Setup SAU Region 0 memory attributes
*/
#define SAU_INIT_REGION0    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START0     0x00000000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END0       0x00000000      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC0       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 1
//   <i> Setup SAU Region 1 memory attributes
*/
#define SAU_INIT_REGION1    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START1     0x00000000      /* start address of SAU region 1 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END1       0x00000000      /* end address of SAU region 1 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC1       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 2
//   <i> Setup SAU Region 2 memory attributes
*/
#define SAU_INIT_REGION2    0
/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START2     0x00000000      /* start address of SAU region 2 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END2       0x00000000      /* end address of SAU region 2 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC2       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 3
//   <i> Setup SAU Region 3 memory attributes
*/
#define SAU_INIT_REGION3    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START3     0x00000000      /* start address of SAU region 3 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END3       0x00000000      /* end address of SAU region 3 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC3       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 4
//   <i> Setup SAU Region 4 memory attributes
*/
#define SAU_INIT_REGION4    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START4     0x00000000      /* start address of SAU region 4 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END4       0x00000000      /* end address of SAU region 4 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC4       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 5
//   <i> Setup SAU Region 5 memory attributes
*/
#define SAU_INIT_REGION5    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START5     0x00000000      /* start address of SAU region 5 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END5       0x00000000      /* end address of SAU region 5 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC5       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 6
//   <i> Setup SAU Region 6 memory attributes
*/
#define SAU_INIT_REGION6    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START6     0x00000000      /* start address of SAU region 6 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END6       0x00000000      /* end address of SAU region 6 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC6       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 7
//   <i> Setup SAU Region 7 memory attributes
*/
#define SAU_INIT_REGION7    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START7     0x00000000      /* start address of SAU region 7 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END7       0x00000000      /* end address of SAU region 7 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC7       0
/*
//   </e>
*/

/*
// </h>
*/

/*
// <e>Setup behaviour of Sleep and Exception Handling
*/
#define SCB_CSR_AIRCR_INIT  0

/*
//   <o> Deep Sleep can be enabled by
//     <0=>Secure and Non-Secure state
//     <1=>Secure state only
//   <i> Value for SCB->CSR register bit DEEPSLEEPS
*/
#define SCB_CSR_DEEPSLEEPS_VAL  0

/*
//   <o>System reset request accessible from
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for SCB->AIRCR register bit SYSRESETREQS
*/
#define SCB_AIRCR_SYSRESETREQS_VAL  0

/*
//   <o>Priority of Non-Secure exceptions is
//     <0=> Not altered
//     <1=> Lowered to 0x80-0xFF
//   <i> Value for SCB->AIRCR register bit PRIS
*/
#define SCB_AIRCR_PRIS_VAL      0

/*
//   <o>BusFault, HardFault, and NMI target
//     <0=> Secure state
//     <1=> Non-Secure state
//   <i> Value for SCB->AIRCR register bit BFHFNMINS
*/
#define SCB_AIRCR_BFHFNMINS_VAL 0

/*
// </e>
*/

/*
// <e>Setup behaviour of Floating Point Unit
*/
#define TZ_FPU_NS_USAGE 1

/*
// <o>Floating Point Unit usage
//     <0=> Secure state only
//     <3=> Secure and Non-Secure state
//   <i> Value for SCB->NSACR register bits CP10, CP11
*/
#define SCB_NSACR_CP10_11_VAL       3

/*
// <o>Treat floating-point registers as Secure
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit TS
*/
#define FPU_FPCCR_TS_VAL            0

/*
// <o>Clear on return (CLRONRET) accessibility
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for FPU->FPCCR register bit CLRONRETS
*/
#define FPU_FPCCR_CLRONRETS_VAL     0

/*
// <o>Clear floating-point caller saved registers on exception return
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit CLRONRET
*/
#define FPU_FPCCR_CLRONRET_VAL      1

/*
// </e>
*/

/*
// <h>Setup Interrupt Target
*/

/*
//   <e>Initialize ITNS 0 (Interrupts 0..31)
*/
#define NVIC_INIT_ITNS0    1

/*
// Interrupts 0..31 (bits [0..31] : <0=> Secure state <1=> Non-Secure state)
//   <o.0>  0   PVD_IRQn              Secure state
//   <o.1>  1   PVM_IRQn              Secure state
//   <o.2>  2   IWDG3_IRQn            Secure state
//   <o.3>  3   IWDG4_IRQn            Secure state
//   <o.4>  4   IWDG1_RST_IRQn        Secure state
//   <o.5>  5   IWDG2_RST_IRQn        Secure state
//   <o.6>  6   IWDG4_RST_IRQn        Secure state
//   <o.7>  7   IWDG5_RST_IRQn        Secure state
//   <o.8>  8   WWDG1_IRQn            Secure state
//   <o.9>  9   RESERVED_9            Secure state
//   <o.10> 10  RESERVED_10           Secure state
//   <o.11> 11  WWDG2_RST_IRQn        Secure state
//   <o.12> 12  TAMP_IRQn             Non-Secure state
//   <o.13> 13  RTC_IRQn              Non-Secure state
//   <o.14> 14  TAMP_S_IRQn           Secure state
//   <o.15> 15  RTC_S_IRQn            Secure state
//   <o.16> 16  RCC_IRQn              Secure state
//   <o.17> 17  EXTI2_0_IRQn          Secure state
//   <o.18> 18  EXTI2_1_IRQn          Secure state
//   <o.19> 19  EXTI2_2_IRQn          Secure state
//   <o.20> 20  EXTI2_3_IRQn          Secure state
//   <o.21> 21  EXTI2_4_IRQn          Secure state
//   <o.22> 22  EXTI2_5_IRQn          Secure state
//   <o.23> 23  EXTI2_6_IRQn          Secure state
//   <o.24> 24  EXTI2_7_IRQn          Secure state
//   <o.25> 25  EXTI2_8_IRQn          Secure state
//   <o.26> 26  EXTI2_9_IRQn          Secure state
//   <o.27> 27  EXTI2_10_IRQn         Secure state
//   <o.28> 28  EXTI2_11_IRQn         Secure state
//   <o.29> 29  EXTI2_12_IRQn         Secure state
//   <o.30> 30  EXTI2_13_IRQn         Secure state
//   <o.31> 31  EXTI2_14_IRQn         Secure state
*/
#define NVIC_INIT_ITNS0_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 1 (Interrupts 32..63)
*/
#define NVIC_INIT_ITNS1    1

/*
// Interrupts 32..63 (bits [32..63] : <0=> Secure state <1=> Non-Secure state)
//   <o.0>  32  EXTI2_15_IRQn         Secure state
//   <o.1>  33  HPDMA1_Channel0_IRQn  Secure state
//   <o.2>  34  HPDMA1_Channel1_IRQn  Secure state
//   <o.3>  35  HPDMA1_Channel2_IRQn  Secure state
//   <o.4>  36  HPDMA1_Channel3_IRQn  Secure state
//   <o.5>  37  HPDMA1_Channel4_IRQn  Secure state
//   <o.6>  38  HPDMA1_Channel5_IRQn  Secure state
//   <o.7>  39  HPDMA1_Channel6_IRQn  Secure state
//   <o.8>  40  HPDMA1_Channel7_IRQn  Secure state
//   <o.9>  41  HPDMA1_Channel8_IRQn  Secure state
//   <o.10> 42  HPDMA1_Channel9_IRQn  Secure state
//   <o.11> 43  HPDMA1_Channel10_IRQn Secure state
//   <o.12> 44  HPDMA1_Channel11_IRQn Secure state
//   <o.13> 45  HPDMA1_Channel12_IRQn Secure state
//   <o.14> 46  HPDMA1_Channel13_IRQn Secure state
//   <o.15> 47  HPDMA1_Channel14_IRQn Secure state
//   <o.16> 48  HPDMA1_Channel15_IRQn Secure state
//   <o.17> 49  HPDMA2_Channel0_IRQn  Secure state
//   <o.18> 50  HPDMA2_Channel1_IRQn  Secure state
//   <o.19> 51  HPDMA2_Channel2_IRQn  Secure state
//   <o.20> 52  HPDMA2_Channel3_IRQn  Secure state
//   <o.21> 53  HPDMA2_Channel4_IRQn  Secure state
//   <o.22> 54  HPDMA2_Channel5_IRQn  Secure state
//   <o.23> 55  HPDMA2_Channel6_IRQn  Secure state
//   <o.24> 56  HPDMA2_Channel7_IRQn  Secure state
//   <o.25> 57  HPDMA2_Channel8_IRQn  Secure state
//   <o.26> 58  HPDMA2_Channel9_IRQn  Secure state
//   <o.27> 59  HPDMA2_Channel10_IRQn Secure state
//   <o.28> 60  HPDMA2_Channel11_IRQn Secure state
//   <o.29> 61  HPDMA2_Channel12_IRQn Secure state
//   <o.30> 62  HPDMA2_Channel13_IRQn Secure state
//   <o.31> 63  HPDMA2_Channel14_IRQn Secure state
*/
#define NVIC_INIT_ITNS1_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 2 (Interrupts 64..95)
*/
#define NVIC_INIT_ITNS2    1

/*
// Interrupts 64..95 (bits [64..95] : <0=> Secure state <1=> Non-Secure state)
//   <o.0>  64  HPDMA2_Channel15_IRQn Secure state
//   <o.1>  65  HPDMA3_Channel0_IRQn  Secure state
//   <o.2>  66  HPDMA3_Channel1_IRQn  Secure state
//   <o.3>  67  HPDMA3_Channel2_IRQn  Secure state
//   <o.4>  68  HPDMA3_Channel3_IRQn  Secure state
//   <o.5>  69  HPDMA3_Channel4_IRQn  Secure state
//   <o.6>  70  HPDMA3_Channel5_IRQn  Secure state
//   <o.7>  71  HPDMA3_Channel6_IRQn  Secure state
//   <o.8>  72  HPDMA3_Channel7_IRQn  Secure state
//   <o.9>  73  HPDMA3_Channel8_IRQn  Secure state
//   <o.10> 74  HPDMA3_Channel9_IRQn  Secure state
//   <o.11> 75  HPDMA3_Channel10_IRQn Secure state
//   <o.12> 76  HPDMA3_Channel11_IRQn Secure state
//   <o.13> 77  HPDMA3_Channel12_IRQn Secure state
//   <o.14> 78  HPDMA3_Channel13_IRQn Secure state
//   <o.15> 79  HPDMA3_Channel14_IRQn Secure state
//   <o.16> 80  HPDMA3_Channel15_IRQn Secure state
//   <o.17> 81  LPDMA_Channel0_IRQn   Secure state
//   <o.18> 82  LPDMA_Channel1_IRQn   Secure state
//   <o.19> 83  LPDMA_Channel2_IRQn   Secure state
//   <o.20> 84  LPDMA_Channel3_IRQn   Secure state
//   <o.21> 85  ICACHE_IRQn           Secure state
//   <o.22> 86  DCACHE_IRQn           Secure state
//   <o.23> 87  ADC1_IRQn             Secure state
//   <o.24> 88  ADC2_IRQn             Secure state
//   <o.25> 89  ADC3_IRQn             Secure state
//   <o.26> 90  FDCAN_CAL_IRQn        Secure state
//   <o.27> 91  FDCAN1_IT0_IRQn       Secure state
//   <o.28> 92  FDCAN2_IT0_IRQn       Secure state
//   <o.29> 93  FDCAN3_IT0_IRQn       Secure state
//   <o.30> 94  FDCAN1_IT1_IRQn       Secure state
//   <o.31> 95  FDCAN2_IT1_IRQn       Secure state
*/
#define NVIC_INIT_ITNS2_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 3 (Interrupts 96..127)
*/
#define NVIC_INIT_ITNS3    1

/*
// Interrupts 96..127 (bits [96..127] : <0=> Secure state <1=> Non-Secure state)
//   <o.0>  96  FDCAN3_IT1_IRQn       Secure state
//   <o.1>  97  TIM1_BRK_IRQn         Secure state
//   <o.2>  98  TIM1_UP_IRQn          Secure state
//   <o.3>  99  TIM1_TRG_COM_IRQn     Secure state
//   <o.4>  100 TIM1_CC_IRQn          Secure state
//   <o.5>  101 TIM20_BRK_IRQn        Secure state
//   <o.6>  102 TIM20_UP_IRQn         Secure state
//   <o.7>  103 TIM20_TRG_COM_IRQn    Secure state
//   <o.8>  104 TIM20_CC_IRQn         Secure state
//   <o.9>  105 TIM2_IRQn             Secure state
//   <o.10> 106 TIM3_IRQn             Secure state
//   <o.11> 107 TIM4_IRQn             Secure state
//   <o.12> 108 I2C1_IRQn             Secure state
//   <o.13> 109 I3C1_IRQn             Secure state
//   <o.14> 110 I2C2_IRQn             Secure state
//   <o.15> 111 I3C2_IRQn             Secure state
//   <o.16> 112 SPI1_IRQn             Secure state
//   <o.17> 113 SPI2_IRQn             Secure state
//   <o.18> 114 USART1_IRQn           Secure state
//   <o.19> 115 USART2_IRQn           Secure state
//   <o.20> 116 USART3_IRQn           Secure state
//   <o.21> 117 VDEC_IRQn             Secure state
//   <o.22> 118 TIM8_BRK_IRQn         Secure state
//   <o.23> 119 TIM8_UP_IRQn          Secure state
//   <o.24> 120 TIM8_TRG_COM_IRQn     Secure state
//   <o.25> 121 TIM8_CC_IRQn          Secure state
//   <o.26> 122 FMC_IRQn              Secure state
//   <o.27> 123 SDMMC1_IRQn           Secure state
//   <o.28> 124 TIM5_IRQn             Secure state
//   <o.29> 125 SPI3_IRQn             Secure state
//   <o.30> 126 UART4_IRQn            Secure state
//   <o.31> 127 UART5_IRQn            Secure state
*/
#define NVIC_INIT_ITNS3_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 4 (Interrupts 128..159)
*/
#define NVIC_INIT_ITNS4    1

/*
// Interrupts 128..159 (bits [128..159] : <0=> Secure state <1=> Non-Secure state)
//   <o.0>  128 TIM6_IRQn             Secure state
//   <o.1>  129 TIM7_IRQn             Secure state
//   <o.2>  130 ETH1_SBD_IRQn         Secure state
//   <o.3>  131 ETH1_PMT_IRQn         Secure state
//   <o.4>  132 ETH1_LPI_IRQn         Secure state
//   <o.5>  133 ETH2_SBD_IRQn         Secure state
//   <o.6>  134 ETH2_PMT_IRQn         Secure state
//   <o.7>  135 ETH2_LPI_IRQn         Secure state
//   <o.8>  136 USART6_IRQn           Secure state
//   <o.9>  137 I2C3_IRQn             Secure state
//   <o.10> 138 I3C3_IRQn             Secure state
//   <o.11> 139 USBH_EHCI_IRQn        Secure state
//   <o.12> 140 USBH_OHCI_IRQn        Secure state
//   <o.13> 141 DCMI_PSSI_IRQn        Secure state
//   <o.14> 142 CSI_IRQn              Secure state
//   <o.15> 143 DSI_IRQn              Secure state
//   <o.16> 144 CRYP1_IRQn            Secure state
//   <o.17> 145 HASH_IRQn             Secure state
//   <o.18> 146 PKA_IRQn              Secure state
//   <o.19> 147 FPU_IRQn              Secure state
//   <o.20> 148 UART7_IRQn            Secure state
//   <o.21> 149 UART8_IRQn            Secure state
//   <o.22> 150 UART9_IRQn            Secure state
//   <o.23> 151 LPUART1_IRQn          Secure state
//   <o.24> 152 SPI4_IRQn             Secure state
//   <o.25> 153 SPI5_IRQn             Secure state
//   <o.26> 154 SPI6_IRQn             Secure state
//   <o.27> 155 SPI7_IRQn             Secure state
//   <o.28> 156 SPI8_IRQn             Secure state
//   <o.29> 157 SAI1_IRQn             Secure state
//   <o.30> 158 LTDC_IRQn             Secure state
//   <o.31> 159 LTDC_ER_IRQn          Secure state
*/
#define NVIC_INIT_ITNS4_VAL      0x00000000

/*
//   <e>Initialize ITNS 5 (Interrupts 160..191)
*/
#define NVIC_INIT_ITNS5    1

/*
// Interrupts 160..191 (bits [160..191] : <0=> Secure state <1=> Non-Secure state)
//   <o.0>  160 LTDC_L2_IRQn          Secure state
//   <o.1>  161 LTDC_L2_ER_IRQn       Secure state
//   <o.2>  162 SAI2_IRQn             Secure state
//   <o.3>  163 OCTOSPI1_IRQn         Secure state
//   <o.4>  164 OCTOSPI2_IRQn         Secure state
//   <o.5>  165 OTFDEC1_IRQn          Secure state
//   <o.6>  166 LPTIM1_IRQn           Secure state
//   <o.7>  167 VENC_IRQn             Secure state
//   <o.8>  168 I2C4_IRQn             Secure state
//   <o.9>  169 USBH_WAKEUP_IRQn      Secure state
//   <o.10> 170 SPDIFRX_IRQn          Secure state
//   <o.11> 171 IPCC1_RX1_IRQn        Non-Secure state
//   <o.12> 172 IPCC1_TX1_IRQn        Non-Secure state
//   <o.13> 173 IPCC1_RX1_S_IRQn      Secure state
//   <o.14> 174 IPCC1_TX1_S_IRQn      Secure state
//   <o.15> 175 IPCC2_RX1_IRQn        Non-Secure state
//   <o.16> 176 IPCC2_TX1_IRQn        Non-Secure state
//   <o.17> 177 IPCC2_RX1_S_IRQn      Secure state
//   <o.18> 178 IPCC2_TX1_S_IRQn      Secure state
//   <o.19> 179 SAES_IRQn             Secure state
//   <o.20> 180 CRYP2_IRQn            Secure state
//   <o.21> 181 I2C5_IRQn             Secure state
//   <o.22> 182 USB3DR_WAKEUP_IRQn    Secure state
//   <o.23> 183 GPU_IRQn              Secure state
//   <o.24> 184 MDF1_FLT0_IRQn        Secure state
//   <o.25> 185 MDF1_FLT1_IRQn        Secure state
//   <o.26> 186 MDF1_FLT2_IRQn        Secure state
//   <o.27> 187 MDF1_FLT3_IRQn        Secure state
//   <o.28> 188 MDF1_FLT4_IRQn        Secure state
//   <o.29> 189 MDF1_FLT5_IRQn        Secure state
//   <o.30> 190 MDF1_FLT6_IRQn        Secure state
//   <o.31> 191 MDF1_FLT7_IRQn        Secure state
*/

#define NVIC_INIT_ITNS5_VAL      0x00000000

/*
//   <e>Initialize ITNS 6 (Interrupts 192..223)
*/
#define NVIC_INIT_ITNS6    1

/*
// Interrupts 192..223 (bits [192..223] : <0=> Secure state <1=> Non-Secure state)
//   <o.0>  192 SAI3_IRQn             Secure state
//   <o.1>  193 TIM15_IRQn            Secure state
//   <o.2>  194 TIM16_IRQn            Secure state
//   <o.3>  195 TIM17_IRQn            Secure state
//   <o.4>  196 TIM12_IRQn            Secure state
//   <o.5>  197 SDMMC2_IRQn           Secure state
//   <o.6>  198 DCMIPP_IRQn           Secure state
//   <o.7>  199 HSEM_IRQn             Non-Secure state
//   <o.8>  200 HSEM_S_IRQn           Secure state
//   <o.9>  201 nCTIIRQ1_IRQn         Secure state
//   <o.10> 202 nCTIIRQ2_IRQn         Secure state
//   <o.11> 203 TIM13_IRQn            Secure state
//   <o.12> 204 TIM14_IRQn            Secure state
//   <o.13> 205 TIM10_IRQn            Secure state
//   <o.14> 206 RNG_IRQn              Secure state
//   <o.15> 207 ADF1_FLT_IRQn         Secure state
//   <o.16> 208 I2C6_IRQn             Secure state
//   <o.17> 209 COMBOPHY_WAKEUP_IRQn  Secure state
//   <o.18> 210 I2C7_IRQn             Secure state
//   <o.19> 211 RESERVED_211          Secure state
//   <o.20> 212 I2C8_IRQn             Secure state
//   <o.21> 213 I3C4_IRQn             Secure state
//   <o.22> 214 SDMMC3_IRQn           Secure state
//   <o.23> 215 LPTIM2_IRQn           Secure state
//   <o.24> 216 LPTIM3_IRQn           Secure state
//   <o.25> 217 LPTIM4_IRQn           Secure state
//   <o.26> 218 LPTIM5_IRQn           Secure state
//   <o.27> 219 OTFDEC2_IRQn          Secure state
//   <o.28> 220 CPU1_SEV_IRQn         Secure state
//   <o.29> 221 CPU3_SEV_IRQn         Secure state
//   <o.30> 222 RCC_WAKEUP_IRQn       Secure state
//   <o.31> 223 SAI4_IRQn             Secure state
*/

#define NVIC_INIT_ITNS6_VAL      0x00000000

/*
//   <e>Initialize ITNS 7 (Interrupts 224..255)
*/
#define NVIC_INIT_ITNS7    1

/*
// Interrupts 224..255 (bits [224..255] : <0=> Secure state <1=> Non-Secure state)
//   <o.0>  224 DTS_IRQn              Secure state
//   <o.1>  225 TIM11_IRQn            Secure state
//   <o.2>  226 CPU2_WAKEUP_PIN_IRQn  Secure state
//   <o.3>  227 USB3DR_BC_IRQn        Secure state
//   <o.4>  228 USB3DR_IRQn           Secure state
//   <o.5>  229 UCPD1_IRQn            Secure state
//   <o.6>  230 RESERVED_230          Secure state
//   <o.7>  231 RESERVED_231          Secure state
//   <o.8>  232 RESERVED_232          Secure state
//   <o.9>  233 RESERVED_233          Secure state
//   <o.10> 234 RESERVED_234          Secure state
//   <o.11> 235 RESERVED_235          Secure state
//   <o.12> 236 RESERVED_236          Secure state
//   <o.13> 237 RESERVED_237          Secure state
//   <o.14> 238 RESERVED_238          Secure state
//   <o.15> 239 RESERVED_239          Secure state
//   <o.16> 240 SERF_IRQn             Secure state
//   <o.17> 241 BUSPERFM_IRQn         Secure state
//   <o.18> 242 RAMCFG_IRQn           Secure state
//   <o.19> 243 DDRCTRL_IRQn          Secure state
//   <o.20> 244 DDRPHY_IRQn           Secure state
//   <o.21> 245 DFI_ERR_IRQn          Secure state
//   <o.22> 246 IAC_IRQn              Secure state
//   <o.23> 247 VDDCPU_VD_IRQn        Secure state
//   <o.24> 248 VDDCORE_VD_IRQn       Secure state
//   <o.25> 249 RESERVED_249          Secure state
//   <o.26> 250 ETHSW_IRQn            Secure state
//   <o.27> 251 ETHSW_MSG_BUF_IRQn    Secure state
//   <o.28> 252 ETHSW_FSC_IRQn        Secure state
//   <o.29> 253 HPDMA1_WKUP_IRQn      Secure state
//   <o.30> 254 HPDMA2_WKUP_IRQn      Secure state
//   <o.31> 255 HPDMA3_WKUP_IRQn      Secure state
*/

#define NVIC_INIT_ITNS7_VAL      0x00000000

/*
//   <e>Initialize ITNS 8 (Interrupts 256..287)
*/
#define NVIC_INIT_ITNS8    1

/*
// Interrupts 256..287 (bits [256..287] : <0=> Secure state <1=> Non-Secure state)
//   <o.0>  256 LPDMA_WKUP_IRQn       Secure state
//   <o.1>  257 UCPD1_VBUS_IRQn       Secure state
//   <o.2>  258 UCPD1_VSAFE5V_IRQn    Secure state
//   <o.3>  259 RCC_HSI_FMON_IRQn     Secure state
//   <o.4>  260 VDDGPU_VD_IRQn        Secure state
//   <o.5>  261 RESERVED_261          Secure state
//   <o.6>  262 RESERVED_262          Secure state
//   <o.7>  263 RESERVED_263          Secure state
//   <o.8>  264 RESERVED_264          Secure state
//   <o.9>  265 RESERVED_265          Secure state
//   <o.10> 266 RESERVED_266          Secure state
//   <o.11> 267 RESERVED_267          Secure state
//   <o.12> 268 EXTI1_0_IRQn          Secure state
//   <o.13> 269 EXTI1_1_IRQn          Secure state
//   <o.14> 270 EXTI1_2_IRQn          Secure state
//   <o.15> 271 EXTI1_3_IRQn          Secure state
//   <o.16> 272 EXTI1_4_IRQn          Secure state
//   <o.17> 273 EXTI1_5_IRQn          Secure state
//   <o.18> 274 EXTI1_6_IRQn          Secure state
//   <o.19> 275 EXTI1_7_IRQn          Secure state
//   <o.20> 276 EXTI1_8_IRQn          Secure state
//   <o.21> 277 EXTI1_9_IRQn          Secure state
//   <o.22> 278 EXTI1_10_IRQn         Secure state
//   <o.23> 279 EXTI1_11_IRQn         Secure state
//   <o.24> 280 EXTI1_12_IRQn         Secure state
//   <o.25> 281 EXTI1_13_IRQn         Secure state
//   <o.26> 282 EXTI1_14_IRQn         Secure state
//   <o.27> 283 EXTI1_15_IRQn         Secure state
//   <o.28> 284 RESERVED_284          Secure state
//   <o.29> 285 RESERVED_285          Secure state
//   <o.30> 286 RESERVED_286          Secure state
//   <o.31> 287 RESERVED_287          Secure state
*/

#define NVIC_INIT_ITNS8_VAL      0x00000000

/*
//   <e>Initialize ITNS 9 (Interrupts 288..319)
*/
#define NVIC_INIT_ITNS9    1

/*
// Interrupts 288..319 (bits [288..319] : <0=> Secure state <1=> Non-Secure state)
//   <o.0>  288 RESERVED_288          Secure state
//   <o.1>  289 RESERVED_289          Secure state
//   <o.2>  290 RESERVED_290          Secure state
//   <o.3>  291 RESERVED_291          Secure state
//   <o.4>  292 RESERVED_292          Secure state
//   <o.5>  293 RESERVED_293          Secure state
//   <o.6>  294 RESERVED_294          Secure state
//   <o.7>  295 RESERVED_295          Secure state
//   <o.8>  296 RESERVED_296          Secure state
//   <o.9>  297 RESERVED_297          Secure state
//   <o.10> 298 RESERVED_298          Secure state
//   <o.11> 299 RESERVED_299          Secure state
//   <o.12> 300 RESERVED_300          Secure state
//   <o.13> 301 RESERVED_301          Secure state
//   <o.14> 302 RESERVED_302          Secure state
//   <o.15> 303 RESERVED_303          Secure state
//   <o.16> 304 RESERVED_304          Secure state
//   <o.17> 305 RESERVED_305          Secure state
//   <o.18> 306 RESERVED_306          Secure state
//   <o.19> 307 RESERVED_307          Secure state
//   <o.20> 308 IS2M_IRQn             Secure state
//   <o.21> 309 RESERVED_309          Secure state
//   <o.22> 310 DDRPERFM_IRQn         Secure state
//   <o.23> 311 RESERVED_311          Secure state
//   <o.24> 312 RESERVED_312          Secure state
//   <o.25> 313 RESERVED_313          Secure state
//   <o.26> 314 RESERVED_314          Secure state
//   <o.27> 315 RESERVED_315          Secure state
//   <o.28> 316 RESERVED_316          Secure state
//   <o.29> 317 RESERVED_317          Secure state
//   <o.30> 318 RESERVED_318          Secure state
//   <o.31> 319 RESERVED_319          Secure state
*/

#define NVIC_INIT_ITNS9_VAL      0x00000000

/*
//   </e>
*/

/*
// </h>
*/

/*
    max 8 SAU regions.
    SAU regions are defined in partition.h
 */

#define SAU_INIT_REGION(n) \
    SAU->RNR  =  (n                                     & SAU_RNR_REGION_Msk); \
    SAU->RBAR =  (SAU_INIT_START##n                     & SAU_RBAR_BADDR_Msk); \
    SAU->RLAR =  (SAU_INIT_END##n                       & SAU_RLAR_LADDR_Msk) | \
                ((SAU_INIT_NSC##n << SAU_RLAR_NSC_Pos)  & SAU_RLAR_NSC_Msk)   | 1U

/**
  \brief   Setup a SAU Region
  \details Writes the region information contained in SAU_Region to the
           registers SAU_RNR, SAU_RBAR, and SAU_RLAR
 */
__STATIC_INLINE void TZ_SAU_Setup (void)
{

#if defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U)

  #if defined (SAU_INIT_REGION0) && (SAU_INIT_REGION0 == 1U)
    SAU_INIT_REGION(0);
  #endif

  #if defined (SAU_INIT_REGION1) && (SAU_INIT_REGION1 == 1U)
    SAU_INIT_REGION(1);
  #endif

  #if defined (SAU_INIT_REGION2) && (SAU_INIT_REGION2 == 1U)
    SAU_INIT_REGION(2);
  #endif

  #if defined (SAU_INIT_REGION3) && (SAU_INIT_REGION3 == 1U)
    SAU_INIT_REGION(3);
  #endif

  #if defined (SAU_INIT_REGION4) && (SAU_INIT_REGION4 == 1U)
    SAU_INIT_REGION(4);
  #endif

  #if defined (SAU_INIT_REGION5) && (SAU_INIT_REGION5 == 1U)
    SAU_INIT_REGION(5);
  #endif

  #if defined (SAU_INIT_REGION6) && (SAU_INIT_REGION6 == 1U)
    SAU_INIT_REGION(6);
  #endif

  #if defined (SAU_INIT_REGION7) && (SAU_INIT_REGION7 == 1U)
    SAU_INIT_REGION(7);
  #endif

#endif /* defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U) */

  #if defined (SAU_INIT_CTRL) && (SAU_INIT_CTRL == 1U)
    SAU->CTRL = ((SAU_INIT_CTRL_ENABLE << SAU_CTRL_ENABLE_Pos) & SAU_CTRL_ENABLE_Msk) |
                ((SAU_INIT_CTRL_ALLNS  << SAU_CTRL_ALLNS_Pos)  & SAU_CTRL_ALLNS_Msk)   ;
  #endif

  #if defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U)
    SCB->SCR   = (SCB->SCR   & ~(SCB_SCR_SLEEPDEEPS_Msk    )) |
                   ((SCB_CSR_DEEPSLEEPS_VAL     << SCB_SCR_SLEEPDEEPS_Pos)     & SCB_SCR_SLEEPDEEPS_Msk);

    SCB->AIRCR = (SCB->AIRCR & ~(SCB_AIRCR_VECTKEY_Msk   | SCB_AIRCR_SYSRESETREQS_Msk |
                                 SCB_AIRCR_BFHFNMINS_Msk | SCB_AIRCR_PRIS_Msk          ))                    |
                   ((0x05FAU                    << SCB_AIRCR_VECTKEY_Pos)      & SCB_AIRCR_VECTKEY_Msk)      |
                   ((SCB_AIRCR_SYSRESETREQS_VAL << SCB_AIRCR_SYSRESETREQS_Pos) & SCB_AIRCR_SYSRESETREQS_Msk) |
                   ((SCB_AIRCR_PRIS_VAL         << SCB_AIRCR_PRIS_Pos)         & SCB_AIRCR_PRIS_Msk)         |
                   ((SCB_AIRCR_BFHFNMINS_VAL    << SCB_AIRCR_BFHFNMINS_Pos)    & SCB_AIRCR_BFHFNMINS_Msk);
  #endif /* defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U) */

  #if defined (__FPU_USED) && (__FPU_USED == 1U) && \
      defined (TZ_FPU_NS_USAGE) && (TZ_FPU_NS_USAGE == 1U)

    SCB->NSACR = (SCB->NSACR & ~(SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk)) |
                   ((SCB_NSACR_CP10_11_VAL << SCB_NSACR_CP10_Pos) & (SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk));

    FPU->FPCCR = (FPU->FPCCR & ~(FPU_FPCCR_TS_Msk | FPU_FPCCR_CLRONRETS_Msk | FPU_FPCCR_CLRONRET_Msk)) |
                   ((FPU_FPCCR_TS_VAL        << FPU_FPCCR_TS_Pos       ) & FPU_FPCCR_TS_Msk       ) |
                   ((FPU_FPCCR_CLRONRETS_VAL << FPU_FPCCR_CLRONRETS_Pos) & FPU_FPCCR_CLRONRETS_Msk) |
                   ((FPU_FPCCR_CLRONRET_VAL  << FPU_FPCCR_CLRONRET_Pos ) & FPU_FPCCR_CLRONRET_Msk );
  #endif

  #if defined (NVIC_INIT_ITNS0) && (NVIC_INIT_ITNS0 == 1U)
    NVIC->ITNS[0] = NVIC_INIT_ITNS0_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS1) && (NVIC_INIT_ITNS1 == 1U)
    NVIC->ITNS[1] = NVIC_INIT_ITNS1_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS2) && (NVIC_INIT_ITNS2 == 1U)
    NVIC->ITNS[2] = NVIC_INIT_ITNS2_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS3) && (NVIC_INIT_ITNS3 == 1U)
    NVIC->ITNS[3] = NVIC_INIT_ITNS3_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS4) && (NVIC_INIT_ITNS4 == 1U)
    NVIC->ITNS[4] = NVIC_INIT_ITNS4_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS5) && (NVIC_INIT_ITNS5 == 1U)
    NVIC->ITNS[5] = NVIC_INIT_ITNS5_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS6) && (NVIC_INIT_ITNS6 == 1U)
    NVIC->ITNS[6] = NVIC_INIT_ITNS6_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS7) && (NVIC_INIT_ITNS7 == 1U)
    NVIC->ITNS[7] = NVIC_INIT_ITNS7_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS8) && (NVIC_INIT_ITNS8 == 1U)
    NVIC->ITNS[8] = NVIC_INIT_ITNS8_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS9) && (NVIC_INIT_ITNS9 == 1U)
    NVIC->ITNS[9] = NVIC_INIT_ITNS9_VAL;
  #endif
}

#endif  /* PARTITION_STM32MP2XX_H */
