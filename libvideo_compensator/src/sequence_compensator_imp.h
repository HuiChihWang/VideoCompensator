#pragma once
#include "../include/seq_compensator.h"

namespace Ivs
{
class CSequenceCompensator: public ISequenceCompensator
{
    public:
        CSequenceCompensator() = default;

        void SetInputMeta(const TInputImageMeta& tInput) override;
        void Process() override;
        bool IsBackgroundRecover() override;
        cv::Mat GetBackgroundImage() override;

    private:
        void InitBackground();

        cv::Mat m_matBackground;
        cv::Mat matBackgroundLabel;
        cv::Mat matCurFrame;
        std::vector<cv::Rect> vecRectObjRegion;

};
}
