#/***********************************************************************
#* SVN: Version Control with Subversion
#* ---------------------------------------------------------------------
#* $Id$
#***********************************************************************
#* LICENSE AND WARRANTY INFORMATION
#* ================================
#* 
#* Copyright (C) 2011
#* Forschungseinrichtung Satellitengeodaesie, TU Muenchen &
#* Bundesamt fuer Kartographie und Geodaesie
#* Geodetic Observatory Wettzell
#* Sackenrieder Str. 25
#* D-93444 Bad Koetzting
#* Germany
#*
#* This program is FREE SOFTWARE under the terms of GNU Lesser General
#* Public License v3 (or any later version) and may be used following
#* this definitions as published by the Free Software Foundation at
#* http://www.gnu.de/documents/lgpl-3.0.en.html. Software parts which
#* include elements from external software distributions may be under
#* different licenses as the Sun License/BSD License for the ONC/Sun RPC
#* (http://www.opensource.org/licenses/bsd-license.php)
#* and the wxWindows Library Licence for the GUI parts with wxWidgets
#* (http://www.opensource.org/licenses/wxwindows.php).
#* In case of variations to the above licenses each particular developer
#* is responsible for defining the dedicated license conditions and terms.
#*
#* This program is distributed in the hope that it will be useful.
#* IT IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING
#* THE WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A
#* PARTICULAR PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE
#* OR TRADE PRACTICE.
#*
#* The software is provided with no support and without any obligation
#* on the part of the Geodetic Observatory Wettzell to assist in its
#* use, correction, modification or enhancement. THE Geodetic Observatory
#* Wettzell SHALL HAVE NO LIABILITY WITH RESPECT TO THE INFRINGEMENT OF
#* COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY THE SOFTWARE OR ANY PART
#* THEREOF. In no event will the Geodetic Observatory Wettzell be liable
#* for any lost revenue or profits or other special, indirect and
#* consequential damages, even if the Geodetic Observatory Wettzell
#* has been advised of the possibility of such damages.
#*
#* You should have received a copy of the license(s) along with this program.
#**********************************************************************/
 
#***********************************************************************
#* Description:                                                        *
#* ------------                                                        *
#*                                                                     *
#* Author: Martin Ettl (ettl@fs.wettzell.de)                           *
#* Date  : 2011-12-07                                                  *
#*                                                                     *
#* LINUX-Makefile (gmake): Ubuntu linux                                *
#* Makefile to compile and build all necessary programms.              *
#*                                                                     *
#* Usage and basic features:                                           *
#*                                                                     *
#*  - make build  [creates the whole project]                          *
#*  - make clean  [removes all object and binary files]                *
#*  - make depend [detects header dependencies]                        *
#*  - make rpc    [generates files using idl2rpc]                      *
#*                                                                     *
#***********************************************************************

# ============================================================
# DEFINITIONS
# ============================================================

# path settings:
APPLICATION_NAME                = wx3DCube
SOURCE_DIR			= ../src
OBJECT_DIR			= ../obj
MAKE_DIR 			= ../make
BIN_DIR 			= ../bin
CONFIG_DIR			= ../config
RPC_DIR 			= ../rpcgen
ICON_DIR			= $(SOURCE_DIR)/image

#===============================================================================
# Determine the number cores of the machine, where the makefile is executed.
# This helps to set the -j option (from make), to speedup the build
# process of 'large' projects.  
NPROCS=1
OS:=$(shell uname -s)
ifeq ($(OS),Linux)
    NPROCS:=$(shell grep -c ^processor /proc/cpuinfo) 
endif
#===============================================================================

#===============================================================================
# path to the idl2rpc generated clients
IDL2RPC_CALL 				= idl2rpc.pl
#===============================================================================
# configure wxWidgets build
WXVERSION		= 2.8
WXCONFIG_CALL		= `wx-config --cxxflags --version=$(WXVERSION)`
WXCONFIG_LINKER_CALL	= `wx-config --version=$(WXVERSION) --libs adv,aui,core,base,html,richtext,xml`

# if no c++-compiler is specified, choose g++ by default
ifndef $(CPPCOMPILER)
         CPPCOMPILER:= g++
