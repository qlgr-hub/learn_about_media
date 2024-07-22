#pragma once

#include "packet.hxx"
#include <string_view>


namespace LAM {

struct IFormatBase {
    virtual bool open(std::string_view filename) = 0;
    virtual void close() = 0;
};


struct IMuxer : public IFormatBase, public IPacketConsumer {
    virtual void initAudioParam(const IAudioCodecParam& audioParam) = 0;
    virtual void initVideoParam(const IVideoCodecParam& videoParam) = 0;
};


struct IDemuxer : public IFormatBase, public IPacketProducer {
    virtual const IAudioCodecParam& getAudioParam() const = 0;
    virtual const IVideoCodecParam& getVideoParam() const = 0;
};

} // namespace LAM