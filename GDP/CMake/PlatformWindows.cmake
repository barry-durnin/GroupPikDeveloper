# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Configuration for compiling the source code on Windows with the MSVC compiler.
# 
# Authored by Robert Johnson.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

message(STATUS "Configuring for platform Windows/MSVC")

# Figure out what version of windows we're compiling
# on. Used by various compile time constructs.
if (CMAKE_SYSTEM_VERSION)
	set(VER ${CMAKE_SYSTEM_VERSION})
	string(REPLACE "." "" VER ${VER})
	string(REGEX REPLACE "([0-9])" "0\\1" VER ${VER})
	set(WIN32_VER "0x${VER}")
endif()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Platform compile flags & defs
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(PLATFORM_COMPILE_DEFS
	FORCE_INLINE=__forceinline		# Inlining strategy
	_SCL_SECURE_NO_WARNINGS			# Allow calling any one of the potentially unsafe methods in the Standard C++ Library
	_CRT_SECURE_NO_WARNINGS			# Disable CRT deprecation warnings
	-D_WIN32_WINNT=${WIN32_VER}
)

set(PLATFORM_COMPILE_FLAGS
	/MT$<$<CONFIG:Debug>:d>			# Use multi-threaded runtime, choosing either /MT or /MTd depending on the config.
	/nologo
	/Zc:wchar_t
	/Zc:forScope
	/GF
	/GS
	/Zi
	/MP
	/W3
	/WX
	/Oi
	$<$<CONFIG:Release>:/GL> 		# Use link-time code generation in release only.
)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Platform libs & linker
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(WINDOWS_LINKER_FLAGS
	/NOLOGO
	/INCREMENTAL:NO
	/NXCOMPAT
	/DYNAMICBASE:NO
)

set(PLATFORM_LINKER_FLAGS_DEBUG
	${WINDOWS_LINKER_FLAGS}
	/DEBUG
)

set(PLATFORM_LINKER_FLAGS_RELEASE
	${WINDOWS_LINKER_FLAGS}
	/OPT:REF
	/LTCG
	/OPT:ICF
	/DELAY:UNLOAD
	)

# CMake delimits lists as commas, MSVC expects space delimited linker flags.
string(REPLACE ";" " " PLATFORM_LINKER_FLAGS_DEBUG "${PLATFORM_LINKER_FLAGS_DEBUG}")
string(REPLACE ";" " " PLATFORM_LINKER_FLAGS_RELEASE "${PLATFORM_LINKER_FLAGS_RELEASE}")

set(PLATFORM_STATIC_LINKER_FLAGS_DEBUG	## Explicitly empty.
)

set(PLATFORM_STATIC_LINKER_FLAGS_RELEASE
	/LTCG
)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Setup global platform vars
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(PLATFORM_BINARIES_PATH
	"${PROJECT_SOURCE_DIR}/Build/${PLATFORM_ARCHITECTURE}/Windows"
)

set(PLATFORM_NAME
	"Windows"
)

set(PLATFORM_BUILD
	"Windows"
)