#pragma once

#pragma comment(lib, "Vendor/liblua54.a")

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

lua_State* GetState();
void CallDEFunctionArg(lua_State* Ls, const char* FuncName, int arg);