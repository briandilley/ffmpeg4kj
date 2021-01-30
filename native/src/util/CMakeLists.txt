project(ffmpeg4kj_util C CXX)

# configure our project
add_library(ffmpeg4kj_util OBJECT
        AbstractNativeObject.h
        AbstractNativeObject.cpp
        AbstractNativeObject_jni.cpp

        JniUtil.h
        JniUtil.cpp

        LogUtil.h
        LogUtil.cpp)

set_target_properties(ffmpeg4kj_util PROPERTIES
        C_STANDARD 99
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE ON)

target_include_directories(ffmpeg4kj_util PUBLIC
        ${JNI_INCLUDE_DIRS}
        ${UTFCPP_INCLUDE_DIRS}
        Poco::Foundation
        ${GENERATED_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ffmpeg4kj_util PUBLIC
        Poco::Foundation)

