#ifndef PHENGINE_GAMEDRAW_H_
#define PHENGINE_GAMEDRAW_H_

#include "PhEngine/Internal/Setup.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT GameDraw
    {
        friend class Game;
    private:
        double m_Alpha;
    public:
        inline double GetAlpha() const noexcept { return m_Alpha; }
    };
}

#endif