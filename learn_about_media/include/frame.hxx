#pragma once

#include "common.hxx"
#include <cstdint>
#include <utility>


namespace LAM {

struct IFrameBase {
    virtual int64_t pts() const = 0;
    virtual Rational timeBase() const = 0;
    virtual std::pair<uint8_t*, int32_t> getData(uint32_t chIdx) const = 0;
};


struct IAudioFrame : public IFrameBase {
    virtual int32_t sampleRate() const = 0;
    virtual int32_t numberOfSamples() const = 0;
    virtual AudioSampleFormat format() const = 0;
    virtual AudioChannelInfo channelInfo() const = 0;
};


enum VideoFrameType {
    VFT_NONE = 0,
    VFT_I,
    VFT_P,
    VFT_B,
    VFT_S,
    VFT_SI,
    VFT_SP,
    VFT_BI,
    VFT_SIZE
};


struct IVideoFrame : public IFrameBase {
    virtual VideoFrameType type() const = 0;
    virtual Rational aspectRatio() const = 0;
    virtual VideoSampleFormat format() const = 0;
    virtual VideoColorInfo colorInfo() const = 0;
    virtual VideoResolution resolution() const = 0;
};


template <typename FrameT>
struct IFrameConsumer {
    virtual bool put(const FrameT*) = 0;
};


template <typename FrameT>
struct IFrameProducer {
    virtual const FrameT* get() const = 0;
};

using IVideoFrameConsumer = IFrameConsumer<IVideoFrame>;
using IVideoFrameProducer = IFrameProducer<IVideoFrame>;
using IAudioFrameConsumer = IFrameConsumer<IAudioFrame>;
using IAudioFrameProducer = IFrameProducer<IAudioFrame>;

} // namespace LAM
