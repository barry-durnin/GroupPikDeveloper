# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Configuration for compiling the source code on Windows with the MSVC compiler.
# 
# Authored by Robert Johnson.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

find_path(SQLITE3_INCLUDE_DIR NAMES sqlite3.h
								PATHS Libs/sqlite3)

find_library(SQLITE3_LIBRARY NAMES sqlite3
								PATHS Libs/sqlite3/${PLATFORM_ARCHITECTURE}/${PLATFORM_NAME})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SQLITE3 DEFAULT_MSG SQLITE3_LIBRARY SQLITE3_INCLUDE_DIR)

if(SQLITE3_FOUND)
	set(SQLITE3_LIBRARIES ${SQLITE3_LIBRARY})
	set(SQLITE3_INCLUDE_DIRS ${SQLITE3_INCLUDE_DIR})
else(SQLITE3_FOUND)
	set(SQLITE3_LIBRARIES)
	set(SQLITE3_INCLUDE_DIRS)
endif(SQLITE3_FOUND)