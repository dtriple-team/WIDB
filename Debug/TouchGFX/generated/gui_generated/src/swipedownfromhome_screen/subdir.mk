################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/swipedownfromHomeViewBase.cpp 

OBJS += \
./TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/swipedownfromHomeViewBase.o 

CPP_DEPS += \
./TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/swipedownfromHomeViewBase.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/%.o TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/%.su TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/%.cyclo: ../TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/%.cpp TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Drivers/pmic -I../Drivers/sensorhub -I../Drivers/pmic/MAX20303 -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB/Core/Src" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB/Drivers/ST7789" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB/Drivers/BL6133" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB/Drivers/WiFi_BLE" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB/Drivers/CatM1" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB/Drivers/BLE" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB/Drivers/BLE/stm32wb_at" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB/Drivers" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-swipedownfromhome_screen

clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-swipedownfromhome_screen:
	-$(RM) ./TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/swipedownfromHomeViewBase.cyclo ./TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/swipedownfromHomeViewBase.d ./TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/swipedownfromHomeViewBase.o ./TouchGFX/generated/gui_generated/src/swipedownfromhome_screen/swipedownfromHomeViewBase.su

.PHONY: clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-swipedownfromhome_screen

