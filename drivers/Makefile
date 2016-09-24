PROJECT_NAME     := nrf_drivers_nrf51_armgcc
TARGETS          := nrf_drivers_lib
OUTPUT_DIRECTORY := _build

SDK_ROOT := ../.
PROJ_DIR := ./.


# Source files common to all targets
SRC_FILES += \
  $(PROJ_DIR)/rtc/nrf_drv_rtc.c \
  $(PROJ_DIR)/common/nrf_drv_common.c \

# Include folders common to all targets
INC_FOLDERS += \
  $(PROJ_DIR)     \
  $(PROJ_DIR)/hal \
  $(SDK_ROOT)/common \
  $(SDK_ROOT)/common/toolchain \
  $(SDK_ROOT)/common/toolchain/cmsis/include \

# Libraries common to all targets
LIB_FILES += \

# C flags common to all targets
CFLAGS += -DNRF51
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs
CFLAGS +=  -Wall -Werror -Os -g3
CFLAGS += -mfloat-abi=soft
# keep every function in separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums 
# generate dependency output file
CFLAGS += -MP -MD

# C++ flags common to all targets
CXXFLAGS += \
  $(SDK_ROOT)/common/nrf_common_lib_nrf51.a \

# Assembler flags common to all targets
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DNRF51

# Linker flags

.PHONY: $(TARGETS) default all clean help flash 
# Default target - first one defined
default: nrf_drivers_lib

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo 	nrf_drivers_lib

TEMPLATE_PATH := $(SDK_ROOT)/common/toolchain/gcc

include $(TEMPLATE_PATH)/Makefile.common
$(call define_library, $(TARGETS), nrf_drivers_lib_nrf51.a)
-include $($(strip $(TARGETS))_dependencies)

define create_library
@echo Creating library: $($@)
$(NO_ECHO)$(AR) $($@) $^
@echo Done
endef
nrf_drivers_lib:
	$(create_library)

