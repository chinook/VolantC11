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
FINAL_IMAGE=${DISTDIR}/Volant.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Volant.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=source/Interrupts.c source/Setup.c source/StateFunctions.c source/StateMachine_Volant.c source/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/source/Interrupts.o ${OBJECTDIR}/source/Setup.o ${OBJECTDIR}/source/StateFunctions.o ${OBJECTDIR}/source/StateMachine_Volant.o ${OBJECTDIR}/source/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/source/Interrupts.o.d ${OBJECTDIR}/source/Setup.o.d ${OBJECTDIR}/source/StateFunctions.o.d ${OBJECTDIR}/source/StateMachine_Volant.o.d ${OBJECTDIR}/source/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/source/Interrupts.o ${OBJECTDIR}/source/Setup.o ${OBJECTDIR}/source/StateFunctions.o ${OBJECTDIR}/source/StateMachine_Volant.o ${OBJECTDIR}/source/main.o

# Source Files
SOURCEFILES=source/Interrupts.c source/Setup.c source/StateFunctions.c source/StateMachine_Volant.c source/main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Volant.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/source/Interrupts.o: source/Interrupts.c  .generated_files/flags/default/11d67208e5f301216f20c684f58559c31e395d0c .generated_files/flags/default/778d9843b01a3d0cabe515e69a3d738216c1758e
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/Interrupts.o.d 
	@${RM} ${OBJECTDIR}/source/Interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"headers" -I"../../ChinookLib/ChinookLib.X/headers" -MP -MMD -MF "${OBJECTDIR}/source/Interrupts.o.d" -o ${OBJECTDIR}/source/Interrupts.o source/Interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/source/Setup.o: source/Setup.c  .generated_files/flags/default/431ded605316f8a22464102c7bb0de08ff3c8956 .generated_files/flags/default/778d9843b01a3d0cabe515e69a3d738216c1758e
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/Setup.o.d 
	@${RM} ${OBJECTDIR}/source/Setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"headers" -I"../../ChinookLib/ChinookLib.X/headers" -MP -MMD -MF "${OBJECTDIR}/source/Setup.o.d" -o ${OBJECTDIR}/source/Setup.o source/Setup.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/source/StateFunctions.o: source/StateFunctions.c  .generated_files/flags/default/9e918b8e5f6241b5c97a89953e589a801c4e6c4f .generated_files/flags/default/778d9843b01a3d0cabe515e69a3d738216c1758e
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/StateFunctions.o.d 
	@${RM} ${OBJECTDIR}/source/StateFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"headers" -I"../../ChinookLib/ChinookLib.X/headers" -MP -MMD -MF "${OBJECTDIR}/source/StateFunctions.o.d" -o ${OBJECTDIR}/source/StateFunctions.o source/StateFunctions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/source/StateMachine_Volant.o: source/StateMachine_Volant.c  .generated_files/flags/default/d8143e9c53d0b25473918101648f86275cb13184 .generated_files/flags/default/778d9843b01a3d0cabe515e69a3d738216c1758e
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/StateMachine_Volant.o.d 
	@${RM} ${OBJECTDIR}/source/StateMachine_Volant.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"headers" -I"../../ChinookLib/ChinookLib.X/headers" -MP -MMD -MF "${OBJECTDIR}/source/StateMachine_Volant.o.d" -o ${OBJECTDIR}/source/StateMachine_Volant.o source/StateMachine_Volant.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/source/main.o: source/main.c  .generated_files/flags/default/62289834747d2367c677e76f68a92799eb6c9141 .generated_files/flags/default/778d9843b01a3d0cabe515e69a3d738216c1758e
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/main.o.d 
	@${RM} ${OBJECTDIR}/source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"headers" -I"../../ChinookLib/ChinookLib.X/headers" -MP -MMD -MF "${OBJECTDIR}/source/main.o.d" -o ${OBJECTDIR}/source/main.o source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/source/Interrupts.o: source/Interrupts.c  .generated_files/flags/default/2e5f31a2ba03041bd900b207c5299cb044070444 .generated_files/flags/default/778d9843b01a3d0cabe515e69a3d738216c1758e
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/Interrupts.o.d 
	@${RM} ${OBJECTDIR}/source/Interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"headers" -I"../../ChinookLib/ChinookLib.X/headers" -MP -MMD -MF "${OBJECTDIR}/source/Interrupts.o.d" -o ${OBJECTDIR}/source/Interrupts.o source/Interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/source/Setup.o: source/Setup.c  .generated_files/flags/default/17316bba25a871ddaa7f921bac784b65730f5368 .generated_files/flags/default/778d9843b01a3d0cabe515e69a3d738216c1758e
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/Setup.o.d 
	@${RM} ${OBJECTDIR}/source/Setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"headers" -I"../../ChinookLib/ChinookLib.X/headers" -MP -MMD -MF "${OBJECTDIR}/source/Setup.o.d" -o ${OBJECTDIR}/source/Setup.o source/Setup.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/source/StateFunctions.o: source/StateFunctions.c  .generated_files/flags/default/dfa67c441da92cf8153fe4bc5920edb4c027c695 .generated_files/flags/default/778d9843b01a3d0cabe515e69a3d738216c1758e
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/StateFunctions.o.d 
	@${RM} ${OBJECTDIR}/source/StateFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"headers" -I"../../ChinookLib/ChinookLib.X/headers" -MP -MMD -MF "${OBJECTDIR}/source/StateFunctions.o.d" -o ${OBJECTDIR}/source/StateFunctions.o source/StateFunctions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/source/StateMachine_Volant.o: source/StateMachine_Volant.c  .generated_files/flags/default/2418f2a11f98ba0c8bd4a9e4d00314d5ba2b4fd3 .generated_files/flags/default/778d9843b01a3d0cabe515e69a3d738216c1758e
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/StateMachine_Volant.o.d 
	@${RM} ${OBJECTDIR}/source/StateMachine_Volant.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"headers" -I"../../ChinookLib/ChinookLib.X/headers" -MP -MMD -MF "${OBJECTDIR}/source/StateMachine_Volant.o.d" -o ${OBJECTDIR}/source/StateMachine_Volant.o source/StateMachine_Volant.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/source/main.o: source/main.c  .generated_files/flags/default/f02dbc7d57637c26d288d621c5d5b720106b87bb .generated_files/flags/default/778d9843b01a3d0cabe515e69a3d738216c1758e
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/main.o.d 
	@${RM} ${OBJECTDIR}/source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"headers" -I"../../ChinookLib/ChinookLib.X/headers" -MP -MMD -MF "${OBJECTDIR}/source/main.o.d" -o ${OBJECTDIR}/source/main.o source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Volant.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../ChinookLib/ChinookLib.X/dist/default/debug/ChinookLib.X.a  
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Volant.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ../../ChinookLib/ChinookLib.X/dist/default/debug/ChinookLib.X.a      -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml,--allow-multiple-definition 
	
else
${DISTDIR}/Volant.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../ChinookLib/ChinookLib.X/dist/default/production/ChinookLib.X.a 
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Volant.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ../../ChinookLib/ChinookLib.X/dist/default/production/ChinookLib.X.a      -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml,--allow-multiple-definition 
	${MP_CC_DIR}/xc32-bin2hex ${DISTDIR}/Volant.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:
	cd ../../ChinookLib/ChinookLib.X && ${MAKE}  -f Makefile CONF=default


# Subprojects
.clean-subprojects:
	cd ../../ChinookLib/ChinookLib.X && rm -rf "build/default" "dist/default"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
