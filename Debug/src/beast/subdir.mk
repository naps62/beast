################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/beast/program_options.cpp 

OBJS += \
./src/beast/program_options.o 

CPP_DEPS += \
./src/beast/program_options.d 


# Each subdirectory must supply rules for building sources it contributes
src/beast/%.o: ../src/beast/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/naps62/projects/beast/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


