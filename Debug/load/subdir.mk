################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../load/AnimationLoader.cpp \
../load/GeometryLoader.cpp \
../load/LineTokenizer.cpp \
../load/SkeletonLoader.cpp 

OBJS += \
./load/AnimationLoader.o \
./load/GeometryLoader.o \
./load/LineTokenizer.o \
./load/SkeletonLoader.o 

CPP_DEPS += \
./load/AnimationLoader.d \
./load/GeometryLoader.d \
./load/LineTokenizer.d \
./load/SkeletonLoader.d 


# Each subdirectory must supply rules for building sources it contributes
load/%.o: ../load/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I"/am/phoenix/home1/remnanjona/git/animation/library" -I/am/phoenix/home1/remnanjona/lib/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


