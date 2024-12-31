################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/security_safety/zcl_ias_ace.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/security_safety/zcl_ias_wd.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/security_safety/zcl_ias_wd_attr.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/security_safety/zcl_ias_zone.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/security_safety/zcl_ias_zone_attr.c 

OBJS += \
./stack/zigbee/zcl/security_safety/zcl_ias_ace.o \
./stack/zigbee/zcl/security_safety/zcl_ias_wd.o \
./stack/zigbee/zcl/security_safety/zcl_ias_wd_attr.o \
./stack/zigbee/zcl/security_safety/zcl_ias_zone.o \
./stack/zigbee/zcl/security_safety/zcl_ias_zone_attr.o 

C_DEPS += \
./stack/zigbee/zcl/security_safety/zcl_ias_ace.d \
./stack/zigbee/zcl/security_safety/zcl_ias_wd.d \
./stack/zigbee/zcl/security_safety/zcl_ias_wd_attr.d \
./stack/zigbee/zcl/security_safety/zcl_ias_zone.d \
./stack/zigbee/zcl/security_safety/zcl_ias_zone_attr.d 


# Each subdirectory must supply rules for building sources it contributes
stack/zigbee/zcl/security_safety/zcl_ias_ace.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/security_safety/zcl_ias_ace.c stack/zigbee/zcl/security_safety/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/security_safety/zcl_ias_wd.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/security_safety/zcl_ias_wd.c stack/zigbee/zcl/security_safety/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/security_safety/zcl_ias_wd_attr.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/security_safety/zcl_ias_wd_attr.c stack/zigbee/zcl/security_safety/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/security_safety/zcl_ias_zone.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/security_safety/zcl_ias_zone.c stack/zigbee/zcl/security_safety/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/security_safety/zcl_ias_zone_attr.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/security_safety/zcl_ias_zone_attr.c stack/zigbee/zcl/security_safety/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


