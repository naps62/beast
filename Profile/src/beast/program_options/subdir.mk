################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/beast/program_options/options.cpp 

OBJS += \
./src/beast/program_options/options.o 

CPP_DEPS += \
./src/beast/program_options/options.d 


# Each subdirectory must supply rules for building sources it contributes
src/beast/program_options/%.o: ../src/beast/program_options/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_Profile -I"/home/naps62/projects/beast/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


