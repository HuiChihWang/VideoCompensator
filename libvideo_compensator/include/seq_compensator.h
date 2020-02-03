#pragma once
#include <memory>
#include "opencv2/core.hpp"

namespace Ivs
{
struct TInputImageMeta
{
    cv::Mat matImage;
    std::vector<cv::Rect> vecObjRegions;
};

class ISequenceCompensator
{
    public:
        virtual ~ISequenceCompensator() = default;
        virtual void SetInputMeta(const TInputImageMeta& tInput) = 0;
        virtual void Process() = 0;
        virtual bool IsBackgroundRecover() = 0;
        virtual cv::Mat GetBackgroundImage() = 0;

};

typedef std::unique_ptr<ISequenceCompensator> PtrSequenceCompensator;
PtrSequenceCompensator CreateSequenceCompensator();
}


