package ffmpeg4kj.util

import ffmpeg4kj.FFMpeg4KJ
import java.io.Closeable
import java.lang.ref.Cleaner

class NativeObjectCleaner(
    private val nativeStatePtr: Long,
    internal val cleanCallbacks: MutableList<Runnable> = mutableListOf()) : Runnable {
    override fun run() {
        clean()
    }
    private fun clean() {
        cleanCallbacks.forEach { it.run() }
        AbstractNativeObject.dispose(nativeStatePtr)
    }
}

open class AbstractNativeObject constructor(nativeStatePtr: Long) : Closeable {

    companion object {

        init {
            FFMpeg4KJ.prepareNativeLibraries()
        }

        const val NULL_POINTER: Long = 0L

        @JvmStatic
        private val CLEANER = Cleaner.create()

        @JvmStatic
        external fun dispose(nativeStatePtr: Long)
    }

    var nativeStatePtr: Long = nativeStatePtr
        private set

    val nullPointer: Boolean get() = nativeStatePtr == NULL_POINTER

    private val cleaner: NativeObjectCleaner = NativeObjectCleaner(this.nativeStatePtr)

    @Suppress("LeakingThis")
    private val cleanable: Cleaner.Cleanable = CLEANER.register(this, cleaner)

    /**
     * Be very careful using this method.  If the Runnable that you pass in
     * has a reference to this object then it'll never get cleaned up.
     */
    fun addDisposeCallback(cb: Runnable) {
        cleaner.cleanCallbacks.add(cb)
    }

    override fun close() {
        dispose()
    }

    fun dispose() {
        cleanable.clean()
        nativeStatePtr = NULL_POINTER
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false
        other as AbstractNativeObject
        if (nativeStatePtr != other.nativeStatePtr) return false
        return true
    }

    override fun hashCode(): Int {
        return nativeStatePtr.hashCode()
    }

    override fun toString(): String {
        return "${this::class.simpleName}(nativeStatePtr=$nativeStatePtr)"
    }

}
