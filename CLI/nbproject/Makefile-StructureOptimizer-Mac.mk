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
CND_CONF=StructureOptimizer-Mac
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/acyclic_selection.o \
	${OBJECTDIR}/bayesian_network.o \
	${OBJECTDIR}/dfs_initializer.o \
	${OBJECTDIR}/fas_initializer.o \
	${OBJECTDIR}/greedy_search.o \
	${OBJECTDIR}/main_structure.o \
	${OBJECTDIR}/permutation_set.o \
	${OBJECTDIR}/random_initializer.o \
	${OBJECTDIR}/score_cache.o \
	${OBJECTDIR}/sparse_parent_bitwise.o \
	${OBJECTDIR}/sparse_parent_list.o \
	${OBJECTDIR}/sparse_parent_tree.o \
	${OBJECTDIR}/weighted_path_initializer.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_structure

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_structure: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_structure ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/acyclic_selection.o: acyclic_selection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/acyclic_selection.o acyclic_selection.cpp

${OBJECTDIR}/bayesian_network.o: bayesian_network.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bayesian_network.o bayesian_network.cpp

${OBJECTDIR}/dfs_initializer.o: dfs_initializer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dfs_initializer.o dfs_initializer.cpp

${OBJECTDIR}/fas_initializer.o: fas_initializer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fas_initializer.o fas_initializer.cpp

${OBJECTDIR}/greedy_search.o: greedy_search.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/greedy_search.o greedy_search.cpp

${OBJECTDIR}/main_structure.o: main_structure.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_structure.o main_structure.cpp

${OBJECTDIR}/permutation_set.o: permutation_set.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/permutation_set.o permutation_set.cpp

${OBJECTDIR}/random_initializer.o: random_initializer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/random_initializer.o random_initializer.cpp

${OBJECTDIR}/score_cache.o: score_cache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/score_cache.o score_cache.cpp

${OBJECTDIR}/sparse_parent_bitwise.o: sparse_parent_bitwise.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sparse_parent_bitwise.o sparse_parent_bitwise.cpp

${OBJECTDIR}/sparse_parent_list.o: sparse_parent_list.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sparse_parent_list.o sparse_parent_list.cpp

${OBJECTDIR}/sparse_parent_tree.o: sparse_parent_tree.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sparse_parent_tree.o sparse_parent_tree.cpp

${OBJECTDIR}/weighted_path_initializer.o: weighted_path_initializer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/weighted_path_initializer.o weighted_path_initializer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_structure

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
