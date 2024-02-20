#ifndef PHENGINE_TASKEXECUTOR_H_
#define PHENGINE_TASKEXECUTOR_H_

#include <cstdint>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>
#include <type_traits>
#include <future>
#include <memory>

#include "PhEngine/Internal/Setup.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT TaskExecutor
    {
    private:
        std::vector<std::thread> m_Threads;
        std::mutex m_QueueMutex;
        std::queue<std::function<void()>> m_TaskQueue;
        std::condition_variable m_TaskCond;
        bool m_DoWork;

        void DoWork();
    public:
        TaskExecutor();
        ~TaskExecutor();

        inline std::size_t GetThreadCount() const noexcept { return m_Threads.size(); }

        template <typename F, typename... A, typename R = std::invoke_result_t<std::decay_t<F>, std::decay_t<A>...>>
        std::future<R> SubmitTask(F&& task, A&&... args)
        {
            std::shared_ptr<std::promise<R>> promise = std::make_shared<std::promise<R>>();

            {
                std::scoped_lock queueLock(m_QueueMutex);
                m_TaskQueue.push([taskFunc = std::bind(std::forward<F>(task), std::forward<A>(args)...), promise]
                {
                    try
                    {
                        if constexpr (std::is_void_v<R>)
                        {
                            std::invoke(taskFunc);
                            promise->set_value();
                        }
                        else
                        {
                            promise->set_value(std::invoke(taskFunc));
                        }
                    }
                    catch (...)
                    {
                        try
                        {
                            promise->set_exception(std::current_exception());
                        }
                        catch (...) { }
                    }
                });
                m_TaskCond.notify_one();
                return promise->get_future();
            }
        }
    };

    template<typename R>
    inline bool IsFutureReady(std::future<R> const& f) { return f.valid() && f.wait_for(std::chrono::seconds(0)) == std::future_status::ready; }
}

#endif