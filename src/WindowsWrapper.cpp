#include "Il2CppModFramework/WindowsWrapper.hpp"

#include <string>
#include <stdexcept>

std::span<const uint8_t> GetModuleMemory(HMODULE module)
{
	MODULEINFO module_info{};
	if (!GetModuleInformation(GetCurrentProcess(), module, &module_info, sizeof(module_info)))
		throw std::runtime_error("GetModuleInformation failed. Error: " + std::to_string(GetLastError()));

	return std::span<const uint8_t>((const uint8_t*)module_info.lpBaseOfDll, (size_t)module_info.SizeOfImage);
}
