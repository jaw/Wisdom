#pragma once
#include <format>

#if defined(_WIN32) && WISDOMDX12
#include <wisdom/dx12/dx12_definitions.h>
#elif defined(WISDOMVK)
#include <wisdom/vulkan/vk_definitions.h>
#endif