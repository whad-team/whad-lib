# Whad-lib Makefile

ifdef ARCH_ARM
	CROSS_COMPILE		?= arm-none-eabi-
	CFLAGS	     		 = -Os -mthumb -mhard-float -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -Wall
else
	CROSS_COMPILE 		= 
	CFLAGS 				= -Wall
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

TEST_SRCS := $(wildcard tests/*.c)
TEST_BINS := $(patsubst tests/%.c,tests/build/%,$(TEST_SRCS))

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

%.o: %.cpp
	echo "file $<"
	$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

lib/libwhad.a: $(OBJS)
	$(AR) -rc $(LIB_DIR)/libwhad.a $(OBJS)

run-tests: $(TEST_BINS)
	@for test in $^; do \
		$$test; \
	done; \

tests/build:
	mkdir -p $@

tests/build/%: tests/%.c lib/libwhad.a | tests/build
	$(CC) $(CFLAGS) $(INCLUDE) $< lib/libwhad.a -o $@

all: lib/libwhad.a

clean:
	@rm -f $(OBJS)
	@rm lib/*.a
	@rm test/build -rf

check: run-tests
