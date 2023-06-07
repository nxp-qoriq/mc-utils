/* Copyright 2013 Freescale Semiconductor, Inc.
 * Copyright 2023 NXP
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * * Neither the name of the above-listed copyright holders nor the
 * names of any contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**************************************************************************//**

 @File          errors.h

 @Description   Error definitions.
*//***************************************************************************/

#ifndef __FSL_ERRORS_H
#define __FSL_ERRORS_H

#include <errno.h>

#include "common/types.h"
#include "common/fsl_stdio.h"
#include "common/fsl_stdlib.h"
#include "common/fsl_core.h"
#include "arch/fsl_soc.h"


/**************************************************************************//**
 @Group         gen_err_g  Errors, Events and Debug

 @Description   External routines.

 @{
*//***************************************************************************/

/*
 * Even though this file includes <errno.h>, developers are guided to use only
 * the following subset, for reasons of consistency and clarity.
 */

#ifndef EPERM
#define EPERM		1	/*!< Permission denied, no privileges */
#endif

#ifndef EIO
#define EIO		5	/*!< Input/output error */
#endif

#ifndef ENOMEM
#define ENOMEM		12	/*!< Out of memory */
#endif

#ifndef EACCES
#define EACCES		13	/*!< Illegal access, or invalid device state */
#endif

#ifndef EFAULT
#define EFAULT		14	/*!< Bad address detected */
#endif

#ifndef EBUSY
#define EBUSY		16	/*!< Device or resource is busy */
#endif

#ifndef EEXIST
#define EEXIST		17	/*!< Resource already exists */
#endif

#ifndef ENODEV
#define ENODEV		19	/*!< No such device, or device not configured */
#endif

#ifndef EINVAL
#define EINVAL		22	/*!< Invalid argument, or conflicting arguments */
#endif

#ifndef ENOSPC
#define ENOSPC		28	/*!< No space left (resource is full) */
#endif

#ifndef ENOTSUP
#define ENOTSUP		95	/*!< Operation not supported */
#endif

#ifndef ETIMEDOUT
#define ETIMEDOUT	110	/*!< Operation timed out */
#endif

#ifndef ENAVAIL
#define ENAVAIL		119	/*!< Resource not available, or not found */
#endif

#undef ENOERR			/* Prevent usage */


//TODO: obsolete - do not use in new code !!!

/**************************************************************************//**
 @Description    Error Type Enumeration
*//***************************************************************************/
enum error_type    /*   Comments / Associated Message Strings                      */
{                           /* ------------------------------------------------------------ */
    E_OK = 0                /*   Never use "RETURN_ERROR" with E_OK; Use "return E_OK;"     */
    ,E_WRITE_FAILED = EIO   /**< Write access failed on memory/device.                      */
                            /*   String: none, or device name.                              */
    ,E_NO_DEVICE = ENODEV   /**< The associated device is not initialized.                  */
                            /*   String: none.                                              */
    ,E_NOT_AVAILABLE = EAGAIN
                            /**< Resource is unavailable.                                   */
                            /*   String: none, unless the operation is not the main goal
                                 of the function (in this case add resource description).   */
    ,E_NO_MEMORY = ENOMEM   /**< External memory allocation failed.                         */
                            /*   String: description of item for which allocation failed.   */
    ,E_INVALID_ADDRESS = EFAULT
                            /**< Invalid address.                                           */
                            /*   String: description of the specific violation.             */
    ,E_BUSY = EBUSY         /**< Resource or module is busy.                                */
                            /*   String: none, unless the operation is not the main goal
                                 of the function (in this case add resource description).   */
    ,E_ALREADY_EXISTS = EEXIST
                            /**< Requested resource or item already exists.                 */
                            /*   Use when resource duplication or sharing are not allowed.
                                 String: none, unless the operation is not the main goal
                                 of the function (in this case add item description).       */
    ,E_INVALID_OPERATION = ENOSYS
                            /**< The operation/command is invalid (unrecognized).           */
                            /*   String: none.                                              */
    ,E_INVALID_VALUE = EDOM /**< Invalid value.                                             */
                            /*   Use for non-enumeration parameters, and
                                 only when other error types are not suitable.
                                 String: parameter description + "(should be <attribute>)",
                                 e.g: "Maximum Rx buffer length (should be divisible by 8)",
                                      "Channel number (should be even)".                    */
    ,E_NOT_IN_RANGE = ERANGE/**< Parameter value is out of range.                           */
                            /*   Don't use this error for enumeration parameters.
                                 String: parameter description + "(should be %d-%d)",
                                 e.g: "Number of pad characters (should be 0-15)".          */
    ,E_NOT_SUPPORTED = 100/*ENOTSUP*/
                            /**< The function is not supported or not implemented.          */
                            /*   String: none.                                              */
    ,E_TIMEOUT/* = ETIMEDOUT*/  /**< The operation timed out.                                   */
                            /*   String: none.                                              */

