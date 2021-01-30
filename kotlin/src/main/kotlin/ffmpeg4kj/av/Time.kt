package ffmpeg4kj.av

class Seconds private constructor(private val nativeStatePtr: Long) {
    external fun value(): Long
    external fun set(value: Long)
    external operator fun set(rational: Rational, value: Double)
    external operator fun get(rational: Rational): Double
}

class Milliseconds private constructor(private val nativeStatePtr: Long) {
    external fun value(): Long
    external fun set(value: Long)
    external operator fun set(rational: Rational, value: Long)
    external operator fun get(rational: Rational): Long
}
