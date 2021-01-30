package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject

class Rational(nativeStatePtr: Long)
    : AbstractNativeObject(nativeStatePtr) {

    constructor(num: Int = 0, den: Int = 0) : this(new(num, den))

    companion object {

        @JvmStatic
        private external fun new(num: Int, den: Int): Long

    }

    private external fun num(): Int
    private external fun num(num: Int)
    var num: Int
        get() = num()
        set(value) { num(value) }

    private external fun den(): Int
    private external fun den(den: Int)
    var den: Int
        get() = den()
        set(value) { den(value) }

    override fun toString(): String {
        return "Rational@${hashCode()}/$nativeStatePtr(den=$den,num=$num)"
    }
}
