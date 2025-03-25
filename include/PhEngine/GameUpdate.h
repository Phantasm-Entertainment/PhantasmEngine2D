#ifndef PHENGINE_GAMEUPDATE_H_
#define PHENGINE_GAMEUPDATE_H_

#include <chrono>

#include <SDL3/SDL.h>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Math/Vector.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT GameUpdate
    {
        friend class Game;
        friend class Window;
    private:
        std::chrono::time_point<std::chrono::steady_clock> m_Now;
        double m_TotalTime;
        double m_Delta;
        std::uint32_t m_FPS;

        inline void Tick()
        {
            m_TotalTime = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_Now).count()) / 1000.0;
        }
        
        inline double GetTimeNow() { return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_Now).count()) / 1000.0; }

        bool* m_OldKeys;
        bool* m_Keys;
        bool* m_OldMouseButtons;
        bool* m_MouseButtons;
        Math::Vector2f m_MousePos;

        void InputUpdate();
    public:
        GameUpdate();
        ~GameUpdate();

        inline double GetTotalTime() const noexcept { return m_TotalTime; }
        inline double GetDelta() const noexcept { return m_Delta; }
        inline std::uint32_t GetFPS() const noexcept { return m_FPS; }

        bool IsKeyDown(int);
        bool IsKeyPressed(int);
        inline const Math::Vector2f& GetMousePos() const noexcept { return m_MousePos; }
    };
}

#endif