################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lighting/types/Directional.cpp \
../lighting/types/Positional.cpp \
../lighting/types/Spotlight.cpp 

OBJS += \
./lighting/types/Directional.o \
./lighting/types/Positional.o \
./lighting/types/Spotlight.o 

CPP_DEPS += \
./lighting/types/Directional.d \
./lighting/types/Positional.d \
./lighting/types/Spotlight.d 


# Each subdirectory must supply rules for building sources it contributes
lighting/types/%.o: ../lighting/types/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I"/am/phoenix/home1/remnanjona/git/animation/library" -I/am/phoenix/home1/remnanjona/lib/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


