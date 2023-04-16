TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS BELOW HERE
ifneq ($(findstring Host, $(VALID_BUILDS)),)
    VALID_BUILDS = Host
endif

# Use typed rset structure (see 3.16.1 release notes)
USR_CPPFLAGS += -DUSE_TYPED_RSET

# xxxRecord.h will be created from xxxRecord.dbd
DBDINC += erRecord
DBDINC += ereventRecord
# DBDINC += menuEventEnable
# DBDINC += menuPolarity

# Build an IOC support library
LIBRARY_IOC += erIocSupport

# Compile and add code to the support library
erIocSupport_SRCS += erRecord.c
erIocSupport_SRCS += ereventRecord.c
erIocSupport_SRCS += devER.c
erIocSupport_SRCS += drvER.c

erIocSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

GENVERSIONMACRO = erIocVERSION

# Build the IOC application
PROD_IOC = erIoc

# erIoc.dbd will be created and installed
DBD += erIoc.dbd

# erIoc.dbd will include these files:
erIoc_DBD += base.dbd
erIoc_DBD += erRecord.dbd
erIoc_DBD += ereventRecord.dbd
erIoc_DBD += devER.dbd

# erIoc_registerRecordDeviceDriver.cpp derives from erIoc.dbd
erIoc_SRCS += erIoc_registerRecordDeviceDriver.cpp

# Build the main IOC entry point where needed
erIoc_SRCS_DEFAULT += erIocMain.cpp
erIoc_SRCS_vxWorks += -nil-

# Link in the code from our support library
erIoc_LIBS += erIocSupport

# Link QSRV (pvAccess Server) if available
ifdef EPICS_QSRV_MAJOR_VERSION
    erIoc_LIBS += qsrv
    erIoc_LIBS += $(EPICS_BASE_PVA_CORE_LIBS)
    erIoc_DBD += PVAServerRegister.dbd
    erIoc_DBD += qsrv.dbd
endif

# Finally link IOC to the EPICS Base libraries
erIoc_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD EXTRA GNUMAKE RULES BELOW HERE

# Explicit dependency needed for generated header file
deverIocVersion$(DEP): $(COMMON_DIR)/$(GENVERSION)
