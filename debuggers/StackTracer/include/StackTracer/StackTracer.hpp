#pragma once

#include <vector>
#include <string>

struct _EXCEPTION_POINTERS;

namespace StackTracer
{

std::string GetStackTrace();
std::string GetStackTrace(_EXCEPTION_POINTERS* pointers);

void LogStackTrace();

[[nodiscard("Number of frames logged may be zero")]]
int LogStackTrace(_EXCEPTION_POINTERS* pointers);

} // namespace StackTracer
