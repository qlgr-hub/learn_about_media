#include <iostream>
#include "../../include/factory.hxx"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Please specify the file path\n";
        return 1;
    }

    LAM::initFF();

    auto demuxer{ LAM::makeDemuxerFF() };
    if (!demuxer) {
        std::cout << "makeDemuxerFF fail\n";
        return 1;
    }

    if (!demuxer->open(argv[1])) {
        std::cout << "demuxer open fail\n";
        return 1;
    }

    auto audioDecoder{ LAM::makeAudioDecoderFF() };
    if (!audioDecoder) {
        std::cout << "makeAudioDecoderFF fail\n";
        return 1;
    }

    if (!audioDecoder->open(demuxer->getAudioParam())) {
        std::cout << "open audio decoder fail\n";
        return 1;
    }

    auto videoDecoder{ LAM::makeVideoDecoderFF() };
    if (!videoDecoder) {
        std::cout << "makeVideoDecoderFF fail\n";
        return 1;
    }
    
    if (!videoDecoder->open(demuxer->getVideoParam())) {
        std::cout << "open vedio decoder fail\n";
        return 1;
    }

    while (auto paket{ demuxer->get() }) {
        if (paket->type() == LAM::MediaType::MT_AUDIO) {
            if (audioDecoder->put(paket)) {
                while (auto frame{ audioDecoder->get() }) {
                    std::cout << "AUDIO FRAME: " << frame->pts() << '\n';
                }
            }
            else {
                break;
            }
        }
        else if (paket->type() == LAM::MediaType::MT_VIDEO) {
            if (videoDecoder->put(paket)) {
                while (auto frame{ videoDecoder->get() }) {
                    std::cout << "VIDEO FRAME: " << frame->pts() << '\n';
                }
            }
            else {
                break;
            }
        }
    }

    demuxer->close();
    audioDecoder->close();
    videoDecoder->close();
    return 0;
}