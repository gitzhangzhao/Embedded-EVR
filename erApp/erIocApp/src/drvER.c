/**
 * File              : drvER.c
 * Author            : zhangzhao <zhangzhao@ihep.ac.cn>
 * Date              : 16.11.2022
 * Last Modified Date: 15.12.2022
 * Last Modified By  : zhangzhao <zhangzhao@ihep.ac.cn>
 * Description       : event receiver driver
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
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>

/* EPICS Standard library */
#include <iocsh.h>
/* #include <epicsInterrupt.h> */
#include <epicsStdio.h>
/* #include <epicsStdlib.h> */
#include <epicsThread.h>
/* #include <epicsTime.h> */
#include <epicsTypes.h>

/* EPICS device support */
#include <devLib.h>

/* EPICS driver support */
#include <drvSup.h>

/* EPICS Symbol exporting macro definitions */
#include <epicsExport.h>

/* EPICS generaltime module*/
#include <generalTimeSup.h>
#include <epicsGeneralTime.h>

/* header files for event receiver */
#include "drvER.h"

/**********************************************************************
 *                         Macro Definitions                          *
 **********************************************************************/

/* the default memory page size of the Linux Kernel is 4KB */
#define PAGE_SIZE 4096UL
/* page mask */
#define PAGE_MASK (PAGE_SIZE - 1)
/* bse address of the register map */
#define BASE_ADDR 0
/* masked address */
#define MASK_ADDR (BASE_ADDR & PAGE_MASK)
/* print error message */
#define FATAL                                                                                                          \
    do {                                                                                                           \
        fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", __LINE__, __FILE__, errno, strerror(errno));  \
        return -1;                                                                                             \
    } while (0)
/* initialize ER structure */
#define ER_INIT                                                                                                        \
{                                                                                                              \
    NULL, NULL, 0, 0, NULL, 0, {0}, {0}                                                               \
}
/* number of event codes */
#define EVENT_NUM 256

/* timestamp clock nanosecond conversion factor */
#define NANO_CONV 10.004001600640256

/* one second */
#define ONE_SECOND 1000000000.0


/**********************************************************************
 *                        Hardware Definitions                        *
 **********************************************************************/
/*     Register  Address Offset  Number */
#define CONTROL 0x00  /*00*/
#define RAM_ADDR 0x04 /*01*/
#define RAM_DATA 0x08 /*02*/
/*#define    OutputPulseEnables     0x0c      */
#define EVENT_CODE 0x10 /*04*/
#define EVENT_NSEC 0x14 /*05*/
#define EVENT_SEC 0x18  /*06*/
#define LATCH_SEC 0x1c  /*07*/
#define LATCH_NSEC 0x20 /*08*/
#define PULSE_SEL 0x24  /*09*/
#define PULSE_WID 0x28  /*10*/
#define PULSE_DLY 0x2c  /*11*/
#define PULSE_POL 0x30  /*12*/
#define PULSE_ENA 0x34  /*13*/
#define FPS_OUT0 0x38   /*14*/
#define FPS_OUT1 0x3c   /*15*/
#define FPS_OUT2 0x40   /*16*/
#define FPS_OUT3 0x44   /*17*/
#define FPS_OUT4 0x48   /*18*/
#define FPS_OUT5 0x4c   /*19*/

/**********************************************************************
 *                   Control Register Bit Assignments                 *
 **********************************************************************/
/* write 1 to global reset */
#define CTRL_RESET 0x0001
/* Event FIFO Empty flag */
#define CTRL_EMPTY 0x0002
/* Event FIFO Full flag */
#define CTRL_FULL 0x0004
/* GTX PLL lock flag */
#define CTRL_PLLCK 0x0008
/* write 1 to latch timestamp */
#define CTRL_LATCH 0x0010
/* 0: disable mappingRAM */
/* 1: enable mappingRAM */
#define CTRL_ENA 0x0020
/* 0: RAM0 for read */
/* 1: RAM1 for read */
#define CTRL_READ 0x0040
/* 0: RAM0 for write */
/* 1: RAM1 for write */
#define CTRL_WRITE 0x0080
/* clear the written RAM */
#define CTRL_CLR 0x0100

/**********************************************************************
 *                       Common IO Definitions                        *
 **********************************************************************/
/* read 32-bit date from offset */
#define READ_32(BASE, OFFSET) *(volatile epicsUInt32 *)((epicsUInt8 *)BASE + OFFSET)

/* write 32-bit date from offset */
#define WRITE_32(BASE, OFFSET, VALUE) *(volatile epicsUInt32 *)((epicsUInt8 *)BASE + OFFSET) = VALUE

/* clear 32-bit register */
#define CLR_32(BASE, OFFSET) WRITE_32(BASE, OFFSET, 0)

/* clear the mask bit of the register */
#define BITCLR(BASE, OFFSET, MASK) WRITE_32(BASE, OFFSET, (READ_32(BASE, OFFSET) & (epicsUInt32) ~(MASK)))

/* set the mask bit of the register */
#define BITSET(BASE, OFFSET, MASK) WRITE_32(BASE, OFFSET, (READ_32(BASE, OFFSET) | (epicsUInt32)(MASK)))

/* get the specified bit of the register */
#define BITGET(BASE, OFFSET, MASK) (((READ_32(BASE, OFFSET)) & (MASK)) ? 1 : 0)

/**********************************************************************
 *                          Static Structure                          *
 **********************************************************************/

static ER_struct ERZ = ER_INIT;

/**********************************************************************
 *                   Function Type Definitions                        *
 **********************************************************************/
/* user-defined event function */
typedef void (*EVENT_FUNC)(void);

/**********************************************************************
 *                  Prototype Function Declarations                   *
 **********************************************************************/
int open_ER(char *, epicsUInt32, epicsUInt32 **);
epicsStatus configure_ER(char *, epicsUInt32);
epicsThreadId init_irq();
void *irq_handler(void *);
epicsStatus get_event_time(ER_struct *, epicsUInt32, epicsTimeStamp *);
epicsStatus register_event_time(epicsTimeStamp *, int);
epicsStatus register_current_time(epicsTimeStamp *);
epicsStatus init_event_time();

/**********************************************************************
 *                        Function Definitions                        *
 **********************************************************************/

/*-----------------------------------------------
 * get_ER: retrieve a pointer to the ER structure
 *-----------------------------------------------
 * output:
 *   er: ER pointer
 * return: status
 */
ER_struct *get_ER()
{
    return &ERZ;
}

/*---------------------------------------------
 * open_ER: open an ER device
 *---------------------------------------------
 * input:
 *   device: the device name in /dev/ directory
 *   offset: accessible address for the device
 * output:
 *   vir_addr: the mapped virtual address
 * return: ER device fd
 */
int open_ER(char *device, epicsUInt32 offset, epicsUInt32 **vir_addr)
{
    int fd;
    void *page_addr;
    char device_name[50];
    /* device name handle */
    strcpy(device_name, "/dev/");
    strcat(device_name, device);
    /* open an image of device */
    if ((fd = open(device_name, O_RDWR | O_SYNC)) == -1)
        FATAL;
    /* map one page for device spacename */
    page_addr = mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset & ~PAGE_MASK);
    if (page_addr == (void *)-1)
        FATAL;
    /* printf("One page mapped at address %p.\n", page_addr); */
    *vir_addr = page_addr + MASK_ADDR;
    return fd;
}

