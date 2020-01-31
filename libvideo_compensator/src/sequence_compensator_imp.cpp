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
}

bool CSequenceCompensator::IsBackgroundRecover()
{
    return false;
}

cv::Mat CSequenceCompensator::GetBackgroundImage()
{
    return m_matBackground;
}

void CSequenceCompensator::InitBackground()
{
    m_matBackground = m_matCurFrame;
    m_matBackgroundLabel = cv::Mat::ones(m_matBackground.size(), CV_8UC1) * 255;

    for (auto& rectObj : m_vecRectObjRegion)
    {
        m_matBackgroundLabel(rectObj).setTo(0);

    }
}
}
