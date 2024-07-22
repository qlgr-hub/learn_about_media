#pragma once

#include "../../include/packet.hxx"
#include "utils.hxx"

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
}


namespace LAM {

class CodecParamFF {
protected:
    AVCodecParameters* _codecpar;

public:
    CodecParamFF() : _codecpar{ nullptr } {
        _codecpar = avcodec_parameters_alloc();
        if (!_codecpar) {
            Utils::Err("avcodec_parameters_alloc fail");
        }
    }

    virtual ~CodecParamFF() {
        avcodec_parameters_free(&_codecpar);
    }

public:
    AVCodecID getCodecId() const {
        return _codecpar->codec_id;
    }

public:
    bool fromStream(const AVStream* stream) {
        auto ret{ avcodec_parameters_copy(_codecpar, stream->codecpar) };
        if (ret < 0) {
            Utils::Err("avcodec_parameters_copy fail", ret);
            return false;
        }

        return true;
    }

    bool toStream(AVStream* stream) const {
        auto ret{ avcodec_parameters_copy(stream->codecpar, _codecpar) };
        if (ret < 0) {
            Utils::Err("avcodec_parameters_copy fail", ret);
            return false;
        }

        return true;
    }

    bool fromCodecContext(const AVCodecContext* codecCtx) {
        auto ret{ avcodec_parameters_from_context(_codecpar, codecCtx) };
        if (ret < 0) {
            Utils::Err("avcodec_parameters_from_context fail", ret);
            return false;
        }

        return true;
    }

    bool toCodecContext(AVCodecContext* codecCtx) const {
        auto ret{ avcodec_parameters_to_context(codecCtx, _codecpar) };
        if (ret < 0) {
            Utils::Err("avcodec_parameters_to_context fail", ret);
            return false;
        }

        return true;
    }
};


class AudioCodecParamFF final : public CodecParamFF, public IAudioCodecParam {
public:
    AudioCodecParamFF() {
    }

    ~AudioCodecParamFF() = default;

public:
    void copyFrom(const IAudioCodecParam& src) {
        auto srcff{ dynamic_cast<const AudioCodecParamFF&>(src) };
        avcodec_parameters_copy(_codecpar, srcff._codecpar);

        // _codecpar->bit_rate = src.bitRate();
        // _codecpar->frame_size = src.frameSize();
        // _codecpar->framerate = { src.frameRate().numeraotr, src.frameRate().denominator };
        // _codecpar->sample_rate = src.sampleRate();
        // _codecpar->format = Utils::as(src.format());
        // _codecpar->codec_id = Utils::as(src.protocal());
    }

public:
    int64_t bitRate() const override {
        return _codecpar->bit_rate;
    }

    int32_t frameSize() const override {
        return _codecpar->frame_size;
    }

    Rational frameRate() const override {
        return { _codecpar->framerate.num, _codecpar->framerate.den };
    }

    int32_t sampleRate() const override {
        return _codecpar->sample_rate;
    }
    
    AudioSampleFormat format() const override {
        return Utils::as(static_cast<AVSampleFormat>(_codecpar->format));
    }

    AudioCodecProtocal protocal() const override {
        return Utils::as(_codecpar->codec_id);
    }
    
    AudioChannelInfo channelInfo() const override {
        return {};
    }
};


class VideoCodecParamFF final : public CodecParamFF, public IVideoCodecParam {
public:
    VideoCodecParamFF() {
    }

    ~VideoCodecParamFF() = default;

public:
    void copyFrom(const IVideoCodecParam& src) {
        // TODO: Does not rely on FFmpeg's deep copy
        auto srcff{ dynamic_cast<const VideoCodecParamFF&>(src) };
        avcodec_parameters_copy(_codecpar, srcff._codecpar);

        // _codecpar->video_delay = src.delay();
        // _codecpar->bit_rate = src.bitRate();
        // _codecpar->framerate = { src.frameRate().numeraotr, src.frameRate().denominator };
        // _codecpar->sample_aspect_ratio = { src.aspectRatio().numeraotr, src.aspectRatio().denominator };
        // _codecpar->format = Utils::as(src.format());
        // _codecpar->width = src.resolution().width;
        // _codecpar->height = src.resolution().height;
        // _codecpar->codec_id = Utils::as(src.protocal());
    }

public:
    int32_t delay() const override {
        return _codecpar->video_delay;
    }

    int64_t bitRate() const override {
        return _codecpar->bit_rate;
    }

    Rational frameRate() const override {
        return { _codecpar->framerate.num, _codecpar->framerate.den };
    }

    Rational aspectRatio() const override {
        return { _codecpar->sample_aspect_ratio.num, _codecpar->sample_aspect_ratio.den };
    }

    VideoSampleFormat format() const override {
        return Utils::as(static_cast<AVPixelFormat>(_codecpar->format));
    }

    VideoColorInfo colorInfo() const override {
        return {};
    }

    VideoResolution resolution() const override {
        return { _codecpar->width, _codecpar->height };
    }

    VideoCodecProtocal protocal() const override {
        return Utils::as(_codecpar->codec_id, 0);
    }
};

} // namespace LAM
