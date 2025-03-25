#include "PhEngine/GameUpdate.h"

#define NUM_MOUSE_BUTTONS 3

namespace PHENGINE_NAMESPACE
{
    GameUpdate::GameUpdate() : m_TotalTime(0.0)
    {
        m_Now = std::chrono::steady_clock::now();
        m_OldKeys = new bool[SDL_SCANCODE_COUNT];
        m_Keys = new bool[SDL_SCANCODE_COUNT];
        
        for (unsigned short i = 0; i < SDL_SCANCODE_COUNT; ++i)
        {
            m_OldKeys[i] = false;
            m_Keys[i] = false;
        }

        m_OldMouseButtons = new bool[NUM_MOUSE_BUTTONS];
        m_MouseButtons = new bool[NUM_MOUSE_BUTTONS];

        for (unsigned short i = 0; i < NUM_MOUSE_BUTTONS; ++i)
        {
            m_OldMouseButtons[i] = false;
            m_MouseButtons[i] = false;
        }
    }

    GameUpdate::~GameUpdate()
    {
        delete m_OldKeys;
        delete m_Keys;
        delete m_OldMouseButtons;
        delete m_MouseButtons;
    }

    void GameUpdate::InputUpdate()
    {
        for (unsigned short i = 0; i < SDL_SCANCODE_COUNT; ++i)
        {
            m_OldKeys[i] = m_Keys[i];
        }

        for (unsigned short i = 0; i < NUM_MOUSE_BUTTONS; ++i)
        {
            m_OldMouseButtons[i] = m_MouseButtons[i];
        }
    }

    bool GameUpdate::IsKeyDown(int key)
    {
        if (key < 1 || key > SDL_SCANCODE_COUNT)
        {
            return false;
        }

        return m_Keys[key];
    }

    bool GameUpdate::IsKeyPressed(int key)
    {
        if (key < 1 || key > SDL_SCANCODE_COUNT)
        {
            return false;
        }
        
        return !m_OldKeys[key] && m_Keys[key];
    }
}
