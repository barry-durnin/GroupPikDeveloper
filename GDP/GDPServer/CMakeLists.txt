# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Configuration for compiling the GDP server project, this is an executable
# 
# Authored by Robert Johnson.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

message(STATUS "Executable: ${GDP_SERVER_TARGET} (${GDP_SERVER_OUTPUT})")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(GDP_SERVER_INCLUDE
	"${PROJECT_SOURCE_DIR}/GDP"
	"${PROJECT_SOURCE_DIR}/GDPMessages"
)

file(GLOB_RECURSE GDP_SERVER_SOURCES
	"${PROJECT_SOURCE_DIR}/GDPServer/*.cpp"
	"${PROJECT_SOURCE_DIR}/GDPServer/*.c"
	"${PROJECT_SOURCE_DIR}/GDPServer/*.h"
	"${PROJECT_SOURCE_DIR}/GDPServer/*.inl"
	"${PROJECT_SOURCE_DIR}/GDPServer/*.qrc"
	"${PROJECT_SOURCE_DIR}/GDPServer/*.ui"
)

# Setup folder hierarchy, the left arg is the folder to search,
# the right arg is the relative folder (i.e. strip this bit from
# the left folder when building the hierarchy).
GDP_GROUP_SOURCES(GDPServer GDPServer)

# Add project to system
add_executable(${GDP_SERVER_TARGET} ${GDP_SERVER_SOURCES})

# Setup include/compile/link options
target_compile_options		(${GDP_SERVER_TARGET} PRIVATE ${GDP_COMPILE_FLAGS})
target_compile_definitions	(${GDP_SERVER_TARGET} PRIVATE ${GDP_COMPILE_DEFS})
target_include_directories	(${GDP_SERVER_TARGET} PRIVATE ${GDP_SERVER_INCLUDE})
target_link_libraries		(${GDP_SERVER_TARGET}
								${GDP_MESSAGES_TARGET}
								Qt5::Widgets 
								Qt5::Multimedia
								Qt5::MultimediaWidgets
								Qt5::Network
								Qt5::Sql)

set_target_properties(${GDP_SERVER_TARGET}
	PROPERTIES
	OUTPUT_NAME 		${GDP_SERVER_OUTPUT}
	LINKER_LANGUAGE		CXX
	LINK_FLAGS_DEBUG	"${PLATFORM_LINKER_FLAGS_DEBUG}"
	LINK_FLAGS_RELEASE	"${PLATFORM_LINKER_FLAGS_RELEASE}"
)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)

# Strip
GDP_STRIP_TARGET(${GDP_SERVER_TARGET})