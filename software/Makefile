# [Directories] ------------------------------------------------------------------
CMSISDIR = /opt/cmsis
DEVICEDIR = $(CMSISDIR)/cmsis-dfp-same51-new/include
COREDIR = $(CMSISDIR)/cmsis-core/CMSIS/Include

TARGETDIR = bin
SOURCEDIR = src
LINKERDIR = ld
OBJECTDIR = bin/obj
INCLUDEDIR = include

# [App] -------------------------------------------------------------------------
APP_NAME = same5x-app
HFXO_VALUE = 0UL
LFXO_VALUE = 32768UL
APP_ADDRESS = 0x00000000

# [General] ----------------------------------------------------------------------
MCU_TYPE = __ATSAME51J20A__

LDSCRIPT = $(LINKERDIR)/atsame51j20.ld

OPTIMIZATION = -O3

BUILD_TYPE ?= debug

DEBUG_OUTPUT ?= true

# Parallel compile (use "$ nproc" to find out how many threads you have)
MAX_PARALLEL = 1

# [Compiler/Linker] --------------------------------------------------------------
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
LD = arm-none-eabi-gcc
AS = arm-none-eabi-as
STRIP = arm-none-eabi-strip
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
GDB = arm-none-eabi-gdb

# [Flags] ------------------------------------------------------------------------


# /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
# file search
STRUCT := $(shell find $(SOURCEDIR) -type d)

SOURCEDIRSTRUCT := $(filter-out %/include, $(STRUCT))
INCLUDEDIRSTRUCT := $(filter %/include, $(STRUCT)) $(DEVICEDIR)/ $(COREDIR)/
OBJECTDIRSTRUCT := $(subst $(SOURCEDIR), $(OBJECTDIR), $(SOURCEDIRSTRUCT))

# Versioning
$(shell if ! test -f $(TARGETDIR)/.version; then echo 0 > $(TARGETDIR)/.version; fi)

INC_VERSION ?= n
BUILD_VERSION = $(shell cat $(TARGETDIR)/.version)

