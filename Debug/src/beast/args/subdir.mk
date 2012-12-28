################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/beast/args/args.cpp 

OBJS += \
./src/beast/args/args.o 

CPP_DEPS += \
./src/beast/args/args.d 


# Each subdirectory must supply rules for building sources it contributes
src/beast/args/%.o: ../src/beast/args/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/naps62/projects/beast/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


