cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

include(ExternalProject)

project(ffmpeg4kj C CXX)

set(THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated)

# Determine the platform.
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    set(OS_MACOS 1)
    set(OS_POSIX 1)
    set(PACKAGE_NAME darwin-x86_64)
    add_definitions(-DOS_MACOS -DOS_POSIX -DUSE_GLFW)

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(OS_LINUX 1)
    set(OS_POSIX 1)
    set(PACKAGE_NAME linux-x86_64)
    add_definitions(-DOS_LINUX -DOS_POSIX -DUSE_EGL)

endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/package/${PACKAGE_NAME})
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/package)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/package/${PACKAGE_NAME})


if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1 -D_DEBUG=1)
    set(CMAKE_CONFIGURATION_TYPES Debug)

elseif(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DDEBUG=0 -D_DEBUG=0)
    set(CMAKE_CONFIGURATION_TYPES Release)

endif()

# support PKG
find_package(PkgConfig REQUIRED)



if (EXISTS "/usr/lib/jvm/java-11-amazon-corretto.x86_64/lib/libawt.so")
    set(JAVA_AWT_LIBRARY "/usr/lib/jvm/java-11-amazon-corretto.x86_64/lib/libawt.so")
    set(JAVA_INCLUDE_PATH "/usr/lib/jvm/java-11-amazon-corretto.x86_64/include")
    set(JAVA_AWT_INCLUDE_PATH "/usr/lib/jvm/java-11-amazon-corretto.x86_64/include")
endif()
find_package(JNI REQUIRED)



# poco
set(Poco_FOUND 1) # this is necessary, if the components aren't found it'll complain
find_package(Poco REQUIRED COMPONENTS
        Foundation)



#ffmpeg
find_path(AVDEVICE_INCLUDE_DIR   libavdevice/avdevice.h         HINTS ${FFMPEG_INCLUDE_DIRS} ${AVDEVICE_INCLUDE_DIR})
find_path(AVUTIL_INCLUDE_DIR     libavutil/avutil.h             HINTS ${FFMPEG_INCLUDE_DIRS} ${AVUTIL_INCLUDE_DIR})
find_path(AVFORMAT_INCLUDE_DIR   libavformat/avformat.h         HINTS ${FFMPEG_INCLUDE_DIRS} ${AVFORMAT_INCLUDE_DIR})
find_path(AVFILTER_INCLUDE_DIR   libavfilter/avfilter.h         HINTS ${FFMPEG_INCLUDE_DIRS} ${AVFILTER_INCLUDE_DIR})
find_path(AVCODEC_INCLUDE_DIR    libavcodec/avcodec.h           HINTS ${FFMPEG_INCLUDE_DIRS} ${AVCODEC_INCLUDE_DIR})
find_path(AVRESAMPLE_INCLUDE_DIR libavresample/avresample.h     HINTS ${FFMPEG_INCLUDE_DIRS} ${AVRESAMPLE_INCLUDE_DIR})
find_path(SWSCALE_INCLUDE_DIR    libswscale/swscale.h           HINTS ${FFMPEG_INCLUDE_DIRS} ${SWSCALE_INCLUDE_DIR})
set(FFMPEG_INCLUDE_DIRS
        ${FFMPEG_INCLUDE_DIRS}
        ${AVDEVICE_INCLUDE_DIR}
        ${AVUTIL_INCLUDE_DIR}
        ${AVFORMAT_INCLUDE_DIR}
        ${AVFILTER_INCLUDE_DIR}
        ${AVCODEC_INCLUDE_DIR}
        ${AVRESAMPLE_INCLUDE_DIR}
        ${SWSCALE_INCLUDE_DIR})
find_library(AVDEVICE_LIB   NAMES avdevice       HINTS ${FFMPEG_LIB_DIRS} ${AVDEVICE_LIB_DIR} REQUIRED)
find_library(AVUTIL_LIB     NAMES avutil         HINTS ${FFMPEG_LIB_DIRS} ${AVUTIL_LIB_DIR} REQUIRED)
find_library(AVFORMAT_LIB   NAMES avformat       HINTS ${FFMPEG_LIB_DIRS} ${AVFORMAT_LIB_DIR} REQUIRED)
find_library(AVFILTER_LIB   NAMES avfilter       HINTS ${FFMPEG_LIB_DIRS} ${AVFILTER_LIB_DIR} REQUIRED)
find_library(AVCODEC_LIB    NAMES avcodec        HINTS ${FFMPEG_LIB_DIRS} ${AVCODEC_LIB_DIR} REQUIRED)
find_library(AVRESAMPLE_LIB NAMES avresample     HINTS ${FFMPEG_LIB_DIRS} ${AVRESAMPLE_LIB_DIR} REQUIRED)
find_library(SWSCALE_LIB    NAMES swscale        HINTS ${FFMPEG_LIB_DIRS} ${SWSCALE_LIB_DIR} REQUIRED)
set(FFMPEG_LIBRARY_DIRS
        ${FFMPEG_LIB_DIRS}
        ${AVDEVICE_LIB_DIR}
        ${AVUTIL_LIB_DIR}
        ${AVFORMAT_LIB_DIR}
        ${AVFILTER_LIB_DIR}
        ${AVCODEC_LIB_DIR}
        ${AVRESAMPLE_LIB_DIR}
        ${SWSCALE_LIB_DIR})
set(FFMPEG_LIBRARIES
        ${AVDEVICE_LIB}
        ${AVUTIL_LIB}
        ${AVFORMAT_LIB}
        ${AVFILTER_LIB}
        ${AVCODEC_LIB}
        ${AVRESAMPLE_LIB}
        ${SWSCALE_LIB})



#utfcpp
set(UTFCPP_DIR ${THIRDPARTY_DIR}/utfcpp-3.1.2)
set(UTFCPP_INCLUDE_DIRS
        ${UTFCPP_DIR}/source)



# the projects
add_subdirectory(src/av)
add_subdirectory(src/util)



# and the project that brings it all together
project(ffmpeg4kj_jni C CXX)

# configure our project
add_library(ffmpeg4kj_jni SHARED
        FFMpeg4KJ_jni.cpp)

set_target_properties(ffmpeg4kj_jni PROPERTIES
        C_STANDARD 99
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE ON)

target_include_directories(ffmpeg4kj_jni PUBLIC
        ffmpeg4kj_util
        ffmpeg4kj_av
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_directories(ffmpeg4kj_jni PUBLIC
        ${FFMPEG_INCLUDE_DIRS}
        ${FFMPEG_LIBRARY_DIRS})

target_link_libraries(ffmpeg4kj_jni PRIVATE
        ffmpeg4kj_util
        ffmpeg4kj_av
        ${FFMPEG_LIBRARIES})
