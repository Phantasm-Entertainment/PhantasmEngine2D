#include "PhEngine/GraphicsDevice.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>

namespace PHENGINE_NAMESPACE
{
    static BOOL ThisIsStupid(HMONITOR monitor, HDC hdc, LPRECT rect, LPARAM lParam)
    {
        std::vector<Monitor>* monitors = reinterpret_cast<std::vector<Monitor>*>(lParam);
        MONITORINFOEX monitorInfo;
        std::memset(&monitorInfo, 0, sizeof(MONITORINFOEX));
        monitorInfo.cbSize = sizeof(MONITORINFOEX);
        GetMonitorInfo(monitor, &monitorInfo);
        
        std::vector<Resolution> resolutions;
        float refreshRate = 0.0f;
        DEVMODE devMode;
        std::memset(&devMode, 0, sizeof(devMode));
        devMode.dmSize = sizeof(devMode);

        for (DWORD i = 0; EnumDisplaySettings(monitorInfo.szDevice, i, &devMode) != 0; ++i)
        {
            float f = static_cast<float>(devMode.dmDisplayFrequency);

            if (f > refreshRate)
            {
                refreshRate = f;
            }

            if (devMode.dmPelsWidth < 800 || devMode.dmPelsHeight < 600)
            {
                continue;
            }

            std::uint16_t w = static_cast<std::uint16_t>(devMode.dmPelsWidth);
            std::uint16_t h = static_cast<std::uint16_t>(devMode.dmPelsHeight);
            bool alreadyIn = false;

            for (const Resolution& r : resolutions)
            {
                if (r.GetWidth() == w || r.GetHeight() == h)
                {
                    alreadyIn = true;
                }
            }

            if (!alreadyIn)
            {
                resolutions.emplace_back(w, h);
            }
        }

        DISPLAY_DEVICE displayDevice;
        std::memset(&displayDevice, 0, sizeof(displayDevice));
        displayDevice.cb = sizeof(displayDevice);
        EnumDisplayDevices(monitorInfo.szDevice, 0, &displayDevice, 0);
        char nameBuffer[32];
        std::memset(&nameBuffer, 0, sizeof(nameBuffer));
        WideCharToMultiByte(CP_UTF8, 0, displayDevice.DeviceString, -1, nameBuffer, 32, NULL, NULL);
        monitors->emplace_back(std::move(std::string(nameBuffer)), monitorInfo.dwFlags & MONITORINFOF_PRIMARY, std::move(resolutions), refreshRate);
        return TRUE;
    }

    GraphicsDevice::GraphicsDevice() : m_VkInstance(VK_NULL_HANDLE), m_VkPhysicalDevice(VK_NULL_HANDLE)
    {
        if (EnumDisplayMonitors(NULL, NULL, ThisIsStupid, reinterpret_cast<LPARAM>(&m_Monitors)) == 0)
        {
            throw Exception("EnumDisplayMonitors didn't work for some reason");
        }

        VkApplicationInfo vkAppInfo;
        std::memset(&vkAppInfo, 0, sizeof(vkAppInfo));
        vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        vkAppInfo.pApplicationName = "Game";
        vkAppInfo.applicationVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
        vkAppInfo.pEngineName = "Phantasm Engine";
        vkAppInfo.engineVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
        vkAppInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo vkCreateInfo;
        std::memset(&vkCreateInfo, 0, sizeof(vkCreateInfo));
        vkCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        vkCreateInfo.pApplicationInfo = &vkAppInfo;
        vkCreateInfo.enabledExtensionCount = 2;
        const char* extensions[] = 
        {
            "VK_KHR_surface", "VK_KHR_win32_surface"
        };
        vkCreateInfo.ppEnabledExtensionNames = extensions;
        vkCreateInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&vkCreateInfo, nullptr, &m_VkInstance) != VK_SUCCESS)
        {
            throw Exception("vkCreateInstance failed");
        }
    }

    GraphicsDevice::~GraphicsDevice()
    {
        if (m_VkInstance != VK_NULL_HANDLE)
        {
            vkDestroyInstance(m_VkInstance, nullptr);
        }
    }
}