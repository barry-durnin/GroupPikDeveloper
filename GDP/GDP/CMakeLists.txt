# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Configuration for compiling the GDP client project, this is an executable
# 
# Authored by Robert Johnson.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

message(STATUS "Executable: ${GDP_CLIENT_TARGET} (${GDP_CLIENT_OUTPUT})")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(GDP_CLIENT_INCLUDE
	"${PROJECT_SOURCE_DIR}/GDP"
	"${PROJECT_SOURCE_DIR}/GDPMessages"
)

file(GLOB_RECURSE GDP_CLIENT_SOURCES
	"${PROJECT_SOURCE_DIR}/GDP/*.cpp"
	"${PROJECT_SOURCE_DIR}/GDP/*.c"
	"${PROJECT_SOURCE_DIR}/GDP/*.h"
	"${PROJECT_SOURCE_DIR}/GDP/*.inl"
	"${PROJECT_SOURCE_DIR}/GDP/*.qrc"
	"${PROJECT_SOURCE_DIR}/GDP/*.ui"
)

# Setup folder hierarchy, the left arg is the folder to search,
# the right arg is the relative folder (i.e. strip this bit from
# the left folder when building the hierarchy).
GDP_GROUP_SOURCES(GDP GDP)

# Add project to system
add_executable(${GDP_CLIENT_TARGET} ${GDP_CLIENT_SOURCES})

# Setup include/compile/link options
target_compile_options		(${GDP_CLIENT_TARGET} PRIVATE ${GDP_COMPILE_FLAGS})
target_compile_definitions	(${GDP_CLIENT_TARGET} PRIVATE ${GDP_COMPILE_DEFS})
target_include_directories	(${GDP_CLIENT_TARGET} PRIVATE ${GDP_CLIENT_INCLUDE})
target_link_libraries		(${GDP_CLIENT_TARGET}
								${GDP_MESSAGES_TARGET}
								Qt5::Widgets 
								Qt5::Multimedia
								Qt5::MultimediaWidgets
								Qt5::Network)

set_target_properties(${GDP_CLIENT_TARGET}
	PROPERTIES
	OUTPUT_NAME 		${GDP_CLIENT_OUTPUT}
	LINKER_LANGUAGE		CXX
	LINK_FLAGS_DEBUG	"${PLATFORM_LINKER_FLAGS_DEBUG}"
	LINK_FLAGS_RELEASE	"${PLATFORM_LINKER_FLAGS_RELEASE}"
)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)

# Strip
GDP_STRIP_TARGET(${GDP_CLIENT_TARGET})