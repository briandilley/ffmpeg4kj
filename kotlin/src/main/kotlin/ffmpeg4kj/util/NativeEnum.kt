package ffmpeg4kj.util

interface NativeEnum {
    val nativeEnumValue: Int
}

fun <T : NativeEnum> forNativeEnumValue(enums: Array<T>, nativeEnumValue: Int): T {
    return enums
        .find { it.nativeEnumValue == nativeEnumValue }
        ?: throw IllegalArgumentException("Unknown nativeEnumValue: $nativeEnumValue")
}
