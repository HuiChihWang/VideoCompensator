#include "sequence_compensator_imp.h"

namespace Ivs
{
PtrSequenceCompensator CreateSequenceCompensator()
{
    return std::make_unique<CSequenceCompensator>();
}

void CSequenceCompensator::SetInputMeta(const TInputImageMeta& tInput)
{
    m_matCurFrame = tInput.matImage;
    m_vecRectObjRegion = tInput.vecObjRegions;

    if (m_matBackground.empty())
    {
        InitBackground();
    }
}

void CSequenceCompensator::Process()
{
    for (auto& rect : m_vecRectObjRegionPrev)
    {
        m_matBackground(rect) = m_matCurFrame(rect);
    }

    UpdateBackgroundMask();
}

bool CSequenceCompensator::IsBackgroundRecover()
{
    return cv::countNonZero(m_matBackgroundMask) == 0;
}

cv::Mat CSequenceCompensator::GetBackgroundImage()
{
    return m_matBackground;
}

void CSequenceCompensator::InitBackground()
{
    m_matBackground = m_matCurFrame;
    m_matBackgroundMask = cv::Mat::zeros(m_matBackground.size(), CV_8UC1);

    for (auto& rectObj : m_vecRectObjRegion)
    {
        m_matBackgroundMask(rectObj).setTo(1);
    }
}

void CSequenceCompensator::UpdateBackgroundMask()
{
    cv::Mat matMaskCur = cv::Mat::zeros(m_matBackgroundMask.size(), CV_8UC1);
    for (auto& rect : m_vecRectObjRegion)
    {
        matMaskCur(rect).setTo(1);
    }

    cv::bitwise_and(m_matBackgroundMask, matMaskCur, m_matBackgroundMask);
    m_vecRectObjRegionPrev = m_vecRectObjRegion;
}

}
