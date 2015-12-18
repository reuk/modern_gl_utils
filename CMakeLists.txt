cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

project(modern_gl_utils)

set(BUILD_SHARED_LIBS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(modern_gl_utils_VERSION 0.0.1)

include(GenerateExportHeader)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -std=gnu++14")

set(name modern_gl_utils)
file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

SET(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

include_directories(${FREETYPE_INCLUDE_DIRS})

add_library(${name} STATIC ${sources})

set(libraries
    ${OPENGL_LIBRARIES}
    ${FREETYPE_LIBRARIES})

if(UNIX)
    set(libraries ${libraries} png z)
endif(UNIX)

target_link_libraries(
    ${name}
    ${libraries})

generate_export_header(${name})
set_property(TARGET ${name} PROPERTY VERSION ${modern_gl_utils_VERSION})
set_property(TARGET ${name} PROPERTY SOVERSION 0)
set_property(TARGET ${name} PROPERTY INTERFACE_${name}_MAJOR_VERSION 0)
set_property(TARGET ${name} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${name}_MAJOR_VERSION)

install(TARGETS ${name} EXPORT modern_gl_utilsTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)
install(FILES ${headers} "${CMAKE_CURRENT_BINARY_DIR}/modern_gl_utils_export.h"
    DESTINATION include/modern_gl_utils COMPONENT Devel)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/modern_gl_utils/modern_gl_utilsConfigVersion.cmake"
    VERSION ${modern_gl_utils_VERSION} COMPATIBILITY AnyNewerVersion)

export(EXPORT modern_gl_utilsTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/modern_gl_utils/modern_gl_utilsTargets.cmake")

configure_file(cmake/modern_gl_utilsConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/modern_gl_utils/modern_gl_utilsConfig.cmake"
    COPYONLY)

set(ConfigPackageLocation lib/cmake/modern_gl_utils)
install(EXPORT modern_gl_utilsTargets
    FILE modern_gl_utilsTargets.cmake
    DESTINATION ${ConfigPackageLocation})
install(FILES
    cmake/modern_gl_utilsConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/modern_gl_utils/modern_gl_utilsConfigVersion.cmake"
    DESTINATION ${ConfigPackageLocation} COMPONENT Devel)