/*---------------------------------------------------------------
 * configure_ER: open and configure the ER device before IOC Init
 *---------------------------------------------------------------
 * input:
 *   device: the device name in /dev/directory
 *   offset: accessible address for the device
 */
epicsStatus configure_ER(char *device, epicsUInt32 offset)
{
    epicsThreadId tid;
    int fd;
    /* open the ERZ device and store the virtual address in *pEr */
    fd = open_ER(device, offset, (epicsUInt32 **)&ERZ.pEr);
    // printf("fd1:%d\n",fd);
    if (fd < 0)
        FATAL;
    /* store the fd into ER structure */
    ERZ.fd = fd;

    /* initialize the interrupt thread */
    tid = init_irq();
    if (tid == 0)
        FATAL;
    /* store the tid into ER structure */
    ERZ.tid = tid;

    /* init event time */
    init_event_time();

    return 0;
}

/*-------------------------------------------
 * init_irq: initialize the interrupt handler
 *-------------------------------------------
 * return: thread tid
 */
epicsThreadId init_irq()
{
    /* the default sched is SCHED_FIFO */
    epicsThreadOpts opts = EPICS_THREAD_OPTS_INIT;
    opts.priority = epicsThreadPriorityHigh;
    /* creat a new thread */
    return epicsThreadCreateOpt("irq_handler", (EPICSTHREADFUNC)irq_handler, (void *)&ERZ.fd, &opts);
}

/*----------------------------------------------
 * irq_handler: handle interrupts from ER device
 *----------------------------------------------
 * input:
 *   argv: parm passed to new thread
 */
