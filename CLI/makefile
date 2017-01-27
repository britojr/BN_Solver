# simple makefile for build and test on linux

# Object Directory
OBJDIR := obj
# Executable Directory
DISTDIR := exec

# Test Directory
TESTDIR=$(OBJDIR)/tests
# Test Object Files Directory
OBJTESTDIR=$(TESTDIR)/obj
# Test Executables Directory
EXECTESTDIR= $(TESTDIR)/exec
# Executable test files
TESTEXECFILES := $(addprefix $(EXECTESTDIR)/, $(basename $(notdir $(wildcard tests/*.cpp))))
# Test Object Files
TESTOBJECTFILES := $(addprefix $(OBJTESTDIR)/, $(patsubst %.cpp,%.o,$(notdir $(wildcard tests/*.cpp))))

# Object Files
OBJECTFILES := $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o,$(wildcard *.cpp)))
# No Main Object Files
NOMOBJFILES := $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%_nomain.o,$(wildcard *.cpp)))

# Link Libraries and Options
LDLIBSOPTIONS := -L/usr/local/lib -lboost_system -lboost_thread -lboost_chrono \
	-lboost_timer -lboost_program_options -lboost_serialization

# Libraries for Unity Tests
LDTESTLIB := -lboost_unit_test_framework

# Includes
INCLUDES := -I/usr/local/include -I/usr/include
INCLSRC := -I../CLI

# Build executable
build: $(DISTDIR)/bn_learning

# Link Executable (Main)
$(DISTDIR)/bn_learning: $(OBJECTFILES) | $(DISTDIR)
	g++ -o $(DISTDIR)/bn_learning $(OBJECTFILES) $(LDLIBSOPTIONS)

# Compile all source
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	g++ -std=c++0x -march=native -c -O3 -s $(INCLUDES) -MMD -MP -MF "$@.d" -o $@ $(patsubst %.o, %.cpp, $(notdir $@))

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(DISTDIR):
	mkdir -p $(DISTDIR)

# Build all the test files
build-tests: build $(TESTEXECFILES)

# Link Executable tests
#~ $(EXECTESTDIR)/%_test: $(OBJTESTDIR)/%_test.o $(NOMOBJFILES) | $(EXECTESTDIR)
#~ $(EXECTESTDIR)/bn_structure_test: $(OBJTESTDIR)/bn_structure_test.o $(NOMOBJFILES) | $(EXECTESTDIR)
$(EXECTESTDIR)/%_test: $(OBJTESTDIR)/%_test.o $(NOMOBJFILES) | $(EXECTESTDIR)
	g++ -o $@ $^ $(LDLIBSOPTIONS) $(LDTESTLIB)

$(EXECTESTDIR):
	mkdir -p $(EXECTESTDIR)

# Compile all test source
$(OBJTESTDIR)/%_test.o: tests/%_test.cpp | $(OBJTESTDIR)
	g++ -std=c++0x -march=native -c -O3 -s $(INCLUDES) $(INCLSRC) -MMD -MP -MF "$@.d" -o $@ $(addprefix tests/, $(patsubst %.o, %.cpp, $(notdir $@)))

$(OBJTESTDIR):
	mkdir -p $(OBJTESTDIR)

# Create nomain object files
$(OBJDIR)/%_nomain.o: $(OBJDIR)/%.o %.cpp | $(OBJDIR)
	@NMOUTPUT=`nm $(patsubst %_nomain.o, %.o, $@)`; \
	if (echo "$$NMOUTPUT" | grep '|main$$') || \
	   (echo "$$NMOUTPUT" | grep 'T main$$') || \
	   (echo "$$NMOUTPUT" | grep 'T _main$$'); \
	then  \
	    rm -f "$@.d";\
	    g++ -std=c++0x -march=native -c -O3 -s $(INCLUDES) -Dmain=__nomain -MMD -MP -MF "$@.d" -o $@ $(patsubst %_nomain.o, %.cpp, $(notdir $@));\
	else  \
	    cp $(patsubst %_nomain.o, %.o, $@) $@;\
	fi

# Run tests
test: build-tests
	@if [ "$(TEST)" = "" ]; \
	then  \
	    $(EXECTESTDIR)/* || true; \
	else  \
	    ./$(EXECTESTDIR)/$(TEST) || true; \
	fi

# Clean compiled files
clean-obj:
	rm -rf $(OBJDIR)/*

clean-dist:
	rm -rf $(DISTDIR)/bn_learning

clean-test:
	rm -rf $(TESTDIR)/*
	rm -rf $(OBJDIR)/*_nomain.o
	rm -rf $(OBJDIR)/*_nomain.o.d

clean: clean-test clean-dist clean-obj
	rm -rf *.h.gch
