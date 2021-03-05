/******************************************************************************
 * @file     startup_pmg1s2.c
 * @brief    CMSIS-Core(M) Device Startup File for Category 2 device
 * @version  V2.0.0
 * @date     20. May 2019
 ******************************************************************************/
/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 * Copyright 2019-2021 Cypress Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdbool.h>
#include <string.h>
#include "cy_utils.h"
#include "system_cat2.h"
#include "cy_device.h"
#include "cy_device_headers.h"
#include "cy_syslib.h"

#ifndef __RAM_VECTOR_TABLE_ATTRIBUTE
    #if defined(__ARMCC_VERSION)
        #define __RAM_VECTOR_TABLE_ATTRIBUTE __attribute((used, section(".bss.RESET_RAM")))
    #elif defined(__GNUC__)
        #define __RAM_VECTOR_TABLE_ATTRIBUTE CY_SECTION(".ram_vectors")
    #elif defined(__ICCARM__)
        #define __RAM_VECTOR_TABLE_ATTRIBUTE __attribute__ ((used, section(".intvec_ram")))
    #else
        #error "An unsupported toolchain"
    #endif  /* (__ARMCC_VERSION) */
#endif /* __RAM_VECTOR_TABLE_ATTRIBUTE */
cy_israddress __RAM_VECTOR_TABLE[CY_VECTOR_TABLE_SIZE] __RAM_VECTOR_TABLE_ATTRIBUTE; /**< Relocated vector table in SRAM */

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;

