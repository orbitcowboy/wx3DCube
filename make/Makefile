#***********************************************************************
#* Description:                                                        *
#* ------------                                                        *
#* $Rev: 508 $     Revision of last commit                             *
#* $Author: ettl $  Author of last commit                              *
#* $Date: 2014-03-06 15:03:17 +0100 (Thu, 06 Mar 2014) $               *
#*                                                                     *
#* Tested on Ubuntu Linux and Raspberry Pi (Raspbian)       		   *
#* Makefile to compile and build programs.               			   *
#*                                                                     *
#* Usage and basic features:                                           *
#*                                                                     *
#*  - make build  [creates the whole project]                          *
#*  - make clean  [removes all object and binary files]                *
#*  - make depend [detects header dependencies]                        *
#*  - make style  [formates the source, based on artistic style]       *
#*                                                                     *
#***********************************************************************

# Folder definitions
SRC_DIR				= ../src
SRC_EXT_DIR         = ../srcext
SRC_TEST            = ../src-test
OBJ_DIR				= ../obj
MAKE_DIR 			= ../make
BIN_DIR 			= ../bin
CONFIG_DIR			= ../config
ICON_DIR			= $(SRC_DIR)/image
APP_NAME			= wx3DCube
TRUTH_TABLE_GEN_PATH= $(SRC_EXT_DIR)/truth_table_generator
EXPRTK_DIR 		    = $(SRC_EXT_DIR)/exprtk
TREE_MULTICTRL_PATH = $(SRC_EXT_DIR)/wxTreeMultiCtrl
STRING_UTIL_PATH    = $(SRC_EXT_DIR)/simple_string_util
TOKENIZE_PATH    	= $(SRC_EXT_DIR)/simple_tokenize
STL_UTIL_PATH    	= $(SRC_EXT_DIR)/simple_stl_util
# ----------------------------------------------------------------------
# Determine the number cores of the machine, where the makefile is 
# executed. This sets the -j option (from make), to speedup the 
# build process of 'large' projects.  
NPROCS=1
OS_TYPE:=$(shell uname -s)
OS_NAME:=$(shell uname -n)
ifeq ($(OS_TYPE),Linux)
	ifneq ($(OS_NAME),raspberrypi)
		NPROCS_TMP:=$(shell grep -c ^processor /proc/cpuinfo) 
		ifneq ($(NPROCS_TMP),0)
			NPROCS:=$(NPROCS_TMP)
		endif
	endif
endif

# ----------------------------------------------------------------------
# Configure wxWidgets build
WXVERSION = 3.1
WXCONFIG_CALL = `wx-config --cxxflags --unicode=yes --version=$(WXVERSION)`
WXCONFIG_LINKER_CALL = `wx-config --version=$(WXVERSION) --libs adv,aui,core,base,html,richtext,xml`

# ----------------------------------------------------------------------
# Activate all sanitizers at once, use SAN=yes
ifdef SAN
	ASAN=yes
	USAN=yes
	ifeq (,$(findstring $(CXX),clang++)) # clang specific checks
       ISAN=yes
    endif 
endif 
# To compile with the address sanitizer, use the option ASAN=yes
ifdef ASAN
	SANITIZE=-fsanitize=address 
endif 
# To compile with the undefined sanitizer, use the option  USAN=yes
ifdef USAN
	SANITIZE+=-fsanitize=undefined 
endif
# To compile with the integer sanitizer, use the option ISAN=yes
ifdef ISAN
	SANITIZE+=-fsanitize=integer
endif
# To compile with the memory sanitizer, use the option MSAN=yes
# In order to get detailed stack traces with line numbers, please make sure the llvm-symbolizer is set properly.
# For example: 
#  $ export MSAN_SYMBOLIZER_PATH=/home/martin/compiler/clang+llvm-3.6.0-rc2-x86_64-linux-gnu/bin/llvm-symbolizer 
ifdef MSAN
	SANITIZE+=-fsanitize=memory -fsanitize-memory-track-origins=2 -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif
# ----------------------------------------------------------------------
# C++ compiler settings:
CXX 		= clang++
CXX_INCLUDE	= -I$(SRC_DIR) -I$(SRC_EXT_DIR) -I$(SRC_TEST) -I$(ICON_DIR) -I$(TRUTH_TABLE_GEN_PATH) -I$(EXPRTK_DIR) -I$(STRING_UTIL_PATH) -I$(TREE_MULTICTRL_PATH) -I$(TOKENIZE_PATH) -I$(STL_UTIL_PATH)
CXX_OPT		= #-O3
CXX_DEBUG	= $(SANITIZE)
CXX_WFLAGS	= -Wno-write-strings #-W -Wall -Wunused -Wshadow -Wconversion -Wsign-conversion\
			  -Wextra -ansi -pedantic -Wno-write-strings -fno-strict-aliasing 
CXXFLAGS 	= $(WXCONFIG_CALL) $(CXX_WFLAGS) $(CXX_DEBUG) $(CXX_INCLUDE) $(CXX_OPT)
CXX_CALL    = $(CXX) -c $(CXXFLAGS) -o $@ $< 