    ,E_INVALID_STATE           /* TODO: obsolete - do not use in new code*/
    ,E_INVALID_SELECTION       /* TODO: obsolete - do not use in new code*/
    ,E_CONFLICT       /* TODO: obsolete - do not use in new code*/
    ,E_NOT_FOUND       /* TODO: obsolete - do not use in new code*/
    ,E_FULL       /* TODO: obsolete - do not use in new code*/
    ,E_EMPTY       /* TODO: obsolete - do not use in new code*/
    ,E_ALREADY_FREE       /* TODO: obsolete - do not use in new code*/
    ,E_READ_FAILED       /* TODO: obsolete - do not use in new code*/
    ,E_INVALID_FRAME       /* TODO: obsolete - do not use in new code*/

    ,E_DUMMY_LAST           /* NEVER USED */
};


/**************************************************************************//**
 @Collection    Debug Levels for Errors and Events

                The level description refers to errors only.
                For events, classification is done by the user.

                The TRACE, INFO and WARNING levels are allowed only when using
                the DBG macro, and are not allowed when using the error macros
                (RETURN_ERROR or REPORT_ERROR).
 @{
*//***************************************************************************/
#define REPORT_LEVEL_CRITICAL   1       /**< Crasher: Incorrect flow, NULL pointers/handles. */
#define REPORT_LEVEL_MAJOR      2       /**< Cannot proceed: Invalid operation, parameters or
                                             configuration. */
#define REPORT_LEVEL_MINOR      3       /**< Recoverable problem: a repeating call with the same
                                             parameters may be successful. */
#define REPORT_LEVEL_WARNING    4       /**< Something is not exactly right, yet it is not an error. */
#define REPORT_LEVEL_INFO       5       /**< Messages which may be of interest to user/programmer. */
#define REPORT_LEVEL_TRACE      6       /**< Program flow messages. */

#define EVENT_DISABLED          0xff    /**< Disabled event (not reported at all) */

/* @} */



#define NO_MSG      ("")

#ifndef DEBUG_GLOBAL_LEVEL
#define DEBUG_GLOBAL_LEVEL  REPORT_LEVEL_WARNING
#endif /* DEBUG_GLOBAL_LEVEL */

#ifndef ERROR_GLOBAL_LEVEL
#define ERROR_GLOBAL_LEVEL  DEBUG_GLOBAL_LEVEL
#endif /* ERROR_GLOBAL_LEVEL */


#ifndef DEBUG_DYNAMIC_LEVEL
#define DEBUG_USING_STATIC_LEVEL

#ifdef DEBUG_STATIC_LEVEL
#define DEBUG_DYNAMIC_LEVEL DEBUG_STATIC_LEVEL
#else
#define DEBUG_DYNAMIC_LEVEL DEBUG_GLOBAL_LEVEL
#endif /* DEBUG_STATIC_LEVEL */

#else /* DEBUG_DYNAMIC_LEVEL */
#ifdef DEBUG_STATIC_LEVEL
#error "please use either DEBUG_STATIC_LEVEL or DEBUG_DYNAMIC_LEVEL (not both)"
#else
int DEBUG_DYNAMIC_LEVEL = DEBUG_GLOBAL_LEVEL;
#endif /* DEBUG_STATIC_LEVEL */
#endif /* !DEBUG_DYNAMIC_LEVEL */


#ifndef ERROR_DYNAMIC_LEVEL

#ifdef ERROR_STATIC_LEVEL
#define ERROR_DYNAMIC_LEVEL ERROR_STATIC_LEVEL
#else
#define ERROR_DYNAMIC_LEVEL ERROR_GLOBAL_LEVEL
#endif /* ERROR_STATIC_LEVEL */

#else /* ERROR_DYNAMIC_LEVEL */
#ifdef ERROR_STATIC_LEVEL
#error "please use either ERROR_STATIC_LEVEL or ERROR_DYNAMIC_LEVEL (not both)"
#else
int ERROR_DYNAMIC_LEVEL = ERROR_GLOBAL_LEVEL;
#endif /* ERROR_STATIC_LEVEL */
#endif /* !ERROR_DYNAMIC_LEVEL */

//#define PRINT_FORMAT        "[CPU%02d, %s:%d %s]"
//#define PRINT_FMT_PARAMS    core_get_id(), __FILE__, __LINE__, __FUNCTION__
#define PRINT_FORMAT        "[CPU, %s:%d %s]"
#define PRINT_FMT_PARAMS    __FILE__, __LINE__, __FUNCTION__

