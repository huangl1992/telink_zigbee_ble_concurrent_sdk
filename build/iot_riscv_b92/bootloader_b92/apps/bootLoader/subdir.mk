################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/apps/bootLoader/bootloader.c \
D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/apps/bootLoader/main.c 

OBJS += \
./apps/bootLoader/bootloader.o \
./apps/bootLoader/main.o 

C_DEPS += \
./apps/bootLoader/bootloader.d \
./apps/bootLoader/main.d 


# Each subdirectory must supply rules for building sources it contributes
apps/bootLoader/bootloader.o: D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/apps/bootLoader/bootloader.c apps/bootLoader/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -D__PROJECT_TL_BOOT_LOADER__=1 -DBOOT_LOADER_MODE=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../apps/bootLoader -I../../../apps/common -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../ -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

apps/bootLoader/main.o: D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/apps/bootLoader/main.c apps/bootLoader/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -D__PROJECT_TL_BOOT_LOADER__=1 -DBOOT_LOADER_MODE=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../apps/bootLoader -I../../../apps/common -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../ -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