void *irq_handler(void *argv)
{
    // cpu_set_t cpuset;
    /* int policy, ret; */
    /* struct sched_param param; */
    /* for main process */
    register epicsUInt32 *pEr = ERZ.pEr;
    int fd = *(int *)argv;
    // printf("fd3:%d\n",fd);
    int irq_count;
    int enable = 1;
    unsigned int mask;
    unsigned int event_code;
    unsigned long seconds;
    unsigned long nanoseconds;
    /* get pthread scheduling algorithm */
    /* ret = pthread_getschedparam(pthread_self(), &policy, &param); */
    /* if (ret != 0) { */
    /*         printf("pthread_getschedparam %s\n", strerror(ret)); */
    /*         exit(1); */
    /* } */
    /* if (policy == SCHED_FIFO) { */
    /*         printf("policy:SCHED_FIFO\n"); */
    /* } else if (policy == SCHED_OTHER) { */
    /*         printf("policy:SCHED_OTHER\n"); */
    /* } else if (policy == SCHED_RR) { */
    /*         printf("policy:SCHED_RR\n"); */
    /* } else { */
    /*         printf("get policy failed\n"); */
    /* } */
    /* printf("interrupt_handler pthread priority is %d\n", param.sched_priority); */
    /* CPU_ZERO(&cpuset); */
    /* cpu 1 is in cpuset now */
    /* CPU_SET(1, &cpuset); */
    /* bind pthread to processor 1 */
    /* if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0) { */
    /* perror("pthread_setaffinity_np"); */
    /* } */
    /* printf("Core 1 is running! this pthread PID is %ld\n", gettid()); */
    /* main process */
    // reset event fifo
    //
    //
    // printf("seconds:%x, nano:%x\n",READ_32(pEr, LATCH_SEC),READ_32(pEr, LATCH_NSEC));
    // printf("second:%x, nano:%x\n",pEr[7], pEr[8]);
    // pEr[0] = 0x1c;
    // usleep(1);
    // printf("second:%x, nano:%x\n",pEr[7], pEr[8]);
    // BITSET(pEr, CONTROL, CTRL_LATCH);
    // pEr[0] = 0x1c;
    // sleep(0.5);
    // printf("seconds:%x, nano:%x\n",READ_32(pEr, LATCH_SEC),READ_32(pEr, LATCH_NSEC));
    // printf("second:%x, nano:%x\n",pEr[7], pEr[8]);

    //printf("pEr[0] address: %p\npEr[8] address: %p\n", &pEr[0], &pEr[8]);


    // BITSET(pEr, CONTROL, CTRL_LATCH);
    // WRITE_32(pEr, LATCH_SEC, 0x666);
    //printf("control:%d\n", READ_32(pEr, CONTROL));
    //printf("seconds:%d, nano:%d\n",READ_32(pEr, LATCH_SEC),READ_32(pEr, LATCH_NSEC));
    // sleep(6);
    /* reset Event FIFO */
    BITSET(pEr, CONTROL, CTRL_RESET);
    //BITSET(pEr, CONTROL, CTRL_LATCH);
    //printf("seconds:%d, nano:%d\n",READ_32(pEr, LATCH_SEC),READ_32(pEr, LATCH_NSEC));
    //printf("control:%d\n", READ_32(pEr, CONTROL));
    /* enable interrupt */
    write(fd, &enable, sizeof(enable));
    while (1) {
        /* unsigned long tmp; */
        if (read(fd, &irq_count, 4) != 4) {
            perror("read uio0");
        }
        if (!(BITGET(pEr, CONTROL, CTRL_PLLCK))) {
            printf("CPLL lost.\n");
            FATAL;
        }
        for (int i = 0; i < 10; i++) {
            if ((READ_32(pEr, CONTROL) & 0x2) == 0x2)
                break;
            seconds = READ_32(pEr, EVENT_SEC);
            nanoseconds = READ_32(pEr, EVENT_NSEC);
            event_code = READ_32(pEr, EVENT_CODE);

            ERZ.event_ts[event_code].secPastEpoch = seconds;
            ERZ.event_ts[event_code].nsec = nanoseconds;
            // if(event_code == 0x7d)
            // printf("seconds: %8ld    nanoseconds: %8ld    event code: %#02x\n", seconds, nanoseconds,
            // event_code);
            /* if (event_code == 0x24) { */
            /*         printf("%ld\n", nanoseconds - tmp); */
            /*         tmp = nanoseconds; */
            /* } */
        }
        if (BITGET(pEr, CONTROL, CTRL_FULL)) {
            printf("FIFO overflow.\n");
            FATAL;
        }
        write(fd, &enable, sizeof(enable));
    }
    return NULL;
}

/*-----------------------------------------
 * check_ER: check the satatus of ER device
 *-----------------------------------------
 */
