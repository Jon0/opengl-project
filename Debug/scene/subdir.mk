################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../scene/GRender.cpp \
../scene/Scene.cpp \
../scene/SpeedCurve.cpp \
../scene/ViewSpline.cpp 

OBJS += \
./scene/GRender.o \
./scene/Scene.o \
./scene/SpeedCurve.o \
./scene/ViewSpline.o 

CPP_DEPS += \
./scene/GRender.d \
./scene/Scene.d \
./scene/SpeedCurve.d \
./scene/ViewSpline.d 


# Each subdirectory must supply rules for building sources it contributes
scene/%.o: ../scene/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I"/am/phoenix/home1/remnanjona/git/animation/library" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


