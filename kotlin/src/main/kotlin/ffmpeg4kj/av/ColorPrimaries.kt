package ffmpeg4kj.av

import ffmpeg4kj.util.NativeEnum

enum class ColorPrimaries(override val nativeEnumValue: Int)
    : NativeEnum {
    AVCOL_PRI_RESERVED0(0),
    AVCOL_PRI_BT709(1),  ///< also ITU-R BT1361 / IEC 61966-2-4 / SMPTE RP177 Annex B
    AVCOL_PRI_UNSPECIFIED(2),
    AVCOL_PRI_RESERVED(3),
    AVCOL_PRI_BT470M(4),  ///< also FCC Title 47 Code of Federal Regulations 73.682 (a)(20)

    AVCOL_PRI_BT470BG(5),  ///< also ITU-R BT601-6 625 / ITU-R BT1358 625 / ITU-R BT1700 625 PAL & SECAM
    AVCOL_PRI_SMPTE170M(6),  ///< also ITU-R BT601-6 525 / ITU-R BT1358 525 / ITU-R BT1700 NTSC
    AVCOL_PRI_SMPTE240M(7),  ///< functionally identical to above
    AVCOL_PRI_FILM(8),  ///< colour filters using Illuminant C
    AVCOL_PRI_BT2020(9),  ///< ITU-R BT2020
    AVCOL_PRI_SMPTE428(10), ///< SMPTE ST 428-1 (CIE 1931 XYZ)
    AVCOL_PRI_SMPTEST428_1(10), // AVCOL_PRI_SMPTE428,
    AVCOL_PRI_SMPTE431(11), ///< SMPTE ST 431-2 (2011) / DCI P3
    AVCOL_PRI_SMPTE432(12), ///< SMPTE ST 432-1 (2010) / P3 D65 / Display P3
    AVCOL_PRI_JEDEC_P22(22), ///< JEDEC P22 phosphors
    AVCOL_PRI_NB(23)                ///< Not part of ABI
    ;

    companion object {
        @JvmStatic
        fun forNativeEnumValue(nativeEnumValue: Int) =
            ffmpeg4kj.util.forNativeEnumValue(values(), nativeEnumValue)
    }
}
