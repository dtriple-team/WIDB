################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/sleepscreen_screen/SleepScreenPresenter.cpp \
../TouchGFX/gui/src/sleepscreen_screen/SleepScreenView.cpp 

OBJS += \
./TouchGFX/gui/src/sleepscreen_screen/SleepScreenPresenter.o \
./TouchGFX/gui/src/sleepscreen_screen/SleepScreenView.o 

CPP_DEPS += \
./TouchGFX/gui/src/sleepscreen_screen/SleepScreenPresenter.d \
./TouchGFX/gui/src/sleepscreen_screen/SleepScreenView.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/sleepscreen_screen/%.o TouchGFX/gui/src/sleepscreen_screen/%.su TouchGFX/gui/src/sleepscreen_screen/%.cyclo: ../TouchGFX/gui/src/sleepscreen_screen/%.cpp TouchGFX/gui/src/sleepscreen_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Drivers/pmic -I../Drivers/sensorhub -I../Drivers/pmic/MAX20303 -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB_jh/Core/Src" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB_jh/Drivers/ST7789" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB_jh/Drivers/BL6133" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB_jh/Drivers/WiFi_BLE" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB_jh/Drivers/CatM1" -I"C:/Users/D-triple/Desktop/WIDB_prj/WIDB_jh/Drivers/BLE" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-sleepscreen_screen

clean-TouchGFX-2f-gui-2f-src-2f-sleepscreen_screen:
	-$(RM) ./TouchGFX/gui/src/sleepscreen_screen/SleepScreenPresenter.cyclo ./TouchGFX/gui/src/sleepscreen_screen/SleepScreenPresenter.d ./TouchGFX/gui/src/sleepscreen_screen/SleepScreenPresenter.o ./TouchGFX/gui/src/sleepscreen_screen/SleepScreenPresenter.su ./TouchGFX/gui/src/sleepscreen_screen/SleepScreenView.cyclo ./TouchGFX/gui/src/sleepscreen_screen/SleepScreenView.d ./TouchGFX/gui/src/sleepscreen_screen/SleepScreenView.o ./TouchGFX/gui/src/sleepscreen_screen/SleepScreenView.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-sleepscreen_screen

