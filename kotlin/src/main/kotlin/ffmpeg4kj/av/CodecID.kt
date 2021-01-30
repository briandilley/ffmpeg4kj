package ffmpeg4kj.av

import ffmpeg4kj.util.NativeEnum

enum class CodecID(override val nativeEnumValue: Int)
    : NativeEnum {
    AV_CODEC_ID_NONE(0),

    /* video codecs */
    AV_CODEC_ID_MPEG1VIDEO(1),
    AV_CODEC_ID_MPEG2VIDEO(2), ///< preferred ID for MPEG-1/2 video decoding
    AV_CODEC_ID_H261(3),
    AV_CODEC_ID_H263(4),
    AV_CODEC_ID_RV10(5),
    AV_CODEC_ID_RV20(6),
    AV_CODEC_ID_MJPEG(7),
    AV_CODEC_ID_MJPEGB(8),
    AV_CODEC_ID_LJPEG(9),
    AV_CODEC_ID_SP5X(10),
    AV_CODEC_ID_JPEGLS(11),
    AV_CODEC_ID_MPEG4(12),
    AV_CODEC_ID_RAWVIDEO(13),
    AV_CODEC_ID_MSMPEG4V1(14),
    AV_CODEC_ID_MSMPEG4V2(15),
    AV_CODEC_ID_MSMPEG4V3(16),
    AV_CODEC_ID_WMV1(17),
    AV_CODEC_ID_WMV2(18),
    AV_CODEC_ID_H263P(19),
    AV_CODEC_ID_H263I(20),
    AV_CODEC_ID_FLV1(21),
    AV_CODEC_ID_SVQ1(22),
    AV_CODEC_ID_SVQ3(23),
    AV_CODEC_ID_DVVIDEO(24),
    AV_CODEC_ID_HUFFYUV(25),
    AV_CODEC_ID_CYUV(26),
    AV_CODEC_ID_H264(27),
    AV_CODEC_ID_INDEO3(28),
    AV_CODEC_ID_VP3(29),
    AV_CODEC_ID_THEORA(30),
    AV_CODEC_ID_ASV1(31),
    AV_CODEC_ID_ASV2(32),
    AV_CODEC_ID_FFV1(33),
    AV_CODEC_ID_4XM(34),
    AV_CODEC_ID_VCR1(35),
    AV_CODEC_ID_CLJR(36),
    AV_CODEC_ID_MDEC(37),
    AV_CODEC_ID_ROQ(38),
    AV_CODEC_ID_INTERPLAY_VIDEO(39),
    AV_CODEC_ID_XAN_WC3(40),
    AV_CODEC_ID_XAN_WC4(41),
    AV_CODEC_ID_RPZA(42),
    AV_CODEC_ID_CINEPAK(43),
    AV_CODEC_ID_WS_VQA(44),
    AV_CODEC_ID_MSRLE(45),
    AV_CODEC_ID_MSVIDEO1(46),
    AV_CODEC_ID_IDCIN(47),
    AV_CODEC_ID_8BPS(48),
    AV_CODEC_ID_SMC(49),
    AV_CODEC_ID_FLIC(50),
    AV_CODEC_ID_TRUEMOTION1(51),
    AV_CODEC_ID_VMDVIDEO(52),
    AV_CODEC_ID_MSZH(53),
    AV_CODEC_ID_ZLIB(54),
    AV_CODEC_ID_QTRLE(55),
    AV_CODEC_ID_TSCC(56),
    AV_CODEC_ID_ULTI(57),
    AV_CODEC_ID_QDRAW(58),
    AV_CODEC_ID_VIXL(59),
    AV_CODEC_ID_QPEG(60),
    AV_CODEC_ID_PNG(61),
    AV_CODEC_ID_PPM(62),
    AV_CODEC_ID_PBM(63),
    AV_CODEC_ID_PGM(64),
    AV_CODEC_ID_PGMYUV(65),
    AV_CODEC_ID_PAM(66),
    AV_CODEC_ID_FFVHUFF(67),
    AV_CODEC_ID_RV30(68),
    AV_CODEC_ID_RV40(69),
    AV_CODEC_ID_VC1(70),
    AV_CODEC_ID_WMV3(71),
    AV_CODEC_ID_LOCO(72),
    AV_CODEC_ID_WNV1(73),
    AV_CODEC_ID_AASC(74),
    AV_CODEC_ID_INDEO2(75),
    AV_CODEC_ID_FRAPS(76),
    AV_CODEC_ID_TRUEMOTION2(77),
    AV_CODEC_ID_BMP(78),
    AV_CODEC_ID_CSCD(79),
    AV_CODEC_ID_MMVIDEO(80),
    AV_CODEC_ID_ZMBV(81),
    AV_CODEC_ID_AVS(82),
    AV_CODEC_ID_SMACKVIDEO(83),
    AV_CODEC_ID_NUV(84),
    AV_CODEC_ID_KMVC(85),
    AV_CODEC_ID_FLASHSV(86),
    AV_CODEC_ID_CAVS(87),
    AV_CODEC_ID_JPEG2000(88),
    AV_CODEC_ID_VMNC(89),
    AV_CODEC_ID_VP5(90),
    AV_CODEC_ID_VP6(91),
    AV_CODEC_ID_VP6F(92),
    AV_CODEC_ID_TARGA(93),
    AV_CODEC_ID_DSICINVIDEO(94),
    AV_CODEC_ID_TIERTEXSEQVIDEO(95),
    AV_CODEC_ID_TIFF(96),
    AV_CODEC_ID_GIF(97),
    AV_CODEC_ID_DXA(98),
    AV_CODEC_ID_DNXHD(99),
    AV_CODEC_ID_THP(100),
    AV_CODEC_ID_SGI(101),
    AV_CODEC_ID_C93(102),
    AV_CODEC_ID_BETHSOFTVID(103),
    AV_CODEC_ID_PTX(104),
    AV_CODEC_ID_TXD(105),
    AV_CODEC_ID_VP6A(106),
    AV_CODEC_ID_AMV(107),
    AV_CODEC_ID_VB(108),
    AV_CODEC_ID_PCX(109),
    AV_CODEC_ID_SUNRAST(110),
    AV_CODEC_ID_INDEO4(111),
    AV_CODEC_ID_INDEO5(112),
    AV_CODEC_ID_MIMIC(113),
    AV_CODEC_ID_RL2(115),
    AV_CODEC_ID_ESCAPE124(115),
    AV_CODEC_ID_DIRAC(116),
    AV_CODEC_ID_BFI(117),
    AV_CODEC_ID_CMV(118),
    AV_CODEC_ID_MOTIONPIXELS(119),
    AV_CODEC_ID_TGV(120),
    AV_CODEC_ID_TGQ(121),
    AV_CODEC_ID_TQI(122),
    AV_CODEC_ID_AURA(123),
    AV_CODEC_ID_AURA2(124),
    AV_CODEC_ID_V210X(125),
    AV_CODEC_ID_TMV(126),
    AV_CODEC_ID_V210(127),
    AV_CODEC_ID_DPX(128),
    AV_CODEC_ID_MAD(129),
    AV_CODEC_ID_FRWU(130),
    AV_CODEC_ID_FLASHSV2(131),
    AV_CODEC_ID_CDGRAPHICS(132),
    AV_CODEC_ID_R210(133),
    AV_CODEC_ID_ANM(134),
    AV_CODEC_ID_BINKVIDEO(135),
    AV_CODEC_ID_IFF_ILBM(136),
    AV_CODEC_ID_IFF_BYTERUN1(136), // #define AV_CODEC_ID_IFF_BYTERUN1 AV_CODEC_ID_IFF_ILBM
    AV_CODEC_ID_KGV1(137),
    AV_CODEC_ID_YOP(138),
    AV_CODEC_ID_VP8(139),
    AV_CODEC_ID_PICTOR(140),
    AV_CODEC_ID_ANSI(141),
    AV_CODEC_ID_A64_MULTI(142),
    AV_CODEC_ID_A64_MULTI5(143),
    AV_CODEC_ID_R10K(144),
    AV_CODEC_ID_MXPEG(145),
    AV_CODEC_ID_LAGARITH(146),
    AV_CODEC_ID_PRORES(147),
    AV_CODEC_ID_JV(148),
    AV_CODEC_ID_DFA(149),
    AV_CODEC_ID_WMV3IMAGE(150),
    AV_CODEC_ID_VC1IMAGE(151),
    AV_CODEC_ID_UTVIDEO(152),
    AV_CODEC_ID_BMV_VIDEO(153),
    AV_CODEC_ID_VBLE(154),
    AV_CODEC_ID_DXTORY(155),
    AV_CODEC_ID_V410(156),
    AV_CODEC_ID_XWD(157),
    AV_CODEC_ID_CDXL(158),
    AV_CODEC_ID_XBM(159),
    AV_CODEC_ID_ZEROCODEC(160),
    AV_CODEC_ID_MSS1(161),
    AV_CODEC_ID_MSA1(162),
    AV_CODEC_ID_TSCC2(163),
    AV_CODEC_ID_MTS2(164),
    AV_CODEC_ID_CLLC(165),
    AV_CODEC_ID_MSS2(166),
    AV_CODEC_ID_VP9(167),
    AV_CODEC_ID_AIC(168),
    AV_CODEC_ID_ESCAPE130(169),
    AV_CODEC_ID_G2M(170),
    AV_CODEC_ID_WEBP(171),
    AV_CODEC_ID_HNM4_VIDEO(172),
    AV_CODEC_ID_HEVC(173),
    AV_CODEC_ID_H265(173), // #define AV_CODEC_ID_H265 AV_CODEC_ID_HEVC
    AV_CODEC_ID_FIC(174),
    AV_CODEC_ID_ALIAS_PIX(175),
    AV_CODEC_ID_BRENDER_PIX(176),
    AV_CODEC_ID_PAF_VIDEO(178),
    AV_CODEC_ID_EXR(179),
    AV_CODEC_ID_VP7(180),
    AV_CODEC_ID_SANM(181),
    AV_CODEC_ID_SGIRLE(182),
    AV_CODEC_ID_MVC1(183),
    AV_CODEC_ID_MVC2(184),
    AV_CODEC_ID_HQX(185),
    AV_CODEC_ID_TDSC(186),
    AV_CODEC_ID_HQ_HQA(187),
    AV_CODEC_ID_HAP(188),
    AV_CODEC_ID_DDS(189),
    AV_CODEC_ID_DXV(190),
    AV_CODEC_ID_SCREENPRESSO(191),
    AV_CODEC_ID_RSCC(192),
    AV_CODEC_ID_AVS2(193),


    AV_CODEC_ID_Y41P(32768), // 0x8000
    AV_CODEC_ID_AVRP(32769),
    AV_CODEC_ID_012V(32770),
    AV_CODEC_ID_AVUI(32771),
    AV_CODEC_ID_AYUV(32772),
    AV_CODEC_ID_TARGA_Y216(32773),
    AV_CODEC_ID_V308(32774),
    AV_CODEC_ID_V408(32775),
    AV_CODEC_ID_YUV4(32776),
    AV_CODEC_ID_AVRN(32777),
    AV_CODEC_ID_CPIA(32778),
    AV_CODEC_ID_XFACE(32779),
    AV_CODEC_ID_SNOW(32780),
    AV_CODEC_ID_SMVJPEG(32781),
    AV_CODEC_ID_APNG(32782),
    AV_CODEC_ID_DAALA(32783),
    AV_CODEC_ID_CFHD(32784),
    AV_CODEC_ID_TRUEMOTION2RT(32785),
    AV_CODEC_ID_M101(32786),
    AV_CODEC_ID_MAGICYUV(32787),
    AV_CODEC_ID_SHEERVIDEO(32788),
    AV_CODEC_ID_YLC(32789),
    AV_CODEC_ID_PSD(32790),
    AV_CODEC_ID_PIXLET(32791),
    AV_CODEC_ID_SPEEDHQ(32792),
    AV_CODEC_ID_FMVC(32793),
    AV_CODEC_ID_SCPR(32794),
    AV_CODEC_ID_CLEARVIDEO(32795),
    AV_CODEC_ID_XPM(32796),
    AV_CODEC_ID_AV1(32797),
    AV_CODEC_ID_BITPACKED(32798),
    AV_CODEC_ID_MSCC(32799),
    AV_CODEC_ID_SRGC(32800),
    AV_CODEC_ID_SVG(32801),
    AV_CODEC_ID_GDV(32802),
    AV_CODEC_ID_FITS(32803),
    AV_CODEC_ID_IMM4(32804),
    AV_CODEC_ID_PROSUMER(32805),
    AV_CODEC_ID_MWSC(32806),
    AV_CODEC_ID_WCMV(32807),
    AV_CODEC_ID_RASC(32808),
    AV_CODEC_ID_HYMT(32809),
    AV_CODEC_ID_ARBC(32810),
    AV_CODEC_ID_AGM(32811),
    AV_CODEC_ID_LSCR(32812),
    AV_CODEC_ID_VP4(32813),

    /* various PCM "codecs" */
    AV_CODEC_ID_FIRST_AUDIO(65536), // 0x10000(0),     ///< A dummy id pointing at the start of audio codecs
    AV_CODEC_ID_PCM_S16LE(65536), // = 0x10000
    AV_CODEC_ID_PCM_S16BE(65537),
    AV_CODEC_ID_PCM_U16LE(65538),
    AV_CODEC_ID_PCM_U16BE(65539),
    AV_CODEC_ID_PCM_S8(65540),
    AV_CODEC_ID_PCM_U8(65541),
    AV_CODEC_ID_PCM_MULAW(65542),
    AV_CODEC_ID_PCM_ALAW(65543),
    AV_CODEC_ID_PCM_S32LE(65544),
    AV_CODEC_ID_PCM_S32BE(65545),
    AV_CODEC_ID_PCM_U32LE(65546),
    AV_CODEC_ID_PCM_U32BE(65547),
    AV_CODEC_ID_PCM_S24LE(65548),
    AV_CODEC_ID_PCM_S24BE(65549),
    AV_CODEC_ID_PCM_U24LE(65550),
    AV_CODEC_ID_PCM_U24BE(65551),
    AV_CODEC_ID_PCM_S24DAUD(65552),
    AV_CODEC_ID_PCM_ZORK(65553),
    AV_CODEC_ID_PCM_S16LE_PLANAR(65554),
    AV_CODEC_ID_PCM_DVD(65554),
    AV_CODEC_ID_PCM_F32BE(65555),
    AV_CODEC_ID_PCM_F32LE(65556),
    AV_CODEC_ID_PCM_F64BE(65557),
    AV_CODEC_ID_PCM_F64LE(65558),
    AV_CODEC_ID_PCM_BLURAY(65559),
    AV_CODEC_ID_PCM_LXF(65560),
    AV_CODEC_ID_S302M(65561),
    AV_CODEC_ID_PCM_S8_PLANAR(65562),
    AV_CODEC_ID_PCM_S24LE_PLANAR(65563),
    AV_CODEC_ID_PCM_S32LE_PLANAR(65564),
    AV_CODEC_ID_PCM_S16BE_PLANAR(65565),

    AV_CODEC_ID_PCM_S64LE(67584), // = 0x10800(0),
    AV_CODEC_ID_PCM_S64BE(67585),
    AV_CODEC_ID_PCM_F16LE(67586),
    AV_CODEC_ID_PCM_F24LE(67587),
    AV_CODEC_ID_PCM_VIDC(67588),

    /* various ADPCM codecs */
    AV_CODEC_ID_ADPCM_IMA_QT(69632), // = 0x11000(0),
    AV_CODEC_ID_ADPCM_IMA_WAV(69633),
    AV_CODEC_ID_ADPCM_IMA_DK3(69634),
    AV_CODEC_ID_ADPCM_IMA_DK4(69635),
    AV_CODEC_ID_ADPCM_IMA_WS(69636),
    AV_CODEC_ID_ADPCM_IMA_SMJPEG(69637),
    AV_CODEC_ID_ADPCM_MS(69638),
    AV_CODEC_ID_ADPCM_4XM(696389),
    AV_CODEC_ID_ADPCM_XA(69640),
    AV_CODEC_ID_ADPCM_ADX(69641),
    AV_CODEC_ID_ADPCM_EA(69642),
    AV_CODEC_ID_ADPCM_G726(69643),
    AV_CODEC_ID_ADPCM_CT(69644),
    AV_CODEC_ID_ADPCM_SWF(69645),
    AV_CODEC_ID_ADPCM_YAMAHA(69646),
    AV_CODEC_ID_ADPCM_SBPRO_4(69647),
    AV_CODEC_ID_ADPCM_SBPRO_3(69648),
    AV_CODEC_ID_ADPCM_SBPRO_2(69649),
    AV_CODEC_ID_ADPCM_THP(69650),
    AV_CODEC_ID_ADPCM_IMA_AMV(69651),
    AV_CODEC_ID_ADPCM_EA_R1(69652),
    AV_CODEC_ID_ADPCM_EA_R3(69653),
    AV_CODEC_ID_ADPCM_EA_R2(69654),
    AV_CODEC_ID_ADPCM_IMA_EA_SEAD(69655),
    AV_CODEC_ID_ADPCM_IMA_EA_EACS(69656),
    AV_CODEC_ID_ADPCM_EA_XAS(69657),
    AV_CODEC_ID_ADPCM_EA_MAXIS_XA(69658),
    AV_CODEC_ID_ADPCM_IMA_ISS(69659),
    AV_CODEC_ID_ADPCM_G722(69660),
    AV_CODEC_ID_ADPCM_IMA_APC(69661),
    AV_CODEC_ID_ADPCM_VIMA(69662),

    AV_CODEC_ID_ADPCM_AFC(71680), // = 0x11800(0),
    AV_CODEC_ID_ADPCM_IMA_OKI(71681),
    AV_CODEC_ID_ADPCM_DTK(71682),
    AV_CODEC_ID_ADPCM_IMA_RAD(71683),
    AV_CODEC_ID_ADPCM_G726LE(71684),
    AV_CODEC_ID_ADPCM_THP_LE(71685),
    AV_CODEC_ID_ADPCM_PSX(71686),
    AV_CODEC_ID_ADPCM_AICA(71687),
    AV_CODEC_ID_ADPCM_IMA_DAT4(71688),
    AV_CODEC_ID_ADPCM_MTAF(71689),
    AV_CODEC_ID_ADPCM_AGM(71690),

    /* AMR */
    AV_CODEC_ID_AMR_NB(73728), // = 0x12000(0),
    AV_CODEC_ID_AMR_WB(73729),

    /* RealAudio codecs*/
    AV_CODEC_ID_RA_144(77824), // = 0x13000(0),
    AV_CODEC_ID_RA_288(77825),

    /* various DPCM codecs */
    AV_CODEC_ID_ROQ_DPCM(81920), // = 0x14000(0),
    AV_CODEC_ID_INTERPLAY_DPCM(81921),
    AV_CODEC_ID_XAN_DPCM(81922),
    AV_CODEC_ID_SOL_DPCM(81923),

    AV_CODEC_ID_SDX2_DPCM(83968), // = 0x14800(0),
    AV_CODEC_ID_GREMLIN_DPCM(839689),

    /* audio codecs */
    AV_CODEC_ID_MP2(86016), // = 0x15000(0),
    AV_CODEC_ID_MP3(86017), ///< preferred ID for decoding MPEG audio layer 1(0),) 2 or 3
    AV_CODEC_ID_AAC(86018),
    AV_CODEC_ID_AC3(86019),
    AV_CODEC_ID_DTS(86020),
    AV_CODEC_ID_VORBIS(86021),
    AV_CODEC_ID_DVAUDIO(86022),
    AV_CODEC_ID_WMAV1(86023),
    AV_CODEC_ID_WMAV2(86024),
    AV_CODEC_ID_MACE3(86025),
    AV_CODEC_ID_MACE6(86026),
    AV_CODEC_ID_VMDAUDIO(86027),
    AV_CODEC_ID_FLAC(86028),
    AV_CODEC_ID_MP3ADU(86029),
    AV_CODEC_ID_MP3ON4(86030),
    AV_CODEC_ID_SHORTEN(86031),
    AV_CODEC_ID_ALAC(86032),
    AV_CODEC_ID_WESTWOOD_SND1(86033),
    AV_CODEC_ID_GSM(86034), ///< as in Berlin toast format
    AV_CODEC_ID_QDM2(86035),
    AV_CODEC_ID_COOK(86036),
    AV_CODEC_ID_TRUESPEECH(86037),
    AV_CODEC_ID_TTA(86038),
    AV_CODEC_ID_SMACKAUDIO(86039),
    AV_CODEC_ID_QCELP(86040),
    AV_CODEC_ID_WAVPACK(86041),
    AV_CODEC_ID_DSICINAUDIO(86042),
    AV_CODEC_ID_IMC(86043),
    AV_CODEC_ID_MUSEPACK7(86044),
    AV_CODEC_ID_MLP(86045),
    AV_CODEC_ID_GSM_MS(86046), /* as found in WAV */
    AV_CODEC_ID_ATRAC3(86047),
    AV_CODEC_ID_APE(86048),
    AV_CODEC_ID_NELLYMOSER(86049),
    AV_CODEC_ID_MUSEPACK8(86050),
    AV_CODEC_ID_SPEEX(86051),
    AV_CODEC_ID_WMAVOICE(86052),
    AV_CODEC_ID_WMAPRO(86053),
    AV_CODEC_ID_WMALOSSLESS(86054),
    AV_CODEC_ID_ATRAC3P(86055),
    AV_CODEC_ID_EAC3(86056),
    AV_CODEC_ID_SIPR(86057),
    AV_CODEC_ID_MP1(86058),
    AV_CODEC_ID_TWINVQ(86059),
    AV_CODEC_ID_TRUEHD(86060),
    AV_CODEC_ID_MP4ALS(86061),
    AV_CODEC_ID_ATRAC1(86062),
    AV_CODEC_ID_BINKAUDIO_RDFT(86063),
    AV_CODEC_ID_BINKAUDIO_DCT(86064),
    AV_CODEC_ID_AAC_LATM(86065),
    AV_CODEC_ID_QDMC(86066),
    AV_CODEC_ID_CELT(86067),
    AV_CODEC_ID_G723_1(86068),
    AV_CODEC_ID_G729(86069),
    AV_CODEC_ID_8SVX_EXP(86070),
    AV_CODEC_ID_8SVX_FIB(86071),
    AV_CODEC_ID_BMV_AUDIO(86072),
    AV_CODEC_ID_RALF(86073),
    AV_CODEC_ID_IAC(86074),
    AV_CODEC_ID_ILBC(86075),
    AV_CODEC_ID_OPUS(86076),
    AV_CODEC_ID_COMFORT_NOISE(86077),
    AV_CODEC_ID_TAK(86078),
    AV_CODEC_ID_METASOUND(86079),
    AV_CODEC_ID_PAF_AUDIO(86080),
    AV_CODEC_ID_ON2AVC(86081),
    AV_CODEC_ID_DSS_SP(86082),
    AV_CODEC_ID_CODEC2(86083),

    AV_CODEC_ID_FFWAVESYNTH(88064), // = 0x15800(),
    AV_CODEC_ID_SONIC(88065),
    AV_CODEC_ID_SONIC_LS(88066),
    AV_CODEC_ID_EVRC(88067),
    AV_CODEC_ID_SMV(88068),
    AV_CODEC_ID_DSD_LSBF(88069),
    AV_CODEC_ID_DSD_MSBF(88070),
    AV_CODEC_ID_DSD_LSBF_PLANAR(88071),
    AV_CODEC_ID_DSD_MSBF_PLANAR(88072),
    AV_CODEC_ID_4GV(88073),
    AV_CODEC_ID_INTERPLAY_ACM(88074),
    AV_CODEC_ID_XMA1(88075),
    AV_CODEC_ID_XMA2(88076),
    AV_CODEC_ID_DST(88077),
    AV_CODEC_ID_ATRAC3AL(88078),
    AV_CODEC_ID_ATRAC3PAL(88079),
    AV_CODEC_ID_DOLBY_E(88080),
    AV_CODEC_ID_APTX(88081),
    AV_CODEC_ID_APTX_HD(88082),
    AV_CODEC_ID_SBC(88083),
    AV_CODEC_ID_ATRAC9(88084),
    AV_CODEC_ID_HCOM(88085),

    /* subtitle codecs */
    AV_CODEC_ID_FIRST_SUBTITLE(94208), // = 0x17000(),          ///< A dummy ID pointing at the start of subtitle codecs.
    AV_CODEC_ID_DVD_SUBTITLE(94208), // = 0x17000(),
    AV_CODEC_ID_DVB_SUBTITLE(94209),
    AV_CODEC_ID_TEXT(94210),  ///< raw UTF-8 text
    AV_CODEC_ID_XSUB(94211),
    AV_CODEC_ID_SSA(94212),
    AV_CODEC_ID_MOV_TEXT(94213),
    AV_CODEC_ID_HDMV_PGS_SUBTITLE(94214),
    AV_CODEC_ID_DVB_TELETEXT(94215),
    AV_CODEC_ID_SRT(94216),

    AV_CODEC_ID_MICRODVD(96256), //   = 0x17800(),
    AV_CODEC_ID_EIA_608(96257),
    AV_CODEC_ID_JACOSUB(96258),
    AV_CODEC_ID_SAMI(96259),
    AV_CODEC_ID_REALTEXT(96260),
    AV_CODEC_ID_STL(96262),
    AV_CODEC_ID_SUBVIEWER1(96263),
    AV_CODEC_ID_SUBVIEWER(96264),
    AV_CODEC_ID_SUBRIP(96265),
    AV_CODEC_ID_WEBVTT(96266),
    AV_CODEC_ID_MPL2(96267),
    AV_CODEC_ID_VPLAYER(96268),
    AV_CODEC_ID_PJS(96269),
    AV_CODEC_ID_ASS(96270),
    AV_CODEC_ID_HDMV_TEXT_SUBTITLE(96271),
    AV_CODEC_ID_TTML(96272),
    AV_CODEC_ID_ARIB_CAPTION(96273),

    /* other specific kind of codecs (generally used for attachments) */
    AV_CODEC_ID_FIRST_UNKNOWN(98304),// = 0x18000(),           ///< A dummy ID pointing at the start of various fake codecs.
    AV_CODEC_ID_TTF(98304), // = 0x18000(),

    AV_CODEC_ID_SCTE_35(98305), ///< Contain timestamp estimated through PCR of program stream.
    AV_CODEC_ID_BINTEXT(100352), //    = 0x18800(),
    AV_CODEC_ID_XBIN(100353),
    AV_CODEC_ID_IDF(100354),
    AV_CODEC_ID_OTF(100355),
    AV_CODEC_ID_SMPTE_KLV(100356),
    AV_CODEC_ID_DVD_NAV(100357),
    AV_CODEC_ID_TIMED_ID3(100358),
    AV_CODEC_ID_BIN_DATA(100359),


    AV_CODEC_ID_PROBE(102400),// = 0x19000(), ///< codec_id is not known (like AV_CODEC_ID_NONE) but lavf should attempt to identify it

    AV_CODEC_ID_MPEG2TS(131072), // = 0x20000(), /**< _FAKE_ codec to indicate a raw MPEG-2 TS
     /* stream (only used by libavformat) */
    AV_CODEC_ID_MPEG4SYSTEMS(131073), // = 0x20001(), /**< _FAKE_ codec to indicate a MPEG-4 Systems
     /* stream (only used by libavformat) */
    AV_CODEC_ID_FFMETADATA(135168), // = 0x21000(),   ///< Dummy codec for streams containing only metadata information.
    AV_CODEC_ID_WRAPPED_AVFRAME(135169) // = 0x21001(), ///< Passthrough codec(0),) AVFrames wrapped in AVPacket

    ;

    companion object {
        @JvmStatic
        fun forNativeEnumValue(nativeEnumValue: Int) =
            ffmpeg4kj.util.forNativeEnumValue(values(), nativeEnumValue)
    }
}
