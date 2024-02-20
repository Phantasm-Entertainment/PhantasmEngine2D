#ifndef PHENGINE_EXCEPTION_H_
#define PHENGINE_EXCEPTION_H_

#include <string>

#include "PhEngine/Internal/Setup.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT Exception
    {
    private:
        std::string m_Msg;
    public:
        inline Exception(const std::string& m) noexcept : m_Msg(m) { }

        inline const std::string& GetMessage() const noexcept { return m_Msg; }
    };
}

#endif