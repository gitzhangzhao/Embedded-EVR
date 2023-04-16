#!../../bin/linux-arm/erIoc

#- You may have to change erIoc to something else
#- everywhere it appears in this file

cd "/root/erApp"

## Register all support components
dbLoadDatabase "dbd/erIoc.dbd"
erIoc_registerRecordDeviceDriver pdbbase

## Load record instances
dbLoadRecords "db/er.db", "user=zhangzh, PulseWidth=200"
dbLoadRecords "db/erevent20.db", "user=zhangzh"
dbLoadRecords "db/erevent50.db", "user=zhangzh"

#- Set this to see messages from mySub
#var mySubDebug 1

#- Run this to trace the stages of iocInit
#traceIocInit

configure_ER("uio0",0)

iocInit

## Start any sequence programs
#seq sncExample, "user=zhangzh"
