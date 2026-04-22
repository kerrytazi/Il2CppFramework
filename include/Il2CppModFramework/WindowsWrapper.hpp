#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <psapi.h>

#include <span>

std::span<const uint8_t> GetModuleMemory(HMODULE module);
