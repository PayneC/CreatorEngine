#include "CrTime.h"
#include "CrDefine.h"

CrTime::CrTime()
: m_lfCurrentTime(0)
, m_lfStartTime(0)
, m_lfDelateTime(0)
, m_lfBeforeTime(0)
, m_lfFrameInterval(0)
{
	SetFramesPerSecond(60);
}

CrTime::~CrTime()
{

}

bool CrTime::Init()
{
	m_lfBeforeTime = m_lfCurrentTime = m_lfStartTime = glfwGetTime();
	return true;
}

void CrTime::Update()
{
	m_lfCurrentTime = glfwGetTime();
}

float CrTime::GetCurrentTime()
{
	return (float)m_lfCurrentTime;
}

float CrTime::GetDelateTime()
{
	return (float)m_lfDelateTime;
}

bool CrTime::IsMeetInterval()
{
	if (m_lfCurrentTime >= m_lfFrameInterval + m_lfBeforeTime)
	{
		m_lfDelateTime = m_lfCurrentTime - m_lfBeforeTime;
		m_lfBeforeTime = m_lfCurrentTime;
		return true;
	}
	return false;
}

void CrTime::SetFrameInterval(double frameInterval)
{
	if (frameInterval <= 0L)
	{
#ifdef _DEBUG
		printf("error: frame interval can not be <= 0");
#endif
		return;
	}
	m_lfFrameInterval = frameInterval;
	m_uFramesPerSecond = (unsigned int)(1L / m_lfFrameInterval);
}

void CrTime::SetFramesPerSecond(unsigned int FPS)
{
	if (FPS <= 1L)
	{
#ifdef _DEBUG
		printf("error: frame interval can not be <= 0");
#endif
		return;
	}

	m_uFramesPerSecond = FPS;
	m_lfFrameInterval = 1L / (double)m_uFramesPerSecond;
}