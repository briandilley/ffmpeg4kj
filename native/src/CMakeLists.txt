# and the project that brings it all together
project(ffmpeg4kj_jni C CXX)

add_subdirectory(av)
add_subdirectory(util)

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
