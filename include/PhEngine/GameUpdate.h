#ifndef PHENGINE_GAMEUPDATE_H_
#define PHENGINE_GAMEUPDATE_H_

#include <chrono>

#include "PhEngine/Internal/Setup.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT GameUpdate
    {
        friend class Game;
    private:
        std::chrono::time_point<std::chrono::steady_clock> m_Now;
        double m_TotalTime;
        double m_Delta;

        inline void Tick()
        {
            m_TotalTime = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_Now).count()) / 1000.0;
        }
        
        inline double GetTimeNow() { return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_Now).count()) / 1000.0; }
    public:
        GameUpdate();

        inline double GetTotalTime() const noexcept { return m_TotalTime; }
        inline double GetDelta() const noexcept { return m_Delta; }
    };
}

#endif