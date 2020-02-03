#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "test_utility.h"

namespace Ivs
{
SCENARIO("Test Init Sequence Compensator")
{
    std::vector<TInputImageMeta> vecInputMeta;

}

SCENARIO("Test Background Recover Simple")
{
    auto vecInputMeta = ReadImageMeta(strTestFolder);

    auto pSeqCompensator = CreateSequenceCompensator();

    for (auto& tMeta : vecInputMeta)
    {
        if (!pSeqCompensator->IsBackgroundRecover())
        {
            pSeqCompensator->SetInputMeta(tMeta);
            pSeqCompensator->Process();
        }
    }


    CHECK(pSeqCompensator->IsBackgroundRecover());
}
}
