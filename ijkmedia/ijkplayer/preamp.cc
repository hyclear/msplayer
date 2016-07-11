#include "preamp.h"
#include <math.h>
#include <string>

CPreamp::CPreamp()
{
	m_enable = false;
	m_gain = 0.0;
	m_scale = 1.0;
	m_needProcess = false;
}

CPreamp::~CPreamp()
{

}


bool CPreamp::Process(int16_t* pData, uint32_t sampleCount, uint32_t channels)
{
	if (!IsNeedProcess())
	{ 
		return false;
	}

	if (m_scale < 0.001)
	{
		memset(pData, 0, sampleCount * channels * sizeof(int16_t));
		return true;
	}

	int16_t* pProcData = pData;
	for (uint32_t i = 0; i < sampleCount; i++)
	{
		if (channels == 1)
		{
			*pProcData = Round(*pProcData * m_scale);
			pProcData++;
		}
		else if (channels == 2)
		{
			*pProcData = Round(*pProcData * m_scale);
			pProcData++;
			*pProcData = Round(*pProcData * m_scale);
			pProcData++;
		}
	}

	return true;
}

void CPreamp::SetGain(float gain)
{
	m_gain = EnsureRange<float>(gain, -20.0, 20.0);
	m_scale = (float)pow(10.0, m_gain / 20.0);
	m_needProcess = fabs(m_gain) > 0.001;
}

float CPreamp::GetGain()
{
	return m_gain;
}

void CPreamp::SetScale(float scale)
{
	m_scale = scale;
	if (m_scale > 0.1)
	{
		m_gain = log10(m_scale) * 20;
	}
	else
	{
		m_gain = -20.0; 
	}
	m_needProcess = fabs(m_gain) > 0.001;
}

float CPreamp::GetScale()
{
	return m_scale;
}

bool CPreamp::IsNeedProcess()
{
	return GetEnable() && m_needProcess;
}

bool CPreamp::GetEnable()
{
	return m_enable;
}

void CPreamp::SetEnable(bool enable)
{
	m_enable = enable;
}