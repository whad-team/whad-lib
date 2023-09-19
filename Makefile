# Whad-lib Makefile

ifdef ARCH_ARM
	CROSS_COMPILE		?= arm-none-eabi-
	CFLAGS	     = -Os -mthumb -mhard-float -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -Wall
else
	$(error Architecture not supported.)
endif

# Define tools names
CC		:= $(CROSS_COMPILE)gcc
CXX		:= $(CROSS_COMPILE)g++
LD		:= $(CROSS_COMPILE)gcc
AR		:= $(CROSS_COMPILE)ar
AS		:= $(CROSS_COMPILE)as
SIZE		:= $(CROSS_COMPILE)size
OBJCOPY		:= $(CROSS_COMPILE)objcopy
OBJDUMP		:= $(CROSS_COMPILE)objdump

# Nanopb dependency
NANOPB_DIR := ./nanopb
WHAD_DIR   := ./protocol

# Build directory
LIB_DIR := lib

# Include flags
INCLUDE  := -I. -Inanopb -Iinc

# NANOPB targets
TARGETS := $(wildcard src/*.c) $(wildcard $(NANOPB_DIR)/*.c) $(wildcard $(WHAD_DIR)/*.c) $(wildcard $(WHAD_DIR)/*/*.c)
OBJS=$(TARGETS:.c=.o)

%.o: %.c
	$(CC) $(INCLUDE) -c $(CFLAGS) $< -o $@

libwhad.a: $(OBJS)
	$(AR) -rc $(LIB_DIR)/libwhad.a $(OBJS)

all: libwhad.a

clean:
	@rm -f $(OBJS)
	@rm lib/*.a
	