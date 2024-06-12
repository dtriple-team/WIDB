################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/max32630hsp/max32630hsp.cpp 

OBJS += \
./Drivers/max32630hsp/max32630hsp.o 

CPP_DEPS += \
./Drivers/max32630hsp/max32630hsp.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/max32630hsp/%.o Drivers/max32630hsp/%.su Drivers/max32630hsp/%.cyclo: ../Drivers/max32630hsp/%.cpp Drivers/max32630hsp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Core/Inc -I../Drivers/max32630hsp -I../Drivers/max32630hsp/MAX20303 -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-max32630hsp

clean-Drivers-2f-max32630hsp:
	-$(RM) ./Drivers/max32630hsp/max32630hsp.cyclo ./Drivers/max32630hsp/max32630hsp.d ./Drivers/max32630hsp/max32630hsp.o ./Drivers/max32630hsp/max32630hsp.su

.PHONY: clean-Drivers-2f-max32630hsp

