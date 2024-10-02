################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32u585aiixq.s 

S_DEPS += \
./Core/Startup/startup_stm32u585aiixq.d 

OBJS += \
./Core/Startup/startup_stm32u585aiixq.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m33 -g3 -DDEBUG -c -I"C:/Users/user/Desktop/WIDB/WIDB/Core/Inc" -I"C:/Users/user/Desktop/WIDB/WIDB/Core/Src" -I"C:/Users/user/Desktop/WIDB/WIDB/TouchGFX/target" -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/ST7789" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/BL6133" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/WiFi_BLE" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/CatM1" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/BLE" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers/BLE/stm32wb_at" -I"C:/Users/user/Desktop/WIDB/WIDB/Drivers" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32u585aiixq.d ./Core/Startup/startup_stm32u585aiixq.o

.PHONY: clean-Core-2f-Startup

