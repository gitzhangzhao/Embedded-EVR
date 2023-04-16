/** @file erRecord.h
 * @brief Declarations for the @ref erRecord "er" record type.
 *
 * This header was generated from erRecord.dbd
 */

#ifndef INC_erRecord_H
#define INC_erRecord_H

#include "epicsTypes.h"
#include "link.h"
#include "epicsMutex.h"
#include "ellLib.h"
#include "devSup.h"
#include "epicsTime.h"

#ifndef menuPolarity_NUM_CHOICES
/** @brief Enumerated type from menu menuPolarity */
typedef enum {
    menuPolarity_Normal             /**< @brief State string "Normal" */,
    menuPolarity_Inverted           /**< @brief State string "Inverted" */
} menuPolarity;
/** @brief Number of states defined for menu menuPolarity */
#define menuPolarity_NUM_CHOICES 2
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

#ifndef menuYesNo_NUM_CHOICES
/** @brief Enumerated type from menu menuYesNo */
typedef enum {
    menuYesNoNO                     /**< @brief State string "NO" */,
    menuYesNoYES                    /**< @brief State string "YES" */
} menuYesNo;
/** @brief Number of states defined for menu menuYesNo */
#define menuYesNo_NUM_CHOICES 2
#endif

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

/** @brief Declaration of er record type. */
typedef struct erRecord {
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
    epicsEnum16         out0;       /**< @brief OTB 0 Enable */
    epicsEnum16         out1;       /**< @brief OTB 1 Enable */
    epicsEnum16         out2;       /**< @brief OTB 2 Enable */
    epicsEnum16         out3;       /**< @brief OTB 3 Enable */
    epicsEnum16         out4;       /**< @brief OTB 4 Enable */
    epicsEnum16         out5;       /**< @brief OTB 5 Enable */
    epicsEnum16         out6;       /**< @brief OTB 6 Enable */
    epicsEnum16         out7;       /**< @brief OTB 7 Enable */
    epicsEnum16         out8;       /**< @brief OTB 7 Enable */
    epicsEnum16         out9;       /**< @brief OTB 7 Enable */
    epicsEnum16         outa;       /**< @brief OTB 7 Enable */
    epicsEnum16         outb;       /**< @brief OTB 7 Enable */
    epicsEnum16         outc;       /**< @brief OTB 7 Enable */
    epicsEnum16         outd;       /**< @brief OTB 7 Enable */
    epicsUInt16         ot0w;       /**< @brief OTP 0 Width */
    epicsUInt16         ot1w;       /**< @brief OTP 1 Width */
    epicsUInt16         ot2w;       /**< @brief OTP 2 Width */
    epicsUInt16         ot3w;       /**< @brief OTP 3 Width */
    epicsUInt16         ot4w;       /**< @brief OTP 4 Width */
    epicsUInt16         ot5w;       /**< @brief OTP 5 Width */
    epicsUInt16         ot6w;       /**< @brief OTP 6 Width */
    epicsUInt16         ot7w;       /**< @brief OTP 7 Width */
    epicsUInt16         ot8w;       /**< @brief OTP 8 Width */
    epicsUInt16         ot9w;       /**< @brief OTP 9 Width */
    epicsUInt16         otaw;       /**< @brief OTP 10 Width */
    epicsUInt16         otbw;       /**< @brief OTP 11 Width */
    epicsUInt16         otcw;       /**< @brief OTP 12 Width */
    epicsUInt16         otdw;       /**< @brief OTP 13 Width */
    epicsUInt32         ot0d;       /**< @brief OTP 0 Delay */
    epicsUInt32         ot1d;       /**< @brief OTP 1 Delay */
    epicsUInt32         ot2d;       /**< @brief OTP 2 Delay */
    epicsUInt32         ot3d;       /**< @brief OTP 3 Delay */
    epicsUInt32         ot4d;       /**< @brief OTP 4 Delay */
    epicsUInt32         ot5d;       /**< @brief OTP 5 Delay */
    epicsUInt32         ot6d;       /**< @brief OTP 6 Delay */
    epicsUInt32         ot7d;       /**< @brief OTP 7 Delay */
    epicsUInt32         ot8d;       /**< @brief OTP 8 Delay */
    epicsUInt32         ot9d;       /**< @brief OTP 9 Delay */
    epicsUInt32         otad;       /**< @brief OTP 10 Delay */
    epicsUInt32         otbd;       /**< @brief OTP 11 Delay */
    epicsUInt32         otcd;       /**< @brief OTP 12 Delay */
    epicsUInt32         otdd;       /**< @brief OTP 13 Delay */
    epicsEnum16         ot0p;       /**< @brief OTP 0 Polarity */
    epicsEnum16         ot1p;       /**< @brief OTP 1 Polarity */
    epicsEnum16         ot2p;       /**< @brief OTP 2 Polarity */
    epicsEnum16         ot3p;       /**< @brief OTP 3 Polarity */
    epicsEnum16         ot4p;       /**< @brief OTP 4 Polarity */
    epicsEnum16         ot5p;       /**< @brief OTP 5 Polarity */
    epicsEnum16         ot6p;       /**< @brief OTP 6 Polarity */
    epicsEnum16         ot7p;       /**< @brief OTP 7 Polarity */
    epicsEnum16         ot8p;       /**< @brief OTP 8 Polarity */
    epicsEnum16         ot9p;       /**< @brief OTP 9 Polarity */
    epicsEnum16         otap;       /**< @brief OTP 10 Polarity */
    epicsEnum16         otbp;       /**< @brief OTP 11 Polarity */
    epicsEnum16         otcp;       /**< @brief OTP 12 Polarity */
    epicsEnum16         otdp;       /**< @brief OTP 13 Polarity */
    epicsUInt16         fps0;       /**< @brief Front Panel output 0 select */
    epicsUInt16         fps1;       /**< @brief Front Panel output 1 select */
    epicsUInt16         fps2;       /**< @brief Front Panel output 2 select */
    epicsUInt16         fps3;       /**< @brief Front Panel output 3 select */
    epicsUInt16         fps4;       /**< @brief Front Panel output 4 select */
    epicsUInt16         fps5;       /**< @brief Front Panel output 5 select */
} erRecord;

