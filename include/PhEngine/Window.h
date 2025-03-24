#ifndef PHENGINE_WINDOW_H_
#define PHENGINE_WINDOW_H_

#include <SDL3/SDL.h>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Exception.h"
#include "PhEngine/GraphicsDevice.h"
#include "PhEngine/GameUpdate.h"
#include "PhEngine/Resolution.h"

namespace PHENGINE_NAMESPACE
{
    //class PHENGINE_EXPORT ImplWindowData;
    
    class PHENGINE_EXPORT Window
    {
        friend class Game;
    private:
        GraphicsDevice* m_GraphicsDevice;
        std::shared_ptr<GameUpdate> m_GameUpdate;
        SDL_Window* m_WinHandle;
        SDL_GLContext m_Context;
        bool m_Closed;

        Resolution m_Resolution;
        bool m_Fullscreen;

        bool Update();
        void SwapBuffers();
        inline bool IsClosed() const noexcept { return m_Closed; }
    public:
        Window(GraphicsDevice*, std::shared_ptr<GameUpdate>);
        ~Window();

        inline GraphicsDevice* const GetGraphicsDevice() const noexcept { return m_GraphicsDevice; }

        void Center() const noexcept;
        void SetSize(std::uint16_t, std::uint16_t) noexcept;
        inline const Resolution& GetSize() const noexcept { return m_Resolution; }
        void Clear(float, float, float, float) const noexcept;
        inline void Clear() const noexcept { Clear(0.0f, 0.0f, 0.0f, 1.0f); }
    };
}

#endif