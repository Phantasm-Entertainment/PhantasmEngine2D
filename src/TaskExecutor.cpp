#include "PhEngine/TaskExecutor.h"

namespace PHENGINE_NAMESPACE
{
    TaskExecutor::TaskExecutor() : m_DoWork(true)
    {
        unsigned int n = std::thread::hardware_concurrency();

        if (n < 2)
        {
            n = 2;
        }

        for (unsigned int i = 0; i < n; ++i)
        {
            m_Threads.emplace_back(&TaskExecutor::DoWork, this);
        }
    }

    TaskExecutor::~TaskExecutor()
    {
        m_DoWork = false;
        m_TaskCond.notify_all();

        for (std::thread& t : m_Threads)
        {
            t.join();
        }
    }

    void TaskExecutor::DoWork()
    {
        std::function<void()> currentTask;

        while (m_DoWork)
        {
            std::unique_lock taskLock(m_QueueMutex);
            m_TaskCond.wait(taskLock, [this] { return !m_TaskQueue.empty() || !m_DoWork; });

            if (!m_DoWork)
            {
                break;
            }

            currentTask = std::move(m_TaskQueue.front());
            m_TaskQueue.pop();
            taskLock.unlock();
            currentTask();
            taskLock.lock();
        }
    }
}