#if (!defined(DEBUG_ERRORS) || (DEBUG_ERRORS == 0))
/* No debug/error/event messages at all */
#define REPORT_ERROR(_level, _err, _vmsg)
#define RETURN_ERROR(_level, _err, _vmsg) \
        return (_err)
#define ERROR_CODE(_err)    (_err)

#else /* DEBUG_ERRORS > 0 */
extern const char *dbg_level_strings[];
extern const char *module_strings[];

char * err_type_strings (enum error_type err);

#define ERROR_CODE(_err)    (_err)
#define GET_ERROR_TYPE(_err)    (_err)

#define REPORT_ERROR(_level, _err, _vmsg) \
    do { \
        if (REPORT_LEVEL_##_level <= ERROR_DYNAMIC_LEVEL) { \
            fsl_os_print("! %s %s error " PRINT_FORMAT ": %s; ", \
                     dbg_level_strings[REPORT_LEVEL_##_level - 1], \
                     module_strings[__ERR_MODULE__ >> 16], \
                     PRINT_FMT_PARAMS, \
                     err_type_strings((enum error_type)GET_ERROR_TYPE(_err))); \
            fsl_os_print _vmsg; \
            fsl_os_print("\r\n"); \
        } \
    } while (0)

#define RETURN_ERROR(_level, _err, _vmsg) \
    do { \
        REPORT_ERROR(_level, (_err), _vmsg); \
        return ERROR_CODE(_err); \
    } while (0)
#endif /* (DEBUG_ERRORS > 0) */


/**************************************************************************//**
 @Function      ASSERT_COND

 @Description   Assertion macro.

 @Param[in]     _cond - The condition being checked, in positive form;
                        Failure of the condition triggers the assert.
*//***************************************************************************/
#ifdef DISABLE_ASSERTIONS
#define ASSERT_COND(_cond)
#else
#define ASSERT_COND(_cond) \
    do { \
        if (!(_cond)) { \
            fsl_os_print("*** ASSERT_COND failed " PRINT_FORMAT "\r\n", \
                    PRINT_FMT_PARAMS); \
            abort(); \
        } \
    } while (0)
#endif /* DISABLE_ASSERTIONS */

#if 0
#ifdef DISABLE_INIT_PARAMETERS_CHECK

#define CHECK_INIT_PARAMETERS(handle, cfg, params, f_check)
#define CHECK_INIT_PARAMETERS_RETURN_VALUE(handle, cfg, params, f_check, retval)

#else
#define CHECK_INIT_PARAMETERS(handle, cfg, params, f_check) \
    do { \
        int err = f_check(handle, cfg, params); \
        if (err != E_OK) { \
            RETURN_ERROR(MAJOR, err, NO_MSG); \
        } \
    } while (0)

#define CHECK_INIT_PARAMETERS_RETURN_VALUE(handle, cfg, params, f_check, retval) \
    do { \
        int err = f_check(handle, cfg, params); \
        if (err != E_OK) { \
            REPORT_ERROR(MAJOR, err, NO_MSG); \
            return (retval); \
        } \
    } while (0)

#endif /* DISABLE_INIT_PARAMETERS_CHECK */
#endif /* 0 */

#ifdef DISABLE_SANITY_CHECKS
#define SANITY_CHECK_RETURN_ERROR(_cond, _err)
#define SANITY_CHECK_RETURN_VALUE(_cond, _err, retval)
#define SANITY_CHECK_RETURN(_cond, _err)
#define SANITY_CHECK_EXIT(_cond, _err)

#else /* DISABLE_SANITY_CHECKS */
#define SANITY_CHECK_RETURN_ERROR(_cond, _err) \
    do { \
        if (!(_cond)) { \
            RETURN_ERROR(CRITICAL, (_err), NO_MSG); \
        } \
    } while (0)

#define SANITY_CHECK_RETURN_VALUE(_cond, _err, retval) \
    do { \
        if (!(_cond)) { \
            REPORT_ERROR(CRITICAL, (_err), NO_MSG); \
            return (retval); \
        } \
    } while (0)

#define SANITY_CHECK_RETURN(_cond, _err) \
    do { \
        if (!(_cond)) { \
            REPORT_ERROR(CRITICAL, (_err), NO_MSG); \
            return; \
        } \
    } while (0)
#endif /* DISABLE_SANITY_CHECKS */

/** @} */ /* end of gen_err_g group */
/** @} */ /* end of gen_g group */


#endif /* __FSL_ERRORS_H */
