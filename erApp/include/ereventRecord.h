/** @file ereventRecord.h
 * @brief Declarations for the @ref ereventRecord "erevent" record type.
 *
 * This header was generated from ereventRecord.dbd
 */

#ifndef INC_ereventRecord_H
#define INC_ereventRecord_H

#include "epicsTypes.h"
#include "link.h"
#include "epicsMutex.h"
#include "ellLib.h"
#include "devSup.h"
#include "epicsTime.h"

#ifndef menuScan_NUM_CHOICES
/** @brief Enumerated type from menu menuScan */
typedef enum {
    menuScanPassive                 /**< @brief State string "Passive" */,
    menuScanEvent                   /**< @brief State string "Event" */,
    menuScanI_O_Intr                /**< @brief State string "I/O Intr" */,
    menuScan10_second               /**< @brief State string "10 second" */,
    menuScan5_second                /**< @brief State string "5 second" */,
    menuScan2_second                /**< @brief State string "2 second" */,
    menuScan1_second                /**< @brief State string "1 second" */,
    menuScan_5_second               /**< @brief State string ".5 second" */,
    menuScan_2_second               /**< @brief State string ".2 second" */,
    menuScan_1_second               /**< @brief State string ".1 second" */
} menuScan;
/** @brief Number of states defined for menu menuScan */
#define menuScan_NUM_CHOICES 10
#endif

#ifndef menuYesNo_NUM_CHOICES
/** @brief Enumerated type from menu menuYesNo */
typedef enum {
    menuYesNoNO                     /**< @brief State string "NO" */,
    menuYesNoYES                    /**< @brief State string "YES" */
} menuYesNo;
/** @brief Number of states defined for menu menuYesNo */
#define menuYesNo_NUM_CHOICES 2
#endif

#ifndef menuPini_NUM_CHOICES
/** @brief Enumerated type from menu menuPini */
typedef enum {
    menuPiniNO                      /**< @brief State string "NO" */,
    menuPiniYES                     /**< @brief State string "YES" */,
    menuPiniRUN                     /**< @brief State string "RUN" */,
    menuPiniRUNNING                 /**< @brief State string "RUNNING" */,
    menuPiniPAUSE                   /**< @brief State string "PAUSE" */,
    menuPiniPAUSED                  /**< @brief State string "PAUSED" */
} menuPini;
/** @brief Number of states defined for menu menuPini */
#define menuPini_NUM_CHOICES 6
#endif

#ifndef menuEventEnable_NUM_CHOICES
/** @brief Enumerated type from menu menuEventEnable */
typedef enum {
    menu_event_disable              /**< @brief State string "Disabled" */,
    menu_event_enable               /**< @brief State string "Enabled" */
} menuEventEnable;
/** @brief Number of states defined for menu menuEventEnable */
#define menuEventEnable_NUM_CHOICES 2
#endif

