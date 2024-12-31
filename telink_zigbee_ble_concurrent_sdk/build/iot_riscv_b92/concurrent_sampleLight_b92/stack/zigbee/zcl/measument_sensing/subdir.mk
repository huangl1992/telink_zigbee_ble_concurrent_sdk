################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_electrical_measurement.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_electrical_measurement_attr.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_illuminance_measurement.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_illuminance_measurement_attr.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_occupancy_sensing.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_occupancy_sensing_attr.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_temperature_measurement.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_temperature_measurement_attr.c 

OBJS += \
./stack/zigbee/zcl/measument_sensing/zcl_electrical_measurement.o \
./stack/zigbee/zcl/measument_sensing/zcl_electrical_measurement_attr.o \
./stack/zigbee/zcl/measument_sensing/zcl_illuminance_measurement.o \
./stack/zigbee/zcl/measument_sensing/zcl_illuminance_measurement_attr.o \
./stack/zigbee/zcl/measument_sensing/zcl_occupancy_sensing.o \
./stack/zigbee/zcl/measument_sensing/zcl_occupancy_sensing_attr.o \
./stack/zigbee/zcl/measument_sensing/zcl_temperature_measurement.o \
./stack/zigbee/zcl/measument_sensing/zcl_temperature_measurement_attr.o 

C_DEPS += \
./stack/zigbee/zcl/measument_sensing/zcl_electrical_measurement.d \
./stack/zigbee/zcl/measument_sensing/zcl_electrical_measurement_attr.d \
./stack/zigbee/zcl/measument_sensing/zcl_illuminance_measurement.d \
./stack/zigbee/zcl/measument_sensing/zcl_illuminance_measurement_attr.d \
./stack/zigbee/zcl/measument_sensing/zcl_occupancy_sensing.d \
./stack/zigbee/zcl/measument_sensing/zcl_occupancy_sensing_attr.d \
./stack/zigbee/zcl/measument_sensing/zcl_temperature_measurement.d \
./stack/zigbee/zcl/measument_sensing/zcl_temperature_measurement_attr.d 


# Each subdirectory must supply rules for building sources it contributes
stack/zigbee/zcl/measument_sensing/zcl_electrical_measurement.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_electrical_measurement.c stack/zigbee/zcl/measument_sensing/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/measument_sensing/zcl_electrical_measurement_attr.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_electrical_measurement_attr.c stack/zigbee/zcl/measument_sensing/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/measument_sensing/zcl_illuminance_measurement.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_illuminance_measurement.c stack/zigbee/zcl/measument_sensing/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/measument_sensing/zcl_illuminance_measurement_attr.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_illuminance_measurement_attr.c stack/zigbee/zcl/measument_sensing/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/measument_sensing/zcl_occupancy_sensing.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_occupancy_sensing.c stack/zigbee/zcl/measument_sensing/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/measument_sensing/zcl_occupancy_sensing_attr.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_occupancy_sensing_attr.c stack/zigbee/zcl/measument_sensing/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/measument_sensing/zcl_temperature_measurement.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_temperature_measurement.c stack/zigbee/zcl/measument_sensing/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/zcl/measument_sensing/zcl_temperature_measurement_attr.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/zcl/measument_sensing/zcl_temperature_measurement_attr.c stack/zigbee/zcl/measument_sensing/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


