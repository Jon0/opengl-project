################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../spline/DynamicPose.cpp \
../spline/Path.cpp \
../spline/Spline.cpp 

OBJS += \
./spline/DynamicPose.o \
./spline/Path.o \
./spline/Spline.o 

CPP_DEPS += \
./spline/DynamicPose.d \
./spline/Path.d \
./spline/Spline.d 


# Each subdirectory must supply rules for building sources it contributes
spline/%.o: ../spline/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I"/am/phoenix/home1/remnanjona/git/animation/library" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


