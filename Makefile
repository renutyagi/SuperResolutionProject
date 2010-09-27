# Super Resolution Project makefile 

SRCDIR		= src
BINDIR		= bin
OBJDIR		= obj
TESTDIR		= test

CXX			= g++
CXXFLAGS	= -O -I/usr/local/include/opencv/ 
SUFFIXES 	+= .d

PROGRAM = $(BINDIR)/superresolution

#We don't need to clean up when we're making these targets
NODEPS		:= clean tags svn

#Find all the C++ files in the src/ directory
SOURCES		:=$(shell find $(SRCDIR)/ -name "*.cpp")

#These are the dependency files, which make will clean up after it creates them
DEPFILES	:=$(patsubst %.cpp,%.d,$(SOURCES))

.PHONY: all
all: $(PROGRAM)

$(PROGRAM): $(patsubst %.cpp,%.o,$(SOURCES))
	$(CXX) -o $@ $^  -lcxcore -lcv -lcvaux -lhighgui -lml

-include $(DEPFILES)

#This is the rule for creating the dependency files
$(SRCDIR)/%.d: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MM -MT '$(patsubst %.cpp,%.o,$<)' $< > $@ 

.PHONY: clean
clean:
	@rm -rf $(SRCDIR)/*.o
	@rm -rf $(SRCDIR)/*.d
	@rm -rf $(BINDIR)/* 
	@rm -rf $(OBJDIR)/*