ifeq ($(INC_VERSION), y)
$(shell if test -f .vscode/launch.json; then sed -i 's/v$(BUILD_VERSION).$(APP_NAME)/v$(shell echo $$(($(BUILD_VERSION) + 1))).$(APP_NAME)/g' .vscode/launch.json; fi)
$(shell echo $$(($(BUILD_VERSION) + 1)) > $(TARGETDIR)/.version)
$(shell rm -rf $(OBJECTDIR)/*)
BUILD_VERSION = $(shell cat $(TARGETDIR)/.version)
endif

ifeq ($(BUILD_VERSION), 0)
$(shell echo $$(($(BUILD_VERSION) + 1)) > $(TARGETDIR)/.version)
$(shell rm -rf $(OBJECTDIR)/*)
BUILD_VERSION = $(shell cat $(TARGETDIR)/.version)
endif

# Compillers & Linker flags
ASFLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS = $(addprefix -I,$(INCLUDEDIRSTRUCT)) -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -nostdlib -nostartfiles -ffunction-sections -fdata-sections -ffreestanding $(OPTIMIZATION) -std=gnu99 -Wpointer-arith -Wundef -Werror -D$(MCU_TYPE) -DHFXO_VALUE=$(HFXO_VALUE) -DLFXO_VALUE=$(LFXO_VALUE) -DBUILD_VERSION=$(BUILD_VERSION)
CXXFLAGS = $(addprefix -I,$(INCLUDEDIRSTRUCT)) -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -nostdlib -nostartfiles -ffunction-sections -fdata-sections -ffreestanding -fno-rtti -fno-exceptions $(OPTIMIZATION) -std=c++17 -Wpointer-arith -Wundef -Werror -D$(MCU_TYPE) -DHFXO_VALUE=$(HFXO_VALUE) -DLFXO_VALUE=$(LFXO_VALUE) -DBUILD_VERSION=$(BUILD_VERSION)
LDFLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nano.specs --specs=nosys.specs -nostdlib -nostartfiles -ffunction-sections -fdata-sections -ffreestanding -Wl,--gc-sections
LDLIBS = -lm -lc -lgcc -lnosys

ifeq ($(BUILD_TYPE), debug)
CFLAGS += -g
CXXFLAGS += -g
endif

ifeq ($(DEBUG_OUTPUT), true)
CFLAGS += -D__DEBUG_OUTPUT__
CXXFLAGS += -D__DEBUG_OUTPUT__
endif

# Target
TARGET = $(TARGETDIR)/v$(BUILD_VERSION).$(APP_NAME)

# Sources & objects
SRCFILES := $(addsuffix /*, $(SOURCEDIRSTRUCT))
SRCFILES := $(wildcard $(SRCFILES))

ASSOURCES := $(filter %.s, $(SRCFILES))
ASOBJECTS := $(subst $(SOURCEDIR), $(OBJECTDIR), $(ASSOURCES:%.s=%.o))

CSOURCES := $(filter %.c, $(SRCFILES))
COBJECTS := $(subst $(SOURCEDIR), $(OBJECTDIR), $(CSOURCES:%.c=%.o))

CXXSOURCES := $(filter %.cpp, $(SRCFILES))
CXXOBJECTS := $(subst $(SOURCEDIR), $(OBJECTDIR), $(CXXSOURCES:%.cpp=%.o))

SOURCES = $(ASSOURCES) $(CSOURCES) $(CXXSOURCES)
OBJECTS = $(ASOBJECTS) $(COBJECTS) $(CXXOBJECTS)

all: clean-bin make-dir version compile mem-usage

compile:
	@$(MAKE) INC_VERSION=n --no-print-directory -j${MAX_PARALLEL} $(TARGET).elf
	@$(MAKE) INC_VERSION=n --no-print-directory -j${MAX_PARALLEL} $(TARGET).bin $(TARGET).hex $(TARGET).lss

$(TARGET).lss: $(TARGET).elf
	@echo Creating LSS file \'$@\'...
	@$(OBJDUMP) -S --disassemble $< > $@

$(TARGET).bin: $(TARGET).elf
	@echo Creating BIN file \'$@\'...
	@$(OBJCOPY) -O binary --only-section=.isr_vector --only-section=.text --only-section=.ARM --only-section=.iram0.text --only-section=.dram0.data --only-section=.data $< $(TARGET).irom0.bin


$(TARGET).hex: $(TARGET).elf
	@echo Creating HEX file \'$@\'...
	@$(OBJCOPY) -O ihex --remove-section=.irom2.text --remove-section=.drom0.data $< $@
	@$(OBJCOPY) -O ihex --only-section=.isr_vector --only-section=.text --only-section=.ARM --only-section=.iram0.text --only-section=.dram0.data --only-section=.data $< $(TARGET).flash.hex

$(TARGET).elf: $(OBJECTS)
	@echo ---------------------------------------------------------------------------
	@echo Creating ELF file \'$@\'...
	@$(LD) $(LDFLAGS) -o $@ $^ -T $(LDSCRIPT) $(LDLIBSPATH) $(LDLIBS) -Wl,-Map=$(TARGET).map
ifeq ($(BUILD_TYPE), release)
	@$(STRIP) -g $@
endif

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.s
	@echo Compilling ASM file \'$<\' \> \'$@\'...
	@$(AS) $(ASFLAGS) -MD -o $@ $<

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c
	@echo Compilling C file \'$<\' \> \'$@\'...
	@$(CC) $(CFLAGS) -MD -c -o $@ $<

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	@echo Compilling C++ file \'$<\' \> \'$@\'...
	@$(CXX) $(CXXFLAGS) -MD -c -o $@ $<

debug: $(TARGET).elf
	$(GDB) $(TARGET).elf

inc-version:
	@echo $$(($(BUILD_VERSION) + 1)) > $(TARGETDIR)/.version
	@if test -f .vscode/launch.json; then sed -i 's/v$(BUILD_VERSION).$(APP_NAME)/v$(shell echo $$(($(BUILD_VERSION) + 1))).$(APP_NAME)/g' .vscode/launch.json; fi

dec-version:
	@echo $$(($(BUILD_VERSION) - 1)) > $(TARGETDIR)/.version
	@if test -f .vscode/launch.json; then sed -i 's/v$(BUILD_VERSION).$(APP_NAME)/v$(shell echo $$(($(BUILD_VERSION) - 1))).$(APP_NAME)/g' .vscode/launch.json; fi

version:
	@echo Build version: v$(BUILD_VERSION)
	@echo ---------------------------------------------------------------------------

mem-usage: $(TARGET).elf
	@echo ---------------------------------------------------------------------------
	@armmem -l $(LDSCRIPT) -d -h $<

make-dir:
	@mkdir -p $(OBJECTDIRSTRUCT)

clean-bin:
	@rm -f $(TARGETDIR)/*.lss
	@rm -f $(TARGETDIR)/*.hex
	@rm -f $(TARGETDIR)/*.bin
	@rm -f $(TARGETDIR)/*.map
	@rm -f $(TARGETDIR)/*.elf

clean: clean-bin
	@rm -rf $(OBJECTDIR)/*

-include $(OBJECTS:.o=.d)

.PHONY: clean clean-bin make-dir mem-usage version dec-version inc-version debug compile all