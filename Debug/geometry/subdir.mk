################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../geometry/Animation.cpp \
../geometry/Skeleton.cpp \
../geometry/Spline.cpp 

OBJS += \
./geometry/Animation.o \
./geometry/Skeleton.o \
./geometry/Spline.o 

CPP_DEPS += \
./geometry/Animation.d \
./geometry/Skeleton.d \
./geometry/Spline.d 


# Each subdirectory must supply rules for building sources it contributes
geometry/%.o: ../geometry/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