/** @brief Declaration of erevent record type. */
typedef struct ereventRecord {
    char                name[61];   /**< @brief Record Name */
    char                desc[41];   /**< @brief Descriptor */
    char                asg[29];    /**< @brief Access Security Group */
    epicsEnum16         scan;       /**< @brief Scan Mechanism */
    epicsEnum16         pini;       /**< @brief Process at iocInit */
    epicsInt16          phas;       /**< @brief Scan Phase */
    char                evnt[40];   /**< @brief Event Name */
    epicsInt16          tse;        /**< @brief Time Stamp Event */
    DBLINK              tsel;       /**< @brief Time Stamp Link */
    epicsEnum16         dtyp;       /**< @brief Device Type */
    epicsInt16          disv;       /**< @brief Disable Value */
    epicsInt16          disa;       /**< @brief Disable */
    DBLINK              sdis;       /**< @brief Scanning Disable */
    epicsMutexId        mlok;       /**< @brief Monitor lock */
    ELLLIST             mlis;       /**< @brief Monitor List */
    ELLLIST             bklnk;      /**< @brief Backwards link tracking */
    epicsUInt8          disp;       /**< @brief Disable putField */
    epicsUInt8          proc;       /**< @brief Force Processing */
    epicsEnum16         stat;       /**< @brief Alarm Status */
    epicsEnum16         sevr;       /**< @brief Alarm Severity */
    char                amsg[40];   /**< @brief Alarm Message */
    epicsEnum16         nsta;       /**< @brief New Alarm Status */
    epicsEnum16         nsev;       /**< @brief New Alarm Severity */
    char                namsg[40];  /**< @brief New Alarm Message */
    epicsEnum16         acks;       /**< @brief Alarm Ack Severity */
    epicsEnum16         ackt;       /**< @brief Alarm Ack Transient */
    epicsEnum16         diss;       /**< @brief Disable Alarm Sevrty */
    epicsUInt8          lcnt;       /**< @brief Lock Count */
    epicsUInt8          pact;       /**< @brief Record active */
    epicsUInt8          putf;       /**< @brief dbPutField process */
    epicsUInt8          rpro;       /**< @brief Reprocess  */
    struct asgMember    *asp;       /**< @brief Access Security Pvt */
    struct processNotify *ppn;      /**< @brief pprocessNotify */
    struct processNotifyRecord *ppnr; /**< @brief pprocessNotifyRecord */
    struct scan_element *spvt;      /**< @brief Scan Private */
    struct typed_rset   *rset;      /**< @brief Address of RSET */
    unambiguous_dset    *dset;      /**< @brief DSET address */
    void                *dpvt;      /**< @brief Device Private */
    struct dbRecordType *rdes;      /**< @brief Address of dbRecordType */
    struct lockRecord   *lset;      /**< @brief Lock Set */
    epicsEnum16         prio;       /**< @brief Scheduling Priority */
    epicsUInt8          tpro;       /**< @brief Trace Processing */
    epicsUInt8          bkpt;       /**< @brief Break Point */
    epicsUInt8          udf;        /**< @brief Undefined */
    epicsEnum16         udfs;       /**< @brief Undefined Alarm Sevrty */
    epicsTimeStamp      time;       /**< @brief Time */
    epicsUInt64         utag;       /**< @brief Time Tag */
    DBLINK              flnk;       /**< @brief Forward Process Link */
    epicsFloat64        val;        /**< @brief Current value */
    epicsInt32          enm;        /**< @brief Event Number */
    epicsInt32          lenm;       /**< @brief Last Event Number */
    epicsInt32          lout;       /**< @brief Last Out Enable Mask */
    epicsEnum16         out0;       /**< @brief Out 0 Enable */
    epicsEnum16         out1;       /**< @brief Out 1 Enable */
    epicsEnum16         out2;       /**< @brief Out 2 Enable */
    epicsEnum16         out3;       /**< @brief Out 3 Enable */
    epicsEnum16         out4;       /**< @brief Out 4 Enable */
    epicsEnum16         out5;       /**< @brief Out 5 Enable */
    epicsEnum16         out6;       /**< @brief Out 6 Enable */
    epicsEnum16         out7;       /**< @brief Out 7 Enable */
    epicsEnum16         out8;       /**< @brief Out 8 Enable */
    epicsEnum16         out9;       /**< @brief Out 9 Enable */
    epicsEnum16         outa;       /**< @brief Out 10 Enable */
    epicsEnum16         outb;       /**< @brief Out 11 Enable */
    epicsEnum16         outc;       /**< @brief Out 12 Enable */
    epicsEnum16         outd;       /**< @brief Out 13 Enable */
    epicsEnum16         ltch;       /**< @brief Time Stamp Latch Enable */
    epicsEnum16         irqs;       /**< @brief Interrupt trigger */
} ereventRecord;

