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
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=ScoreCalculator-Mac
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/acyclic_selection.o \
	${OBJECTDIR}/ad_node.o \
	${OBJECTDIR}/ad_tree.o \
	${OBJECTDIR}/bayesian_network.o \
	${OBJECTDIR}/bic_scoring_function.o \
	${OBJECTDIR}/greedy_selection.o \
	${OBJECTDIR}/independence_selection.o \
	${OBJECTDIR}/log_likelihood_calculator.o \
	${OBJECTDIR}/main_scores.o \
	${OBJECTDIR}/parent_set_selection.o \
	${OBJECTDIR}/score_cache.o \
	${OBJECTDIR}/sequential_selection.o \
	${OBJECTDIR}/vary_node.o


# C Compiler Flags
CFLAGS=-march=native

# CC Compiler Flags
CCFLAGS=-std=c++0x -march=native
CXXFLAGS=-std=c++0x -march=native

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/lib -lboost_system -lboost_thread-mt -lboost_chrono -lboost_timer -lboost_program_options -lboost_container -lboost_serialization

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_scorer

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_scorer: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_scorer ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/acyclic_selection.o: acyclic_selection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/acyclic_selection.o acyclic_selection.cpp

${OBJECTDIR}/ad_node.o: ad_node.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ad_node.o ad_node.cpp

${OBJECTDIR}/ad_tree.o: ad_tree.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ad_tree.o ad_tree.cpp

${OBJECTDIR}/bayesian_network.o: bayesian_network.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bayesian_network.o bayesian_network.cpp

${OBJECTDIR}/bic_scoring_function.o: bic_scoring_function.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bic_scoring_function.o bic_scoring_function.cpp

${OBJECTDIR}/greedy_selection.o: greedy_selection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/greedy_selection.o greedy_selection.cpp

${OBJECTDIR}/independence_selection.o: independence_selection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/independence_selection.o independence_selection.cpp

${OBJECTDIR}/log_likelihood_calculator.o: log_likelihood_calculator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/log_likelihood_calculator.o log_likelihood_calculator.cpp

${OBJECTDIR}/main_scores.o: main_scores.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_scores.o main_scores.cpp

${OBJECTDIR}/parent_set_selection.o: parent_set_selection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parent_set_selection.o parent_set_selection.cpp

${OBJECTDIR}/score_cache.o: score_cache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/score_cache.o score_cache.cpp

${OBJECTDIR}/sequential_selection.o: sequential_selection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sequential_selection.o sequential_selection.cpp

${OBJECTDIR}/vary_node.o: vary_node.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vary_node.o vary_node.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_scorer

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
