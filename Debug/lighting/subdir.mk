################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lighting/LightingModel.cpp \
../lighting/Tree.cpp \
../lighting/TreeNode.cpp 

OBJS += \
./lighting/LightingModel.o \
./lighting/Tree.o \
./lighting/TreeNode.o 

CPP_DEPS += \
./lighting/LightingModel.d \
./lighting/Tree.d \
./lighting/TreeNode.d 


# Each subdirectory must supply rules for building sources it contributes
lighting/%.o: ../lighting/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I"/am/phoenix/home1/remnanjona/git/animation/library" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


