#pragma once
#include "LuaHeaders.h"
#include "../Window/Window.h"

namespace DLuaEngine
{
	void Lua_InitWindowLibs(lua_State* Ls, Window* win);
}