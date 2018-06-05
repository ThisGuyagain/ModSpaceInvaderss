#Generated by VisualGDB (http://visualgdb.com)
#DO NOT EDIT THIS FILE MANUALLY UNLESS YOU ABSOLUTELY NEED TO
#USE VISUALGDB PROJECT PROPERTIES DIALOG INSTEAD

BINARYDIR := Debug

#Toolchain
CC := gcc
CXX := g++
LD := $(CXX)
AR := ar
OBJCOPY := objcopy

#Additional flags
PREPROCESSOR_MACROS := DEBUG RASPBERRY
INCLUDE_DIRS := /opt/vc/include /opt/vc/include/interface/vcos/pthreads /opt/vc/include/interface /opt/vc/include/interface/vmcs_host/linux
LIBRARY_DIRS := /opt/vc/lib /usr/lib/arm-linux-gnueabihf
LIBRARY_NAMES := GLESv2_static EGL_static vchiq_arm vcos khrn_static bcm_host pthread
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -ggdb -ffunction-sections -O0 -std=c++11
CXXFLAGS := -ggdb -ffunction-sections -O0 -std=c++11
ASFLAGS := 
LDFLAGS := -Wl,-gc-sections
COMMONFLAGS := 
LINKER_SCRIPT := 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group

#Additional options detected from testing the toolchain
IS_LINUX_PROJECT := 1
