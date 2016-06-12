# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Various CMake macros used to help in the development of the CMake build scripts
# employed by this project.
# 
# Authored by Robert Johnson.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Groups source code by folder structure by recrusively walking through the 
# structure starting from SOURCE_DIR.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
macro(GDP_GROUP_SOURCES SOURCE_DIR)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${SOURCE_DIR}	${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/*)

	foreach(child ${children})
		if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/${child})
			GDP_GROUP_SOURCES(${SOURCE_DIR}/${child})
		else()
			string(REPLACE "/" "\\" GROUP_NAME ${SOURCE_DIR})
			source_group(${GROUP_NAME} FILES ${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/${child})
		endif()
	endforeach()
endmacro()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Groups source code by folder structure by recursively walking through the
# structure starting from SOURCE_DIR, this removes the RELATIVE_DIR portion
# from the grouping. Such that nested source directories can be trimmed upwards.
# i.e. source lives in src/core/, src/core/ is common amongst all the source
# in the project so trim it from the group names to reduce folder depth in
# the IDE for convenience sake.
# 
# Note: SOURCE_DIR & RELATIVE_DIR should not contain a trailing slash.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
macro(GDP_GROUP_SOURCES SOURCE_DIR RELATIVE_DIR)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${SOURCE_DIR}	${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/*)

	foreach(child ${children})
		if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/${child})
			GDP_GROUP_SOURCES(${SOURCE_DIR}/${child} ${RELATIVE_DIR})
		else()
			if(${RELATIVE_DIR} STREQUAL ${SOURCE_DIR})
				set(GROUP_NAME " ")
			else()
				string(REPLACE "${RELATIVE_DIR}/" "" RELATIVE_SOURCE_DIR ${SOURCE_DIR})
				string(REPLACE "/" "\\" GROUP_NAME ${RELATIVE_SOURCE_DIR})
			endif()

			set(CHILD_FILE ${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/${child})

			# Add file to source group
			source_group(${GROUP_NAME} FILES ${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/${child})
		endif()
	endforeach()
endmacro()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Detects the chosen platform architecture for selecting the correct libraries.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
macro(GDP_SETUP_ARCHITECTURE)
	set(X64 OFF)
	set(PLATFORM_ARCHITECTURE "x86")
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(X64 ON)
		set(PLATFORM_ARCHITECTURE "x64")
	endif()
endmacro()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Sets up the platform based upon the detected local architecture/OS. This 
# essentially removes cross-compile support. Not an issue right now.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
macro(GDP_SETUP_PLATFORM)
	if(MSVC)
		include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/PlatformWindows.cmake)
	elseif(UNIX)
		include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/PlatformLinux.cmake)
	else()
		message(FATAL_ERROR "Unsupported platform/compiler combination")
	endif()
endmacro()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Wrapper around appending an option to a list based upon a condition being
# met.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
macro(GDP_ENABLE_OPTION_IF LIST_VAL CHECK IF_VAL MESSAGE)
	if(${CHECK})
		message("${MESSAGE}: true")
		list(APPEND ${LIST_VAL} ${IF_VAL})
	else()
		message(STATUS "${MESSAGE}: false")
	endif()
endmacro()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Same as above except it handles the else case.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
macro(GDP_ENABLE_OPTION_EF LIST_VAL CHECK IF_VAL ELSE_VAL MESSAGE)
	if(${CHECK})
		message("${MESSAGE}: true")
		list(APPEND ${LIST_VAL} ${IF_VAL})
	else()
		message(STATUS "${MESSAGE}: false")
		list(APPEND ${LIST_VAL} ${ELSE_VAL})
	endif()
endmacro()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Helper to add a custom command post-build that strips all unneeded symbols
# from a binary on Linux (Windows is pretty good at doing this already).
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
macro(GDP_STRIP_TARGET TARGET_NAME)
	if(NOT MSVC)
		if( NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
			add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND strip --strip-unneeded $<TARGET_FILE:${TARGET_NAME}>)
		endif()
	endif()
endmacro()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Sets up the name of individual projects, as projects should have a friendly
# name, i.e. GDP, but need a proper binary name libGDP.lib the binary name is
# the name that get's linked against. Interestingly the MSVC generator can 
# resolve correctly against a targets #output_name property, but the GCC generator
# can't, it tries to resolve against the target name, to solve all problems this
# macro behaves differently on Windows
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
macro(GDP_MAKE_PROJECT_NAME IDENTIFIER FRIENDLY_NAME OUTPUT_NAME)
	if(NOT MSVC OR NOT GDP_ENABLE_FRIENDLY_NAMES)
		set(${IDENTIFIER}_TARGET ${OUTPUT_NAME})
		set(${IDENTIFIER}_OUTPUT ${OUTPUT_NAME})
	else()
		set(${IDENTIFIER}_TARGET ${FRIENDLY_NAME})
		set(${IDENTIFIER}_OUTPUT ${OUTPUT_NAME})
	endif()
endmacro()


macro(GDP_SETUP_QT)
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
	set(CMAKE_AUTOMOC OFF)
	set(CMAKE_AUTOUIC OFF)

	message($ENV{QT_DEV_PATH})

	# @todo Handle different platforms/enviroment
	if(X64)
		set(CMAKE_PREFIX_PATH $ENV{QT_DEV_PATH}/msvc2015_64)
	else()
		set(CMAKE_PREFIX_PATH $ENV{QT_DEV_PATH}/msvc2015)
	endif()

	find_package(Qt5Core)
	find_package(Qt5Widgets)
	find_package(Qt5Multimedia)
	find_package(Qt5MultimediaWidgets)
	find_package(Qt5Network)
	find_package(Qt5Sql)
	# Plus any other packages the projects may need

endmacro()