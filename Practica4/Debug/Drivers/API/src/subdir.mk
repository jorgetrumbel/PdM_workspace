################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/src/API_debounce.c \
../Drivers/API/src/API_delay.c \
../Drivers/API/src/API_uart.c 

OBJS += \
./Drivers/API/src/API_debounce.o \
./Drivers/API/src/API_delay.o \
./Drivers/API/src/API_uart.o 

C_DEPS += \
./Drivers/API/src/API_debounce.d \
./Drivers/API/src/API_delay.d \
./Drivers/API/src/API_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/src/%.o: ../Drivers/API/src/%.c Drivers/API/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"/home/alejandro/Documents/Programacion_de_microprocesadores/PdM_workspace/Practica4/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/alejandro/Documents/Programacion_de_microprocesadores/PdM_workspace/Practica4/Drivers/CMSIS/Include" -I"/home/alejandro/Documents/Programacion_de_microprocesadores/PdM_workspace/Practica4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/alejandro/Documents/Programacion_de_microprocesadores/PdM_workspace/Practica4/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/home/alejandro/Documents/Programacion_de_microprocesadores/PdM_workspace/Practica4/Drivers/Core/Inc" -I"/home/alejandro/Documents/Programacion_de_microprocesadores/PdM_workspace/Practica4/Drivers/STM32F4xx_HAL_Driver/Src" -I"/home/alejandro/Documents/Programacion_de_microprocesadores/PdM_workspace/Practica4/Drivers/API/src" -I"/home/alejandro/Documents/Programacion_de_microprocesadores/PdM_workspace/Practica4/Drivers/API" -I"/home/alejandro/Documents/Programacion_de_microprocesadores/PdM_workspace/Practica4/Drivers" -I"/home/alejandro/Documents/Programacion_de_microprocesadores/PdM_workspace/Practica4/Drivers/API/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
