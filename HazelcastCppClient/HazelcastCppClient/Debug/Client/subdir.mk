################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Client/ClientConfig.cpp \
../Client/Foo.cpp \
../Client/GroupConfig.cpp \
../Client/HazelcastClient.cpp \
../Client/Map.cpp 

OBJS += \
./Client/ClientConfig.o \
./Client/Foo.o \
./Client/GroupConfig.o \
./Client/HazelcastClient.o \
./Client/Map.o 

CPP_DEPS += \
./Client/ClientConfig.d \
./Client/Foo.d \
./Client/GroupConfig.d \
./Client/HazelcastClient.d \
./Client/Map.d 


# Each subdirectory must supply rules for building sources it contributes
Client/%.o: ../Client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


