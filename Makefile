# Whad-lib Makefile

ifdef ARCH_ARM
	CROSS_COMPILE		?= arm-none-eabi-
	CFLAGS	     		 = -Os -mthumb -mhard-float -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -Wall
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

# WHAD Library
TARGETS := $(wildcard nanopb/*.c) \
	$(wildcard whad/protocol/*.c) \
	$(wildcard whad/protocol/*/*.c) \
	$(wildcard src/*.c) \
	$(wildcard src/domains/*.c) \
	$(wildcard src/cpp/*.cpp) \
	$(wildcard src/cpp/domains/*.cpp) \
	$(wildcard src/cpp/domains/*/*.cpp) \
	$(wildcard src/cpp/discovery/*.cpp) \
	$(wildcard src/cpp/generic/*.cpp)
OBJS := $(TARGETS:.c=.o)
OBJS := $(OBJS:.cpp=.o)

# WHAD Lib
INC_FOLDERS += \
	-I./ \
	-Iinc \
	-Iinc/cpp \
	-Inanopb \
	-Iwhad/protocol \
	-Iwhad/protocol/ble \
	-Iwhad/protocol/dot15d4 \
	-Iwhad/protocol/esb \
	-Iwhad/protocol/phy
INCLUDE += $(INC_FOLDERS)

dir:
	mkdir -p lib

%.o: %.cpp
	echo "file $<"
	$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

libwhad.a: dir $(OBJS)
	echo $(OBJS)
	$(AR) -rc $(LIB_DIR)/libwhad.a $(OBJS)

all: libwhad.a

clean:
	@rm -f $(OBJS)
	@rm lib/*.a
	