typedef enum {
	erRecordNAME = 0,
	erRecordDESC = 1,
	erRecordASG = 2,
	erRecordSCAN = 3,
	erRecordPINI = 4,
	erRecordPHAS = 5,
	erRecordEVNT = 6,
	erRecordTSE = 7,
	erRecordTSEL = 8,
	erRecordDTYP = 9,
	erRecordDISV = 10,
	erRecordDISA = 11,
	erRecordSDIS = 12,
	erRecordMLOK = 13,
	erRecordMLIS = 14,
	erRecordBKLNK = 15,
	erRecordDISP = 16,
	erRecordPROC = 17,
	erRecordSTAT = 18,
	erRecordSEVR = 19,
	erRecordAMSG = 20,
	erRecordNSTA = 21,
	erRecordNSEV = 22,
	erRecordNAMSG = 23,
	erRecordACKS = 24,
	erRecordACKT = 25,
	erRecordDISS = 26,
	erRecordLCNT = 27,
	erRecordPACT = 28,
	erRecordPUTF = 29,
	erRecordRPRO = 30,
	erRecordASP = 31,
	erRecordPPN = 32,
	erRecordPPNR = 33,
	erRecordSPVT = 34,
	erRecordRSET = 35,
	erRecordDSET = 36,
	erRecordDPVT = 37,
	erRecordRDES = 38,
	erRecordLSET = 39,
	erRecordPRIO = 40,
	erRecordTPRO = 41,
	erRecordBKPT = 42,
	erRecordUDF = 43,
	erRecordUDFS = 44,
	erRecordTIME = 45,
	erRecordUTAG = 46,
	erRecordFLNK = 47,
	erRecordVAL = 48,
	erRecordOUT0 = 49,
	erRecordOUT1 = 50,
	erRecordOUT2 = 51,
	erRecordOUT3 = 52,
	erRecordOUT4 = 53,
	erRecordOUT5 = 54,
	erRecordOUT6 = 55,
	erRecordOUT7 = 56,
	erRecordOUT8 = 57,
	erRecordOUT9 = 58,
	erRecordOUTA = 59,
	erRecordOUTB = 60,
	erRecordOUTC = 61,
	erRecordOUTD = 62,
	erRecordOT0W = 63,
	erRecordOT1W = 64,
	erRecordOT2W = 65,
	erRecordOT3W = 66,
	erRecordOT4W = 67,
	erRecordOT5W = 68,
	erRecordOT6W = 69,
	erRecordOT7W = 70,
	erRecordOT8W = 71,
	erRecordOT9W = 72,
	erRecordOTAW = 73,
	erRecordOTBW = 74,
	erRecordOTCW = 75,
	erRecordOTDW = 76,
	erRecordOT0D = 77,
	erRecordOT1D = 78,
	erRecordOT2D = 79,
	erRecordOT3D = 80,
	erRecordOT4D = 81,
	erRecordOT5D = 82,
	erRecordOT6D = 83,
	erRecordOT7D = 84,
	erRecordOT8D = 85,
	erRecordOT9D = 86,
	erRecordOTAD = 87,
	erRecordOTBD = 88,
	erRecordOTCD = 89,
	erRecordOTDD = 90,
	erRecordOT0P = 91,
	erRecordOT1P = 92,
	erRecordOT2P = 93,
	erRecordOT3P = 94,
	erRecordOT4P = 95,
	erRecordOT5P = 96,
	erRecordOT6P = 97,
	erRecordOT7P = 98,
	erRecordOT8P = 99,
	erRecordOT9P = 100,
	erRecordOTAP = 101,
	erRecordOTBP = 102,
	erRecordOTCP = 103,
	erRecordOTDP = 104,
	erRecordFPS0 = 105,
	erRecordFPS1 = 106,
	erRecordFPS2 = 107,
	erRecordFPS3 = 108,
	erRecordFPS4 = 109,
	erRecordFPS5 = 110
} erFieldIndex;

