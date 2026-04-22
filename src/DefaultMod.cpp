#include "Il2CppModFramework/Mod.hpp"


#pragma comment(linker, "/alternatename:ModBeforeBootstrapInit=DefaultModBeforeBootstrapInit")
extern "C" void DefaultModBeforeBootstrapInit()
{
}

#pragma comment(linker, "/alternatename:ModAfterBootstrapDeinit=DefaultModAfterBootstrapDeinit")
extern "C" void DefaultModAfterBootstrapDeinit()
{
}

#pragma comment(linker, "/alternatename:ModOnLoad=DefaultModOnLoad")
extern "C" void DefaultModOnLoad()
{
}

#pragma comment(linker, "/alternatename:ModOnUnload=DefaultModOnUnload")
extern "C" void DefaultModOnUnload()
{
}

#pragma comment(linker, "/alternatename:ModOnUpdate=DefaultModOnUpdate")
extern "C" void DefaultModOnUpdate()
{
}

#pragma comment(linker, "/alternatename:ModOnPostUpdate=DefaultModOnPostUpdate")
extern "C" void DefaultModOnPostUpdate()
{
}
