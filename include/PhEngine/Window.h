#ifndef PHENGINE_WINDOW_H_
#define PHENGINE_WINDOW_H_

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Exception.h"
#include "PhEngine/GraphicsDevice.h"
#include "PhEngine/Resolution.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT ImplWindowData;

    class PHENGINE_EXPORT Window
    {
        friend class Game;
        friend class ImplWindowData;
    private:
        GraphicsDevice* m_GraphicsDevice;
        ImplWindowData* m_ImplWindowData;
        bool m_Closed;

        Resolution m_Resolution;
        bool m_Fullscreen;

        bool Update();
        void SwapBuffers();
        inline bool IsClosed() const noexcept { return m_Closed; }
    public:
        Window(GraphicsDevice*);
        ~Window();

        inline GraphicsDevice* const GetGraphicsDevice() const noexcept { return m_GraphicsDevice; }

        void Center() const noexcept;
        void Clear(float, float, float, float) const noexcept;
        inline void Clear() const noexcept { Clear(0.0f, 0.0f, 0.0f, 1.0f); }
    };
}

#endif