/* epicsStatus check_ER(ER_struct *ER) */
/* { */
/*         register epicsUInt32 pEr; */
/*         int pll; */
/*         int full; */

/*         pEr = ER->pEr; */
/*         if (0 == (pll = BITGET(pEr, CONTROL, CTRL_PLLCK))) */
/*                 printf("PLL clock failed."); */

/*         if (1 == (full = BITGET(pEr, CONTROL, CTRL_FULL))) */
/*                 printf("Event FIFO has overflowed."); */
/*         /1* add ... *1/ */
/* } */

/*------------------------------------------------
 * enable_ram: enable mappingRAM 0 or mappingRAM 1
 *------------------------------------------------
 * input:
 *   ER: pointer to ER structure
 *   num: mappingRAM number (0 or 1)
 */
/* epicsStatus enable_ram(ER_struct *ER, int num) */
/* { */
/*         register epicsUInt32 pEr; */
/*         pEr = ER->pEr; */

/*         if (num < 0 || num > 1) */
/*                 return -1; */
/*         /1* enable RAM 0, disbale RAM 1 *1/ */
/*         if (0 == num) */
/*                 BITCLR(pEr, CONTROL, CTRL_ENA); */
/*         else */
/*                 /1* enable RAM 1, disbale RAM 0 *1/ */
/*                 BITSET(pEr, CONTROL, CTRL_ENA); */
/*         return 0; */
/* } */

/*---------------------------------------------
 * check_ram: check the status of specified RAM
 *---------------------------------------------
 *
 */
/* epicsStatus check_ram(ER_struct *ER, int num) */
/* { */
/*         register epicsUInt32 pEr; */
/*         pEr = ER->pEr; */
/*         if (0 == (BITGET(pEr, CONTROL, CTRL_ENA))) */
/*                 return 0 */
/*         /1* add ... *1/ */
/* } */

/*-------------------------------------------------------------
 * set_pulse: set 14 programmable width and delay pulse outputs
 *-------------------------------------------------------------
 * input:
 *   ER: pointer to ER structure
 *   channel: select one of the 14 pulse outputs (0-13)
 *   enable: enable or disable the selected channel
 *   delay: set the pulse delay (event clock period)
 *   width: set the pulse width (event clock period)
 *   polarity: polarity for selected channel
 */
void set_pulse(ER_struct *ER, epicsUInt32 channel, bool enable, epicsUInt32 delay, epicsUInt32 width,
        bool polarity)
{
    register epicsUInt32 *pEr = ER->pEr;
    /* mask for setting channel enable and polarity */
    epicsUInt32 mask = 1 << channel;

    WRITE_32(pEr, PULSE_SEL, channel);
    /* set the pulse delay */
    WRITE_32(pEr, PULSE_DLY, delay);
    /* set the pulse width */
    WRITE_32(pEr, PULSE_WID, width);

    /* set polarity for the channel */
    if (polarity)
        BITSET(pEr, PULSE_POL, mask);
    else
        BITCLR(pEr, PULSE_POL, mask);

    /* set enable for the channel */
    if (enable)
        BITSET(pEr, PULSE_ENA, mask);
    else
        BITCLR(pEr, PULSE_ENA, mask);
}

/*-----------------------------------------
 * program_ram: load and activate a new map
 *-----------------------------------------
 * input:
 *   ER: pointer to ER structure
 */
void program_ram(ER_struct *ER)
{
    /* local variables */
    epicsUInt32 event;
    epicsUInt16 map;
    int inactive_ram;
    register epicsUInt32 *pEr = ER->pEr;

    epicsUInt16 *event_map = ER->event_map;

    /* select the inactive RAM to write */
    if (BITGET(pEr, CONTROL, CTRL_READ)) {
        inactive_ram = 0;
        BITCLR(pEr, CONTROL, CTRL_WRITE);
    } else {
        inactive_ram = 1;
        BITSET(pEr, CONTROL, CTRL_WRITE);
    }

    CLR_32(pEr, RAM_ADDR);

    /* write the event output map to the inactive RAM */
    for (event = 0; event < EVENT_NUM; event++) {
        map = event_map[event];
        WRITE_32(pEr, RAM_ADDR, event);
        WRITE_32(pEr, RAM_DATA, map);
        /* printf("address:%d, data:%x\n",event,map); */
    }

    CLR_32(pEr, RAM_ADDR);

    /* select the inactive RAM to read */
    if (inactive_ram)
        BITSET(pEr, CONTROL, CTRL_READ);
    else
        BITCLR(pEr, CONTROL, CTRL_READ);
}

