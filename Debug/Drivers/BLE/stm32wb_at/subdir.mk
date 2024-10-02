################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BLE/stm32wb_at/ble_at_appli.c \
../Drivers/BLE/stm32wb_at/stm32wb_at.c \
../Drivers/BLE/stm32wb_at/stm32wb_at_ble.c \
../Drivers/BLE/stm32wb_at/stm32wb_at_client.c \
../Drivers/BLE/stm32wb_at/stm32wb_at_ll.c 

C_DEPS += \
./Drivers/BLE/stm32wb_at/ble_at_appli.d \
./Drivers/BLE/stm32wb_at/stm32wb_at.d \
./Drivers/BLE/stm32wb_at/stm32wb_at_ble.d \
./Drivers/BLE/stm32wb_at/stm32wb_at_client.d \
./Drivers/BLE/stm32wb_at/stm32wb_at_ll.d 

OBJS += \
./Drivers/BLE/stm32wb_at/ble_at_appli.o \
./Drivers/BLE/stm32wb_at/stm32wb_at.o \
./Drivers/BLE/stm32wb_at/stm32wb_at_ble.o \
./Drivers/BLE/stm32wb_at/stm32wb_at_client.o \
./Drivers/BLE/stm32wb_at/stm32wb_at_ll.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BLE/stm32wb_at/%.o Drivers/BLE/stm32wb_at/%.su Drivers/BLE/stm32wb_at/%.cyclo: ../Drivers/BLE/stm32wb_at/%.c Drivers/BLE/stm32wb_at/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Core/Inc -I../Drivers/sensorhub -I../Drivers/pmic -I../Drivers/pmic/MAX20303 -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I"C:/Users/user/Desktop/WIDB/WIDB/Core/Src" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/ST7789" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/BL6133" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/WiFi_BLE" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/CatM1" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/BLE" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/BLE/stm32wb_at" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BLE-2f-stm32wb_at

clean-Drivers-2f-BLE-2f-stm32wb_at:
	-$(RM) ./Drivers/BLE/stm32wb_at/ble_at_appli.cyclo ./Drivers/BLE/stm32wb_at/ble_at_appli.d ./Drivers/BLE/stm32wb_at/ble_at_appli.o ./Drivers/BLE/stm32wb_at/ble_at_appli.su ./Drivers/BLE/stm32wb_at/stm32wb_at.cyclo ./Drivers/BLE/stm32wb_at/stm32wb_at.d ./Drivers/BLE/stm32wb_at/stm32wb_at.o ./Drivers/BLE/stm32wb_at/stm32wb_at.su ./Drivers/BLE/stm32wb_at/stm32wb_at_ble.cyclo ./Drivers/BLE/stm32wb_at/stm32wb_at_ble.d ./Drivers/BLE/stm32wb_at/stm32wb_at_ble.o ./Drivers/BLE/stm32wb_at/stm32wb_at_ble.su ./Drivers/BLE/stm32wb_at/stm32wb_at_client.cyclo ./Drivers/BLE/stm32wb_at/stm32wb_at_client.d ./Drivers/BLE/stm32wb_at/stm32wb_at_client.o ./Drivers/BLE/stm32wb_at/stm32wb_at_client.su ./Drivers/BLE/stm32wb_at/stm32wb_at_ll.cyclo ./Drivers/BLE/stm32wb_at/stm32wb_at_ll.d ./Drivers/BLE/stm32wb_at/stm32wb_at_ll.o ./Drivers/BLE/stm32wb_at/stm32wb_at_ll.su

.PHONY: clean-Drivers-2f-BLE-2f-stm32wb_at

