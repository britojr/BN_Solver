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
CND_CONF=Release-Linux
CND_DISTDIR=dist
CND_BUILDDIR=build

# Directories
INCLUDE_DIR=/opt/apps/programas/gnu/old_boost.1.58.0/include
LIBRARY_DIR=/opt/apps/programas/gnu/old_boost.1.58.0/lib/

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ad_node.o \
	${OBJECTDIR}/ad_tree.o \
	${OBJECTDIR}/bayesian_network.o \
	${OBJECTDIR}/bic_scoring_function.o \
	${OBJECTDIR}/dfs_2.o \
	${OBJECTDIR}/dfs_3.o \
	${OBJECTDIR}/dfs_4.o \
	${OBJECTDIR}/dfs_initializer.o \
	${OBJECTDIR}/fas_initializer.o \
	${OBJECTDIR}/greedy_search.o \
	${OBJECTDIR}/greedy_selection.o \
	${OBJECTDIR}/independence_selection.o \
	${OBJECTDIR}/log_likelihood_calculator.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/parent_set_selection.o \
	${OBJECTDIR}/permutation_set.o \
	${OBJECTDIR}/random_initializer.o \
	${OBJECTDIR}/score_cache.o \
	${OBJECTDIR}/sequential_selection.o \
	${OBJECTDIR}/sparse_parent_bitwise.o \
	${OBJECTDIR}/sparse_parent_list.o \
	${OBJECTDIR}/sparse_parent_tree.o \
	${OBJECTDIR}/vary_node.o \
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
LDLIBSOPTIONS=-L${LIBRARY_DIR} -lboost_system -lboost_thread-mt -lboost_chrono -lboost_timer -lboost_program_options -lboost_container -lboost_serialization

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_learning

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_learning: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_learning ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/ad_node.o: ad_node.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ad_node.o ad_node.cpp

${OBJECTDIR}/ad_tree.o: ad_tree.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ad_tree.o ad_tree.cpp

${OBJECTDIR}/bayesian_network.o: bayesian_network.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bayesian_network.o bayesian_network.cpp

${OBJECTDIR}/bic_scoring_function.o: bic_scoring_function.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bic_scoring_function.o bic_scoring_function.cpp

${OBJECTDIR}/dfs_2.o: dfs_2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dfs_2.o dfs_2.cpp

${OBJECTDIR}/dfs_3.o: dfs_3.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dfs_3.o dfs_3.cpp

${OBJECTDIR}/dfs_4.o: dfs_4.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dfs_4.o dfs_4.cpp

${OBJECTDIR}/dfs_initializer.o: dfs_initializer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dfs_initializer.o dfs_initializer.cpp

${OBJECTDIR}/fas_initializer.o: fas_initializer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fas_initializer.o fas_initializer.cpp

${OBJECTDIR}/greedy_search.o: greedy_search.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/greedy_search.o greedy_search.cpp

${OBJECTDIR}/greedy_selection.o: greedy_selection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/greedy_selection.o greedy_selection.cpp

${OBJECTDIR}/independence_selection.o: independence_selection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/independence_selection.o independence_selection.cpp

${OBJECTDIR}/log_likelihood_calculator.o: log_likelihood_calculator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/log_likelihood_calculator.o log_likelihood_calculator.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/parent_set_selection.o: parent_set_selection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parent_set_selection.o parent_set_selection.cpp

${OBJECTDIR}/permutation_set.o: permutation_set.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/permutation_set.o permutation_set.cpp

${OBJECTDIR}/random_initializer.o: random_initializer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/random_initializer.o random_initializer.cpp

${OBJECTDIR}/score_cache.o: score_cache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/score_cache.o score_cache.cpp

${OBJECTDIR}/sequential_selection.o: sequential_selection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sequential_selection.o sequential_selection.cpp

${OBJECTDIR}/sparse_parent_bitwise.o: sparse_parent_bitwise.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sparse_parent_bitwise.o sparse_parent_bitwise.cpp

${OBJECTDIR}/sparse_parent_list.o: sparse_parent_list.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sparse_parent_list.o sparse_parent_list.cpp

${OBJECTDIR}/sparse_parent_tree.o: sparse_parent_tree.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sparse_parent_tree.o sparse_parent_tree.cpp

${OBJECTDIR}/vary_node.o: vary_node.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vary_node.o vary_node.cpp

${OBJECTDIR}/weighted_path_initializer.o: weighted_path_initializer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I${INCLUDE_DIR} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/weighted_path_initializer.o weighted_path_initializer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bn_learning

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
