#pragma once

#include "frame.hxx"
#include "packet.hxx"


namespace LAM {

template <typename CodecParamT>
struct ICodecBase {
    virtual bool open(const CodecParamT& param) = 0;
    virtual void close() = 0;
};


template <typename FrameT, typename CodecParamT>
struct IEncoder : public ICodecBase<CodecParamT>, public IFrameConsumer<FrameT>, public IPacketProducer {
    virtual const CodecParamT& getCodecParam() const = 0;
};


template <typename FrameT, typename CodecParamT>
struct IDecoder : public ICodecBase<CodecParamT>, public IFrameProducer<FrameT>, public IPacketConsumer {
};

using IAudioEncoder = IEncoder<IAudioFrame, IAudioCodecParam>;
using IVideoEncoder = IEncoder<IVideoFrame, IVideoCodecParam>;
using IAudioDecoder = IDecoder<IAudioFrame, IAudioCodecParam>;
using IVideoDecoder = IDecoder<IVideoFrame, IVideoCodecParam>;

} // namespace LAM