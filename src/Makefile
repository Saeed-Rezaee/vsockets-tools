#
# * vsockets tools - project Makefile
# *
# * Copyright (C) 2015 Pedro Mendes da Silva
# *
# *  This program is free software; you can redistribute it and/or modify
# *  it under the terms of the GNU General Public License as published by
# *  the Free Software Foundation; either version 2 of the License, or
# *  (at your option) any later version.
# *
# *  This program is distributed in the hope that it will be useful,
# *  but WITHOUT ANY WARRANTY; without even the implied warranty of
# *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# *  GNU General Public License for more details.
# *
# *  You should have received a copy of the GNU General Public License
# *  along with this program; if not, write to the Free Software
# *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
# *

CC:=gcc

host-type := $(shell uname)

ifeq ($(host-type),Linux)
PLATFORM := LINUX
BUILD_DATE := $(shell date --utc)

else

PLATFORM := WIN32
BUILD_DATE := $(shell date /t) $(shell time /t)

endif

ifeq ($(PLATFORM),WIN32)

INCLUDES:= ./lib/liblist-2.4/
LIBS:= ./lib/liblist-2.4.mingw32/list.o -lws2_32

PLATFORM_DIR=win32

else

# -L../lib/tmp/liblist-2.4.mingw32/lib

#LIBS:= -L../lib/tmp/  -llist 

LIBS:= ../lib/tmp/list.o
INCLUDES:= .

PLATFORM_DIR=linux

endif

DEFINES:= -DBUILD_DATE="$(BUILD_DATE)"

COPTIONS:=-g -static -I$(INCLUDES) $(DEFINES)

COMMON_C_FILES:= vsockets_common.c sockets_common.c debug_common.c

TARGETDIR:=../target/$(PLATFORM_DIR)

TARGETBINDIR:=$(TARGETDIR)/bin

#LIBS:= ../lib/tmp/list.o


BINS:=

all: vsockets_hostname vsockets_nc 

vsockets_hostname: ./vsockets_hostname.c $(COMMON_C_FILES)
	@echo "### Making vsockets_hostname"
	$(CC) $(COPTIONS)  vsockets_hostname.c $(COMMON_C_FILES) $(LIBS) -o $(TARGETBINDIR)/vsockets_hostname

vsockets_nc: ./vsockets_nc.c $(COMMON_C_FILES) ipv4_common.c
	@echo "### Making vsockets_nc"
	$(CC) $(COPTIONS) vsockets_nc.c $(COMMON_C_FILES) ipv4_common.c $(LIBS) -o $(TARGETBINDIR)/vsockets_nc 