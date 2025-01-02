################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include proj/os/subdir.mk
-include proj/drivers/usb/app/subdir.mk
-include proj/drivers/usb/subdir.mk
-include proj/drivers/subdir.mk
-include proj/common/subdir.mk
-include platform/services/subdir.mk
-include platform/chip_b92/flash/subdir.mk
-include platform/chip_b92/error_handler/subdir.mk
-include platform/chip_b92/subdir.mk
-include platform/boot/b92/subdir.mk
-include platform/boot/subdir.mk
-include apps/common/subdir.mk
-include apps/bootLoader/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := bootloader_b92
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
bootloader_b92.bin \

SECONDARY_LIST += \
bootloader_b92.lst \

SECONDARY_SIZE += \
bootloader_b92.siz \


# All Target
all:
	+@$(MAKE) --no-print-directory pre-build && $(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: bootloader_b92.elf secondary-outputs

# Tool invocations
bootloader_b92.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -T ../boot.link -nostartfiles -Xlinker --gc-sections -L../../../platform/lib -Wl,-Map,"bootloader_b92.map" -mcpu=d25f -ffunction-sections -fdata-sections -mext-dsp -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -o "bootloader_b92.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

bootloader_b92.bin: bootloader_b92.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv32-elf-objcopy -O binary "bootloader_b92.elf"  "bootloader_b92.bin"
	@echo 'Finished building: $@'
	@echo ' '

bootloader_b92.lst: bootloader_b92.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv32-elf-objdump --source --all-headers --demangle --line-numbers --wide "bootloader_b92.elf" > "bootloader_b92.lst"
	@echo 'Finished building: $@'
	@echo ' '

bootloader_b92.siz: bootloader_b92.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv32-elf-size "bootloader_b92.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) bootloader_b92.elf
	-@echo ' '

pre-build:
	-"D:\hl\telink\zigbee_test\telink_zigbee_ble_concurrent_sdk_20241217\build\iot_riscv_b92/../../tools/tl_link_load.sh" "D:\hl\telink\zigbee_test\telink_zigbee_ble_concurrent_sdk_20241217\build\iot_riscv_b92/../../platform/boot/b92/boot_b92.link" "D:\hl\telink\zigbee_test\telink_zigbee_ble_concurrent_sdk_20241217\build\iot_riscv_b92/boot.link"
	-@echo ' '

post-build:
	-"D:\hl\telink\zigbee_test\telink_zigbee_ble_concurrent_sdk_20241217\build\iot_riscv_b92/../../tools/tl_check_fw.sh" bootloader_b92 iot_riscv
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents main-build pre-build post-build

-include ../makefile.targets
