################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gpEpCfg.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_proxy.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_proxyTab.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_sink.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_sinkTab.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_trans.c \
F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_transCfg.c 

OBJS += \
./stack/zigbee/gp/gp.o \
./stack/zigbee/gp/gpEpCfg.o \
./stack/zigbee/gp/gp_proxy.o \
./stack/zigbee/gp/gp_proxyTab.o \
./stack/zigbee/gp/gp_sink.o \
./stack/zigbee/gp/gp_sinkTab.o \
./stack/zigbee/gp/gp_trans.o \
./stack/zigbee/gp/gp_transCfg.o 

C_DEPS += \
./stack/zigbee/gp/gp.d \
./stack/zigbee/gp/gpEpCfg.d \
./stack/zigbee/gp/gp_proxy.d \
./stack/zigbee/gp/gp_proxyTab.d \
./stack/zigbee/gp/gp_sink.d \
./stack/zigbee/gp/gp_sinkTab.d \
./stack/zigbee/gp/gp_trans.d \
./stack/zigbee/gp/gp_transCfg.d 


# Each subdirectory must supply rules for building sources it contributes
stack/zigbee/gp/gp.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp.c stack/zigbee/gp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/gp/gpEpCfg.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gpEpCfg.c stack/zigbee/gp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/gp/gp_proxy.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_proxy.c stack/zigbee/gp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/gp/gp_proxyTab.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_proxyTab.c stack/zigbee/gp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/gp/gp_sink.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_sink.c stack/zigbee/gp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/gp/gp_sinkTab.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_sinkTab.c stack/zigbee/gp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/gp/gp_trans.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_trans.c stack/zigbee/gp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stack/zigbee/gp/gp_transCfg.o: F:/telink/x-zigbee-sdk/telink_zigbee_ble_concurrent_sdk_20241217/stack/zigbee/gp/gp_transCfg.c stack/zigbee/gp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-elf-gcc -mcmodel=medium -mcmodel=medium -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -flto -Wall -Wno-nonnull-compare -DMCU_CORE_B92=1 -DROUTER=1 -D__PROJECT_TL_LIGHT__=1 -I"C:\TelinkIoTStudio\\RDS\V5.1.2\toolchains\nds32le-elf-mculib-v5f\lib\gcc\riscv32-elf\10.3.0\include" -I../../../stack/ble -I../../../apps/common -I../../../apps/sampleLight_concurrent -I../../../platform/chip_b92 -I../../../platform/riscv -I../../../platform -I../../../proj/common -I../../../proj -I../../../stack/zigbee/common/includes -I../../../stack/zigbee/zbapi -I../../../stack/zigbee/bdb/includes -I../../../stack/zigbee/gp -I../../../stack/zigbee/zcl -I../../../stack/zigbee/ota -I../../../stack/zigbee/wwah -I../../../ -I../../../zbhci -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fuse-ld=bfd -fno-jump-tables -fno-fat-lto-objects -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