# ----------------------------------------------------------------------
# C compiler settings:
CC	        = gcc
CC_INCLUDE  = 
CC_DEBUG	= $(SANITIZE)
CC_OPT      = -O3
CC_WFLAGS   = -W -Wall -Wunused -Wextra -Wconversion -ansi -pedantic
CFLAGS 	    = $(WXCONFIG_CALL) -I$(CC_INCLUDE) $(CC_OPT) $(CC_WFLAGS)
CC_CALL     = $(CC) -c $(CFLAGS) -o $@ $< 

# ----------------------------------------------------------------------
# Linker settings:
LINKER      = $(CXX) 
LDFLAGS     = $(WXCONFIG_LINKER_CALL) $(SANITIZE)
LINKER_CALL = $(LINKER) -o $@ $^ $(LDFLAGS)

# Targets
all: $(BIN_DIR)/$(APP_NAME)

# ============================================================
# LINKER-RULES
# ===========================================================
../bin/$(APP_NAME) : $(OBJ_DIR)/CubeApp.o\
                     $(OBJ_DIR)/CubeDlg.o
	    
	$(LINKER_CALL)
# 
# ===========================================================
# SOURCES
# ===========================================================
SRCS = $(SRC_DIR)/CubeApp.cpp\
       $(SRC_DIR)/CubeDlg.cpp

# ----------------------------------------------------------------------
# C sources: 
CSRCS =

# ----------------------------------------------------------------------
# Supported rules: 
touch:
	/bin/touch $(SRC_DIR)/*

build: mrproper depend 
	# after generating the dependencies it is necessary to call make again
	/usr/bin/make -j$(NPROCS) all 

clean:
	/bin/rm -f $(BIN_DIR)/$(APP_NAME)
	/bin/rm -f $(OBJ_DIR)/*.o
	/bin/rm -f $(SRC_DIR)/*.orig
	/bin/rm -f $(SRC_DIR)/*.bck
	/bin/rm -f $(MAKE_DIR)/.Makefile*
	/bin/rm -f $(MAKE_DIR)/*.bck
	/bin/rm -f $(MAKE_DIR)/*.bak

mrproper: clean
	/bin/rm -f $(CONFIG_DIR)/*.bck

style:
	/usr/bin/find $(SRC_DIR) -name "*.cpp" -type f -exec astyle --style=ansi -S -N -w -Y -p -C -c {} \;
	/usr/bin/find $(SRC_DIR) -name "*.hpp" -type f -exec astyle --style=ansi -S -N -w -Y -p -C -c {} \;
	/usr/bin/find $(SRC_DIR) -name "*.c"   -type f -exec astyle --style=ansi -S -N -w -Y -p -C -c {} \;
	/usr/bin/find $(SRC_DIR) -name "*.h"   -type f -exec astyle --style=ansi -S -N -w -Y -p -C -c {} \;

depend:
	@cat < /dev/null > makedep
	@cat < /dev/null > cmakedep
# First C++
	@for i in ${SRCS}; do \
		 (echo $$i; $(CXX) $(CXXFLAGS) -MM $$i >> makedep); done
# Write full path information before each *.o-dependency
	@echo 's/.*\.o:/..\/obj\/&/g' > eddep
	@sed -f eddep makedep > makedep1
	@mv makedep1 makedep
	@rm eddep
# Add the rule to each dependency
	@echo 'a' > eddep
	@echo '	$$(CXX_CALL)' >> eddep
	@echo '.' >> eddep
	@echo 'g/.*\.o:/i\' >> eddep
	@echo '	$$(CXX_CALL)\' >> eddep
	@echo '.' >> eddep
	@echo '1,1d' >> eddep
	@echo 'w' >> eddep
	@ed - makedep < eddep
	@rm eddep
# Then C
	@for i in ${CSRCS}; do \
		 (echo $$i; $(CC_CALL) $(CFLAGS) -MM $$i >> cmakedep); done
# Write full path information before each *.o-dependency
	@echo 's/.*\.o:/..\/obj\/&/g' > ceddep
	@sed -f ceddep cmakedep > cmakedep1
	@mv cmakedep1 cmakedep
	@rm ceddep
# Add the rule to each dependency
	@echo 'a' > ceddep
	@echo '	$$(CC_CALL)' >> ceddep
	@echo '.' >> ceddep
	@echo 'g/.*\.o:/i\' >> ceddep
	@echo '	$$(CC_CALL)\' >> ceddep
	@echo '.' >> ceddep
	@echo '1,1d' >> ceddep
	@echo 'w' >> ceddep
	@ed - cmakedep < ceddep
	@rm ceddep
	@cat < cmakedep >> makedep
	@rm cmakedep
	@echo '# DO NOT EDIT THIS FILE HERE.' > .Makefile.dep
	@cat < makedep >> .Makefile.dep
	@echo '# DO NOT EDIT THIS FILE HERE.' >> .Makefile.dep
	@rm makedep

.Makefile.dep: 
	@cat < /dev/null > .Makefile.dep

include .Makefile.dep
