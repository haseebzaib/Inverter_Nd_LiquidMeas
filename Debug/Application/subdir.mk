################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Application/ControlnDDisplayTask.cpp \
../Application/InverterTask.cpp \
../Application/ModemTask.cpp \
../Application/app_main.cpp 

OBJS += \
./Application/ControlnDDisplayTask.o \
./Application/InverterTask.o \
./Application/ModemTask.o \
./Application/app_main.o 

CPP_DEPS += \
./Application/ControlnDDisplayTask.d \
./Application/InverterTask.d \
./Application/ModemTask.d \
./Application/app_main.d 


# Each subdirectory must supply rules for building sources it contributes
Application/%.o Application/%.su Application/%.cyclo: ../Application/%.cpp Application/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/haseeb/liquidMeasuringProject/Inverter_Nd_LiquidMeas/Application" -I"F:/haseeb/liquidMeasuringProject/Inverter_Nd_LiquidMeas/Application/Display" -I"F:/haseeb/liquidMeasuringProject/Inverter_Nd_LiquidMeas/Application/System" -I"F:/haseeb/liquidMeasuringProject/Inverter_Nd_LiquidMeas/Application/Sensor" -I"F:/haseeb/liquidMeasuringProject/Inverter_Nd_LiquidMeas/Application/Modem" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m4/gnu/inc/ -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application

clean-Application:
	-$(RM) ./Application/ControlnDDisplayTask.cyclo ./Application/ControlnDDisplayTask.d ./Application/ControlnDDisplayTask.o ./Application/ControlnDDisplayTask.su ./Application/InverterTask.cyclo ./Application/InverterTask.d ./Application/InverterTask.o ./Application/InverterTask.su ./Application/ModemTask.cyclo ./Application/ModemTask.d ./Application/ModemTask.o ./Application/ModemTask.su ./Application/app_main.cyclo ./Application/app_main.d ./Application/app_main.o ./Application/app_main.su

.PHONY: clean-Application

