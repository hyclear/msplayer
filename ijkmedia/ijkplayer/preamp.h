#ifndef _PREAMP_H_
#define _PREAMP_H_

//#include "audio_utils.h"

class CPreamp 
{
public:
	CPreamp();
	~CPreamp();

	bool Process(int16_t* pPcm, uint32_t sampleCount, uint32_t channels);
	void SetGain(float gain);
	float GetGain();
	void SetScale(float scale);
	float GetScale();
	bool IsNeedProcess();
	bool GetEnable();
	void SetEnable(bool enable);

private:
	float m_gain;
	float m_scale;
	bool m_enable;
	bool m_needProcess;
};


#endif