#include "PhEngine/GameUpdate.h"

namespace PHENGINE_NAMESPACE
{
    GameUpdate::GameUpdate() : m_TotalTime(0.0)
    {
        m_Now = std::chrono::steady_clock::now();
    }
}