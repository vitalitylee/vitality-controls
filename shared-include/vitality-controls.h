#pragma once

#ifdef VITALITY_CONTROLS_EXPORTS
#define VIC_API __declspec(dllexport)
#else
#define VIC_API __declspec(dllimport)
#endif // VITALITY_CONTROLS_EXPORTS

#include <stdio.h>

VIC_API void vic_prints(const char* str);
