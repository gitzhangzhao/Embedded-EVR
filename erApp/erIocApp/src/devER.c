/**
 * File              : devER.c
 * Author            : zhangzhao <zhangzhao@ihep.ac.cn>
 * Date              : 06.12.2022
 * Last Modified Date: 15.12.2022
 * Last Modified By  : zhangzhao <zhangzhao@ihep.ac.cn>
 * Description       : event receiver device support
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
/* Standard C library */
#include <stdio.h>

/* EPICS Standard library */
#include <epicsInterrupt.h>
#include <epicsStdio.h>
#include <epicsStdlib.h>
#include <epicsThread.h>
#include <epicsTypes.h>
/* EPICS device support */
#include <devLib.h>
#include <devSup.h>
#include <recSup.h>
/* EPICS driver support */
#include <drvSup.h>
/* EPICS Symbol exporting macro definitions */
#include <epicsExport.h>
/* EPICS Record Support global routine definitions */
#include <recGbl.h>

/* header files for event receiver */
#include "drvER.h"
#include "devER.h"
#include "erRecord.h"
#include "ereventRecord.h"

/**********************************************************************
 *                         Macro Definitions                          *
 **********************************************************************/
/* event code output map masks */
#define EVENT_MAP0 0x0001      /* output 0 */
#define EVENT_MAP1 0x0002      /* output 1 */
#define EVENT_MAP2 0x0004      /* output 2 */
#define EVENT_MAP3 0x0008      /* output 3 */
#define EVENT_MAP4 0x0010      /* output 4 */
#define EVENT_MAP5 0x0020      /* output 5 */
#define EVENT_MAP6 0x0040      /* output 6 */
#define EVENT_MAP7 0x0080      /* output 7 */
#define EVENT_MAP8 0x0100      /* output 8 */
#define EVENT_MAP9 0x0200      /* output 9 */
#define EVENT_MAP10 0x0400     /* output 10 */
#define EVENT_MAP11 0x0800     /* output 11 */
#define EVENT_MAP12 0x1000     /* output 12 */
#define EVENT_MAP13 0x2000     /* output 13 */
#define EVENT_LATCH 0x4000     /* output 14 */
#define EVENT_INTERRUPT 0x8000 /* output 15 */

/**********************************************************************
 *                       Prototype Declarations                       *
 **********************************************************************/
/* device support functions for ER */
epicsStatus init_record(erRecord *);
epicsStatus process(erRecord *);

/* device support functions for ER event */
epicsStatus init_event_record(ereventRecord *);
epicsStatus event_process(ereventRecord *);

/**********************************************************************
 *                 Device Support Entry Table (DSET)                  *
 **********************************************************************/
/* ER record */
static dset_struct ER_dset = {5,
                              /* -- No device report routine */
                              (DEVSUPFUN)NULL,
                              /* -- No device initialization route */
                              (DEVSUPFUN)NULL,
                              /* Record initialization routine */
                              (DEVSUPFUN)init_record,
                              /* -- No I/O Interrupt information routine */
                              (DEVSUPFUN)NULL,
                              /* Record processing routine */
                              (DEVSUPFUN)process};

epicsExportAddress(dset, ER_dset);

/* ER event record */
static dset_struct ER_event_dset = {5,
                                    /* -- No device report routine */
                                    (DEVSUPFUN)NULL,
                                    /* -- No device initialization route */
                                    (DEVSUPFUN)NULL,
                                    /* Record initialization routine */
                                    (DEVSUPFUN)init_event_record,
                                    /* -- No I/O Interrupt information routine */
                                    (DEVSUPFUN)NULL,
                                    /* Record processing routine */
                                    (DEVSUPFUN)event_process};

epicsExportAddress(dset, ER_event_dset);

/**********************************************************************
 *                        Function Definitions                        *
 **********************************************************************/

/*-----------------------------------------------------------------------------
 * init_record: init ER record. This routine is called from the EPICS iocInit()
 *-----------------------------------------------------------------------------
 * input:
 *   pRec: pointer to ER record structure
 */
epicsStatus init_record(erRecord *pRec)
{
        ER_struct *ER = get_ER();

        /* check if the record has been occupied */
        if (ER->pRec != NULL) {
                pRec->pact = epicsTrue;
                pRec->dpvt = NULL;
                recGblRecordError(S_dev_badCard, (void *)pRec, "init_record(): ER record is occupied");
                return S_dev_badCard;
        }

        /* register record structure */
        ER->pRec = (epicsUInt32*)pRec;

        /* initialize the IOSCANPVT structure */
        for (int i = 0; i < EVENT_NUM; i++)
                scanIoInit(&ER->ioscan_pvt[i]);

        pRec->dpvt = (void *)ER;

        /* if the PINI field is not set to YES, call the process routine */
        if (menuYesNoNO == pRec->pini)
                process(pRec);

        // printf("devER: init_record. pRec->dpvt:%x\n", pRec->dpvt);
        return 0;
}

/*------------------------------------------------
 * process: process routine for the ER record type
 *------------------------------------------------
 * input:
 *   pRec: pointer to ER record structure
 */
