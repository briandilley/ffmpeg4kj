package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject

class Codec private constructor(nativeStatePtr: Long)
    : AbstractNativeObject(nativeStatePtr) {

    companion object {

        @JvmStatic
        external fun findEncoderByName(name: String): Codec?

        @JvmStatic
        external fun findEncoderById(id: Int): Codec?

        @JvmStatic
        external fun findEncoderById(id: CodecID): Codec?

        @JvmStatic
        external fun findDecoderByName(name: String): Codec?

        @JvmStatic
        external fun findDecoderById(id: Int): Codec?

        @JvmStatic
        external fun findDecoderById(id: CodecID): Codec?

    }

    private external fun id(): CodecID
    val id: CodecID get() = id()

    private external fun capabilities(): Int
    val capabilities: Int get() = capabilities()

    private external fun name(): String
    val name: String get() = name()

    private external fun wrapperName(): String?
    val wrapperName: String? get() = wrapperName()

    private external fun longName(): String?
    val longName: String? get() = longName()

    private external fun type(): Int
    val type: Int get() = type()
}
