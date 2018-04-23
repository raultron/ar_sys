# Install script for directory: /home/salinas/Libraries/aruco/trunk/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/salinas/Libraries/Android/appcv/app/3rdparty/aruco/armeabi-v7a")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "/home/salinas/Libraries/aruco/trunk/build_android/src/libaruco.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libaruco.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libaruco.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/salinas/Android/Sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libaruco.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aruco" TYPE FILE FILES
    "/home/salinas/Libraries/aruco/trunk/src/aruco_export.h"
    "/home/salinas/Libraries/aruco/trunk/src/cameraparameters.h"
    "/home/salinas/Libraries/aruco/trunk/src/cvdrawingutils.h"
    "/home/salinas/Libraries/aruco/trunk/src/dictionary.h"
    "/home/salinas/Libraries/aruco/trunk/src/ippe.h"
    "/home/salinas/Libraries/aruco/trunk/src/marker.h"
    "/home/salinas/Libraries/aruco/trunk/src/markerdetector.h"
    "/home/salinas/Libraries/aruco/trunk/src/markerlabeler.h"
    "/home/salinas/Libraries/aruco/trunk/src/markermap.h"
    "/home/salinas/Libraries/aruco/trunk/src/posetracker.h"
    "/home/salinas/Libraries/aruco/trunk/src/markerlabelers/dictionary_based.h"
    "/home/salinas/Libraries/aruco/trunk/src/timers.h"
    "/home/salinas/Libraries/aruco/trunk/src/debug.h"
    "/home/salinas/Libraries/aruco/trunk/src/aruco.h"
    "/home/salinas/Libraries/aruco/trunk/src/markerlabelers/svmmarkers.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/aruco/cmake/arucoConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/aruco/cmake/arucoConfig.cmake"
         "/home/salinas/Libraries/aruco/trunk/build_android/src/CMakeFiles/Export/share/aruco/cmake/arucoConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/aruco/cmake/arucoConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/aruco/cmake/arucoConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/aruco/cmake" TYPE FILE FILES "/home/salinas/Libraries/aruco/trunk/build_android/src/CMakeFiles/Export/share/aruco/cmake/arucoConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/aruco/cmake" TYPE FILE FILES "/home/salinas/Libraries/aruco/trunk/build_android/src/CMakeFiles/Export/share/aruco/cmake/arucoConfig-release.cmake")
  endif()
endif()

