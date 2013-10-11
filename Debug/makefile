################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include window/subdir.mk
-include view/subdir.mk
-include texture/subdir.mk
-include spline/subdir.mk
-include shader/subdir.mk
-include scene/play/subdir.mk
-include scene/subdir.mk
-include pipeline/subdir.mk
-include octree/subdir.mk
-include math/subdir.mk
-include load/subdir.mk
-include lighting/types/subdir.mk
-include lighting/subdir.mk
-include geometry/subdir.mk
-include buffer/subdir.mk
-include assets/obj/subdir.mk
-include assets/Sponza/subdir.mk
-include assets/Avatar/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: animation

# Tool invocations
animation: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -L/u/students/remnanjona/lib/lib -o "animation" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) animation
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
