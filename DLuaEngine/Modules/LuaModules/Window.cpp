#include "Window.h"

namespace DLuaEngine
{
	Window* window;

	static int Lua_DrawLine(lua_State* L)
	{
		window->DrawLine(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
		return 0;
	}

	static int Lua_DrawRect(lua_State* L)
	{
		window->DrawRect(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
		return 0;
	}

	static int Lua_DrawPixel(lua_State* L)
	{
		window->DrawPixel(lua_tonumber(L, 1), lua_tonumber(L, 2));
		return 0;
	}

	static int Lua_SetDrawColor(lua_State* L)
	{
		window->SetDrawColor(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
		return 0;
	}

	static int Lua_SetSize(lua_State* L)
	{
		window->SetSize(lua_tonumber(L, 1), lua_tonumber(L, 2));
		return 0;
	}

	static int Lua_SetTitle(lua_State* L)
	{
		window->SetTitle(lua_tostring(L, 1));
		return 0;
	}

	static int Lua_SetBackgroundColor(lua_State* L)
	{
		window->BackgroundR = lua_tonumber(L, 1);
		window->BackgroundG = lua_tonumber(L, 2);
		window->BackgroundB = lua_tonumber(L, 3);

		return 0;
	}

	static int Lua_GetMousePos(lua_State* L)
	{
		int x, y;
		window->GetMousePos(x, y);

		lua_pushnumber(L, x);
		lua_pushnumber(L, y);

		return 2;
	}

	static int Lua_GetSize(lua_State* L)
	{
		int w, h;
		window->GetSize(w, h);

		lua_pushnumber(L, w);
		lua_pushnumber(L, h);
		
		return 2;
	}

	static int Lua_CurTime(lua_State* Ls)
	{
		lua_pushnumber(Ls, window->CurTime());

		return 1;
	}

	void Lua_InitWindowLibs(lua_State* Ls, Window* win)
	{
		window = win;

		lua_newtable(Ls); // window
			lua_pushcfunction(Ls, Lua_DrawLine);
			lua_setfield(Ls, -2, "DrawLine");

			lua_pushcfunction(Ls, Lua_DrawRect);
			lua_setfield(Ls, -2, "DrawRect");

			lua_pushcfunction(Ls, Lua_DrawPixel);
			lua_setfield(Ls, -2, "DrawPixel");

			lua_pushcfunction(Ls, Lua_SetDrawColor);
			lua_setfield(Ls, -2, "SetDrawColor");

			lua_pushcfunction(Ls, Lua_SetBackgroundColor);
			lua_setfield(Ls, -2, "SetBackgroundColor");

			lua_pushcfunction(Ls, Lua_SetSize);
			lua_setfield(Ls, -2, "SetSize");

			lua_pushcfunction(Ls, Lua_SetTitle);
			lua_setfield(Ls, -2, "SetTitle");

			lua_pushcfunction(Ls, Lua_GetMousePos);
			lua_setfield(Ls, -2, "GetMousePos");

			lua_pushcfunction(Ls, Lua_CurTime);
			lua_setfield(Ls, -2, "CurTime");

			lua_pushcfunction(Ls, Lua_GetSize);
			lua_setfield(Ls, -2, "GetSize");
		lua_setglobal(Ls, "window");
	}
}