# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Configuration for compiling the GDPMessages project, this is a static library
# 
# Authored by Robert Johnson.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

message(STATUS "Static Library: ${GDP_MESSAGES_TARGET} (${GDP_MESSAGES_OUTPUT})")

set(GDP_GDP_INCLUDE
	"${PROJECT_SOURCE_DIR}/GDPMessages"
)

file(GLOB_RECURSE GDP_MESSAGES_SOURCES
	"${PROJECT_SOURCE_DIR}/GDPMessages/*.cpp"
	"${PROJECT_SOURCE_DIR}/GDPMessages/*.c"
	"${PROJECT_SOURCE_DIR}/GDPMessages/*.h"
)

# Setup folder hierarchy
GDP_GROUP_SOURCES(GDPMessages GDPMessages)

# Add project to system
add_library(${GDP_MESSAGES_TARGET} ${GDP_MESSAGES_SOURCES})

# Setup include/compile/link options
target_compile_options		(${GDP_MESSAGES_TARGET} PRIVATE ${GDP_COMPILE_FLAGS})
target_compile_definitions	(${GDP_MESSAGES_TARGET} PRIVATE ${GDP_COMPILE_DEFS})
target_include_directories	(${GDP_MESSAGES_TARGET} PRIVATE ${GDP_MESSAGES_INCLUDE})

# Used to setup Qt include paths correctly.
# Not really any linking going as this is static.
target_link_libraries		(${GDP_MESSAGES_TARGET} Qt5::Core)

set_target_properties(${GDP_MESSAGES_TARGET}
	PROPERTIES
	OUTPUT_NAME 		${GDP_MESSAGES_OUTPUT}
	LINKER_LANGUAGE		CXX
	LINK_FLAGS_DEBUG	"${PLATFORM_LINKER_FLAGS_DEBUG}"
	LINK_FLAGS_RELEASE	"${PLATFORM_LINKER_FLAGS_RELEASE}"
)

# Strip
GDP_STRIP_TARGET(${GDP_MESSAGES_TARGET})