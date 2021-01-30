project(ffmpeg4kj_av C CXX)

# configure our project
add_library(ffmpeg4kj_av OBJECT

        BufferNativeObject.h
        BufferNativeObject.cpp
        BufferNativeObject_jni.cpp

        BufferPoolNativeObject.h
        BufferPoolNativeObject.cpp
        BufferPoolNativeObject_jni.cpp

        RationalNativeObject.h
        RationalNativeObject.cpp
        RationalNativeObject_jni.cpp

        PacketNativeObject.h
        PacketNativeObject.cpp
        PacketNativeObject_jni.cpp

        FrameNativeObject.cpp
        FrameNativeObject.h
        FrameNativeObject_jni.cpp

        CodecNativeObject.cpp
        CodecNativeObject.h
        CodecNativeObject_jni.cpp

        CodecParametersNativeObject.cpp
        CodecParametersNativeObject.h
        CodecParametersNativeObject_jni.cpp

        StreamNativeObject.cpp
        StreamNativeObject.h
        StreamNativeObject_jni.cpp

        DecoderNativeObject.cpp
        DecoderNativeObject.h
        DecoderNativeObject_jni.cpp

        EncoderNativeObject.cpp
        EncoderNativeObject.h
        EncoderNativeObject_jni.cpp

        CodecContextNativeObject.cpp
        CodecContextNativeObject.h
        CodecContextNativeObject_jni.cpp

        FormatContextNativeObject.cpp
        FormatContextNativeObject.h
        FormatContextNativeObject_jni.cpp

        MuxerNativeObject.cpp
        MuxerNativeObject.h
        MuxerNativeObject_jni.cpp

        DemuxerNativeObject.cpp
        DemuxerNativeObject.h
        DemuxerNativeObject_jni.cpp

        TimeNativeObjects.h
        Mathematics_jni.cpp
        SecondsNativeObject_jni.cpp
        MillisecondsNativeObject_jni.cpp

        ParserNativeObject.cpp
        ParserNativeObject.h
        ParserNativeObject_jni.cpp

        IOContextNativeObject.cpp
        IOContextNativeObject.h
        IOContextNativeObject_jni.cpp

        ImageConverterNativeObject.cpp
        ImageConverterNativeObject.h
        ImageConverterNativeObject_jni.cpp)

set_target_properties(ffmpeg4kj_av PROPERTIES
        C_STANDARD 99
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE ON)

target_include_directories(ffmpeg4kj_av PUBLIC
        ${JNI_INCLUDE_DIRS}
        ${UTFCPP_INCLUDE_DIRS}
        ${FFMPEG_INCLUDE_DIRS}
        Poco::Foundation
        ffmpeg4kj_util
        ${GENERATED_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ffmpeg4kj_av PUBLIC
        Poco::Foundation
        ffmpeg4kj_util)
