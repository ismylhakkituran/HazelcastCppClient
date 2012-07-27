################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Socket\ Source/ClientSocket.cpp \
../Socket\ Source/Socket.cpp 

OBJS += \
./Socket\ Source/ClientSocket.o \
./Socket\ Source/Socket.o 

CPP_DEPS += \
./Socket\ Source/ClientSocket.d \
./Socket\ Source/Socket.d 


# Each subdirectory must supply rules for building sources it contributes
Socket\ Source/ClientSocket.o: ../Socket\ Source/ClientSocket.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Socket Source/ClientSocket.d" -MT"Socket\ Source/ClientSocket.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Socket\ Source/Socket.o: ../Socket\ Source/Socket.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Socket Source/Socket.d" -MT"Socket\ Source/Socket.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


