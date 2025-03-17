/**
 ******************************************************************************
 * @file        : faults.c
 * @brief       : error helper module
 * @author      : Serge Ayer <serge.ayer@hefr.ch>
 * @author      : Luca Haab <luca.haab@hefr.ch>
 * @date        : 19. March 2023
 ******************************************************************************
 * @copyright   : Copyright (c) 2023 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Helper module for errors
 ******************************************************************************
 */

/* Although normally "The Standard Library input/output functions shall not be
   used" (Rule 21.6), in this case we make use of it as temporary solution. */
// cppcheck-suppress misra-c2012-21.6 
#include <stdio.h>

#include "EventRecorder.h"

/* Local variables located in shared RAM */
#define STR_LENGTH 128
static char temp_str[STR_LENGTH] __attribute__((section("ram_shared")));

#define ERROR_LOG_ARRAY(x) EventRecordData(EventID(EventLevelError, 0xFD, 0x01), x, STR_LENGTH)

static void error_handler(void)
{
    // report the error and loop
    ERROR_LOG_ARRAY(&temp_str);
    while (1) {
    }
}

void startup_error_handler(void)
{   
    (void)snprintf(temp_str, sizeof(temp_str), "A Fatal Error was detected, the system will halt");
    error_handler();
}

void app_error_handler(uint32_t errNo)
{
    (void)snprintf(temp_str, sizeof(temp_str), "A Application Error was detected (%d), the system will halt", errNo);
    error_handler();
}