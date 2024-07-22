#include "../../include/factory.hxx"
#include "codecparamff.hxx"
#include "frameff.hxx"
#include "packetff.hxx"
#include "utils.hxx"

extern "C" {
    #include <libavcodec/codec_id.h>
    #include <libavcodec/codec.h>
    #include <libavcodec/avcodec.h>
}


namespace LAM {

class CodecBaseFF {
protected:
    AVCodecContext* _codecCtx;

private:
    virtual const AVCodec* __findCodec(AVCodecID codecId) const = 0;
    virtual bool __parserInit(AVCodecID codecId) = 0;

protected:
    bool _open(const CodecParamFF& codecParam) {
        const AVCodec* codec{ __findCodec(codecParam.getCodecId()) };
        if (!codec) {
            Utils::Err("find Codec fail");
            return false;
        }

        if (!__parserInit(codec->id))
            return false;

        _codecCtx = avcodec_alloc_context3(codec);
        if (!_codecCtx) {
            Utils::Err("avcodec_alloc_context3 fail");
            return false;
        }

        if (!codecParam.toCodecContext(_codecCtx))
            return false;

        auto ret{ avcodec_open2(_codecCtx, codec, nullptr)  };
        if (ret < 0) {
            Utils::Err("avcodec_open2 fail", ret);
            return false;
        }

        return true;
    }

protected:
    CodecBaseFF() : _codecCtx{ nullptr } {
    }

    virtual ~CodecBaseFF() {
        avcodec_free_context(&_codecCtx);
    }
};


template <typename IFrameT, typename FFFrameT, typename ICodecParamT, typename FFCodecParamT>
class EncoderFF final : public CodecBaseFF, public IEncoder<IFrameT, ICodecParamT> {
    FFCodecParamT __codecParam;
    PacketFF __packet;

private:
    const AVCodec* __findCodec(AVCodecID codecId) const override {
        return avcodec_find_encoder(codecId);
    }

    bool __parserInit(AVCodecID codecId) override {
        // Encoder doesn't need parser
        return true;
    }

public:
    EncoderFF() = default;
    ~EncoderFF() = default;

public:
    bool open(const ICodecParamT& param) override {
        __codecParam.copyFrom(param);
        return _open(__codecParam);
    }

    bool put(const IFrameT* frame) override {
        auto frameff{ dynamic_cast<const FFFrameT*>(frame) };
        if (frameff)
            frameff->sendTo(_codecCtx);

        return false;
    }

    const IPacket* get() const override {
        if (__packet.receiveFrom(_codecCtx))
            return &__packet;
        
        return nullptr;
    }

    const ICodecParamT& getCodecParam() const override {
        return __codecParam;
    }

    void close() override {
    }
};


template <typename IFrameT, typename FFFrameT, typename ICodecParamT, typename FFCodecParamT>
class DecoderFF final : public CodecBaseFF, public IDecoder<IFrameT, ICodecParamT> {
    AVCodecParserContext* __parser;
    FFCodecParamT __codecParam;
    FFFrameT __frame;

private:
    const AVCodec* __findCodec(AVCodecID codecId) const override {
        return avcodec_find_decoder(codecId);
    }

    bool __parserInit(AVCodecID codecId) override {
        __parser = av_parser_init(codecId);
        if (!__parser) {
            Utils::Err("av_parser_init fail");
            return false;
        }

        return true;
    }

public: 
    DecoderFF() : __parser{ nullptr } {
    }

    ~DecoderFF() {
        av_parser_close(__parser);
        __parser = nullptr;
    }

public:
    bool open(const ICodecParamT& param) override {
        __codecParam.copyFrom(param);
        return _open(__codecParam);
    }

    bool put(const IPacket* packet) override {
        // TODO: Does not rely on FFmpeg's deep copy
        auto packetff{ dynamic_cast<const PacketFF*>(packet) };
        if (packetff)
            return packetff->sendTo(_codecCtx);

        return false;
    }

    const IFrameT* get() const override {
        if (__frame.receiveFrom(_codecCtx))
            return &__frame;

        return nullptr;
    }

    void close() override {
    }
};

using AudioEncoderFF = EncoderFF<IAudioFrame, AudioFrameFF, IAudioCodecParam, AudioCodecParamFF>;
using AudioDecoderFF = DecoderFF<IAudioFrame, AudioFrameFF, IAudioCodecParam, AudioCodecParamFF>;
using VideoEncoderFF = EncoderFF<IVideoFrame, VideoFrameFF, IVideoCodecParam, VideoCodecParamFF>;
using VideoDecoderFF = DecoderFF<IVideoFrame, VideoFrameFF, IVideoCodecParam, VideoCodecParamFF>;


std::shared_ptr<IAudioEncoder> makeAudioEncoderFF() {
    return std::make_shared<AudioEncoderFF>();
}

std::shared_ptr<IAudioDecoder> makeAudioDecoderFF() {
    return std::make_shared<AudioDecoderFF>();
}

std::shared_ptr<IVideoEncoder> makeVideoEncoderFF() {
    return std::make_shared<VideoEncoderFF>();
}

std::shared_ptr<IVideoDecoder> makeVideoDecoderFF() {
    return std::make_shared<VideoDecoderFF>();
}

} // namespace LAM