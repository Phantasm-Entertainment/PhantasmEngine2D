#ifndef PHENGINE_MONITOR_H_
#define PHENGINE_MONITOR_H_

#include <string>
#include <vector>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Resolution.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT Monitor
    {
    private:
        std::string m_Name;
        bool m_Primary;
        std::vector<Resolution> m_Resolutions;
        float m_RefreshRate;
    public:
        inline Monitor(std::string&& n, bool p, std::vector<Resolution>&& res, float r) :
        m_Name(std::move(n)), m_Primary(p), m_Resolutions(std::move(res)), m_RefreshRate(r) { }

        inline const std::string& GetName() const noexcept { return m_Name; }
        inline bool IsPrimary() const noexcept { return m_Primary; }
        inline const std::vector<Resolution>& GetResolutions() const noexcept { return m_Resolutions; }
        inline const Resolution& GetMinResolution() const noexcept { return m_Resolutions[0]; }
        inline const Resolution& GetMaxResolution() const noexcept { return m_Resolutions[m_Resolutions.size() - 1]; }
        inline float GetRefreshRate() const noexcept { return m_RefreshRate; }
    };
}

#endif