/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    compiler.h
  * @author  GPM WBL Application Team
  * @brief   Compiler-dependent macros.
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

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __COMPILER_H__
#define __COMPILER_H__

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define QUOTEME(a) #a

#define FUNCTION_PROTOTYPE(func_name, ret_type, ...) ret_type func_name(__VA_ARGS__);

/** @addtogroup compiler_macros compiler macros
  * @{
  */

/** @addtogroup IAR_toolchain_macros    IAR toolchain macros
  * @{
  */

/**
  * @brief  This is the section dedicated to IAR toolchain
  */
#if defined(__ICCARM__) || defined(__IAR_SYSTEMS_ASM__)

/**
  * @brief  PACKED
  *         Use the PACKED macro for variables that needs to be packed.
  *         Usage:  PACKED(struct) myStruct_s
  *                 PACKED(union) myStruct_s
  */
#define PACKED(decl)                   __packed decl

/**
  * @brief  REQUIRED
  *         Use the REQUIRED macro for variables that must be always included.
  *         Usage:  REQUIRED(static uint8_t my_array[16])
  *                 REQUIRED(static int my_int)
  */
#define REQUIRED(decl)                 __root decl

/**
  * @brief  NORETURN_FUNCTION
  *         Use the NORETURN_FUNCTION macro to declare a no return function.
  *         Usage:  NORETURN_FUNCTION(void my_noretrun_function(void))
  */
#define NORETURN_FUNCTION(function)                 __noreturn function

/**
  * @brief  NOSTACK_FUNCTION
  *         Use the NOSTACK_FUNCTION macro to indicate that function should not use any stack.
  *         Typical usage is for hard fault handler, to avoid altering the value of the stack pointer.
  *         Usage:  NOSTACK_FUNCTION(void my_noretrun_function(void))
  */
#define NOSTACK_FUNCTION(function)                 __stackless function

/**
  * @brief  SECTION
  *         Use the SECTION macro to assign data or code in a specific section.
  *         Usage:  SECTION(".my_section")
  */
#define SECTION(name)                  _Pragma(QUOTEME(location=name))

/**
  * @brief  ALIGN
  *         Use the ALIGN macro to specify the alignment of a variable.
  *         Usage:  ALIGN(4)
  */
#define ALIGN(v)                       _Pragma(QUOTEME(data_alignment=v))

/**
  * @brief  WEAK_FUNCTION
  *         Use the WEAK_FUNCTION macro to declare a weak function.
  *         Usage:  WEAK_FUNCTION(int my_weak_function(void))
  */
#define WEAK_FUNCTION(function)        __weak function

/**
  * @brief  WEAK_ALIAS_FUNCTION
  *         Use the WEAK_ALIAS_FUNCTION macro to declare a weak alias of a function.
  *         Usage:  WEAK_ALIAS_FUNCTION(my_weak_alias_function, my_function, <return_type>, <args...>)
  */
#define WEAK_ALIAS_FUNCTION(new_name, old_name, ...) _Pragma(QUOTEME(weak new_name=old_name))

/**
  * @brief  NO_INIT
  *         Use the NO_INIT macro to declare a not initialized variable in RAM
  *         Usage:  NO_INIT(int my_no_init_var)
  *         Usage:  NO_INIT(uint16_t my_no_init_array[10])
  */
#define NO_INIT(var)                   __no_init var

/**
  * @brief  NO_INIT_SECTION
  *         Use the NO_INIT_SECTION macro to declare a not initialized variable in RAM in
  *         in a specific section.
  *         Usage:  NO_INIT_SECTION(int my_no_init_var, "MySection")
  *         Usage:  NO_INIT_SECTION(uint16_t my_no_init_array[10], "MySection")
  */
#define NO_INIT_SECTION(var, sect)                  SECTION(sect) __no_init var

/**
  * @brief  NO_INLINE
  *         This function attribute suppresses the inlining of a function at the call points of the function.
  *         Usage:  NO_INLINE(void my_noinline_function(void))
  */
#define NO_INLINE(function)                   _Pragma(QUOTEME(optimize=no_inline)) function

#define VARIABLE_SIZE 0
#pragma segment = "CSTACK"
#define _INITIAL_SP                  __sfe( "CSTACK" ) /* Stack address */
extern void __iar_program_start(void);
#define RESET_HANDLER                  __iar_program_start

/**
 * @}
 */

/** @addtogroup Keil_toolchain_macros    Keil toolchain macros
  * @{
  */

/**
  * @brief  This is the section dedicated to Keil toolchain
  */
#else
#if defined(__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100))