/*---------------------------------
 * set_fps: setting the fps outputs
 *---------------------------------
 * input:
 *   ER: pointer to ER structure
 *   out: output channel
 *   map: register value
 */
void set_fps(ER_struct *ER, int out, epicsUInt16 map)
{
    register epicsUInt32 *pEr = ER->pEr;

    /* write the map value to registers */
    switch (out) {
        case 0:
            WRITE_32(pEr, FPS_OUT0, map);
            break;
        case 1:
            WRITE_32(pEr, FPS_OUT1, map);
            break;
        case 2:
            WRITE_32(pEr, FPS_OUT2, map);
            break;
        case 3:
            WRITE_32(pEr, FPS_OUT3, map);
            break;
        case 4:
            WRITE_32(pEr, FPS_OUT4, map);
            break;
        case 5:
            WRITE_32(pEr, FPS_OUT5, map);
            break;
    }
}

/*-----------------------------------------------
 * init_event_time: init Epics generaltime module
 *-----------------------------------------------
 */
epicsStatus init_event_time(){
    int ret = 0;
    ret |= generalTimeCurrentTpRegister("Event", 70, register_current_time);
    ret |= generalTimeEventTpRegister("Event", 70, register_event_time);

    if(ret)
    {
        printf("init_event_time failed.\n");
        FATAL;
    }
}

/*-----------------------------------------------------------
 * register_current_time: get current time without event code
 *-----------------------------------------------------------
 * input:
 *   pDest: pointer to EPICS timestamp structure
 */
epicsStatus register_current_time(epicsTimeStamp *pDest)
{
    int ret;
    ret = register_event_time(pDest,0);
    // printf("current_time:%d\n", ret);
    return ret;
}

/*-----------------------------------------------------------------
 * register_event_time: get event time for the specified event code
 *-----------------------------------------------------------------
 * input:
 *   pDest: pointer to EPICS timestamp structure
 *   event: event code
 */
epicsStatus register_event_time(epicsTimeStamp *pDest, int event_code)
{
    ER_struct *ER = get_ER();
    int ret;
    ret = get_event_time(ER, event_code, pDest);
    // printf("event_time:%d\n", ret);
    return ret;
}

/*---------------------------------------
 * get_event_time: get timestamp from ER 
 *---------------------------------------
 * input:
 *   ER: pointer to ER structure
 *   event: event code
 *   timestamp: epics timestamp structure
 */
epicsStatus get_event_time(ER_struct *ER, epicsUInt32 event_code, epicsTimeStamp *timestamp)
{
    epicsTimeStamp localtime;
    epicsUInt32 overflow;
    epicsFloat64 nanoseconds_tmp;
    register epicsUInt32 *pEr = ER->pEr;

    /* clear timestamp structure */
    timestamp->secPastEpoch = 0;
    timestamp->nsec = 0;

    /* get timestamp from ER */
    if((event_code > 0) && (event_code < EVENT_NUM))
    {
       localtime = ER->event_ts[event_code];
    }
    else
    {
        /* latch timestamp */
        BITSET(pEr, CONTROL, CTRL_LATCH);

        /* read the latched timestamp */
        localtime.secPastEpoch = READ_32(pEr, LATCH_SEC);
        localtime.nsec = READ_32(pEr, LATCH_NSEC);
    }

    /* convert the timestamp into EPICS timestamp */
    nanoseconds_tmp = (epicsFloat64)localtime.nsec;

    nanoseconds_tmp = (nanoseconds_tmp * NANO_CONV);

    if (nanoseconds_tmp >= ONE_SECOND) {
        overflow = (epicsUInt32)(nanoseconds_tmp / ONE_SECOND);
        localtime.secPastEpoch += overflow;
        nanoseconds_tmp -= ((epicsFloat64)overflow * ONE_SECOND);
    }

    /* store the converted timestamp */
    localtime.nsec = (epicsUInt32)(nanoseconds_tmp + 0.5);

    *timestamp = localtime;
    
    return 0;
}

/**********************************************************************
 *                      register IOC Shell                            *
 **********************************************************************/
const iocshArg configure_ERArg0 = {"device", iocshArgString};
const iocshArg configure_ERArg1 = {"offset", iocshArgInt};
const iocshArg *const configure_ERArgs[2] = {&configure_ERArg0, &configure_ERArg1};
const iocshFuncDef configure_ERDef = {"configure_ER", 2, configure_ERArgs};
void configure_ERCall(const iocshArgBuf *args)
{
    configure_ER(args[0].sval, (epicsUInt32)args[1].ival);
}
static void configure_ERRegister(void) {
    iocshRegister(&configure_ERDef, configure_ERCall);
}
epicsExportRegistrar (configure_ERRegister);

