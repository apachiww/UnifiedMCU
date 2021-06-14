# ####### This is the Makefile of mcs51 project template #######
#
#	Put your main.c and other userspace code (*.c) under user/
#
#	Generated .ihx files can be found under gen/
#	gen/release for non-debug and gen/debug for debug
#
#	Put your source *.h files under inc/, and *.c under src/
#
#	Put your *.lib archives under lib/ and headers lib/inc
#
#	gen/VER/tmp/ is for intermediate files, like object files
#
#	apachiww@github.com
#

# Usage:
#
# 	`make VER=release` or `make VER=debug` to make the .ihx file
#
# 	`make clean` to remove all generated files
#
# 	`make install PORT=/dev/YOUR_TTY` (Experimental), to burn the
# 	 .ihx file to your device, using stcflash from 
# 	 https://github.com/laborer/stcflash
#
#	Planning to rewrite a downloader using ANSI C to replace stcflash
#	in the future


#
# Include the common makedefs
#

SHARE_DIR := ../share

include ${SHARE_DIR}/makedefs

#
# Set the directories
#

# Source directories

INC_DIR := ./inc
SRC_DIR := ./src
LIB_DIR := ./lib
LIB_INC_DIR := ${LIB_DIR}/inc
USER_DIR := ./user

# Output directories and filenames

GEN_RELEASE_DIR := ./gen/release
GEN_DEBUG_DIR := ./gen/debug

GEN_RELEASE := out
GEN_DEBUG := out

#
# Set Flags
#

# CPPFLAGS := 
CFLAGS := -mmcs51 --std-sdcc11
# ASFLAGS := 
# LDFLAGS := -i

# ARFLAGS := 

#
# Compile version, default release. Use `make VER=debug`
#

VER := release

# Use vm8051 as debugger instead

DEBUG := vm8051

# Use stcflash, from https://github.com/laborer/stcflash, default /dev/ttyUSB0, 
# use `make install PORT=/dev/YOUR_TTY` to set your tty 

FLASH := python ./stcflash/stcflash.py
PORT := /dev/ttyUSB0
FLASH_OPTION := --port ${PORT}

#
# Directory of debug or release
#

ifeq (${VER},release)
GEN_DIR := ${GEN_RELEASE_DIR}
GEN_NAME := ${GEN_RELEASE}
TMP_DIR := ${GEN_RELEASE_DIR}/tmp
else
GEN_DIR := ${GEN_DEBUG_DIR}
GEN_NAME := ${GEN_DEBUG}
TMP_DIR := ${GEN_DEBUG_DIR}/tmp
CFLAGS += --debug
# LDFLAGS += -y
endif


#
# Run phase 2 of make: Initialize filenames
#

# Input files

LIB = ${wildcard ${LIB_DIR}/*.lib}
LIB_HEADERS = ${wildcard ${LIB_INC_DIR}/*.h}

SRC = ${wildcard ${SRC_DIR}/*.c}
SRC_HEADERS = ${wildcard ${INC_DIR}/*.h}

USER_SRC = ${wildcard ${USER_DIR}/*.c}

# Target files

USER_OBJ = ${USER_SRC:${USER_DIR}/%.c=${TMP_DIR}/%.rel}
SRC_OBJ = ${SRC:${SRC_DIR}/%.c=${TMP_DIR}/%.rel}

#
# Default target all: .ihx
#

all : ${GEN_DIR}/${GEN_NAME}.ihx

#
# File dependency and recipes
#

# The final link, let sdcc invoke sdld automatically

${GEN_DIR}/${GEN_NAME}.ihx : ${USER_OBJ} ${SRC_OBJ} ${LIB}
	@echo "Finally building ${GEN_NAME}.ihx (${VER})"
	@${CC} ${CFLAGS} -o $@ $^

# Target files under tmp may from userspace or predefined sourcecode

${TMP_DIR}/%.rel : ${USER_DIR}/%.c
	@echo "Building ${notdir $@}"
	@${CC} ${CFLAGS} -c -I ${INC_DIR} -I ${LIB_INC_DIR} -o $@ $<

${TMP_DIR}/%.rel : ${SRC_DIR}/%.c
	@echo "Building ${notdir $@}"
	@${CC} ${CFLAGS} -c -I ${INC_DIR} -o $@ $<

# Userspace file dependency, from include headers and library headers

${USER_SRC} : ${LIB_HEADERS} ${SRC_HEADERS}

# Source header dependency

${SRC_DIR}/%.c : ${INC_DIR}/%.h

#
# Below are definitions of miscellaneous commands
#

# Remove all generated files, use command 'make clean'

clean :
	@echo "Removing all generated files..."
	${RM} ${GEN_RELEASE_DIR}/tmp/*
	${RM} ${GEN_RELEASE_DIR}/*.*
	${RM} ${GEN_DEBUG_DIR}/tmp/*
	${RM} ${GEN_DEBUG_DIR}/*.*

# Burn the .ihx code to your device, use command 'make install'

install :
	@${FLASH} ${GEN_RELEASE_DIR}/${GEN_RELEASE}.ihx ${FLASH_OPTION}

# Launch debug

debug :
	@${DEBUG} ${GEN_DEBUG_DIR}/${GEN_DEBUG}.ihx


.PNONY : clean install debug all