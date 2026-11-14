#pragma once
#include <functional>
#include "utlvector.h"

class CTimerBase {
public:
	CTimerBase(float flInitialInterval) :
		m_flInterval(flInitialInterval) {};

    virtual bool Execute() = 0;

    float m_flInterval;
    float m_flLastExecute = -1;
};

extern CUtlVector<CTimerBase*> g_timers;

class CTimer : public CTimerBase
{
public:
    CTimer(float flInitialInterval, std::function<float()> func) :
		CTimerBase(flInitialInterval), m_func(func)
    {
        g_timers.AddToTail(this);
    };

    inline bool Execute() override
    {
	    m_flInterval = m_func();

        return m_flInterval >= 0;
    }

    inline void RemoveTimer()
    {
        for (int i = 0; i < g_timers.Count(); ++i)
        {
            if (g_timers[i] == this)
            {
                g_timers.Remove(i);
                delete this;
                return;
            }
        }
    }

    std::function<float()> m_func;
};

void RemoveTimers();