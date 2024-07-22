#pragma once

#include "../../include/frame.hxx"
#include "../../include/packet.hxx"
#include <optional>
#include <string_view>

extern "C" {
    #include <libavutil/avutil.h>
    #include <libavutil/pixfmt.h>
    #include <libavutil/samplefmt.h>
    #include <libavcodec/codec_id.h>
}


namespace LAM {

namespace Utils {
    MediaType as(AVMediaType typeff);
    AVMediaType as(MediaType type);

    VideoFrameType as(AVPictureType picType);
    AVPictureType as(VideoFrameType picType);

    AudioSampleFormat as(AVSampleFormat sampleFmt);
    AVSampleFormat as(AudioSampleFormat sampleFmt);

    VideoSampleFormat as(AVPixelFormat sampleFmt);
    AVPixelFormat as(VideoSampleFormat sampleFmt);

    AudioCodecProtocal as(AVCodecID codecId);
    AVCodecID as(AudioCodecProtocal codecId);
    VideoCodecProtocal as(AVCodecID codecId, int);
    AVCodecID as(VideoCodecProtocal codecId);


    void Err(std::string_view msg, std::optional<int> errCode = std::nullopt, const char* file = __FILE__, int line = __LINE__);
};

} // namespace LAM
