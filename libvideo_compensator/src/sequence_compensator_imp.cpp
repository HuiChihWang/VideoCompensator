#include "sequence_compensator_imp.h"

namespace Ivs
{
PtrSequenceCompensator CreateSequenceCompensator()
{
    return std::make_unique<CSequenceCompensator>();
}

CSequenceCompensator::~CSequenceCompensator()
{
    m_matBackgroundMask.release();
    m_matBackground.release();
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
        m_matCurFrame(rect).copyTo(m_matBackground(rect));
    }

    UpdateBackgroundMask();
}

bool CSequenceCompensator::IsBackgroundRecover()
{
    if (m_matBackgroundMask.empty())
    {
        return false;
    }

    return cv::countNonZero(m_matBackgroundMask) == 0;
}

cv::Mat CSequenceCompensator::GetBackgroundImage()
{
    return m_matBackground;
}

void CSequenceCompensator::InitBackground()
{
    m_matCurFrame.copyTo(m_matBackground);
    m_matBackgroundMask = cv::Mat::zeros(m_matBackground.size(), CV_8UC1);

    for (auto& rectObj : m_vecRectObjRegion)
    {
        m_matBackgroundMask(rectObj).setTo(255);
    }
}

void CSequenceCompensator::UpdateBackgroundMask()
{

    cv::Mat matMaskCur = cv::Mat::zeros(m_matBackgroundMask.size(), CV_8UC1);
    for (auto& rect : m_vecRectObjRegion)
    {
        matMaskCur(rect).setTo(255);
    }

    cv::bitwise_and(m_matBackgroundMask, matMaskCur, m_matBackgroundMask);
    m_vecRectObjRegionPrev = m_vecRectObjRegion;

    matMaskCur.release();
}

}
