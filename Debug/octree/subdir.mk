################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../octree/Tree.cpp \
../octree/TreeNode.cpp 

OBJS += \
./octree/Tree.o \
./octree/TreeNode.o 

CPP_DEPS += \
./octree/Tree.d \
./octree/TreeNode.d 


# Each subdirectory must supply rules for building sources it contributes
octree/%.o: ../octree/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I../library/ -I"/u/students/remnanjona/lib/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


