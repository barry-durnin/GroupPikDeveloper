# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Configuration for compiling the source code on Linux with the GCC compiler.
# 
# Authored by Robert Johnson.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

message(STATUS "Configuring for platform Linux/GCC")

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Platform compile flags & defs
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(PLATFORM_COMPILE_DEFS
	FORCE_INLINE=inline
	_SCL_SECURE_NO_WARNINGS			# Allow calling any one of the potentially unsafe methods in the Standard C++ Library
	_CRT_SECURE_NO_WARNINGS			# Disable CRT deprecation warnings
	_FILE_OFFSET_BITS=64
)

set(PLATFORM_COMPILE_FLAGS
	-g3
	-Wall
	-Werror
	-pthread
	-fPIC
	-static
	-Wunused
	-ffunction-sections
	-funwind-tables
	-fstack-protector
	-no-canonical-prefixes
	-fomit-frame-pointer
	-fno-strict-aliasing
	-finline-limit=64
	-msse4.2
	$<$<CONFIG:Debug>:-O0>
	$<$<CONFIG:Release>:-O2>
	$<$<CONFIG:Release>:-fvisibility=hidden>
)

# Special case C++11 support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -frtti")

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Platform libs & linker
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

find_library(PLATFORM_DL_LIBRARY
	NAMES 		dl
	DOC 		"DL library used by x264")

find_library(PLATFORM_RT_LIBRARY
	NAMES 		rt
	DOC 		"RT library")

# Theres an alternative package for finding the correct threading library
find_library(PLATFORM_PTHREAD_LIBRARY
	NAMES 		pthread
	DOC 		"pthread library")

find_library(PLATFORM_M_LIBRARY
	NAMES 		m
	DOC 		"m library")

set(PLATFORM_LIBRARIES ${PLATFORM_DL_LIBRARY} ${PLATFORM_RT_LIBRARY} ${PLATFORM_PTHREAD_LIBRARY} ${PLATFORM_M_LIBRARY})
message(STATUS "Platform Libraries: ${PLATFORM_LIBRARIES}")

# Recommendation is to not mess with these, quite sensitive is the linker on Linux.
set(PLATFORM_LINKER_FLAGS_DEBUG
	"-Wl,--no-as-needed -pthread -Wl,--exclude-libs,ALL '-Wl,-rpath,$ORIGIN'"
)

set(PLATFORM_LINKER_FLAGS_RELEASE
	"-Wl,--no-as-needed -pthread -Wl,--exclude-libs,ALL '-Wl,-rpath,$ORIGIN'"
)

set(PLATFORM_STATIC_LINKER_FLAGS_DEBUG	## Explicitly empty.
)

set(PLATFORM_STATIC_LINKER_FLAGS_RELEASE	## Explicitly empty.
)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Distro detection, used to output to a unique
# folder per distribution.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

if(EXISTS "/etc/centos-release")
	set(PLATFORM_LINUX_DISTRIBUTION "Centos")	# Strip out the consistent text.
else()
	exec_program(lsb_release ARGS -i OUTPUT_VARIABLE LSB_OUTPUT)
	string(REPLACE "Distributor ID:	" "" PLATFORM_LINUX_DISTRIBUTION ${LSB_OUTPUT})	# Strip out the consistent text.
endif()

message(STATUS "Detected Linux distribution: ${PLATFORM_LINUX_DISTRIBUTION}")

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Setup global platform vars
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(PLATFORM_BINARIES_PATH
	"${PROJECT_SOURCE_DIR}/Build/${PLATFORM_ARCHITECTURE}/Linux/${PLATFORM_LINUX_DISTRIBUTION}"
)

set(PLATFORM_STATIC_SUFFIX
	".a"
)

set(PLATFORM_NAME
	${PLATFORM_LINUX_DISTRIBUTION}
)

set(PLATFORM_BUILD
	"Linux"
)