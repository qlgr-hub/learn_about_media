#pragma once

#include "../../include/frame.hxx"
#include "utils.hxx"

extern "C" {
    #include <libavutil/frame.h>
    #include <libavcodec/avcodec.h>
}


namespace LAM {

class FrameFF {
private:
    void __reset() const {
        av_frame_unref(_frame);
    }

protected:
    AVFrame* _frame;

    FrameFF() : _frame{ nullptr } {
        _frame = av_frame_alloc();
        if (!_frame) {
            Utils::Err("av_frame_alloc fail");
        }
    }

    virtual ~FrameFF() {
        av_frame_free(&_frame);
    }

// Interaction part with AVCodecContext
public:
    bool sendTo(AVCodecContext* codecCtx) const {
        auto ret{ avcodec_send_frame(codecCtx, _frame) };
        if (ret < 0) {
            Utils::Err("avcodec_send_frame fail", ret);
            return false;
        }

        return true;
    }

    bool receiveFrom(AVCodecContext* codecCtx) const {
        __reset();

        auto ret { avcodec_receive_frame(codecCtx, _frame) };
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            return false;
        }
        else if (ret < 0) {
            Utils::Err("avcodec_receive_frame fail", ret);
            return false;
        }

        return true;
    }
};


class VideoFrameFF final : public FrameFF, public IVideoFrame {
public:
    VideoFrameFF() = default;
    ~VideoFrameFF() = default;

public:
    int64_t pts() const override {
        return _frame->pts;
    }

    Rational timeBase() const override {
        return { _frame->time_base.num, _frame->time_base.den };
    }

    VideoFrameType type() const override {
        return Utils::as(_frame->pict_type);
    }

    Rational aspectRatio() const override {
        return { _frame->sample_aspect_ratio.num, _frame->sample_aspect_ratio.den };
    }

    VideoSampleFormat format() const override {
        return Utils::as(static_cast<AVPixelFormat>(_frame->format));
    }

    VideoColorInfo colorInfo() const override {
        return {}; // TODO:
    }

    VideoResolution resolution() const override {
        return { _frame->width, _frame->height };
    }

    std::pair<uint8_t*, int32_t> getData(uint32_t chIdx) const override {
        return { _frame->data[chIdx], _frame->linesize[chIdx] };
    }
};


class AudioFrameFF final : public FrameFF, public IAudioFrame {
public:
    AudioFrameFF() = default;
    ~AudioFrameFF() = default;

public:
    int64_t pts() const override {
        return _frame->pts;
    }

    Rational timeBase() const override {
        return { _frame->time_base.num, _frame->time_base.den };
    }

    virtual int32_t sampleRate() const override {
        return _frame->sample_rate;
    }
    
    int32_t numberOfSamples() const override {
        return _frame->nb_samples;
    }

    AudioSampleFormat format() const override {
        return Utils::as(static_cast<AVSampleFormat>(_frame->format));
    }

    AudioChannelInfo channelInfo() const override {
        return {};
    }
    
    std::pair<uint8_t*, int32_t> getData(uint32_t chIdx) const override {
        return { _frame->data[chIdx], _frame->linesize[chIdx] };
    }
};

} // namespace LAM
