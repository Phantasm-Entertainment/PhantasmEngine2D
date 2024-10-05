#ifndef PHENGINE_CONTENTMANAGER_H_
#define PHENGINE_CONTENTMANAGER_H_

#include <cstdint>
#include <string>
#include <map>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Graphics/Texture2D.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT ContentManager
    {
    private:
        std::map<std::string, Graphics::Texture2D> m_Textures;
    };
}

#endif