typedef enum {
	ereventRecordNAME = 0,
	ereventRecordDESC = 1,
	ereventRecordASG = 2,
	ereventRecordSCAN = 3,
	ereventRecordPINI = 4,
	ereventRecordPHAS = 5,
	ereventRecordEVNT = 6,
	ereventRecordTSE = 7,
	ereventRecordTSEL = 8,
	ereventRecordDTYP = 9,
	ereventRecordDISV = 10,
	ereventRecordDISA = 11,
	ereventRecordSDIS = 12,
	ereventRecordMLOK = 13,
	ereventRecordMLIS = 14,
	ereventRecordBKLNK = 15,
	ereventRecordDISP = 16,
	ereventRecordPROC = 17,
	ereventRecordSTAT = 18,
	ereventRecordSEVR = 19,
	ereventRecordAMSG = 20,
	ereventRecordNSTA = 21,
	ereventRecordNSEV = 22,
	ereventRecordNAMSG = 23,
	ereventRecordACKS = 24,
	ereventRecordACKT = 25,
	ereventRecordDISS = 26,
	ereventRecordLCNT = 27,
	ereventRecordPACT = 28,
	ereventRecordPUTF = 29,
	ereventRecordRPRO = 30,
	ereventRecordASP = 31,
	ereventRecordPPN = 32,
	ereventRecordPPNR = 33,
	ereventRecordSPVT = 34,
	ereventRecordRSET = 35,
	ereventRecordDSET = 36,
	ereventRecordDPVT = 37,
	ereventRecordRDES = 38,
	ereventRecordLSET = 39,
	ereventRecordPRIO = 40,
	ereventRecordTPRO = 41,
	ereventRecordBKPT = 42,
	ereventRecordUDF = 43,
	ereventRecordUDFS = 44,
	ereventRecordTIME = 45,
	ereventRecordUTAG = 46,
	ereventRecordFLNK = 47,
	ereventRecordVAL = 48,
	ereventRecordENM = 49,
	ereventRecordLENM = 50,
	ereventRecordLOUT = 51,
	ereventRecordOUT0 = 52,
	ereventRecordOUT1 = 53,
	ereventRecordOUT2 = 54,
	ereventRecordOUT3 = 55,
	ereventRecordOUT4 = 56,
	ereventRecordOUT5 = 57,
	ereventRecordOUT6 = 58,
	ereventRecordOUT7 = 59,
	ereventRecordOUT8 = 60,
	ereventRecordOUT9 = 61,
	ereventRecordOUTA = 62,
	ereventRecordOUTB = 63,
	ereventRecordOUTC = 64,
	ereventRecordOUTD = 65,
	ereventRecordLTCH = 66,
	ereventRecordIRQS = 67
} ereventFieldIndex;

#ifdef GEN_SIZE_OFFSET