epicsStatus process(erRecord *pRec)
{
        ER_struct *ER = pRec->dpvt;
        if (NULL == ER) {
                recGblRecordError(S_dev_badCard, (void *)pRec, "process: ER record not initialized");
                pRec->pact = epicsTrue;
                return S_dev_badCard;
        }

        /* set 14 programmable width and delay pulse outputs */
        set_pulse(ER, 0, pRec->out0, pRec->ot0d, pRec->ot0w, pRec->ot0p);
        set_pulse(ER, 1, pRec->out1, pRec->ot1d, pRec->ot1w, pRec->ot1p);
        set_pulse(ER, 2, pRec->out2, pRec->ot2d, pRec->ot2w, pRec->ot2p);
        set_pulse(ER, 3, pRec->out3, pRec->ot3d, pRec->ot3w, pRec->ot3p);
        set_pulse(ER, 4, pRec->out4, pRec->ot4d, pRec->ot4w, pRec->ot4p);
        set_pulse(ER, 5, pRec->out5, pRec->ot5d, pRec->ot5w, pRec->ot5p);
        set_pulse(ER, 6, pRec->out6, pRec->ot6d, pRec->ot6w, pRec->ot6p);
        set_pulse(ER, 7, pRec->out7, pRec->ot7d, pRec->ot7w, pRec->ot7p);
        set_pulse(ER, 8, pRec->out8, pRec->ot8d, pRec->ot8w, pRec->ot8p);
        set_pulse(ER, 9, pRec->out9, pRec->ot9d, pRec->ot9w, pRec->ot9p);
        set_pulse(ER, 10, pRec->outa, pRec->otad, pRec->otaw, pRec->otap);
        set_pulse(ER, 11, pRec->outb, pRec->otbd, pRec->otbw, pRec->otbp);
        set_pulse(ER, 12, pRec->outc, pRec->otcd, pRec->otcw, pRec->otcp);
        set_pulse(ER, 13, pRec->outd, pRec->otdd, pRec->otdw, pRec->otdp);

        /* set 6 output map */
        set_fps(ER, 0, pRec->fps0);
        set_fps(ER, 1, pRec->fps1);
        set_fps(ER, 2, pRec->fps2);
        set_fps(ER, 3, pRec->fps3);
        set_fps(ER, 4, pRec->fps4);
        set_fps(ER, 5, pRec->fps5);

        // printf("devER: process. pRec->dpvt:%x\n", pRec->dpvt);

        pRec->udf = 0;
        return 0;
}

/*----------------------------------------------------------
 * init_event_record: ER event record Initialization Routine
 *----------------------------------------------------------
 * input:
 *   pRec: pointer to ER event record structure
 */
epicsStatus init_event_record(struct ereventRecord *pRec)
{
        ER_struct *ER = get_ER();

        /* initialize the ER event record structure */
        pRec->dpvt = (void *)ER;

        /* if the PINI field is not set to YES, call the event process routine */
        if (menuYesNoNO == pRec->pini)
                event_process(pRec);
        /* force setting on first process */
        pRec->lenm = -1;

        /* clear the 'last' event Mask */
        pRec->lout = 0;

        return 0;
}

/*--------------------------------------------------
 * event_process: ER event record processing routine
 * input:
 *   pRec: pointer to ER event record structure
 *--------------------------------------------------
 */
epicsStatus event_process(struct ereventRecord *pRec)
{
        epicsUInt16 mask;
        int program_ram_flag = 0;
        ER_struct *ER = get_ER();

        /* calculate output mask for the event code */
        if (menu_event_enable == pRec->out0)
                mask |= EVENT_MAP0;
        if (menu_event_enable == pRec->out1)
                mask |= EVENT_MAP1;
        if (menu_event_enable == pRec->out2)
                mask |= EVENT_MAP2;
        if (menu_event_enable == pRec->out3)
                mask |= EVENT_MAP3;
        if (menu_event_enable == pRec->out4)
                mask |= EVENT_MAP4;
        if (menu_event_enable == pRec->out5)
                mask |= EVENT_MAP5;
        if (menu_event_enable == pRec->out6)
                mask |= EVENT_MAP6;
        if (menu_event_enable == pRec->out7)
                mask |= EVENT_MAP7;
        if (menu_event_enable == pRec->out8)
                mask |= EVENT_MAP8;
        if (menu_event_enable == pRec->out9)
                mask |= EVENT_MAP9;
        if (menu_event_enable == pRec->outa)
                mask |= EVENT_MAP10;
        if (menu_event_enable == pRec->outb)
                mask |= EVENT_MAP11;
        if (menu_event_enable == pRec->outc)
                mask |= EVENT_MAP12;
        if (menu_event_enable == pRec->outd)
                mask |= EVENT_MAP13;
        if (menu_event_enable == pRec->ltch)
                mask |= EVENT_LATCH;
        if (menu_event_enable == pRec->irqs)
                mask |= EVENT_INTERRUPT;

        /* check to see if the event code is valid */
        if ((pRec->enm < EVENT_NUM) && (pRec->enm > 0)) {
            /* check to see if the event code has changed */
                if (pRec->enm != pRec->lenm) {
                        ER->event_map[pRec->lenm] = 0;
                        pRec->lenm = pRec->enm;
                        program_ram_flag = 1;
                }
        } else {
                recGblRecordError(S_dev_badCard, (void *)pRec, "devMrfEr: event_process() invalid event number");
        }

        /* check to see if the output mask has changed */
        if (mask != pRec->lout) {
                ER->event_map[pRec->enm] = mask;
                pRec->lout = mask;
                program_ram_flag = 1;
        }

        /* update mapping RAM for ER */
        if (program_ram_flag)
                program_ram(ER);

        return 0;
}
