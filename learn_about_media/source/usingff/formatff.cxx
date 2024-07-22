#include "../../include/factory.hxx"
#include "codecparamff.hxx"
#include "packetff.hxx"
#include "utils.hxx"

extern "C" {
    #include <libavformat/avformat.h>
}


namespace LAM {

class FormatBaseFF {
protected:
    AVFormatContext* _fmtCtx;
    AudioCodecParamFF _audioParam;
    VideoCodecParamFF _videoParam;

public:
    FormatBaseFF() : _fmtCtx{ nullptr } {
    }

    virtual ~FormatBaseFF() {
    }
};


class MuxerFF final : public FormatBaseFF, public IMuxer {
private:
    bool _addStream(const CodecParamFF& codecParam) {
        auto st{ avformat_new_stream(_fmtCtx, nullptr) };
        if (!st) {
            Utils::Err("avformat_new_stream fail");
            return false;
        }

        st->id = _fmtCtx->nb_streams - 1;
        return codecParam.toStream(st);
    }

public:
    MuxerFF() : FormatBaseFF{} {
    }

    ~MuxerFF() {
        close();

        avformat_free_context(_fmtCtx);
        _fmtCtx = nullptr;
    }

public:
    void initAudioParam(const IAudioCodecParam& audioParam) override {
        _audioParam.copyFrom(audioParam);
    }

    void initVideoParam(const IVideoCodecParam& videoParam) override {
        _videoParam.copyFrom(videoParam);
    }

    bool open(std::string_view filename) override {
        auto ret{ avformat_alloc_output_context2(&_fmtCtx, nullptr, nullptr, filename.data()) };
        if (ret < 0) {
            Utils::Err("avformat_alloc_output_context2 fail", ret);
            return false;
        }

        if (_audioParam.protocal() != AudioCodecProtocal::ACP_NONE)
            if (!_addStream(_audioParam))
                return false;

        if (_videoParam.protocal() != VideoCodecProtocal::VCP_NONE)
            if (!_addStream(_videoParam))
                return false;

        ret = avformat_write_header(_fmtCtx, nullptr);
        if (ret < 0) {
            Utils::Err("avformat_write_header fail", ret);
            return false;
        }
        
        return true;
    }

    bool put(const IPacket* packet) override {
        // TODO: Does not rely on FFmpeg's deep copy
        auto packetff{ dynamic_cast<const PacketFF*>(packet) };
        if (packetff)
            return packetff->writeTo(_fmtCtx);

        return false;
    }

    void close() override {
        auto ret{ av_write_trailer(_fmtCtx) };
        if (ret < 0)
            Utils::Err("av_write_trailer fail", ret);
    }
};


class DemuxerFF final : public FormatBaseFF, public IDemuxer {
    PacketFF __packet;

public:
    DemuxerFF() = default;

    ~DemuxerFF() {
        close();
    }

public:
    bool open(std::string_view filename) override {
        auto ret{ avformat_open_input(&_fmtCtx, filename.data(), nullptr, nullptr) };
        if (ret < 0) {
            Utils::Err("avformat_open_input fail", ret);
            return false;
        }

        ret = avformat_find_stream_info(_fmtCtx, nullptr);
        if (ret < 0) {
            Utils::Err("avformat_find_stream_info fail", ret);
            return false;
        }

        for (int i{ 0 }; i < _fmtCtx->nb_streams; ++i) {
            auto st{ _fmtCtx->streams[i] };
            if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
                if (!_audioParam.fromStream(st))
                    return false;
            }
            else if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                if (!_videoParam.fromStream(st))
                    return false;
            }
        }

        return true;   
    }

    const IAudioCodecParam& getAudioParam() const override {
        return _audioParam;
    }

    const IVideoCodecParam& getVideoParam() const override {
        return _videoParam;
    }

    const IPacket* get() const override {
        if (__packet.readFrom(_fmtCtx))
            return &__packet;
        
        return nullptr;
    }

    void close() override {
        avformat_close_input(&_fmtCtx);
    }
};


std::shared_ptr<IMuxer> makeMuxerFF() {
    return std::make_shared<MuxerFF>();
}

std::shared_ptr<IDemuxer> makeDemuxerFF() {
    return std::make_shared<DemuxerFF>();
}

} // namespace LAM