#ifdef GEN_SIZE_OFFSET

#include <epicsExport.h>
#include <cantProceed.h>
#ifdef __cplusplus
extern "C" {
#endif
static int erRecordSizeOffset(dbRecordType *prt)
{
    erRecord *prec = 0;

    if (prt->no_fields != 111) {
        cantProceed("IOC build or installation error:\n"
            "    The erRecord defined in the DBD file has %d fields,\n"
            "    but the record support code was built with 111.\n",
            prt->no_fields);
    }
    prt->papFldDes[erRecordNAME]->size = sizeof(prec->name);
    prt->papFldDes[erRecordNAME]->offset = (unsigned short)((char *)&prec->name - (char *)prec);
    prt->papFldDes[erRecordDESC]->size = sizeof(prec->desc);
    prt->papFldDes[erRecordDESC]->offset = (unsigned short)((char *)&prec->desc - (char *)prec);
    prt->papFldDes[erRecordASG]->size = sizeof(prec->asg);
    prt->papFldDes[erRecordASG]->offset = (unsigned short)((char *)&prec->asg - (char *)prec);
    prt->papFldDes[erRecordSCAN]->size = sizeof(prec->scan);
    prt->papFldDes[erRecordSCAN]->offset = (unsigned short)((char *)&prec->scan - (char *)prec);
    prt->papFldDes[erRecordPINI]->size = sizeof(prec->pini);
    prt->papFldDes[erRecordPINI]->offset = (unsigned short)((char *)&prec->pini - (char *)prec);
    prt->papFldDes[erRecordPHAS]->size = sizeof(prec->phas);
    prt->papFldDes[erRecordPHAS]->offset = (unsigned short)((char *)&prec->phas - (char *)prec);
    prt->papFldDes[erRecordEVNT]->size = sizeof(prec->evnt);
    prt->papFldDes[erRecordEVNT]->offset = (unsigned short)((char *)&prec->evnt - (char *)prec);
    prt->papFldDes[erRecordTSE]->size = sizeof(prec->tse);
    prt->papFldDes[erRecordTSE]->offset = (unsigned short)((char *)&prec->tse - (char *)prec);
    prt->papFldDes[erRecordTSEL]->size = sizeof(prec->tsel);
    prt->papFldDes[erRecordTSEL]->offset = (unsigned short)((char *)&prec->tsel - (char *)prec);
    prt->papFldDes[erRecordDTYP]->size = sizeof(prec->dtyp);
    prt->papFldDes[erRecordDTYP]->offset = (unsigned short)((char *)&prec->dtyp - (char *)prec);
    prt->papFldDes[erRecordDISV]->size = sizeof(prec->disv);
    prt->papFldDes[erRecordDISV]->offset = (unsigned short)((char *)&prec->disv - (char *)prec);
    prt->papFldDes[erRecordDISA]->size = sizeof(prec->disa);
    prt->papFldDes[erRecordDISA]->offset = (unsigned short)((char *)&prec->disa - (char *)prec);
    prt->papFldDes[erRecordSDIS]->size = sizeof(prec->sdis);
    prt->papFldDes[erRecordSDIS]->offset = (unsigned short)((char *)&prec->sdis - (char *)prec);
    prt->papFldDes[erRecordMLOK]->size = sizeof(prec->mlok);
    prt->papFldDes[erRecordMLOK]->offset = (unsigned short)((char *)&prec->mlok - (char *)prec);
    prt->papFldDes[erRecordMLIS]->size = sizeof(prec->mlis);
    prt->papFldDes[erRecordMLIS]->offset = (unsigned short)((char *)&prec->mlis - (char *)prec);
    prt->papFldDes[erRecordBKLNK]->size = sizeof(prec->bklnk);
    prt->papFldDes[erRecordBKLNK]->offset = (unsigned short)((char *)&prec->bklnk - (char *)prec);
    prt->papFldDes[erRecordDISP]->size = sizeof(prec->disp);
    prt->papFldDes[erRecordDISP]->offset = (unsigned short)((char *)&prec->disp - (char *)prec);
    prt->papFldDes[erRecordPROC]->size = sizeof(prec->proc);
    prt->papFldDes[erRecordPROC]->offset = (unsigned short)((char *)&prec->proc - (char *)prec);
    prt->papFldDes[erRecordSTAT]->size = sizeof(prec->stat);
    prt->papFldDes[erRecordSTAT]->offset = (unsigned short)((char *)&prec->stat - (char *)prec);
    prt->papFldDes[erRecordSEVR]->size = sizeof(prec->sevr);
    prt->papFldDes[erRecordSEVR]->offset = (unsigned short)((char *)&prec->sevr - (char *)prec);
    prt->papFldDes[erRecordAMSG]->size = sizeof(prec->amsg);
    prt->papFldDes[erRecordAMSG]->offset = (unsigned short)((char *)&prec->amsg - (char *)prec);
    prt->papFldDes[erRecordNSTA]->size = sizeof(prec->nsta);
    prt->papFldDes[erRecordNSTA]->offset = (unsigned short)((char *)&prec->nsta - (char *)prec);
    prt->papFldDes[erRecordNSEV]->size = sizeof(prec->nsev);
    prt->papFldDes[erRecordNSEV]->offset = (unsigned short)((char *)&prec->nsev - (char *)prec);
    prt->papFldDes[erRecordNAMSG]->size = sizeof(prec->namsg);
    prt->papFldDes[erRecordNAMSG]->offset = (unsigned short)((char *)&prec->namsg - (char *)prec);
    prt->papFldDes[erRecordACKS]->size = sizeof(prec->acks);
    prt->papFldDes[erRecordACKS]->offset = (unsigned short)((char *)&prec->acks - (char *)prec);
    prt->papFldDes[erRecordACKT]->size = sizeof(prec->ackt);
    prt->papFldDes[erRecordACKT]->offset = (unsigned short)((char *)&prec->ackt - (char *)prec);
    prt->papFldDes[erRecordDISS]->size = sizeof(prec->diss);
    prt->papFldDes[erRecordDISS]->offset = (unsigned short)((char *)&prec->diss - (char *)prec);
    prt->papFldDes[erRecordLCNT]->size = sizeof(prec->lcnt);
    prt->papFldDes[erRecordLCNT]->offset = (unsigned short)((char *)&prec->lcnt - (char *)prec);
    prt->papFldDes[erRecordPACT]->size = sizeof(prec->pact);
    prt->papFldDes[erRecordPACT]->offset = (unsigned short)((char *)&prec->pact - (char *)prec);
    prt->papFldDes[erRecordPUTF]->size = sizeof(prec->putf);
    prt->papFldDes[erRecordPUTF]->offset = (unsigned short)((char *)&prec->putf - (char *)prec);
    prt->papFldDes[erRecordRPRO]->size = sizeof(prec->rpro);
    prt->papFldDes[erRecordRPRO]->offset = (unsigned short)((char *)&prec->rpro - (char *)prec);
    prt->papFldDes[erRecordASP]->size = sizeof(prec->asp);
    prt->papFldDes[erRecordASP]->offset = (unsigned short)((char *)&prec->asp - (char *)prec);
    prt->papFldDes[erRecordPPN]->size = sizeof(prec->ppn);
    prt->papFldDes[erRecordPPN]->offset = (unsigned short)((char *)&prec->ppn - (char *)prec);
    prt->papFldDes[erRecordPPNR]->size = sizeof(prec->ppnr);
    prt->papFldDes[erRecordPPNR]->offset = (unsigned short)((char *)&prec->ppnr - (char *)prec);
    prt->papFldDes[erRecordSPVT]->size = sizeof(prec->spvt);
    prt->papFldDes[erRecordSPVT]->offset = (unsigned short)((char *)&prec->spvt - (char *)prec);
    prt->papFldDes[erRecordRSET]->size = sizeof(prec->rset);
    prt->papFldDes[erRecordRSET]->offset = (unsigned short)((char *)&prec->rset - (char *)prec);
    prt->papFldDes[erRecordDSET]->size = sizeof(prec->dset);
    prt->papFldDes[erRecordDSET]->offset = (unsigned short)((char *)&prec->dset - (char *)prec);
    prt->papFldDes[erRecordDPVT]->size = sizeof(prec->dpvt);
    prt->papFldDes[erRecordDPVT]->offset = (unsigned short)((char *)&prec->dpvt - (char *)prec);
    prt->papFldDes[erRecordRDES]->size = sizeof(prec->rdes);
    prt->papFldDes[erRecordRDES]->offset = (unsigned short)((char *)&prec->rdes - (char *)prec);
    prt->papFldDes[erRecordLSET]->size = sizeof(prec->lset);
    prt->papFldDes[erRecordLSET]->offset = (unsigned short)((char *)&prec->lset - (char *)prec);
    prt->papFldDes[erRecordPRIO]->size = sizeof(prec->prio);
    prt->papFldDes[erRecordPRIO]->offset = (unsigned short)((char *)&prec->prio - (char *)prec);
    prt->papFldDes[erRecordTPRO]->size = sizeof(prec->tpro);
    prt->papFldDes[erRecordTPRO]->offset = (unsigned short)((char *)&prec->tpro - (char *)prec);
    prt->papFldDes[erRecordBKPT]->size = sizeof(prec->bkpt);
    prt->papFldDes[erRecordBKPT]->offset = (unsigned short)((char *)&prec->bkpt - (char *)prec);
    prt->papFldDes[erRecordUDF]->size = sizeof(prec->udf);
    prt->papFldDes[erRecordUDF]->offset = (unsigned short)((char *)&prec->udf - (char *)prec);
    prt->papFldDes[erRecordUDFS]->size = sizeof(prec->udfs);
    prt->papFldDes[erRecordUDFS]->offset = (unsigned short)((char *)&prec->udfs - (char *)prec);
    prt->papFldDes[erRecordTIME]->size = sizeof(prec->time);
    prt->papFldDes[erRecordTIME]->offset = (unsigned short)((char *)&prec->time - (char *)prec);
    prt->papFldDes[erRecordUTAG]->size = sizeof(prec->utag);
    prt->papFldDes[erRecordUTAG]->offset = (unsigned short)((char *)&prec->utag - (char *)prec);
    prt->papFldDes[erRecordFLNK]->size = sizeof(prec->flnk);
    prt->papFldDes[erRecordFLNK]->offset = (unsigned short)((char *)&prec->flnk - (char *)prec);
    prt->papFldDes[erRecordVAL]->size = sizeof(prec->val);
    prt->papFldDes[erRecordVAL]->offset = (unsigned short)((char *)&prec->val - (char *)prec);
    prt->papFldDes[erRecordOUT0]->size = sizeof(prec->out0);
    prt->papFldDes[erRecordOUT0]->offset = (unsigned short)((char *)&prec->out0 - (char *)prec);
    prt->papFldDes[erRecordOUT1]->size = sizeof(prec->out1);
    prt->papFldDes[erRecordOUT1]->offset = (unsigned short)((char *)&prec->out1 - (char *)prec);
    prt->papFldDes[erRecordOUT2]->size = sizeof(prec->out2);
    prt->papFldDes[erRecordOUT2]->offset = (unsigned short)((char *)&prec->out2 - (char *)prec);
    prt->papFldDes[erRecordOUT3]->size = sizeof(prec->out3);
    prt->papFldDes[erRecordOUT3]->offset = (unsigned short)((char *)&prec->out3 - (char *)prec);
    prt->papFldDes[erRecordOUT4]->size = sizeof(prec->out4);
    prt->papFldDes[erRecordOUT4]->offset = (unsigned short)((char *)&prec->out4 - (char *)prec);
    prt->papFldDes[erRecordOUT5]->size = sizeof(prec->out5);
    prt->papFldDes[erRecordOUT5]->offset = (unsigned short)((char *)&prec->out5 - (char *)prec);
    prt->papFldDes[erRecordOUT6]->size = sizeof(prec->out6);
    prt->papFldDes[erRecordOUT6]->offset = (unsigned short)((char *)&prec->out6 - (char *)prec);
    prt->papFldDes[erRecordOUT7]->size = sizeof(prec->out7);
    prt->papFldDes[erRecordOUT7]->offset = (unsigned short)((char *)&prec->out7 - (char *)prec);
    prt->papFldDes[erRecordOUT8]->size = sizeof(prec->out8);
    prt->papFldDes[erRecordOUT8]->offset = (unsigned short)((char *)&prec->out8 - (char *)prec);
    prt->papFldDes[erRecordOUT9]->size = sizeof(prec->out9);
    prt->papFldDes[erRecordOUT9]->offset = (unsigned short)((char *)&prec->out9 - (char *)prec);
    prt->papFldDes[erRecordOUTA]->size = sizeof(prec->outa);
    prt->papFldDes[erRecordOUTA]->offset = (unsigned short)((char *)&prec->outa - (char *)prec);
    prt->papFldDes[erRecordOUTB]->size = sizeof(prec->outb);
    prt->papFldDes[erRecordOUTB]->offset = (unsigned short)((char *)&prec->outb - (char *)prec);
    prt->papFldDes[erRecordOUTC]->size = sizeof(prec->outc);
    prt->papFldDes[erRecordOUTC]->offset = (unsigned short)((char *)&prec->outc - (char *)prec);
    prt->papFldDes[erRecordOUTD]->size = sizeof(prec->outd);
    prt->papFldDes[erRecordOUTD]->offset = (unsigned short)((char *)&prec->outd - (char *)prec);
    prt->papFldDes[erRecordOT0W]->size = sizeof(prec->ot0w);
    prt->papFldDes[erRecordOT0W]->offset = (unsigned short)((char *)&prec->ot0w - (char *)prec);
    prt->papFldDes[erRecordOT1W]->size = sizeof(prec->ot1w);
    prt->papFldDes[erRecordOT1W]->offset = (unsigned short)((char *)&prec->ot1w - (char *)prec);
    prt->papFldDes[erRecordOT2W]->size = sizeof(prec->ot2w);
    prt->papFldDes[erRecordOT2W]->offset = (unsigned short)((char *)&prec->ot2w - (char *)prec);
    prt->papFldDes[erRecordOT3W]->size = sizeof(prec->ot3w);
    prt->papFldDes[erRecordOT3W]->offset = (unsigned short)((char *)&prec->ot3w - (char *)prec);
    prt->papFldDes[erRecordOT4W]->size = sizeof(prec->ot4w);
    prt->papFldDes[erRecordOT4W]->offset = (unsigned short)((char *)&prec->ot4w - (char *)prec);
    prt->papFldDes[erRecordOT5W]->size = sizeof(prec->ot5w);
    prt->papFldDes[erRecordOT5W]->offset = (unsigned short)((char *)&prec->ot5w - (char *)prec);
    prt->papFldDes[erRecordOT6W]->size = sizeof(prec->ot6w);
    prt->papFldDes[erRecordOT6W]->offset = (unsigned short)((char *)&prec->ot6w - (char *)prec);
    prt->papFldDes[erRecordOT7W]->size = sizeof(prec->ot7w);
    prt->papFldDes[erRecordOT7W]->offset = (unsigned short)((char *)&prec->ot7w - (char *)prec);
    prt->papFldDes[erRecordOT8W]->size = sizeof(prec->ot8w);
    prt->papFldDes[erRecordOT8W]->offset = (unsigned short)((char *)&prec->ot8w - (char *)prec);
    prt->papFldDes[erRecordOT9W]->size = sizeof(prec->ot9w);
    prt->papFldDes[erRecordOT9W]->offset = (unsigned short)((char *)&prec->ot9w - (char *)prec);
    prt->papFldDes[erRecordOTAW]->size = sizeof(prec->otaw);
    prt->papFldDes[erRecordOTAW]->offset = (unsigned short)((char *)&prec->otaw - (char *)prec);
    prt->papFldDes[erRecordOTBW]->size = sizeof(prec->otbw);
    prt->papFldDes[erRecordOTBW]->offset = (unsigned short)((char *)&prec->otbw - (char *)prec);
    prt->papFldDes[erRecordOTCW]->size = sizeof(prec->otcw);
    prt->papFldDes[erRecordOTCW]->offset = (unsigned short)((char *)&prec->otcw - (char *)prec);
    prt->papFldDes[erRecordOTDW]->size = sizeof(prec->otdw);
    prt->papFldDes[erRecordOTDW]->offset = (unsigned short)((char *)&prec->otdw - (char *)prec);
    prt->papFldDes[erRecordOT0D]->size = sizeof(prec->ot0d);
    prt->papFldDes[erRecordOT0D]->offset = (unsigned short)((char *)&prec->ot0d - (char *)prec);
    prt->papFldDes[erRecordOT1D]->size = sizeof(prec->ot1d);
    prt->papFldDes[erRecordOT1D]->offset = (unsigned short)((char *)&prec->ot1d - (char *)prec);
    prt->papFldDes[erRecordOT2D]->size = sizeof(prec->ot2d);
    prt->papFldDes[erRecordOT2D]->offset = (unsigned short)((char *)&prec->ot2d - (char *)prec);
    prt->papFldDes[erRecordOT3D]->size = sizeof(prec->ot3d);
    prt->papFldDes[erRecordOT3D]->offset = (unsigned short)((char *)&prec->ot3d - (char *)prec);
    prt->papFldDes[erRecordOT4D]->size = sizeof(prec->ot4d);
    prt->papFldDes[erRecordOT4D]->offset = (unsigned short)((char *)&prec->ot4d - (char *)prec);
    prt->papFldDes[erRecordOT5D]->size = sizeof(prec->ot5d);
    prt->papFldDes[erRecordOT5D]->offset = (unsigned short)((char *)&prec->ot5d - (char *)prec);
    prt->papFldDes[erRecordOT6D]->size = sizeof(prec->ot6d);
    prt->papFldDes[erRecordOT6D]->offset = (unsigned short)((char *)&prec->ot6d - (char *)prec);
    prt->papFldDes[erRecordOT7D]->size = sizeof(prec->ot7d);
    prt->papFldDes[erRecordOT7D]->offset = (unsigned short)((char *)&prec->ot7d - (char *)prec);
    prt->papFldDes[erRecordOT8D]->size = sizeof(prec->ot8d);
    prt->papFldDes[erRecordOT8D]->offset = (unsigned short)((char *)&prec->ot8d - (char *)prec);
    prt->papFldDes[erRecordOT9D]->size = sizeof(prec->ot9d);
    prt->papFldDes[erRecordOT9D]->offset = (unsigned short)((char *)&prec->ot9d - (char *)prec);
    prt->papFldDes[erRecordOTAD]->size = sizeof(prec->otad);
    prt->papFldDes[erRecordOTAD]->offset = (unsigned short)((char *)&prec->otad - (char *)prec);
    prt->papFldDes[erRecordOTBD]->size = sizeof(prec->otbd);
    prt->papFldDes[erRecordOTBD]->offset = (unsigned short)((char *)&prec->otbd - (char *)prec);
    prt->papFldDes[erRecordOTCD]->size = sizeof(prec->otcd);
    prt->papFldDes[erRecordOTCD]->offset = (unsigned short)((char *)&prec->otcd - (char *)prec);
    prt->papFldDes[erRecordOTDD]->size = sizeof(prec->otdd);
    prt->papFldDes[erRecordOTDD]->offset = (unsigned short)((char *)&prec->otdd - (char *)prec);
    prt->papFldDes[erRecordOT0P]->size = sizeof(prec->ot0p);
    prt->papFldDes[erRecordOT0P]->offset = (unsigned short)((char *)&prec->ot0p - (char *)prec);
    prt->papFldDes[erRecordOT1P]->size = sizeof(prec->ot1p);
    prt->papFldDes[erRecordOT1P]->offset = (unsigned short)((char *)&prec->ot1p - (char *)prec);
    prt->papFldDes[erRecordOT2P]->size = sizeof(prec->ot2p);
    prt->papFldDes[erRecordOT2P]->offset = (unsigned short)((char *)&prec->ot2p - (char *)prec);
    prt->papFldDes[erRecordOT3P]->size = sizeof(prec->ot3p);
    prt->papFldDes[erRecordOT3P]->offset = (unsigned short)((char *)&prec->ot3p - (char *)prec);
    prt->papFldDes[erRecordOT4P]->size = sizeof(prec->ot4p);
    prt->papFldDes[erRecordOT4P]->offset = (unsigned short)((char *)&prec->ot4p - (char *)prec);
    prt->papFldDes[erRecordOT5P]->size = sizeof(prec->ot5p);
    prt->papFldDes[erRecordOT5P]->offset = (unsigned short)((char *)&prec->ot5p - (char *)prec);
    prt->papFldDes[erRecordOT6P]->size = sizeof(prec->ot6p);
    prt->papFldDes[erRecordOT6P]->offset = (unsigned short)((char *)&prec->ot6p - (char *)prec);
    prt->papFldDes[erRecordOT7P]->size = sizeof(prec->ot7p);
    prt->papFldDes[erRecordOT7P]->offset = (unsigned short)((char *)&prec->ot7p - (char *)prec);
    prt->papFldDes[erRecordOT8P]->size = sizeof(prec->ot8p);
    prt->papFldDes[erRecordOT8P]->offset = (unsigned short)((char *)&prec->ot8p - (char *)prec);
    prt->papFldDes[erRecordOT9P]->size = sizeof(prec->ot9p);
    prt->papFldDes[erRecordOT9P]->offset = (unsigned short)((char *)&prec->ot9p - (char *)prec);
    prt->papFldDes[erRecordOTAP]->size = sizeof(prec->otap);
    prt->papFldDes[erRecordOTAP]->offset = (unsigned short)((char *)&prec->otap - (char *)prec);
    prt->papFldDes[erRecordOTBP]->size = sizeof(prec->otbp);
    prt->papFldDes[erRecordOTBP]->offset = (unsigned short)((char *)&prec->otbp - (char *)prec);
    prt->papFldDes[erRecordOTCP]->size = sizeof(prec->otcp);
    prt->papFldDes[erRecordOTCP]->offset = (unsigned short)((char *)&prec->otcp - (char *)prec);
    prt->papFldDes[erRecordOTDP]->size = sizeof(prec->otdp);
    prt->papFldDes[erRecordOTDP]->offset = (unsigned short)((char *)&prec->otdp - (char *)prec);
    prt->papFldDes[erRecordFPS0]->size = sizeof(prec->fps0);
    prt->papFldDes[erRecordFPS0]->offset = (unsigned short)((char *)&prec->fps0 - (char *)prec);
    prt->papFldDes[erRecordFPS1]->size = sizeof(prec->fps1);
    prt->papFldDes[erRecordFPS1]->offset = (unsigned short)((char *)&prec->fps1 - (char *)prec);
    prt->papFldDes[erRecordFPS2]->size = sizeof(prec->fps2);
    prt->papFldDes[erRecordFPS2]->offset = (unsigned short)((char *)&prec->fps2 - (char *)prec);
    prt->papFldDes[erRecordFPS3]->size = sizeof(prec->fps3);
    prt->papFldDes[erRecordFPS3]->offset = (unsigned short)((char *)&prec->fps3 - (char *)prec);
    prt->papFldDes[erRecordFPS4]->size = sizeof(prec->fps4);
    prt->papFldDes[erRecordFPS4]->offset = (unsigned short)((char *)&prec->fps4 - (char *)prec);
    prt->papFldDes[erRecordFPS5]->size = sizeof(prec->fps5);
    prt->papFldDes[erRecordFPS5]->offset = (unsigned short)((char *)&prec->fps5 - (char *)prec);
    prt->rec_size = sizeof(*prec);
    return 0;
}
epicsExportRegistrar(erRecordSizeOffset);

#ifdef __cplusplus
}
#endif
#endif /* GEN_SIZE_OFFSET */

#endif /* INC_erRecord_H */