/**
  * @brief  PACKED
  *         Use the PACKED macro for variables that needs to be packed.
  *         Usage:  PACKED(struct) myStruct_s
  *                 PACKED(union) myStruct_s
  */
#define PACKED(decl)                    decl __attribute__((packed))

/**
  * @brief  REQUIRED
  *         Use the REQUIRED macro for variables that must be always included.
  *         Usage:  REQUIRED(static uint8_t my_array[16])
  *                 REQUIRED(static int my_int)
  */
#ifndef REQUIRED
  #define REQUIRED(decl)                      decl __attribute__((used))
#endif

/**
  * @brief  SECTION
  *         Use the SECTION macro to assign data or code in a specific section.
  *         Usage:  SECTION(".my_section")
  */
#define SECTION(name)                   __attribute__((section(name)))

/**
  * @brief  ALIGN
  *         Use the ALIGN macro to specify the alignment of a variable.
  *         Usage:  ALIGN(4)
  */
#define ALIGN(N)                        __attribute__((aligned(N)))

/**
  * @brief  WEAK_ALIAS_FUNCTION
  *         Use the WEAK_ALIAS_FUNCTION macro to declare a weak alias of a function.
  *         Usage:  WEAK_ALIAS_FUNCTION(my_weak_alias_function, my_function, <return_type>, <args...>)
  */
#define WEAK_ALIAS_FUNCTION(new_name, old_name, ...) \
    __attribute__((weak, alias(QUOTEME(old_name)))) FUNCTION_PROTOTYPE(new_name, __VA_ARGS__)

/**
  * @brief  NORETURN_FUNCTION
  *         Use the NORETURN_FUNCTION macro to declare a no return function.
  *         Usage:  NORETURN_FUNCTION(void my_noretrun_function(void))
  */
#define NORETURN_FUNCTION(function)     __attribute__((noreturn)) function

/**
  * @brief  NOSTACK_FUNCTION
  *         Use the NOSTACK_FUNCTION macro to indicate that function should not use any stack.
  *         Typical usage is for hard fault handler, to avoid altering the value of the stack pointer.
  *         In keil this is a dummy implementation since no equivalent function is available
  *         Usage:  NOSTACK_FUNCTION(void my_noretrun_function(void))
  */
#define NOSTACK_FUNCTION(function)                 function

/**
  * @brief  NO_INLINE
  *         This function attribute suppresses the inlining of a function at the call points of the function.
  *         Usage:  NO_INLINE(void my_noinline_function(void))
  */
#define NO_INLINE(function)                   __attribute__((noinline)) function

#if defined(__CC_ARM)
/**
  * @brief  WEAK_FUNCTION
  *         Use the WEAK_FUNCTION macro to declare a weak function.
  *         Usage:  WEAK_FUNCTION(int my_weak_function(void))
  */
#define WEAK_FUNCTION(function)             __weak function

/**
  * @brief  NO_INIT
  *         Use the NO_INIT macro to declare a not initialized variable.
  *         Usage:  NO_INIT(int my_no_init_var)
  *         Usage:  NO_INIT(uint16_t my_no_init_array[10])
  */
#define NO_INIT(var)                        var __attribute__((section( ".noinit.data" ), zero_init))

/**
  * @brief  NO_INIT_SECTION
  *         Use the NO_INIT_SECTION macro to declare a not initialized variable that should be placed in a specific section.
	*         Linker script is in charge of placing that section in RAM.
  *         Usage:  NO_INIT_SECTION(int my_no_init_var, "MySection")
  *         Usage:  NO_INIT_SECTION(uint16_t my_no_init_array[10], "MySection")
  */
#define NO_INIT_SECTION(var, sect)                   var __attribute__((section( sect ), zero_init))
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100)
/**
  * @brief  WEAK_FUNCTION
  *         Use the WEAK_FUNCTION macro to declare a weak function.
  *         Usage:  WEAK_FUNCTION(int my_weak_function(void))
  */
#define WEAK_FUNCTION(function)             __attribute__((weak)) function

/**
  * @brief  NO_INIT
  *         Use the NO_INIT macro to declare a not initialized variable.
  *         Usage:  NO_INIT(int my_no_init_var)
  *         Usage:  NO_INIT(uint16_t my_no_init_array[10])
  */
#define NO_INIT(var)                       var __attribute__((section(".bss.noinit.data")))

/**
  * @brief  NO_INIT_SECTION
  *         Use the NO_INIT_SECTION macro to declare a not initialized variable that should be placed in a specific section.
	*         Linker script is in charge of placing that section in RAM.
  *         Usage:  NO_INIT_SECTION(int my_no_init_var, "MySection")
  *         Usage:  NO_INIT_SECTION(uint16_t my_no_init_array[10], "MySection")
  */
