################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/ClientConfig.cpp \
../Source/GroupConfig.cpp \
../Source/HazelcastClient.cpp \
../Source/IMap.cpp 

OBJS += \
./Source/ClientConfig.o \
./Source/GroupConfig.o \
./Source/HazelcastClient.o \
./Source/IMap.o 

CPP_DEPS += \
./Source/ClientConfig.d \
./Source/GroupConfig.d \
./Source/HazelcastClient.d \
./Source/IMap.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


