################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../geometry/Cube.cpp \
../geometry/DrawList.cpp \
../geometry/GMesh.cpp \
../geometry/GPolygon.cpp \
../geometry/GVertex.cpp \
../geometry/Skeleton.cpp \
../geometry/SkeletonMesh.cpp \
../geometry/Teapot.cpp 

OBJS += \
./geometry/Cube.o \
./geometry/DrawList.o \
./geometry/GMesh.o \
./geometry/GPolygon.o \
./geometry/GVertex.o \
./geometry/Skeleton.o \
./geometry/SkeletonMesh.o \
./geometry/Teapot.o 

CPP_DEPS += \
./geometry/Cube.d \
./geometry/DrawList.d \
./geometry/GMesh.d \
./geometry/GPolygon.d \
./geometry/GVertex.d \
./geometry/Skeleton.d \
./geometry/SkeletonMesh.d \
./geometry/Teapot.d 


# Each subdirectory must supply rules for building sources it contributes
geometry/%.o: ../geometry/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I../library/ -I"/u/students/remnanjona/lib/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


