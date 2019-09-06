#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/SiM/include/artemis/extractor/DiscreteCosineTransformation.o \
	${OBJECTDIR}/SiM/include/artemis/extractor/EdgeHistogram.o \
	${OBJECTDIR}/SiM/include/artemis/extractor/HMMDColorSystem.o \
	${OBJECTDIR}/SiM/include/artemis/extractor/HSVColorSystem.o \
	${OBJECTDIR}/SiM/include/artemis/extractor/HaralickFeature.o \
	${OBJECTDIR}/SiM/include/artemis/extractor/SRGBColorSystem.o \
	${OBJECTDIR}/SiM/include/artemis/extractor/XYZColorSystem.o \
	${OBJECTDIR}/SiM/include/artemis/extractor/YCrCbColorSystem.o \
	${OBJECTDIR}/SiM/include/artemis/image/ImageBase.o \
	${OBJECTDIR}/SiM/include/artemis/image/Pixel.o \
	${OBJECTDIR}/SiM/include/artemis/image/bmp/BmpLib.o \
	${OBJECTDIR}/SiM/include/artemis/image/jpg/JpgLib.o \
	${OBJECTDIR}/SiM/include/artemis/image/krl/FileHandler.o \
	${OBJECTDIR}/SiM/include/artemis/image/krl/KrlLib.o \
	${OBJECTDIR}/SiM/include/artemis/image/png/PngLib.o \
	${OBJECTDIR}/detector/NBClassifier.o \
	${OBJECTDIR}/detector/Slic.o \
	${OBJECTDIR}/detector/SmokeBlockClassifier.o \
	${OBJECTDIR}/detector/SmokeBlockResult.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nsmokeblock

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nsmokeblock: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nsmokeblock ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/SiM/include/artemis/extractor/DiscreteCosineTransformation.o: SiM/include/artemis/extractor/DiscreteCosineTransformation.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/extractor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/extractor/DiscreteCosineTransformation.o SiM/include/artemis/extractor/DiscreteCosineTransformation.cpp

${OBJECTDIR}/SiM/include/artemis/extractor/EdgeHistogram.o: SiM/include/artemis/extractor/EdgeHistogram.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/extractor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/extractor/EdgeHistogram.o SiM/include/artemis/extractor/EdgeHistogram.cpp

${OBJECTDIR}/SiM/include/artemis/extractor/HMMDColorSystem.o: SiM/include/artemis/extractor/HMMDColorSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/extractor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/extractor/HMMDColorSystem.o SiM/include/artemis/extractor/HMMDColorSystem.cpp

${OBJECTDIR}/SiM/include/artemis/extractor/HSVColorSystem.o: SiM/include/artemis/extractor/HSVColorSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/extractor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/extractor/HSVColorSystem.o SiM/include/artemis/extractor/HSVColorSystem.cpp

${OBJECTDIR}/SiM/include/artemis/extractor/HaralickFeature.o: SiM/include/artemis/extractor/HaralickFeature.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/extractor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/extractor/HaralickFeature.o SiM/include/artemis/extractor/HaralickFeature.cpp

${OBJECTDIR}/SiM/include/artemis/extractor/SRGBColorSystem.o: SiM/include/artemis/extractor/SRGBColorSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/extractor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/extractor/SRGBColorSystem.o SiM/include/artemis/extractor/SRGBColorSystem.cpp

${OBJECTDIR}/SiM/include/artemis/extractor/XYZColorSystem.o: SiM/include/artemis/extractor/XYZColorSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/extractor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/extractor/XYZColorSystem.o SiM/include/artemis/extractor/XYZColorSystem.cpp

${OBJECTDIR}/SiM/include/artemis/extractor/YCrCbColorSystem.o: SiM/include/artemis/extractor/YCrCbColorSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/extractor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/extractor/YCrCbColorSystem.o SiM/include/artemis/extractor/YCrCbColorSystem.cpp

${OBJECTDIR}/SiM/include/artemis/image/ImageBase.o: SiM/include/artemis/image/ImageBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/image
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/image/ImageBase.o SiM/include/artemis/image/ImageBase.cpp

${OBJECTDIR}/SiM/include/artemis/image/Pixel.o: SiM/include/artemis/image/Pixel.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/image
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/image/Pixel.o SiM/include/artemis/image/Pixel.cpp

${OBJECTDIR}/SiM/include/artemis/image/bmp/BmpLib.o: SiM/include/artemis/image/bmp/BmpLib.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/image/bmp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/image/bmp/BmpLib.o SiM/include/artemis/image/bmp/BmpLib.cpp

${OBJECTDIR}/SiM/include/artemis/image/jpg/JpgLib.o: SiM/include/artemis/image/jpg/JpgLib.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/image/jpg
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/image/jpg/JpgLib.o SiM/include/artemis/image/jpg/JpgLib.cpp

${OBJECTDIR}/SiM/include/artemis/image/krl/FileHandler.o: SiM/include/artemis/image/krl/FileHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/image/krl
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/image/krl/FileHandler.o SiM/include/artemis/image/krl/FileHandler.cpp

${OBJECTDIR}/SiM/include/artemis/image/krl/KrlLib.o: SiM/include/artemis/image/krl/KrlLib.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/image/krl
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/image/krl/KrlLib.o SiM/include/artemis/image/krl/KrlLib.cpp

${OBJECTDIR}/SiM/include/artemis/image/png/PngLib.o: SiM/include/artemis/image/png/PngLib.cpp 
	${MKDIR} -p ${OBJECTDIR}/SiM/include/artemis/image/png
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SiM/include/artemis/image/png/PngLib.o SiM/include/artemis/image/png/PngLib.cpp

${OBJECTDIR}/detector/NBClassifier.o: detector/NBClassifier.cpp 
	${MKDIR} -p ${OBJECTDIR}/detector
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/detector/NBClassifier.o detector/NBClassifier.cpp

${OBJECTDIR}/detector/Slic.o: detector/Slic.cpp 
	${MKDIR} -p ${OBJECTDIR}/detector
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/detector/Slic.o detector/Slic.cpp

${OBJECTDIR}/detector/SmokeBlockClassifier.o: detector/SmokeBlockClassifier.cpp 
	${MKDIR} -p ${OBJECTDIR}/detector
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/detector/SmokeBlockClassifier.o detector/SmokeBlockClassifier.cpp

${OBJECTDIR}/detector/SmokeBlockResult.o: detector/SmokeBlockResult.cpp 
	${MKDIR} -p ${OBJECTDIR}/detector
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/detector/SmokeBlockResult.o detector/SmokeBlockResult.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nsmokeblock

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
