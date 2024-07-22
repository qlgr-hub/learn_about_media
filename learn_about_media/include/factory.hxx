#pragma once

#include "api.hxx"
#include "codec.hxx"
#include "format.hxx"
#include <memory>


namespace LAM {

LAM_API void initFF();

LAM_API std::shared_ptr<IMuxer>   makeMuxerFF();
LAM_API std::shared_ptr<IDemuxer> makeDemuxerFF();

LAM_API std::shared_ptr<IAudioEncoder> makeAudioEncoderFF();
LAM_API std::shared_ptr<IVideoEncoder> makeVideoEncoderFF();
LAM_API std::shared_ptr<IAudioDecoder> makeAudioDecoderFF();
LAM_API std::shared_ptr<IVideoDecoder> makeVideoDecoderFF();

} // namespace LAM
