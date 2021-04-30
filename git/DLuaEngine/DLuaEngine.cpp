#ifndef DLUAENGINE_H
#define DLUAENGINE_H

#include "Modules/Standard/Console.h"
#include "Modules/Window/Window.h"
#include "Modules/LuaModules/Window.h"

#include "DLuaEngine.h"

using namespace DLuaEngine;

Window* window;
lua_State* Ls;

static void PrintStack(lua_State* L, int blist = 0)
{
	int top = lua_gettop(L);
	printf("Stack (%d):\n", top);
	for (int i = 1; i <= top; i++) {
		if (i == blist) continue;
		lua_getglobal(L, "tostring");
		lua_pushvalue(L, i);
		lua_call(L, 1, 1);
		printf("  %d  =  %s (%s)\n", i, lua_tostring(L, -1), luaL_typename(L, i));
		lua_pop(L, 1);
	}
	printf("\n");
	return;
}

lua_State* GetState()
{
	return Ls;
}

bool CheckLua(lua_State* L, int file, const char* &error)
{
	if (file != LUA_OK)
	{
		if (error != NULL)
			error = lua_tostring(L, -1);

		return false;
	}

	return true;
}

void CallDEFunction(lua_State* Ls, const char* FuncName)
{
	lua_getglobal(Ls, "DE");
	lua_getfield(Ls, -1, FuncName);

	const char* err;
	if (!CheckLua(Ls, lua_pcall(Ls, 0, 0, 0), err))
	{
		PrintStack(Ls);
		Console::WriteLine(err);
	}
}

void CallDEFunctionArg(lua_State* Ls, const char* FuncName, int arg)
{
	lua_getglobal(Ls, "DE");
	lua_getfield(Ls, -1, FuncName);
	lua_pushnumber(Ls, arg);

	const char* err;
	if (!CheckLua(Ls, lua_pcall(Ls, 1, 0, 0), err))
	{
		PrintStack(Ls);
		Console::WriteLine(err);
	}
}

int main(int argc, char* args[])
{
	Console::WriteLine("Starting Up...");


	window = new Window();


	Ls = luaL_newstate();

	lua_newtable(Ls);
	lua_setglobal(Ls, "DE");

	luaL_openlibs(Ls);
	Lua_InitWindowLibs(Ls, window);

	const char* err;
	if (!CheckLua(Ls, luaL_dofile(Ls, "lua/main.lua"), err))
	{
		Console::WriteLine(err);
	}

	CallDEFunction(Ls, "Init");

	Console::WriteLine("Started!");
	while (!window->ShouldClose())
	{
		window->Clear();

		CallDEFunction(Ls, "Render");

		window->Update();
	}

	return 0;
}

#endif // DLUAENGINE_H