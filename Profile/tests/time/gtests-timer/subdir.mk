################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tests/time/gtests-timer/main.cpp 

OBJS += \
./tests/time/gtests-timer/main.o 

CPP_DEPS += \
./tests/time/gtests-timer/main.d 


# Each subdirectory must supply rules for building sources it contributes
tests/time/gtests-timer/%.o: ../tests/time/gtests-timer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_Profile -I"/home/naps62/projects/beast/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


