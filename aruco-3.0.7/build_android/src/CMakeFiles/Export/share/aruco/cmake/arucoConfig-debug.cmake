#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "aruco" for configuration "Debug"
set_property(TARGET aruco APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(aruco PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libaruco.so"
  IMPORTED_SONAME_DEBUG "libaruco.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS aruco )
list(APPEND _IMPORT_CHECK_FILES_FOR_aruco "${_IMPORT_PREFIX}/lib/libaruco.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
