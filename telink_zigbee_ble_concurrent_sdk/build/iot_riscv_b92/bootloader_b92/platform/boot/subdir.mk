################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/boot/link_cfg.S 

OBJS += \
./platform/boot/link_cfg.o 

S_UPPER_DEPS += \
./platform/boot/link_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
platform/boot/link_cfg.o: D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/boot/link_cfg.S platform/boot/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -x assembler-with-cpp -DMCU_CORE_B92=1 -D__PROJECT_TL_BOOT_LOADER__=1 -DBOOT_LOADER_MODE=1 -I../../../apps/common -I../../../apps/bootLoader -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../ -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


