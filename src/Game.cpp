#include "PhEngine/Game.h"

#include <GLFW/glfw3.h>

namespace PHENGINE_NAMESPACE
{
    void Game::Initialise() { }
    void Game::Update(std::shared_ptr<GameUpdate>) { }
    void Game::Draw(std::shared_ptr<GameDraw>) { }
    void Game::OnExit() { }

    Game::Game() : m_Exit(false)
    {
        ModifyRunningGame(this, true);
    }

    Game::~Game()
    {
        ModifyRunningGame(this, false);
    }

    void Game::RunGameFixed(double updateRate)
    {
        if (glfwInit() != GLFW_TRUE)
        {
            throw Exception("glfwInit failed!");
        }

        m_GraphicsDevice = std::make_unique<GraphicsDevice>();
        m_Window = std::make_unique<Window>(m_GraphicsDevice.get());
        m_TaskExecutor = std::make_unique<TaskExecutor>();

        Initialise();

        std::shared_ptr<GameUpdate> gameUpdate = std::make_shared<GameUpdate>();
        std::shared_ptr<GameDraw> gameDraw = std::make_shared<GameDraw>();

        gameUpdate->Tick();

        double currentTime = gameUpdate->GetTimeNow();
        double accumulator = 0.0;

        double newTime, frameTime, deltaTime = 1.0 / updateRate;
        gameUpdate->m_Delta = deltaTime;

        while (!m_Exit)
        {
            newTime = gameUpdate->GetTimeNow();
            frameTime = newTime - currentTime;
            if (frameTime > 0.25) { frameTime = 0.25; }
            currentTime = newTime;
            accumulator += frameTime;
            m_Exit = m_Window->Update();

            while (accumulator >= deltaTime)
            {
                gameUpdate->Tick();
                Update(gameUpdate);
                accumulator -= deltaTime;
            }

            gameDraw->m_Alpha = accumulator / deltaTime;
            Draw(gameDraw);
            m_Window->SwapBuffers();
        }

        OnExit();
        glfwTerminate();
    }

    std::map<std::thread::id, Game*> Game::m_RunningGames;
    std::mutex Game::m_GameMutex;

    void Game::ModifyRunningGame(Game* g, bool add)
    {
        std::scoped_lock lock(m_GameMutex);

        if (add)
        {
            m_RunningGames[std::this_thread::get_id()] = g;
        }
        else
        {
            m_RunningGames.erase(std::this_thread::get_id());
        }
    }
}