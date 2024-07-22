#pragma once

#include "../../include/packet.hxx"
#include "utils.hxx"
#include <cerrno>
#include <libavutil/error.h>

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
}


namespace LAM {

class PacketFF final : public IPacket {
    mutable MediaType __type;
    mutable AVRational __srcTimeBase;
    AVPacket* __packet;

private:
    void __reset() const {
        av_packet_unref(__packet);
    }

public:
    PacketFF() : __type{ MediaType::MT_NONE }, __packet{ nullptr } {
        __packet = av_packet_alloc();
        if (!__packet) {
            Utils::Err("av_packet_alloc fail");
        }
    }

    ~PacketFF() {
        av_packet_free(&__packet);
    }

// Interaction part with AVCodecContext
public:
    bool sendTo(AVCodecContext* codecCtx) const {
        auto ret{ avcodec_send_packet(codecCtx, __packet) };
        if (ret < 0) {
            Utils::Err("avcodec_send_packet fail", ret);
            return false;
        }

        return true;
    }

    bool receiveFrom(AVCodecContext* codecCtx) const {
        __reset();

        auto ret{ avcodec_receive_packet(codecCtx, __packet) };
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            return false;
        }
        else if (ret < 0) {
            Utils::Err("avcodec_receive_packet fail", ret);
            return false;
        }

        __srcTimeBase = codecCtx->time_base;
        __type = Utils::as(codecCtx->codec_type);
        return true;
    }

// Interaction part with AVFormatContext
public:
    bool writeTo(AVFormatContext* fmtCtx) const {
        AVStream* st{ nullptr };
        for (int i{ 0 }; i < fmtCtx->nb_streams; ++i) {
            st = fmtCtx->streams[i];
            if (st->codecpar->codec_type == Utils::as(__type))
                break;
        }

        if (!st) {
            Utils::Err("[writeTo] No corresponding stream found");
            return false;
        }

        av_packet_rescale_ts(__packet, __srcTimeBase, st->time_base);
        __packet->stream_index = st->index;

        auto ret{ av_interleaved_write_frame(fmtCtx, __packet) };
        if (ret < 0) {
            Utils::Err("av_interleaved_write_frame fail", ret);
            return false;
        }

        return true;
    }

    bool readFrom(AVFormatContext* fmtCtx) const {
        __reset();

        auto ret{ av_read_frame(fmtCtx, __packet) };
        if (ret < 0) {
            Utils::Err("av_read_frame fail", ret);
            return false;
        }

        auto st{ fmtCtx->streams[__packet->stream_index] };
        assert(st);
        __srcTimeBase = st->time_base;
        __type = Utils::as(st->codecpar->codec_type);
        __packet->pos = -1; // TODO: Need further confirmation
        return true;
    }

public:
    MediaType type() const override {
        return __type;
    }

    int64_t pts() const override {
        return __packet->pts;
    }

    int64_t dts() const override {
        return __packet->dts;
    }

    int64_t duration() const override {
        return __packet->duration;
    }

    Rational timeBase() const override {
        return { __packet->time_base.num, __packet->time_base.den };
    }

    std::pair<uint8_t*, int32_t> data() const override {
        return { __packet->data, __packet->size };
    }
};

} // namespace LAM