endif
CPP_WFLAGS	  = -Wsequence-point -Wno-old-style-cast -Wno-unknown-pragmas -Wno-deprecated \
		    -W -Wall -Wno-variadic-macros -Wextra -Wno-long-long -pedantic -Wunused  -Wformat=2 -ansi -Wno-write-strings  
CPPCOMPILER_FLAGS = $(WXCONFIG_CALL) $(CPP_WFLAGS)
CPPCOMPILER_CALL  = $(CPPCOMPILER) -c $(CPPCOMPILER_FLAGS) -o $@ $< 

# if no c-compiler is specified, choose gcc by default
ifndef $(CCOMPILER)
         CCOMPILER:= gcc
endif
CC_WFLAGS	= -W -Wall -Wunused -ansi -g -pipe 
CCOMPILER_FLAGS = $(WXCONFIG_CALL) $(CC_WFLAGS)
CCOMPILER_CALL  = $(CCOMPILER) -c $(CCOMPILER_FLAGS) -o $@ $< 

LINKER          = $(CPPCOMPILER)
LINKER_FLAGS    = $(WXCONFIG_LINKER_CALL)
LINKER_CALL     = $(LINKER) -o $@ $^ $(LINKER_FLAGS)

all: ../bin/$(APPLICATION_NAME)

# ============================================================
# LINKER-RULES
# ===========================================================
../bin/$(APPLICATION_NAME) : ../obj/CubeApp.o\
                             ../obj/CubeDlg.o
	    
	$(LINKER_CALL)
# 
# ===========================================================
# SOURCES
# ===========================================================
SRCS = ../src/CubeApp.cpp\
       ../src/CubeDlg.cpp

 
#CSRCS = ../src/azelfit.c\
#	 ../src/Parser.c

# ===========================================================
# SUPPORTING-RULES
# ===========================================================


build: mrproper depend 
	# after generating the dependencies it is necessary to call make again
	make -j$(NPROCS) all 

touch:
	touch $(SOURCE_DIR)/*

rpc:
	# This option is not suppored in this project

clean:
	rm -f $(BIN_DIR)/wx*
	rm -f $(OBJECT_DIR)/*

mrproper:
	rm -f $(MAKE_DIR)/.Makefile.dep
	rm -f $(MAKE_DIR)/*.bck
	rm -f $(MAKE_DIR)/*.bak
	rm -f $(BIN_DIR)/*
	rm -f $(OBJECT_DIR)/*
	rm -f $(SOURCE_DIR)/*.bck

install: build
	install -d /usr/bin/
	install ../bin/$(APPLICATION_NAME) /usr/bin/

depend:
	@cat < /dev/null > makedep
	@cat < /dev/null > cmakedep
# First C++
	@for i in ${SRCS}; do \
		 (echo $$i; $(CPPCOMPILER) $(CPPCOMPILER_FLAGS) -MM $$i >> makedep); done
#       Write full path information before each *.o-dependency
	@echo 's/.*\.o:/..\/obj\/&/g' > eddep
	@sed -f eddep makedep > makedep1
	@mv makedep1 makedep
	@rm eddep
#       Add the rule to each dependency
	@echo 'a' > eddep
	@echo '	$$(CPPCOMPILER_CALL)' >> eddep
	@echo '.' >> eddep
	@echo 'g/.*\.o:/i\' >> eddep
	@echo '	$$(CPPCOMPILER_CALL)\' >> eddep
	@echo '.' >> eddep
	@echo '1,1d' >> eddep
	@echo 'w' >> eddep
	@ed - makedep < eddep
	@rm eddep
# Then C
	@for i in ${CSRCS}; do \
		 (echo $$i; $(CCOMPILER) $(CCOMPILER_FLAGS) -MM $$i >> cmakedep); done
#       Write full path information before each *.o-dependency
	@echo 's/.*\.o:/..\/obj\/&/g' > ceddep
	@sed -f ceddep cmakedep > cmakedep1
	@mv cmakedep1 cmakedep
	@rm ceddep
##       Add the rule to each dependency
	@echo 'a' > ceddep
	@echo '	$$(CCOMPILER_CALL)' >> ceddep
	@echo '.' >> ceddep
	@echo 'g/.*\.o:/i\' >> ceddep
	@echo '	$$(CCOMPILER_CALL)\' >> ceddep
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
