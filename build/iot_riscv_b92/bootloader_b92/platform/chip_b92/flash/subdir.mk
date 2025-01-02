################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid146085.c \
D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid1460c8.c \
D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid156085.c \
D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid1560c8.c \
D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid166085.c \
D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid1660c8.c \
D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid186085.c 

OBJS += \
./platform/chip_b92/flash/flash_mid146085.o \
./platform/chip_b92/flash/flash_mid1460c8.o \
./platform/chip_b92/flash/flash_mid156085.o \
./platform/chip_b92/flash/flash_mid1560c8.o \
./platform/chip_b92/flash/flash_mid166085.o \
./platform/chip_b92/flash/flash_mid1660c8.o \
./platform/chip_b92/flash/flash_mid186085.o 

C_DEPS += \
./platform/chip_b92/flash/flash_mid146085.d \
./platform/chip_b92/flash/flash_mid1460c8.d \
./platform/chip_b92/flash/flash_mid156085.d \
./platform/chip_b92/flash/flash_mid1560c8.d \
./platform/chip_b92/flash/flash_mid166085.d \
./platform/chip_b92/flash/flash_mid1660c8.d \
./platform/chip_b92/flash/flash_mid186085.d 


# Each subdirectory must supply rules for building sources it contributes
platform/chip_b92/flash/flash_mid146085.o: D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid146085.c platform/chip_b92/flash/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -D__PROJECT_TL_BOOT_LOADER__=1 -DBOOT_LOADER_MODE=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../apps/bootLoader -I../../../apps/common -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../ -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/chip_b92/flash/flash_mid1460c8.o: D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid1460c8.c platform/chip_b92/flash/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -D__PROJECT_TL_BOOT_LOADER__=1 -DBOOT_LOADER_MODE=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../apps/bootLoader -I../../../apps/common -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../ -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/chip_b92/flash/flash_mid156085.o: D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid156085.c platform/chip_b92/flash/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -D__PROJECT_TL_BOOT_LOADER__=1 -DBOOT_LOADER_MODE=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../apps/bootLoader -I../../../apps/common -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../ -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/chip_b92/flash/flash_mid1560c8.o: D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid1560c8.c platform/chip_b92/flash/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -D__PROJECT_TL_BOOT_LOADER__=1 -DBOOT_LOADER_MODE=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../apps/bootLoader -I../../../apps/common -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../ -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/chip_b92/flash/flash_mid166085.o: D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid166085.c platform/chip_b92/flash/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -D__PROJECT_TL_BOOT_LOADER__=1 -DBOOT_LOADER_MODE=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../apps/bootLoader -I../../../apps/common -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../ -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/chip_b92/flash/flash_mid1660c8.o: D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid1660c8.c platform/chip_b92/flash/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -D__PROJECT_TL_BOOT_LOADER__=1 -DBOOT_LOADER_MODE=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../apps/bootLoader -I../../../apps/common -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../ -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/chip_b92/flash/flash_mid186085.o: D:/hl/telink/zigbee_test/telink_zigbee_ble_concurrent_sdk_20241217/platform/chip_b92/flash/flash_mid186085.c platform/chip_b92/flash/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -D__PROJECT_TL_BOOT_LOADER__=1 -DBOOT_LOADER_MODE=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../apps/bootLoader -I../../../apps/common -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../ -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


