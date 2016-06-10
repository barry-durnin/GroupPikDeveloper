# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Entry point for the GDP solution CMake scripts. These are used as a cross-
# platform method of generating build scripts which should facilitate swift
# uptake on target architectures/platforms with little cost.
# 
# Authored by Robert Johnson.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

cmake_minimum_required(VERSION 2.8.12.2 FATAL_ERROR)

# Project description
set(PROJECT_NAME "GDP")

# Options
option(GDP_LIMIT_CONFIGS 			"Generate limited configs (just Debug and Release"	ON)
option(GDP_ENABLE_FRIENDLY_NAMES 	"Enables friendly project names on MSVC"			ON)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# CMake configuration
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

if(PE_LIMIT_CONFIGS)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited Configs" FORCE)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: ${CMAKE_CONFIGURATION_TYPES}")
set(CMAKE_SKIP_RPATH TRUE)
set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)		# Used by the IDEs for grouping source files.
include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/Macros.cmake)

message(STATUS "Generating for build config: ${CMAKE_BUILD_TYPE}")

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Solution configuration
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

project(${PROJECT_NAME} C CXX)
GDP_SETUP_ARCHITECTURE()
GDP_SETUP_PLATFORM()

# Libraries
# Note: Setup an environment variable to point to your Qt installation
# 		e.g. QT_DEV_PATH = Z:\Development\Qt\5.6
#		This folder should contain a folder named "msvc2015_64" (and others maybe)
GDP_SETUP_QT()

# Binary destination
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PLATFORM_BINARIES_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLATFORM_BINARIES_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PLATFORM_BINARIES_PATH})

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Project defines - global
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

message(STATUS "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
message("                 Configuring options                 ")
message(STATUS "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

set(GDP_COMPILE_FLAGS ${PLATFOMR_COMPILE_FLAGS})
set(GDP_COMPILE_DEFS ${PLATFORM_COMPILE_DEFS})

# This is an example of how to setup an option, theres the option name which is
# specified above, then theres the define that you would use in the code to enable/
# disable the functionality. Naturally these could be the same name if desired.
# GDP_ENABLE_OPTION_IF(GDP_COMPILE_DEFS GBP_ENABLE_SOME_CMAKE_OPTION GDP_CODE_DEFINE_NAME "Enabling some option")

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Project setup - per project
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

message(STATUS "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
message("                Configuring projects                 ")
message(STATUS "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

# This may seem pointless duplicating the project name vs. friendly name,
# this is a little future thinking that it'll grow to ridiculous names.
GDP_MAKE_PROJECT_NAME(GDP_CLIENT		GDPClient 			GDPClient)
GDP_MAKE_PROJECT_NAME(GDP_MESSAGES		GDPMessages 		GDPMessages)
GDP_MAKE_PROJECT_NAME(GDP_SERVER 		GDPServer 			GDPServer)

# Add projects
add_subdirectory(GDP)
add_subdirectory(GDPMessages)
add_subdirectory(GDPServer)

# Setup dependencies
add_dependencies(${GDP_CLIENT_TARGET}	${GDP_MESSAGES_TARGET})
add_dependencies(${GDP_SERVER_TARGET}	${GDP_MESSAGES_TARGET})

message(STATUS "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")