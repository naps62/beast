################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tests/program_options/gtests-po_options/main.cpp 

OBJS += \
./tests/program_options/gtests-po_options/main.o 

CPP_DEPS += \
./tests/program_options/gtests-po_options/main.d 


# Each subdirectory must supply rules for building sources it contributes
tests/program_options/gtests-po_options/%.o: ../tests/program_options/gtests-po_options/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_Profile -I"/home/naps62/projects/beast/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


