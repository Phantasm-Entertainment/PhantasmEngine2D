#include "PhEngine/Game.h"

namespace PHENGINE_NAMESPACE
{
    void Game::Initialise() { }
    void Game::Update(std::shared_ptr<GameUpdate>) { }
    void Game::Draw(std::shared_ptr<GameDraw>) { }
    void Game::OnExit() { }

    Game::Game() : m_Exit(false)
    {
        m_ThreadID = std::this_thread::get_id();

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        {
            throw Exception("SDL_Init failed");
        }
        
        ModifyRunningGame(this, true);
    }

    Game::~Game()
    {
        ModifyRunningGame(this, false);
        SDL_Quit();
    }

    void Game::RunGameFixed(double updateRate)
    {
        if (std::this_thread::get_id() != m_ThreadID)
        {
            throw Exception("wrong thread");
        }

        m_GraphicsDevice = std::make_unique<GraphicsDevice>();
        std::shared_ptr<GameUpdate> gameUpdate = std::make_shared<GameUpdate>();
        m_Window = std::make_unique<Window>(m_GraphicsDevice.get(), gameUpdate);
        m_TaskExecutor = std::make_unique<TaskExecutor>();

        m_GraphicsDevice->InitGL();
        m_Window->Clear(0.0f, 0.0f, 0.0f, 1.0f);
        Initialise();

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
            
            while (accumulator >= deltaTime)
            {
                gameUpdate->InputUpdate();
                m_Exit = m_Window->Update();
                gameUpdate->Tick();
                Update(gameUpdate);
                accumulator -= deltaTime;
            }

            gameDraw->m_Alpha = accumulator / deltaTime;
            Draw(gameDraw);
            m_Window->SwapBuffers();
        }

        OnExit();
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