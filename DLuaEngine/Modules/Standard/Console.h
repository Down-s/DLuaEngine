#pragma once

#include <stdio.h>

namespace DLuaEngine
{
	class Console
	{
	public:
		static void WriteLine(const char* txt)
		{
			printf("%s\n", txt);
		}
	};
}