/**
 * File              : erRecord.c
 * Author            : zhangzhao <zhangzhao@ihep.ac.cn>
 * Date              : 15.12.2022
 * Last Modified Date: 15.12.2022
 * Last Modified By  : zhangzhao <zhangzhao@ihep.ac.cn>
 * Description       : record support for event receiver
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
 *                       Imported Header Files                        *
 **********************************************************************/
#include <alarm.h>
#include <dbAccess.h>
#include <dbDefs.h>
#include <dbEvent.h>
#include <dbFldTypes.h>
#include <devSup.h>
#include <epicsExport.h>
#include <epicsPrint.h>
#include <epicsStdio.h>
#include <epicsTypes.h>
#include <errMdef.h>
#include <recGbl.h>
#include <recSup.h>

/* for device support entry table */
#include <devER.h>

#define GEN_SIZE_OFFSET
#include "erRecord.h"
#undef GEN_SIZE_OFFSET

/**********************************************************************
 *        Prototype Declarations for Record Support Functions         *
 **********************************************************************/

// static void erMonitor(struct erRecord *);

/* Create RSET - Record Support Entry Table*/
#define report NULL
#define initialize NULL
static long erInitRec(struct erRecord *, int);
static long erProc(struct erRecord *);
static void erMonitor(struct erRecord *);
#define special NULL
#define get_value NULL
#define cvt_dbaddr NULL
#define get_array_info NULL
#define put_array_info NULL
#define get_units NULL
#define get_precision NULL
#define get_enum_str NULL
#define get_enum_strs NULL
#define put_enum_str NULL
/* static long get_graphic_double(DBADDR *, struct dbr_grDouble *); */
/* static long get_control_double(DBADDR *, struct dbr_ctrlDouble *); */
/* static long get_alarm_double(DBADDR *, struct dbr_alDouble *); */
#define get_graphic_double NULL
#define get_control_double NULL
#define get_alarm_double NULL


rset erRSET = {RSETNUMBER,
               report,
               initialize,
               erInitRec,
               erProc,
               special,
               get_value,
               cvt_dbaddr,
               get_array_info,
               put_array_info,
               get_units,
               get_precision,
               get_enum_str,
               get_enum_strs,
               put_enum_str,
               get_graphic_double,
               get_control_double,
               get_alarm_double};
epicsExportAddress(rset, erRSET);

/**********************************************************************
 *                         ER Record Routines                         *
 **********************************************************************/

/*---------------------------------------------
 * erInitRec: init ER record for record support
 *---------------------------------------------
 * input:
 *   pRec: pointer to ER record structure
 *   pass: process control
 */

static long erInitRec(struct erRecord *pRec, int pass)
{
        dset_struct *pDset = (dset_struct *)pRec->dset;

        if (pass == 1) {
                /* Make sure only a usable device support module */
                if (pDset == NULL) {
                        recGblRecordError(S_dev_noDSET, (void *)pRec, "er: erInitRec");
                        return (S_dev_noDSET);
                }
                if (pDset->number < 5) {
                        recGblRecordError(S_dev_missingSup, (void *)pRec, "er: erInitRec");
                        return (S_dev_missingSup);
                }
                /* call device support init routine */
                if (pDset->initRec != NULL)
                        return (*pDset->initRec)(pRec);
        }
        // printf("erRecord: erInitRec. pRec->dset:%x\n", pRec->dset);

        return 0;
}

/*---------------------------------------
 * erProc: process ER record
 *---------------------------------------
 * input:
 *   pRec: pointer to ER record structure
 */
static long erProc(struct erRecord *pRec)
{
        dset_struct *pDset = (dset_struct *)pRec->dset;
        long status;

        /* make sure the record is being processed */
        if ((pDset == NULL) || (pDset->proc == NULL)){
            pRec->pact = epicsTrue;
            recGblRecordError(S_dev_missingSup, (void *)pRec, "proc");
            return(S_dev_missingSup);
        }

        /* call device support process routine */
        if (pDset->proc != NULL) {
                status = (*pDset->proc)(pRec);
                if (status)
                        return status;
        }

        pRec->pact = epicsTrue;
        pRec->udf = epicsFalse;
        /* deal with local time(&pRec->time) */
        recGblGetTimeStamp(pRec);
        erMonitor(pRec);

        /* Deal with monitor stuff */
        /* erMonitor(pRec); */

        /* process the forward scan link record */
        recGblFwdLink(pRec);

        pRec->pact = epicsFalse;
        // printf("erRecord: erProc. pRec->dset:%x\n", pRec->dset);

        return 0;
}

/*---------------------------------------
 * erMonitor: monitor ER record
 *---------------------------------------
 * input:
 *   pRec: pointer to ER record structure
 */
static void erMonitor(struct erRecord *pRec)
{
    unsigned short  monitor_mask;

    monitor_mask = recGblResetAlarms(pRec);
    monitor_mask |= (DBE_VALUE | DBE_LOG);
    db_post_events(pRec,&pRec->val,monitor_mask);
    return;
}




