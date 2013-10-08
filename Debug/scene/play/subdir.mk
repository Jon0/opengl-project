################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../scene/play/SkeletonTransform.cpp 

OBJS += \
./scene/play/SkeletonTransform.o 

CPP_DEPS += \
./scene/play/SkeletonTransform.d 


# Each subdirectory must supply rules for building sources it contributes
scene/play/%.o: ../scene/play/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I../library/ -I"/u/students/remnanjona/lib/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


