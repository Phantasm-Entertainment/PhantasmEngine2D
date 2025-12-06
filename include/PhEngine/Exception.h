#ifndef PHENGINE_EXCEPTION_H_
#define PHENGINE_EXCEPTION_H_

#include <string>
#include <source_location>
#include <iostream>

#include "PhEngine/Internal/Setup.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT Exception
    {
    private:
        std::string m_Msg;
        std::source_location m_Loc;
    public:
        inline Exception(const std::string& m, std::source_location loc = std::source_location::current()) noexcept : m_Msg(m), m_Loc(loc) { }

        inline const std::string& GetMessage() const noexcept { return m_Msg; }
        inline const std::source_location& GetLocation() const noexcept { return m_Loc; }
    };
}

std::ostream& operator<<(std::ostream&, const PHENGINE_NAMESPACE::Exception&);

#endif