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
        void UpdateBackgroundMask();
        cv::Mat m_matBackground;
        cv::Mat m_matBackgroundMask;
        cv::Mat m_matCurFrame;
        std::vector<cv::Rect> m_vecRectObjRegion;
        std::vector<cv::Rect> m_vecRectObjRegionPrev;

};
}
