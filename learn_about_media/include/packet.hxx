#pragma once

#include "common.hxx"
#include <cstdint>
#include <utility>


namespace LAM {

enum class AudioCodecProtocal {
    ACP_NONE = -1,
    ACP_PCM_S16LE,
    ACP_PCM_S16BE,
    ACP_PCM_U16LE,
    ACP_PCM_U16BE,
    ACP_PCM_S8,
    ACP_PCM_U8,
    ACP_PCM_MULAW,
    ACP_PCM_ALAW,
    ACP_PCM_S32LE,
    ACP_PCM_S32BE,
    ACP_PCM_U32LE,
    ACP_PCM_U32BE,
    ACP_PCM_S24LE,
    ACP_PCM_S24BE,
    ACP_PCM_U24LE,
    ACP_PCM_U24BE,
    ACP_PCM_S24DAUD,
    ACP_PCM_ZORK,
    ACP_PCM_S16LE_PLANAR,
    ACP_PCM_DVD,
    ACP_PCM_F32BE,
    ACP_PCM_F32LE,
    ACP_PCM_F64BE,
    ACP_PCM_F64LE,
    ACP_PCM_BLURAY,
    ACP_PCM_LXF,
    ACP_S302M,
    ACP_PCM_S8_PLANAR,
    ACP_PCM_S24LE_PLANAR,
    ACP_PCM_S32LE_PLANAR,
    ACP_PCM_S16BE_PLANAR,
    ACP_PCM_S64LE,
    ACP_PCM_S64BE,
    ACP_PCM_F16LE,
    ACP_PCM_F24LE,
    ACP_PCM_VIDC,
    ACP_PCM_SGA,
    ACP_ADPCM_IMA_QT,
    ACP_ADPCM_IMA_WAV,
    ACP_ADPCM_IMA_DK3,
    ACP_ADPCM_IMA_DK4,
    ACP_ADPCM_IMA_WS,
    ACP_ADPCM_IMA_SMJPEG,
    ACP_ADPCM_MS,
    ACP_ADPCM_4XM,
    ACP_ADPCM_XA,
    ACP_ADPCM_ADX,
    ACP_ADPCM_EA,
    ACP_ADPCM_G726,
    ACP_ADPCM_CT,
    ACP_ADPCM_SWF,
    ACP_ADPCM_YAMAHA,
    ACP_ADPCM_SBPRO_4,
    ACP_ADPCM_SBPRO_3,
    ACP_ADPCM_SBPRO_2,
    ACP_ADPCM_THP,
    ACP_ADPCM_IMA_AMV,
    ACP_ADPCM_EA_R1,
    ACP_ADPCM_EA_R3,
    ACP_ADPCM_EA_R2,
    ACP_ADPCM_IMA_EA_SEAD,
    ACP_ADPCM_IMA_EA_EACS,
    ACP_ADPCM_EA_XAS,
    ACP_ADPCM_EA_MAXIS_XA,
    ACP_ADPCM_IMA_ISS,
    ACP_ADPCM_G722,
    ACP_ADPCM_IMA_APC,
    ACP_ADPCM_VIMA,
    ACP_ADPCM_AFC,
    ACP_ADPCM_IMA_OKI,
    ACP_ADPCM_DTK,
    ACP_ADPCM_IMA_RAD,
    ACP_ADPCM_G726LE,
    ACP_ADPCM_THP_LE,
    ACP_ADPCM_PSX,
    ACP_ADPCM_AICA,
    ACP_ADPCM_IMA_DAT4,
    ACP_ADPCM_MTAF,
    ACP_ADPCM_AGM,
    ACP_ADPCM_ARGO,
    ACP_ADPCM_IMA_SSI,
    ACP_ADPCM_ZORK,
    ACP_ADPCM_IMA_APM,
    ACP_ADPCM_IMA_ALP,
    ACP_ADPCM_IMA_MTF,
    ACP_ADPCM_IMA_CUNNING,
    ACP_ADPCM_IMA_MOFLEX,
    ACP_ADPCM_IMA_ACORN,
    ACP_ADPCM_XMD,
    ACP_AMR_NB,
    ACP_AMR_WB,
    ACP_RA_144,
    ACP_RA_288,
    ACP_ROQ_DPCM,
    ACP_INTERPLAY_DPCM,
    ACP_XAN_DPCM,
    ACP_SOL_DPCM,
    ACP_SDX2_DPCM,
    ACP_GREMLIN_DPCM,
    ACP_DERF_DPCM,
    ACP_WADY_DPCM,
    ACP_CBD2_DPCM,
    ACP_MP2,
    ACP_MP3,
    ACP_AAC,
    ACP_AC3,
    ACP_DTS,
    ACP_VORBIS,
    ACP_DVAUDIO,
    ACP_WMAV1,
    ACP_WMAV2,
    ACP_MACE3,
    ACP_MACE6,
    ACP_VMDAUDIO,
    ACP_FLAC,
    ACP_MP3ADU,
    ACP_MP3ON4,
    ACP_SHORTEN,
    ACP_ALAC,
    ACP_WESTWOOD_SND1,
    ACP_GSM,
    ACP_QDM2,
    ACP_COOK,
    ACP_TRUESPEECH,
    ACP_TTA,
    ACP_SMACKAUDIO,
    ACP_QCELP,
    ACP_WAVPACK,
    ACP_DSICINAUDIO,
    ACP_IMC,
    ACP_MUSEPACK7,
    ACP_MLP,
    ACP_GSM_MS,
    ACP_ATRAC3,
    ACP_APE,
    ACP_NELLYMOSER,
    ACP_MUSEPACK8,
    ACP_SPEEX,
    ACP_WMAVOICE,
    ACP_WMAPRO,
    ACP_WMALOSSLESS,
    ACP_ATRAC3P,
    ACP_EAC3,
    ACP_SIPR,
    ACP_MP1,
    ACP_TWINVQ,
    ACP_TRUEHD,
    ACP_MP4ALS,
    ACP_ATRAC1,
    ACP_BINKAUDIO_RDFT,
    ACP_BINKAUDIO_DCT,
    ACP_AAC_LATM,
    ACP_QDMC,
    ACP_CELT,
    ACP_G723_1,
    ACP_G729,
    ACP_8SVX_EXP,
    ACP_8SVX_FIB,
    ACP_BMV_AUDIO,
    ACP_RALF,
    ACP_IAC,
    ACP_ILBC,
    ACP_OPUS,
    ACP_COMFORT_NOISE,
    ACP_TAK,
    ACP_METASOUND,
    ACP_PAF_AUDIO,
    ACP_ON2AVC,
    ACP_DSS_SP,
    ACP_CODEC2,
    ACP_FFWAVESYNTH,
    ACP_SONIC,
    ACP_SONIC_LS,
    ACP_EVRC,
    ACP_SMV,
    ACP_DSD_LSBF,
    ACP_DSD_MSBF,
    ACP_DSD_LSBF_PLANAR,
    ACP_DSD_MSBF_PLANAR,
    ACP_4GV,
    ACP_INTERPLAY_ACM,
    ACP_XMA1,
    ACP_XMA2,
    ACP_DST,
    ACP_ATRAC3AL,
    ACP_ATRAC3PAL,
    ACP_DOLBY_E,
    ACP_APTX,
    ACP_APTX_HD,
    ACP_SBC,
    ACP_ATRAC9,
    ACP_HCOM,
    ACP_ACELP_KELVIN,
    ACP_MPEGH_3D_AUDIO,
    ACP_SIREN,
    ACP_HCA,
    ACP_FASTAUDIO,
    ACP_MSNSIREN,
    ACP_DFPWM,
    ACP_BONK,
    ACP_MISC4,
    ACP_APAC,
    ACP_FTR,
    ACP_WAVARC,
    ACP_RKA,
    ACP_AC4,
    ACP_OSQ,
    ACP_QOA,
    ACP_SIZE
};


enum class VideoCodecProtocal {
    VCP_NONE,
    VCP_MPEG1VIDEO,
    VCP_MPEG2VIDEO,
    VCP_H261,
    VCP_H263,
    VCP_RV10,
    VCP_RV20,
    VCP_MJPEG,
    VCP_MJPEGB,
    VCP_LJPEG,
    VCP_SP5X,
    VCP_JPEGLS,
    VCP_MPEG4,
    VCP_RAWVIDEO,
    VCP_MSMPEG4V1,
    VCP_MSMPEG4V2,
    VCP_MSMPEG4V3,
    VCP_WMV1,
    VCP_WMV2,
    VCP_H263P,
    VCP_H263I,
    VCP_FLV1,
    VCP_SVQ1,
    VCP_SVQ3,
    VCP_DVVIDEO,
    VCP_HUFFYUV,
    VCP_CYUV,
    VCP_H264,
    VCP_INDEO3,
    VCP_VP3,
    VCP_THEORA,
    VCP_ASV1,
    VCP_ASV2,
    VCP_FFV1,
    VCP_4XM,
    VCP_VCR1,
    VCP_CLJR,
    VCP_MDEC,
    VCP_ROQ,
    VCP_INTERPLAY_VIDEO,
    VCP_XAN_WC3,
    VCP_XAN_WC4,
    VCP_RPZA,
    VCP_CINEPAK,
    VCP_WS_VQA,
    VCP_MSRLE,
    VCP_MSVIDEO1,
    VCP_IDCIN,
    VCP_8BPS,
    VCP_SMC,
    VCP_FLIC,
    VCP_TRUEMOTION1,
    VCP_VMDVIDEO,
    VCP_MSZH,
    VCP_ZLIB,
    VCP_QTRLE,
    VCP_TSCC,
    VCP_ULTI,
    VCP_QDRAW,
    VCP_VIXL,
    VCP_QPEG,
    VCP_PNG,
    VCP_PPM,
    VCP_PBM,
    VCP_PGM,
    VCP_PGMYUV,
    VCP_PAM,
    VCP_FFVHUFF,
    VCP_RV30,
    VCP_RV40,
    VCP_VC1,
    VCP_WMV3,
    VCP_LOCO,
    VCP_WNV1,
    VCP_AASC,
    VCP_INDEO2,
    VCP_FRAPS,
    VCP_TRUEMOTION2,
    VCP_BMP,
    VCP_CSCD,
    VCP_MMVIDEO,
    VCP_ZMBV,
    VCP_AVS,
    VCP_SMACKVIDEO,
    VCP_NUV,
    VCP_KMVC,
    VCP_FLASHSV,
    VCP_CAVS,
    VCP_JPEG2000,
    VCP_VMNC,
    VCP_VP5,
    VCP_VP6,
    VCP_VP6F,
    VCP_TARGA,
    VCP_DSICINVIDEO,
    VCP_TIERTEXSEQVIDEO,
    VCP_TIFF,
    VCP_GIF,
    VCP_DXA,
    VCP_DNXHD,
    VCP_THP,
    VCP_SGI,
    VCP_C93,
    VCP_BETHSOFTVID,
    VCP_PTX,
    VCP_TXD,
    VCP_VP6A,
    VCP_AMV,
    VCP_VB,
    VCP_PCX,
    VCP_SUNRAST,
    VCP_INDEO4,
    VCP_INDEO5,
    VCP_MIMIC,
    VCP_RL2,
    VCP_ESCAPE124,
    VCP_DIRAC,
    VCP_BFI,
    VCP_CMV,
    VCP_MOTIONPIXELS,
    VCP_TGV,
    VCP_TGQ,
    VCP_TQI,
    VCP_AURA,
    VCP_AURA2,
    VCP_V210X,
    VCP_TMV,
    VCP_V210,
    VCP_DPX,
    VCP_MAD,
    VCP_FRWU,
    VCP_FLASHSV2,
    VCP_CDGRAPHICS,
    VCP_R210,
    VCP_ANM,
    VCP_BINKVIDEO,
    VCP_IFF_ILBM,
    VCP_KGV1,
    VCP_YOP,
    VCP_VP8,
    VCP_PICTOR,
    VCP_ANSI,
    VCP_A64_MULTI,
    VCP_A64_MULTI5,
    VCP_R10K,
    VCP_MXPEG,
    VCP_LAGARITH,
    VCP_PRORES,
    VCP_JV,
    VCP_DFA,
    VCP_WMV3IMAGE,
    VCP_VC1IMAGE,
    VCP_UTVIDEO,
    VCP_BMV_VIDEO,
    VCP_VBLE,
    VCP_DXTORY,
    VCP_V410,
    VCP_XWD,
    VCP_CDXL,
    VCP_XBM,
    VCP_ZEROCODEC,
    VCP_MSS1,
    VCP_MSA1,
    VCP_TSCC2,
    VCP_MTS2,
    VCP_CLLC,
    VCP_MSS2,
    VCP_VP9,
    VCP_AIC,
    VCP_ESCAPE130,
    VCP_G2M,
    VCP_WEBP,
    VCP_HNM4_VIDEO,
    VCP_HEVC,
    VCP_FIC,
    VCP_ALIAS_PIX,
    VCP_BRENDER_PIX,
    VCP_PAF_VIDEO,
    VCP_EXR,
    VCP_VP7,
    VCP_SANM,
    VCP_SGIRLE,
    VCP_MVC1,
    VCP_MVC2,
    VCP_HQX,
    VCP_TDSC,
    VCP_HQ_HQA,
    VCP_HAP,
    VCP_DDS,
    VCP_DXV,
    VCP_SCREENPRESSO,
    VCP_RSCC,
    VCP_AVS2,
    VCP_PGX,
    VCP_AVS3,
    VCP_MSP2,
    VCP_VVC,
    VCP_Y41P,
    VCP_AVRP,
    VCP_012V,
    VCP_AVUI,
    VCP_TARGA_Y216,
    VCP_V308,
    VCP_V408,
    VCP_YUV4,
    VCP_AVRN,
    VCP_CPIA,
    VCP_XFACE,
    VCP_SNOW,
    VCP_SMVJPEG,
    VCP_APNG,
    VCP_DAALA,
    VCP_CFHD,
    VCP_TRUEMOTION2RT,
    VCP_M101,
    VCP_MAGICYUV,
    VCP_SHEERVIDEO,
    VCP_YLC,
    VCP_PSD,
    VCP_PIXLET,
    VCP_SPEEDHQ,
    VCP_FMVC,
    VCP_SCPR,
    VCP_CLEARVIDEO,
    VCP_XPM,
    VCP_AV1,
    VCP_BITPACKED,
    VCP_MSCC,
    VCP_SRGC,
    VCP_SVG,
    VCP_GDV,
    VCP_FITS,
    VCP_IMM4,
    VCP_PROSUMER,
    VCP_MWSC,
    VCP_WCMV,
    VCP_RASC,
    VCP_HYMT,
    VCP_ARBC,
    VCP_AGM,
    VCP_LSCR,
    VCP_VP4,
    VCP_IMM5,
    VCP_MVDV,
    VCP_MVHA,
    VCP_CDTOONS,
    VCP_MV30,
    VCP_NOTCHLC,
    VCP_PFM,
    VCP_MOBICLIP,
    VCP_PHOTOCD,
    VCP_IPU,
    VCP_ARGO,
    VCP_CRI,
    VCP_SIMBIOSIS_IMX,
    VCP_SGA_VIDEO,
    VCP_GEM,
    VCP_VBN,
    VCP_JPEGXL,
    VCP_QOI,
    VCP_PHM,
    VCP_RADIANCE_HDR,
    VCP_WBMP,
    VCP_MEDIA100,
    VCP_VQC,
    VCP_PDV,
    VCP_EVC,
    VCP_RTV1,
    VCP_VMIX,
    VCP_LEAD,
    VCP_SIZE
};


struct IAudioCodecParam {
    virtual int64_t bitRate() const = 0;
    virtual int32_t frameSize() const = 0;
    virtual Rational frameRate() const = 0;
    virtual int32_t sampleRate() const = 0;
    virtual AudioSampleFormat format() const = 0;
    virtual AudioCodecProtocal protocal() const = 0;
    virtual AudioChannelInfo channelInfo() const = 0;
};


struct IVideoCodecParam {
    virtual int32_t delay() const = 0;
    virtual int64_t bitRate() const = 0;
    virtual Rational frameRate() const = 0;
    virtual Rational aspectRatio() const = 0;
    virtual VideoColorInfo colorInfo() const = 0;
    virtual VideoSampleFormat format() const = 0;
    virtual VideoResolution resolution() const = 0;
    virtual VideoCodecProtocal protocal() const = 0;
};


enum MediaType {
    MT_NONE = -1,
    MT_AUDIO,
    MT_VIDEO,
    // ...
    MT_SIZE
};


struct IPacket {
    virtual MediaType type() const = 0;
    virtual int64_t pts() const = 0;
    virtual int64_t dts() const = 0;
    virtual int64_t duration() const = 0;
    virtual Rational timeBase() const = 0;
    virtual std::pair<uint8_t*, int32_t> data() const = 0;
};


struct IPacketConsumer {
    virtual bool put(const IPacket*) = 0; 
};


struct IPacketProducer {
    virtual const IPacket* get() const = 0; 
};

} // namespace LAM