extern __NO_RETURN void __PROGRAM_START(void);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void __NO_RETURN Default_Handler(void);
void __NO_RETURN Reset_Handler  (void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#if (__GNUC__ >= 9)
#pragma GCC diagnostic ignored "-Wmissing-attributes"
#endif /* (__GNUC__ >= 9) */
#endif /* defined(__GNUC__) */

void NMI_Handler                        (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler                  (void) __attribute__ ((weak));
void SVC_Handler                        (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                     (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));

void ioss_interrupts_gpio_0_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler"))); /* GPIO P0 */
void ioss_interrupts_gpio_1_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler"))); /* GPIO P1 */
void ioss_interrupts_gpio_2_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler"))); /* GPIO P2 */
void ioss_interrupts_gpio_3_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler"))); /* GPIO P3 */
void ioss_interrupts_gpio_4_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler"))); /* GPIO P4 USB Wakeup */
void ioss_interrupt_gpio_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler"))); /* GPIO All ports */
void usbpd_0_interrupt_wakeup_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler"))); /* Ganged USBPD Interrupt */
void srss_interrupt_wdt_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler"))); /* WDT or Temp (WDT only in DeepSleep) */
void scb_0_interrupt_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler"))); /* SCB[0] */
void scb_1_interrupt_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler"))); /* SCB[1] */
void scb_2_interrupt_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler"))); /* SCB[2] */
void scb_3_interrupt_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler"))); /* SCB[3] */
void cpuss_interrupt_spcif_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler"))); /* SPC */
void usbpd_0_interrupt_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler"))); /* Synchronous USBPD Interrupts */
void tcpwm_interrupts_0_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler"))); /* TCPWM counter #0 */
void tcpwm_interrupts_1_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler"))); /* TCPWM counter #1 */
void tcpwm_interrupts_2_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler"))); /* TCPWM counter #2 */
void tcpwm_interrupts_3_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler"))); /* TCPWM counter #3 */
void usb_interrupt_hi_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler"))); /* USB Start of Frame */
void usb_interrupt_med_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler"))); /* USB EP1-EP8 data */
void usb_interrupt_lo_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler"))); /* USB EP1-EP8 data */
void crypto_interrupt_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler"))); /* Crypto block */


/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

extern const cy_israddress __VECTOR_TABLE[CY_VECTOR_TABLE_SIZE];
       const cy_israddress __VECTOR_TABLE[CY_VECTOR_TABLE_SIZE] __VECTOR_TABLE_ATTRIBUTE = {
    (cy_israddress)(&__INITIAL_SP),           /*     Initial Stack Pointer */
    Reset_Handler,                            /*     Reset Handler */
    NMI_Handler,                              /* -14 NMI Handler */
    HardFault_Handler,                        /* -13 Hard Fault Handler */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    SVC_Handler,                              /*  -5 SVCall Handler */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    PendSV_Handler,                           /*  -2 PendSV Handler */
    SysTick_Handler,                          /*  -1 SysTick Handler */

    /* Interrupts */
    ioss_interrupts_gpio_0_IRQHandler,        /*   0 GPIO P0 */
    ioss_interrupts_gpio_1_IRQHandler,        /*   1 GPIO P1 */
    ioss_interrupts_gpio_2_IRQHandler,        /*   2 GPIO P2 */
    ioss_interrupts_gpio_3_IRQHandler,        /*   3 GPIO P3 */
    ioss_interrupts_gpio_4_IRQHandler,        /*   4 GPIO P4 USB Wakeup */
    ioss_interrupt_gpio_IRQHandler,           /*   5 GPIO All ports */
    usbpd_0_interrupt_wakeup_IRQHandler,      /*   6 Ganged USBPD Interrupt */
    srss_interrupt_wdt_IRQHandler,            /*   7 WDT or Temp (WDT only in DeepSleep) */
    scb_0_interrupt_IRQHandler,               /*   8 SCB[0] */
    scb_1_interrupt_IRQHandler,               /*   9 SCB[1] */
    scb_2_interrupt_IRQHandler,               /*  10 SCB[2] */
    scb_3_interrupt_IRQHandler,               /*  11 SCB[3] */
    cpuss_interrupt_spcif_IRQHandler,         /*  12 SPC */
    usbpd_0_interrupt_IRQHandler,             /*  13 Synchronous USBPD Interrupts */
    tcpwm_interrupts_0_IRQHandler,            /*  14 TCPWM counter #0 */
    tcpwm_interrupts_1_IRQHandler,            /*  15 TCPWM counter #1 */
    tcpwm_interrupts_2_IRQHandler,            /*  16 TCPWM counter #2 */
    tcpwm_interrupts_3_IRQHandler,            /*  17 TCPWM counter #3 */
    usb_interrupt_hi_IRQHandler,              /*  18 USB Start of Frame */
    usb_interrupt_med_IRQHandler,             /*  19 USB EP1-EP8 data */
    usb_interrupt_lo_IRQHandler,              /*  20 USB EP1-EP8 data */
    crypto_interrupt_IRQHandler               /*  21 Crypto block */
};

#if defined (__GNUC__)
#pragma GCC diagnostic pop
#endif

/* Provide empty __WEAK implementation for the low-level initialization
   routine required by the RTOS-enabled applications.
   clib-support library provides FreeRTOS-specific implementation:
   https://github.com/cypresssemiconductorco/clib-support */
void cy_toolchain_init(void);
__WEAK void cy_toolchain_init(void)
{
}

#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
/* GCC: newlib crt0 _start executes software_init_hook.
   The cy_toolchain_init hook provided by clib-support library must execute
   after static data initialization and before static constructors. */
void software_init_hook();
void software_init_hook()
{
    cy_toolchain_init();
}
#elif defined(__ICCARM__)
/* Initialize data section */
void __iar_data_init3(void);

/* Call the constructors of all global objects */
void __iar_dynamic_initialization(void);

/* Define strong version to return zero for __iar_program_start
   to skip data sections initialization (__iar_data_init3). */
int __low_level_init(void);
int __low_level_init(void)
{
    return 0;
}
#endif


/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
    Cy_OnResetUser();

    /* CMSIS System Initialization */
    SystemInit();

    /* Copy vector table from ROM to RAM*/
    memcpy(__RAM_VECTOR_TABLE, __VECTOR_TABLE, CY_VECTOR_TABLE_SIZE_BYTES);

    /* Set vector table offset */
#if (__VTOR_PRESENT == 1u)
    SCB->VTOR = (uint32_t)&__RAM_VECTOR_TABLE;
#else
    CPUSS->CONFIG |= CPUSS_CONFIG_VECT_IN_RAM_Msk;
#endif /* (__VTOR_PRESENT == 1u) */
    __DSB();

#if defined(__ICCARM__)
    /* Initialize data section */
    __iar_data_init3();

    /* Initialize mutex pools for multi-thread applications */
    cy_toolchain_init();

    /* Call the constructors of all global objects */
    __iar_dynamic_initialization();
#endif

    /* Enter PreMain (C library entry point) */
    __PROGRAM_START();
}


/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
    while(1);
}

/*----------------------------------------------------------------------------
  Default Handler for Hard Fault
 *----------------------------------------------------------------------------*/
__WEAK void HardFault_Handler(void)
{
    Cy_SysLib_ProcessingFault();
}

__WEAK void Cy_OnResetUser(void)
{
    /* Empty weak function. The actual implementation to be in the provided by
    *  the application code strong function.
    *
    *  Call \ref SystemCoreClockUpdate() in this function to ensure global
    * global variables with CPU frequency are initialized properly.
    */
}

/* [] END OF FILE */