#define NO_INIT_SECTION(var, sect)                  var __attribute__((section(".bss" sect)))

#endif

extern void __main(void);
extern int main(void);
extern unsigned int Image$$ARM_LIB_STACK$$ZI$$Limit;
#define _INITIAL_SP                         (void(*)(void))&Image$$ARM_LIB_STACK$$ZI$$Limit  /* Stack address */
#define VARIABLE_SIZE 1

/**
 * @}
  */

/** @addtogroup GCC_toolchain_macros    GCC toolchain macros
  * @{
  */

/**
  * @brief  This is the section dedicated to GCC toolchain
  */
#else
#ifdef __GNUC__

/**
  * @brief  PACKED
  *         Use the PACKED macro for variables that needs to be packed.
  *         Usage:  PACKED(struct) myStruct_s
  *                 PACKED(union) myStruct_s
  */
#define PACKED(decl)                    decl __attribute__((packed))

/**
  * @brief  REQUIRED
  *         Use the REQUIRED macro for variables that must be always included.
  *         Usage:  REQUIRED(static uint8_t my_array[16])
  *                 REQUIRED(static int my_int)
  */
#define REQUIRED(var)                   var __attribute__((used))

/**
  * @brief  SECTION
  *         Use the SECTION macro to assign data or code in a specific section.
  *         Usage:  SECTION(".my_section")
  */
#define SECTION(name)                   __attribute__((section(name)))

/**
  * @brief  ALIGN
  *         Use the ALIGN macro to specify the alignment of a variable.
  *         Usage:  ALIGN(4)
  */
#define ALIGN(N)                        __attribute__((aligned(N)))

/**
  * @brief  WEAK_FUNCTION
  *         Use the WEAK_FUNCTION macro to declare a weak function.
  *         Usage:  WEAK_FUNCTION(int my_weak_function(void))
  */
#define WEAK_FUNCTION(function)         __attribute__((weak)) function

/**
  * @brief  WEAK_ALIAS_FUNCTION
  *         Use the WEAK_ALIAS_FUNCTION macro to declare a weak alias of a function.
  *         Usage:  WEAK_ALIAS_FUNCTION(my_weak_alias_function, my_function, <return_type>, <args...>)
  */
#define WEAK_ALIAS_FUNCTION(new_name, old_name, ...) \
    __attribute__((weak, alias(QUOTEME(old_name)))) FUNCTION_PROTOTYPE(new_name, __VA_ARGS__)

/**
  * @brief  NORETURN_FUNCTION
  *         Use the NORETURN_FUNCTION macro to declare a no return function.
  *         Usage:  NORETURN_FUNCTION(void my_noretrun_function(void))
  */
#define NORETURN_FUNCTION(function)     __attribute__((noreturn)) function

/**
  * @brief  NOSTACK_FUNCTION
  *         Use the NOSTACK_FUNCTION macro to indicate that function should not use any stack.
  *         Typical usage is for hard fault handler, to avoid altering the value of the stack pointer.
  *         In keil this is a dummy implementation since no equivalent function is available
  *         Usage:  NOSTACK_FUNCTION(void my_noretrun_function(void))
  */
#define NOSTACK_FUNCTION(function)                 function

/**
  * @brief  NO_INIT
  *         Use the NO_INIT macro to declare a not initialized variable placed in RAM
  *         Linker script has to make sure that section ".noinit" is not initialized
  *         Usage:  NO_INIT(int my_no_init_var)
  *         Usage:  NO_INIT(uint16_t my_no_init_array[10])
 */
#define NO_INIT(var)                    var  __attribute__((section(".noinit")))

/**
  * @brief  NO_INIT_SECTION
  *         Use the NO_INIT_SECTION macro to declare a not initialized variable.
  *         In order to work properly this macro should be aligned with the linker file.
  *         Usage:  NO_INIT_SECTION(int my_no_init_var, "MySection")
  *         Usage:  NO_INIT_SECTION(uint16_t my_no_init_array[10], "MySection")
  */
#define NO_INIT_SECTION(var, sect)                   var  __attribute__((section(sect)))

/**
  * @brief  NO_INLINE
  *         This function attribute suppresses the inlining of a function at the call points of the function.
  *         Usage:  NO_INIT_SECTION(void my_noinline_function(void))
  */
#define NO_INLINE(function)                   __attribute__((noinline)) function

#define _INITIAL_SP                     (void(*)(void))(&_estack)
#define VARIABLE_SIZE 0

#else

#error Neither ICCARM, CC ARM nor GNUC C detected. Define your macros.

#endif
#endif
#endif

/**
 * @}
 */

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif /* __COMPILER_H__ */
