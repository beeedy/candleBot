#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/finalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/finalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="/Users/broderickcarlin/candleBot/PIC firmware/colorSensor.c" "/Users/broderickcarlin/candleBot/PIC firmware/compass.c" "/Users/broderickcarlin/candleBot/PIC firmware/delays.c" "/Users/broderickcarlin/candleBot/PIC firmware/encoders.c" "/Users/broderickcarlin/candleBot/PIC firmware/fft.c" "/Users/broderickcarlin/candleBot/PIC firmware/FONA.c" "/Users/broderickcarlin/candleBot/PIC firmware/I2C.c" "/Users/broderickcarlin/candleBot/PIC firmware/LCD.c" "/Users/broderickcarlin/candleBot/PIC firmware/main.c" "/Users/broderickcarlin/candleBot/PIC firmware/motorDrive.c" "/Users/broderickcarlin/candleBot/PIC firmware/PS2.c" "/Users/broderickcarlin/candleBot/PIC firmware/settings.c" "/Users/broderickcarlin/candleBot/PIC firmware/UART.c" "/Users/broderickcarlin/candleBot/PIC firmware/USB.c" "/Users/broderickcarlin/candleBot/PIC firmware/whiskers.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/684626063/colorSensor.p1 ${OBJECTDIR}/_ext/684626063/compass.p1 ${OBJECTDIR}/_ext/684626063/delays.p1 ${OBJECTDIR}/_ext/684626063/encoders.p1 ${OBJECTDIR}/_ext/684626063/fft.p1 ${OBJECTDIR}/_ext/684626063/FONA.p1 ${OBJECTDIR}/_ext/684626063/I2C.p1 ${OBJECTDIR}/_ext/684626063/LCD.p1 ${OBJECTDIR}/_ext/684626063/main.p1 ${OBJECTDIR}/_ext/684626063/motorDrive.p1 ${OBJECTDIR}/_ext/684626063/PS2.p1 ${OBJECTDIR}/_ext/684626063/settings.p1 ${OBJECTDIR}/_ext/684626063/UART.p1 ${OBJECTDIR}/_ext/684626063/USB.p1 ${OBJECTDIR}/_ext/684626063/whiskers.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/684626063/colorSensor.p1.d ${OBJECTDIR}/_ext/684626063/compass.p1.d ${OBJECTDIR}/_ext/684626063/delays.p1.d ${OBJECTDIR}/_ext/684626063/encoders.p1.d ${OBJECTDIR}/_ext/684626063/fft.p1.d ${OBJECTDIR}/_ext/684626063/FONA.p1.d ${OBJECTDIR}/_ext/684626063/I2C.p1.d ${OBJECTDIR}/_ext/684626063/LCD.p1.d ${OBJECTDIR}/_ext/684626063/main.p1.d ${OBJECTDIR}/_ext/684626063/motorDrive.p1.d ${OBJECTDIR}/_ext/684626063/PS2.p1.d ${OBJECTDIR}/_ext/684626063/settings.p1.d ${OBJECTDIR}/_ext/684626063/UART.p1.d ${OBJECTDIR}/_ext/684626063/USB.p1.d ${OBJECTDIR}/_ext/684626063/whiskers.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/684626063/colorSensor.p1 ${OBJECTDIR}/_ext/684626063/compass.p1 ${OBJECTDIR}/_ext/684626063/delays.p1 ${OBJECTDIR}/_ext/684626063/encoders.p1 ${OBJECTDIR}/_ext/684626063/fft.p1 ${OBJECTDIR}/_ext/684626063/FONA.p1 ${OBJECTDIR}/_ext/684626063/I2C.p1 ${OBJECTDIR}/_ext/684626063/LCD.p1 ${OBJECTDIR}/_ext/684626063/main.p1 ${OBJECTDIR}/_ext/684626063/motorDrive.p1 ${OBJECTDIR}/_ext/684626063/PS2.p1 ${OBJECTDIR}/_ext/684626063/settings.p1 ${OBJECTDIR}/_ext/684626063/UART.p1 ${OBJECTDIR}/_ext/684626063/USB.p1 ${OBJECTDIR}/_ext/684626063/whiskers.p1

