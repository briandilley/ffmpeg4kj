package ffmpeg4kj.av

import ffmpeg4kj.util.NativeEnum

enum class ColorTransferCharacteristic(override val nativeEnumValue: Int)
    : NativeEnum {

    AVCOL_TRC_RESERVED0(0),
    AVCOL_TRC_BT709(1),  ///< also ITU-R BT1361
    AVCOL_TRC_UNSPECIFIED(2),
    AVCOL_TRC_RESERVED(3),
    AVCOL_TRC_GAMMA22(4),  ///< also ITU-R BT470M / ITU-R BT1700 625 PAL & SECAM
    AVCOL_TRC_GAMMA28(5),  ///< also ITU-R BT470BG
    AVCOL_TRC_SMPTE170M(6),  ///< also ITU-R BT601-6 525 or 625 / ITU-R BT1358 525 or 625 / ITU-R BT1700 NTSC
    AVCOL_TRC_SMPTE240M(7),
    AVCOL_TRC_LINEAR(8),  ///< "Linear transfer characteristics"
    AVCOL_TRC_LOG(9),  ///< "Logarithmic transfer characteristic (100:1 range)"
    AVCOL_TRC_LOG_SQRT(10), ///< "Logarithmic transfer characteristic (100 * Sqrt(10) : 1 range)"
    AVCOL_TRC_IEC61966_2_4(11), ///< IEC 61966-2-4
    AVCOL_TRC_BT1361_ECG(12), ///< ITU-R BT1361 Extended Colour Gamut
    AVCOL_TRC_IEC61966_2_1(13), ///< IEC 61966-2-1 (sRGB or sYCC)
    AVCOL_TRC_BT2020_10(14), ///< ITU-R BT2020 for 10-bit system
    AVCOL_TRC_BT2020_12(15), ///< ITU-R BT2020 for 12-bit system
    AVCOL_TRC_SMPTE2084(16), ///< SMPTE ST 2084 for 10-, 12-, 14- and 16-bit systems
    AVCOL_TRC_SMPTEST2084(16), //AVCOL_TRC_SMPTE2084),
    AVCOL_TRC_SMPTE428(17), ///< SMPTE ST 428-1
    AVCOL_TRC_SMPTEST428_1(17), //AVCOL_TRC_SMPTE428),
    AVCOL_TRC_ARIB_STD_B67(18), ///< ARIB STD-B67, known as "Hybrid log-gamma"
    AVCOL_TRC_NB(19)                 ///< Not part of ABI
    ;

    companion object {
        @JvmStatic
        fun forNativeEnumValue(nativeEnumValue: Int) =
            ffmpeg4kj.util.forNativeEnumValue(values(), nativeEnumValue)
    }
}
