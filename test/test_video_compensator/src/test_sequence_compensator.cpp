#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "../../../libvideo_compensator/include/seq_compensator.h"

namespace Ivs
{
SCENARIO("Test Init Sequence Compensator")
{

}

SCENARIO("Test Background Recover Simple")
{
    std::vector<TInputImageMeta> vecInputMeta;

    auto pSeqCompensator = CreateSequenceCompensator();

    for (auto& tMeta : vecInputMeta)
    {
        if (!pSeqCompensator->IsBackgroundRecover())
        {
            pSeqCompensator->SetInputMeta(tMeta);
            pSeqCompensator->Process();
        }
    }

}
}
