#ifndef PHENGINE_GAME_H_
#define PHENGINE_GAME_H_

#include <memory>
#include <thread>
#include <map>
#include <mutex>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/GraphicsDevice.h"
#include "PhEngine/Window.h"
#include "PhEngine/TaskExecutor.h"
#include "PhEngine/ContentManager.h"
#include "PhEngine/GameUpdate.h"
#include "PhEngine/GameDraw.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT Game
    {
    private:
        std::unique_ptr<GraphicsDevice> m_GraphicsDevice;
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<TaskExecutor> m_TaskExecutor;
        std::unique_ptr<ContentManager> m_ContentManager;

        static std::map<std::thread::id, Game*> m_RunningGames;
        static std::mutex m_GameMutex;
        static void ModifyRunningGame(Game*, bool);

        std::thread::id m_ThreadID;
        bool m_Exit;
    public:
        Game();
        virtual ~Game();

        inline GraphicsDevice* const GetGraphicsDevice() const noexcept { return m_GraphicsDevice.get(); }
        inline Window* const GetWindow() const noexcept { return m_Window.get(); }
        inline TaskExecutor* const GetTaskExecutor() const noexcept { return m_TaskExecutor.get(); }
        inline ContentManager* const GetContentManager() const noexcept { return m_ContentManager.get(); }

        void RunGameFixed(double updateRate = 60.0);
    protected:
        virtual void Initialise();
        virtual void Update(std::shared_ptr<GameUpdate>);
        virtual void Draw(std::shared_ptr<GameDraw>);
        virtual void OnExit();

        inline void Exit() noexcept
        {
            m_Exit = true;
        }
    };
}

#endif