#include <epicsExport.h>
#include <cantProceed.h>
#ifdef __cplusplus
extern "C" {
#endif
static int ereventRecordSizeOffset(dbRecordType *prt)
{
    ereventRecord *prec = 0;

    if (prt->no_fields != 68) {
        cantProceed("IOC build or installation error:\n"
            "    The ereventRecord defined in the DBD file has %d fields,\n"
            "    but the record support code was built with 68.\n",
            prt->no_fields);
    }
    prt->papFldDes[ereventRecordNAME]->size = sizeof(prec->name);
    prt->papFldDes[ereventRecordNAME]->offset = (unsigned short)((char *)&prec->name - (char *)prec);
    prt->papFldDes[ereventRecordDESC]->size = sizeof(prec->desc);
    prt->papFldDes[ereventRecordDESC]->offset = (unsigned short)((char *)&prec->desc - (char *)prec);
    prt->papFldDes[ereventRecordASG]->size = sizeof(prec->asg);
    prt->papFldDes[ereventRecordASG]->offset = (unsigned short)((char *)&prec->asg - (char *)prec);
    prt->papFldDes[ereventRecordSCAN]->size = sizeof(prec->scan);
    prt->papFldDes[ereventRecordSCAN]->offset = (unsigned short)((char *)&prec->scan - (char *)prec);
    prt->papFldDes[ereventRecordPINI]->size = sizeof(prec->pini);
    prt->papFldDes[ereventRecordPINI]->offset = (unsigned short)((char *)&prec->pini - (char *)prec);
    prt->papFldDes[ereventRecordPHAS]->size = sizeof(prec->phas);
    prt->papFldDes[ereventRecordPHAS]->offset = (unsigned short)((char *)&prec->phas - (char *)prec);
    prt->papFldDes[ereventRecordEVNT]->size = sizeof(prec->evnt);
    prt->papFldDes[ereventRecordEVNT]->offset = (unsigned short)((char *)&prec->evnt - (char *)prec);
    prt->papFldDes[ereventRecordTSE]->size = sizeof(prec->tse);
    prt->papFldDes[ereventRecordTSE]->offset = (unsigned short)((char *)&prec->tse - (char *)prec);
    prt->papFldDes[ereventRecordTSEL]->size = sizeof(prec->tsel);
    prt->papFldDes[ereventRecordTSEL]->offset = (unsigned short)((char *)&prec->tsel - (char *)prec);
    prt->papFldDes[ereventRecordDTYP]->size = sizeof(prec->dtyp);
    prt->papFldDes[ereventRecordDTYP]->offset = (unsigned short)((char *)&prec->dtyp - (char *)prec);
    prt->papFldDes[ereventRecordDISV]->size = sizeof(prec->disv);
    prt->papFldDes[ereventRecordDISV]->offset = (unsigned short)((char *)&prec->disv - (char *)prec);
    prt->papFldDes[ereventRecordDISA]->size = sizeof(prec->disa);
    prt->papFldDes[ereventRecordDISA]->offset = (unsigned short)((char *)&prec->disa - (char *)prec);
    prt->papFldDes[ereventRecordSDIS]->size = sizeof(prec->sdis);
    prt->papFldDes[ereventRecordSDIS]->offset = (unsigned short)((char *)&prec->sdis - (char *)prec);
    prt->papFldDes[ereventRecordMLOK]->size = sizeof(prec->mlok);
    prt->papFldDes[ereventRecordMLOK]->offset = (unsigned short)((char *)&prec->mlok - (char *)prec);
    prt->papFldDes[ereventRecordMLIS]->size = sizeof(prec->mlis);
    prt->papFldDes[ereventRecordMLIS]->offset = (unsigned short)((char *)&prec->mlis - (char *)prec);
    prt->papFldDes[ereventRecordBKLNK]->size = sizeof(prec->bklnk);
    prt->papFldDes[ereventRecordBKLNK]->offset = (unsigned short)((char *)&prec->bklnk - (char *)prec);
    prt->papFldDes[ereventRecordDISP]->size = sizeof(prec->disp);
    prt->papFldDes[ereventRecordDISP]->offset = (unsigned short)((char *)&prec->disp - (char *)prec);
    prt->papFldDes[ereventRecordPROC]->size = sizeof(prec->proc);
    prt->papFldDes[ereventRecordPROC]->offset = (unsigned short)((char *)&prec->proc - (char *)prec);
    prt->papFldDes[ereventRecordSTAT]->size = sizeof(prec->stat);
    prt->papFldDes[ereventRecordSTAT]->offset = (unsigned short)((char *)&prec->stat - (char *)prec);
    prt->papFldDes[ereventRecordSEVR]->size = sizeof(prec->sevr);
    prt->papFldDes[ereventRecordSEVR]->offset = (unsigned short)((char *)&prec->sevr - (char *)prec);
    prt->papFldDes[ereventRecordAMSG]->size = sizeof(prec->amsg);
    prt->papFldDes[ereventRecordAMSG]->offset = (unsigned short)((char *)&prec->amsg - (char *)prec);
    prt->papFldDes[ereventRecordNSTA]->size = sizeof(prec->nsta);
    prt->papFldDes[ereventRecordNSTA]->offset = (unsigned short)((char *)&prec->nsta - (char *)prec);
    prt->papFldDes[ereventRecordNSEV]->size = sizeof(prec->nsev);
    prt->papFldDes[ereventRecordNSEV]->offset = (unsigned short)((char *)&prec->nsev - (char *)prec);
    prt->papFldDes[ereventRecordNAMSG]->size = sizeof(prec->namsg);
    prt->papFldDes[ereventRecordNAMSG]->offset = (unsigned short)((char *)&prec->namsg - (char *)prec);
    prt->papFldDes[ereventRecordACKS]->size = sizeof(prec->acks);
    prt->papFldDes[ereventRecordACKS]->offset = (unsigned short)((char *)&prec->acks - (char *)prec);
    prt->papFldDes[ereventRecordACKT]->size = sizeof(prec->ackt);
    prt->papFldDes[ereventRecordACKT]->offset = (unsigned short)((char *)&prec->ackt - (char *)prec);
    prt->papFldDes[ereventRecordDISS]->size = sizeof(prec->diss);
    prt->papFldDes[ereventRecordDISS]->offset = (unsigned short)((char *)&prec->diss - (char *)prec);
    prt->papFldDes[ereventRecordLCNT]->size = sizeof(prec->lcnt);
    prt->papFldDes[ereventRecordLCNT]->offset = (unsigned short)((char *)&prec->lcnt - (char *)prec);
    prt->papFldDes[ereventRecordPACT]->size = sizeof(prec->pact);
    prt->papFldDes[ereventRecordPACT]->offset = (unsigned short)((char *)&prec->pact - (char *)prec);
    prt->papFldDes[ereventRecordPUTF]->size = sizeof(prec->putf);
    prt->papFldDes[ereventRecordPUTF]->offset = (unsigned short)((char *)&prec->putf - (char *)prec);
    prt->papFldDes[ereventRecordRPRO]->size = sizeof(prec->rpro);
    prt->papFldDes[ereventRecordRPRO]->offset = (unsigned short)((char *)&prec->rpro - (char *)prec);
    prt->papFldDes[ereventRecordASP]->size = sizeof(prec->asp);
    prt->papFldDes[ereventRecordASP]->offset = (unsigned short)((char *)&prec->asp - (char *)prec);
    prt->papFldDes[ereventRecordPPN]->size = sizeof(prec->ppn);
    prt->papFldDes[ereventRecordPPN]->offset = (unsigned short)((char *)&prec->ppn - (char *)prec);
    prt->papFldDes[ereventRecordPPNR]->size = sizeof(prec->ppnr);
    prt->papFldDes[ereventRecordPPNR]->offset = (unsigned short)((char *)&prec->ppnr - (char *)prec);
    prt->papFldDes[ereventRecordSPVT]->size = sizeof(prec->spvt);
    prt->papFldDes[ereventRecordSPVT]->offset = (unsigned short)((char *)&prec->spvt - (char *)prec);
    prt->papFldDes[ereventRecordRSET]->size = sizeof(prec->rset);
    prt->papFldDes[ereventRecordRSET]->offset = (unsigned short)((char *)&prec->rset - (char *)prec);
    prt->papFldDes[ereventRecordDSET]->size = sizeof(prec->dset);
    prt->papFldDes[ereventRecordDSET]->offset = (unsigned short)((char *)&prec->dset - (char *)prec);
    prt->papFldDes[ereventRecordDPVT]->size = sizeof(prec->dpvt);
    prt->papFldDes[ereventRecordDPVT]->offset = (unsigned short)((char *)&prec->dpvt - (char *)prec);
    prt->papFldDes[ereventRecordRDES]->size = sizeof(prec->rdes);
    prt->papFldDes[ereventRecordRDES]->offset = (unsigned short)((char *)&prec->rdes - (char *)prec);
    prt->papFldDes[ereventRecordLSET]->size = sizeof(prec->lset);
    prt->papFldDes[ereventRecordLSET]->offset = (unsigned short)((char *)&prec->lset - (char *)prec);
    prt->papFldDes[ereventRecordPRIO]->size = sizeof(prec->prio);
    prt->papFldDes[ereventRecordPRIO]->offset = (unsigned short)((char *)&prec->prio - (char *)prec);
    prt->papFldDes[ereventRecordTPRO]->size = sizeof(prec->tpro);
    prt->papFldDes[ereventRecordTPRO]->offset = (unsigned short)((char *)&prec->tpro - (char *)prec);
    prt->papFldDes[ereventRecordBKPT]->size = sizeof(prec->bkpt);
    prt->papFldDes[ereventRecordBKPT]->offset = (unsigned short)((char *)&prec->bkpt - (char *)prec);
    prt->papFldDes[ereventRecordUDF]->size = sizeof(prec->udf);
    prt->papFldDes[ereventRecordUDF]->offset = (unsigned short)((char *)&prec->udf - (char *)prec);
    prt->papFldDes[ereventRecordUDFS]->size = sizeof(prec->udfs);
    prt->papFldDes[ereventRecordUDFS]->offset = (unsigned short)((char *)&prec->udfs - (char *)prec);
    prt->papFldDes[ereventRecordTIME]->size = sizeof(prec->time);
    prt->papFldDes[ereventRecordTIME]->offset = (unsigned short)((char *)&prec->time - (char *)prec);
    prt->papFldDes[ereventRecordUTAG]->size = sizeof(prec->utag);
    prt->papFldDes[ereventRecordUTAG]->offset = (unsigned short)((char *)&prec->utag - (char *)prec);
    prt->papFldDes[ereventRecordFLNK]->size = sizeof(prec->flnk);
    prt->papFldDes[ereventRecordFLNK]->offset = (unsigned short)((char *)&prec->flnk - (char *)prec);
    prt->papFldDes[ereventRecordVAL]->size = sizeof(prec->val);
    prt->papFldDes[ereventRecordVAL]->offset = (unsigned short)((char *)&prec->val - (char *)prec);
    prt->papFldDes[ereventRecordENM]->size = sizeof(prec->enm);
    prt->papFldDes[ereventRecordENM]->offset = (unsigned short)((char *)&prec->enm - (char *)prec);
    prt->papFldDes[ereventRecordLENM]->size = sizeof(prec->lenm);
    prt->papFldDes[ereventRecordLENM]->offset = (unsigned short)((char *)&prec->lenm - (char *)prec);
    prt->papFldDes[ereventRecordLOUT]->size = sizeof(prec->lout);
    prt->papFldDes[ereventRecordLOUT]->offset = (unsigned short)((char *)&prec->lout - (char *)prec);
    prt->papFldDes[ereventRecordOUT0]->size = sizeof(prec->out0);
    prt->papFldDes[ereventRecordOUT0]->offset = (unsigned short)((char *)&prec->out0 - (char *)prec);
    prt->papFldDes[ereventRecordOUT1]->size = sizeof(prec->out1);
    prt->papFldDes[ereventRecordOUT1]->offset = (unsigned short)((char *)&prec->out1 - (char *)prec);
    prt->papFldDes[ereventRecordOUT2]->size = sizeof(prec->out2);
    prt->papFldDes[ereventRecordOUT2]->offset = (unsigned short)((char *)&prec->out2 - (char *)prec);
    prt->papFldDes[ereventRecordOUT3]->size = sizeof(prec->out3);
    prt->papFldDes[ereventRecordOUT3]->offset = (unsigned short)((char *)&prec->out3 - (char *)prec);
    prt->papFldDes[ereventRecordOUT4]->size = sizeof(prec->out4);
    prt->papFldDes[ereventRecordOUT4]->offset = (unsigned short)((char *)&prec->out4 - (char *)prec);
    prt->papFldDes[ereventRecordOUT5]->size = sizeof(prec->out5);
    prt->papFldDes[ereventRecordOUT5]->offset = (unsigned short)((char *)&prec->out5 - (char *)prec);
    prt->papFldDes[ereventRecordOUT6]->size = sizeof(prec->out6);
    prt->papFldDes[ereventRecordOUT6]->offset = (unsigned short)((char *)&prec->out6 - (char *)prec);
    prt->papFldDes[ereventRecordOUT7]->size = sizeof(prec->out7);
    prt->papFldDes[ereventRecordOUT7]->offset = (unsigned short)((char *)&prec->out7 - (char *)prec);
    prt->papFldDes[ereventRecordOUT8]->size = sizeof(prec->out8);
    prt->papFldDes[ereventRecordOUT8]->offset = (unsigned short)((char *)&prec->out8 - (char *)prec);
    prt->papFldDes[ereventRecordOUT9]->size = sizeof(prec->out9);
    prt->papFldDes[ereventRecordOUT9]->offset = (unsigned short)((char *)&prec->out9 - (char *)prec);
    prt->papFldDes[ereventRecordOUTA]->size = sizeof(prec->outa);
    prt->papFldDes[ereventRecordOUTA]->offset = (unsigned short)((char *)&prec->outa - (char *)prec);
    prt->papFldDes[ereventRecordOUTB]->size = sizeof(prec->outb);
    prt->papFldDes[ereventRecordOUTB]->offset = (unsigned short)((char *)&prec->outb - (char *)prec);
    prt->papFldDes[ereventRecordOUTC]->size = sizeof(prec->outc);
    prt->papFldDes[ereventRecordOUTC]->offset = (unsigned short)((char *)&prec->outc - (char *)prec);
    prt->papFldDes[ereventRecordOUTD]->size = sizeof(prec->outd);
    prt->papFldDes[ereventRecordOUTD]->offset = (unsigned short)((char *)&prec->outd - (char *)prec);
    prt->papFldDes[ereventRecordLTCH]->size = sizeof(prec->ltch);
    prt->papFldDes[ereventRecordLTCH]->offset = (unsigned short)((char *)&prec->ltch - (char *)prec);
    prt->papFldDes[ereventRecordIRQS]->size = sizeof(prec->irqs);
    prt->papFldDes[ereventRecordIRQS]->offset = (unsigned short)((char *)&prec->irqs - (char *)prec);
    prt->rec_size = sizeof(*prec);
    return 0;
}
epicsExportRegistrar(ereventRecordSizeOffset);

#ifdef __cplusplus
}
#endif
#endif /* GEN_SIZE_OFFSET */

#endif /* INC_ereventRecord_H */