# Source Files
SOURCEFILES=/Users/broderickcarlin/candleBot/PIC firmware/colorSensor.c /Users/broderickcarlin/candleBot/PIC firmware/compass.c /Users/broderickcarlin/candleBot/PIC firmware/delays.c /Users/broderickcarlin/candleBot/PIC firmware/encoders.c /Users/broderickcarlin/candleBot/PIC firmware/fft.c /Users/broderickcarlin/candleBot/PIC firmware/FONA.c /Users/broderickcarlin/candleBot/PIC firmware/I2C.c /Users/broderickcarlin/candleBot/PIC firmware/LCD.c /Users/broderickcarlin/candleBot/PIC firmware/main.c /Users/broderickcarlin/candleBot/PIC firmware/motorDrive.c /Users/broderickcarlin/candleBot/PIC firmware/PS2.c /Users/broderickcarlin/candleBot/PIC firmware/settings.c /Users/broderickcarlin/candleBot/PIC firmware/UART.c /Users/broderickcarlin/candleBot/PIC firmware/USB.c /Users/broderickcarlin/candleBot/PIC firmware/whiskers.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/finalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F97J94
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/684626063/colorSensor.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/colorSensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/colorSensor.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/colorSensor.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/colorSensor.p1  "/Users/broderickcarlin/candleBot/PIC firmware/colorSensor.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/colorSensor.d ${OBJECTDIR}/_ext/684626063/colorSensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/colorSensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/compass.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/compass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/compass.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/compass.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/compass.p1  "/Users/broderickcarlin/candleBot/PIC firmware/compass.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/compass.d ${OBJECTDIR}/_ext/684626063/compass.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/compass.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/delays.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/delays.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/delays.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/delays.p1  "/Users/broderickcarlin/candleBot/PIC firmware/delays.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/delays.d ${OBJECTDIR}/_ext/684626063/delays.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/delays.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/encoders.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/encoders.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/encoders.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/encoders.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/encoders.p1  "/Users/broderickcarlin/candleBot/PIC firmware/encoders.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/encoders.d ${OBJECTDIR}/_ext/684626063/encoders.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/encoders.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/fft.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/fft.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/fft.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/fft.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/fft.p1  "/Users/broderickcarlin/candleBot/PIC firmware/fft.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/fft.d ${OBJECTDIR}/_ext/684626063/fft.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/fft.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/FONA.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/FONA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/FONA.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/FONA.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/FONA.p1  "/Users/broderickcarlin/candleBot/PIC firmware/FONA.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/FONA.d ${OBJECTDIR}/_ext/684626063/FONA.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/FONA.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/I2C.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/I2C.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/I2C.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/I2C.p1  "/Users/broderickcarlin/candleBot/PIC firmware/I2C.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/I2C.d ${OBJECTDIR}/_ext/684626063/I2C.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/I2C.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/LCD.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/LCD.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/LCD.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/LCD.p1  "/Users/broderickcarlin/candleBot/PIC firmware/LCD.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/LCD.d ${OBJECTDIR}/_ext/684626063/LCD.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/LCD.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/main.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/main.p1  "/Users/broderickcarlin/candleBot/PIC firmware/main.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/main.d ${OBJECTDIR}/_ext/684626063/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/motorDrive.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/motorDrive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/motorDrive.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/motorDrive.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/motorDrive.p1  "/Users/broderickcarlin/candleBot/PIC firmware/motorDrive.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/motorDrive.d ${OBJECTDIR}/_ext/684626063/motorDrive.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/motorDrive.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/PS2.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/PS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/PS2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/PS2.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/PS2.p1  "/Users/broderickcarlin/candleBot/PIC firmware/PS2.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/PS2.d ${OBJECTDIR}/_ext/684626063/PS2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/PS2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/settings.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/settings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/settings.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/settings.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/settings.p1  "/Users/broderickcarlin/candleBot/PIC firmware/settings.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/settings.d ${OBJECTDIR}/_ext/684626063/settings.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/settings.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/UART.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/UART.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/UART.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/UART.p1  "/Users/broderickcarlin/candleBot/PIC firmware/UART.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/UART.d ${OBJECTDIR}/_ext/684626063/UART.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/UART.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/USB.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/USB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/USB.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/USB.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/USB.p1  "/Users/broderickcarlin/candleBot/PIC firmware/USB.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/USB.d ${OBJECTDIR}/_ext/684626063/USB.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/USB.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/whiskers.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/whiskers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/whiskers.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/whiskers.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/whiskers.p1  "/Users/broderickcarlin/candleBot/PIC firmware/whiskers.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/whiskers.d ${OBJECTDIR}/_ext/684626063/whiskers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/whiskers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/684626063/colorSensor.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/colorSensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/colorSensor.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/colorSensor.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/colorSensor.p1  "/Users/broderickcarlin/candleBot/PIC firmware/colorSensor.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/colorSensor.d ${OBJECTDIR}/_ext/684626063/colorSensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/colorSensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/compass.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/compass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/compass.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/compass.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/compass.p1  "/Users/broderickcarlin/candleBot/PIC firmware/compass.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/compass.d ${OBJECTDIR}/_ext/684626063/compass.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/compass.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/delays.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/delays.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/delays.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/delays.p1  "/Users/broderickcarlin/candleBot/PIC firmware/delays.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/delays.d ${OBJECTDIR}/_ext/684626063/delays.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/delays.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/encoders.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/encoders.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/encoders.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/encoders.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/encoders.p1  "/Users/broderickcarlin/candleBot/PIC firmware/encoders.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/encoders.d ${OBJECTDIR}/_ext/684626063/encoders.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/encoders.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/fft.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/fft.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/fft.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/fft.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/fft.p1  "/Users/broderickcarlin/candleBot/PIC firmware/fft.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/fft.d ${OBJECTDIR}/_ext/684626063/fft.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/fft.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/FONA.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/FONA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/FONA.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/FONA.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/FONA.p1  "/Users/broderickcarlin/candleBot/PIC firmware/FONA.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/FONA.d ${OBJECTDIR}/_ext/684626063/FONA.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/FONA.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/I2C.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/I2C.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/I2C.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/I2C.p1  "/Users/broderickcarlin/candleBot/PIC firmware/I2C.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/I2C.d ${OBJECTDIR}/_ext/684626063/I2C.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/I2C.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/LCD.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/LCD.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/LCD.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/LCD.p1  "/Users/broderickcarlin/candleBot/PIC firmware/LCD.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/LCD.d ${OBJECTDIR}/_ext/684626063/LCD.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/LCD.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/main.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/main.p1  "/Users/broderickcarlin/candleBot/PIC firmware/main.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/main.d ${OBJECTDIR}/_ext/684626063/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/motorDrive.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/motorDrive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/motorDrive.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/motorDrive.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/motorDrive.p1  "/Users/broderickcarlin/candleBot/PIC firmware/motorDrive.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/motorDrive.d ${OBJECTDIR}/_ext/684626063/motorDrive.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/motorDrive.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/PS2.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/PS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/PS2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/PS2.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/PS2.p1  "/Users/broderickcarlin/candleBot/PIC firmware/PS2.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/PS2.d ${OBJECTDIR}/_ext/684626063/PS2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/PS2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/settings.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/settings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/settings.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/settings.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/settings.p1  "/Users/broderickcarlin/candleBot/PIC firmware/settings.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/settings.d ${OBJECTDIR}/_ext/684626063/settings.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/settings.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/UART.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/UART.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/UART.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/UART.p1  "/Users/broderickcarlin/candleBot/PIC firmware/UART.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/UART.d ${OBJECTDIR}/_ext/684626063/UART.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/UART.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/USB.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/USB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/USB.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/USB.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/USB.p1  "/Users/broderickcarlin/candleBot/PIC firmware/USB.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/USB.d ${OBJECTDIR}/_ext/684626063/USB.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/USB.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/684626063/whiskers.p1: /Users/broderickcarlin/candleBot/PIC\ firmware/whiskers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/684626063" 
	@${RM} ${OBJECTDIR}/_ext/684626063/whiskers.p1.d 
	@${RM} ${OBJECTDIR}/_ext/684626063/whiskers.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/684626063/whiskers.p1  "/Users/broderickcarlin/candleBot/PIC firmware/whiskers.c" 
	@-${MV} ${OBJECTDIR}/_ext/684626063/whiskers.d ${OBJECTDIR}/_ext/684626063/whiskers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/684626063/whiskers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/finalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/finalProject.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        -odist/${CND_CONF}/${IMAGE_TYPE}/finalProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/finalProject.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/finalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/finalProject.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -odist/${CND_CONF}/${IMAGE_TYPE}/finalProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
