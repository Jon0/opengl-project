################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../pipeline/Pipeline.cpp \
../pipeline/Render.cpp \
../pipeline/Skybox.cpp \
../pipeline/Voxelize.cpp 

OBJS += \
./pipeline/Pipeline.o \
./pipeline/Render.o \
./pipeline/Skybox.o \
./pipeline/Voxelize.o 

CPP_DEPS += \
./pipeline/Pipeline.d \
./pipeline/Render.d \
./pipeline/Skybox.d \
./pipeline/Voxelize.d 


# Each subdirectory must supply rules for building sources it contributes
pipeline/%.o: ../pipeline/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I../library/ -I"/u/students/remnanjona/lib/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


