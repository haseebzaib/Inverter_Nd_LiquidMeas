################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Application/Sensor/sensor_dht.cpp \
../Application/Sensor/sensor_liquidMeas.cpp 

OBJS += \
./Application/Sensor/sensor_dht.o \
./Application/Sensor/sensor_liquidMeas.o 

CPP_DEPS += \
./Application/Sensor/sensor_dht.d \
./Application/Sensor/sensor_liquidMeas.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Sensor/%.o Application/Sensor/%.su Application/Sensor/%.cyclo: ../Application/Sensor/%.cpp Application/Sensor/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/haseeb/liquidMeasuringProject/Inverter_Nd_LiquidMeas/Application" -I"F:/haseeb/liquidMeasuringProject/Inverter_Nd_LiquidMeas/Application/Sensor" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Sensor

clean-Application-2f-Sensor:
	-$(RM) ./Application/Sensor/sensor_dht.cyclo ./Application/Sensor/sensor_dht.d ./Application/Sensor/sensor_dht.o ./Application/Sensor/sensor_dht.su ./Application/Sensor/sensor_liquidMeas.cyclo ./Application/Sensor/sensor_liquidMeas.d ./Application/Sensor/sensor_liquidMeas.o ./Application/Sensor/sensor_liquidMeas.su

.PHONY: clean-Application-2f-Sensor

