/**
 * File              : drvER.h
 * Author            : zhangzhao <zhangzhao@ihep.ac.cn>
 * Date              : 15.11.2022
 * Last Modified Date: 15.12.2022
 * Last Modified By  : zhangzhao <zhangzhao@ihep.ac.cn>
 * Description       : header File              : drvER.h
 *
 * Copyright (c) 2022 zhangzhao <zhangzhao@ihep.ac.cn>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**********************************************************************
 *              Other Header Files Required by This File              *
 **********************************************************************/
#include <stdbool.h>
/* EPICS Architecture-independent type definitions*/
#include <epicsTypes.h>
/* EPICS Timestamp support library*/
#include <epicsTime.h>
/* EPICS Database scan routines and definitions*/
#include <dbScan.h>
/* EPICS thread library */
#include <epicsThread.h>
/* Choice menu for "Yes/No" fields*/
/* #include <menuYesNo.h> */
/* MRF Event link status values*/
/* #include <menuLinkStatus.h> */

/**********************************************************************
 *                         Macro Definitions                          *
 **********************************************************************/
#define EVENT_NUM 256

/**********************************************************************
 *                          Device Prototype                          *
 **********************************************************************/
/* ER structure prototype */
typedef struct ER_struct {
        /* Pointer to the event receiver record */
        epicsUInt32 *pRec;
        /* Pointer to the event receiver register map */
        epicsUInt32 *pEr;
        /* ER device fd */
        int fd;
        /* irq thread id */
        epicsThreadId tid;
        /* Pointer to user function */
        void* event_func;
        /* Mapping RAM enable */
        bool ram_ena;
        /* Event timestamps */
        epicsTimeStamp event_ts[EVENT_NUM];
        /* Current view of mapping RAM */
        epicsUInt16 event_map[EVENT_NUM];
        /* Record processing struct */
        IOSCANPVT ioscan_pvt[EVENT_NUM];
} ER_struct;


/**********************************************************************
 *         Function Prototypes For Driver Support Routines            *
 **********************************************************************/
ER_struct* get_ER();
void set_pulse(ER_struct *, epicsUInt32, bool, epicsUInt32, epicsUInt32, bool);
void program_ram(ER_struct *);
void set_fps(ER_struct *, int, epicsUInt16);


