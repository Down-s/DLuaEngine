#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "../../DLuaEngine.h"

namespace DLuaEngine
{
	class Window
	{
	public:
		int BackgroundR = 255;
		int BackgroundG = 255;
		int BackgroundB = 255;

		Window(const char* title = "DLuaEngine")
		{
			SDL_Init(SDL_INIT_VIDEO);
			m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
			m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
		}

		void Clear()
		{
			SetDrawColor(BackgroundR, BackgroundG, BackgroundB);
			SDL_RenderClear(m_Renderer);
		}
		
		void Update()
		{
			SDL_RenderPresent(m_Renderer);

			while (SDL_PollEvent(&m_Event) != 0)
			{
				if (m_Event.type == SDL_QUIT)
				{
					Close();
				}

				switch (m_Event.type)
				{
					case SDL_KEYDOWN:
					{
						if (m_Event.key.repeat)
						{
							return;
						}

						CallDEFunctionArg(GetState(), "KeyDown", m_Event.key.keysym.sym);
						break;
					}
					case SDL_KEYUP:
					{
						if (m_Event.key.repeat)
						{
							return;
						}

						CallDEFunctionArg(GetState(), "KeyUp", m_Event.key.keysym.sym);
						break;
					}
					case SDL_MOUSEBUTTONDOWN:
					{
						int mb = m_Event.button.button;
						if (mb == 2)
						{
							mb = 3;
						}
						else if (mb == 3)
						{
							mb = 2;
						}

						CallDEFunctionArg(GetState(), "MouseDown", mb);
						break;
					}
					case SDL_MOUSEBUTTONUP:
					{
						int mb = m_Event.button.button;
						if (mb == 2)
						{
							mb = 3;
						}
						else if (mb == 3)
						{
							mb = 2;
						}

						CallDEFunctionArg(GetState(), "MouseUp", mb);
						break;
					}
					default:
						break;
				}

			}
		}

		int CurTime()
		{
			return SDL_GetTicks();
		}

		bool ShouldClose()
		{
			return m_ShouldClose;
		}

		void Close()
		{
			m_ShouldClose = true;
			SDL_Quit();
		}

		void SetSize(int w, int h)
		{
			SDL_SetWindowSize(m_Window, w, h);
		}

		void SetTitle(const char* title)
		{
			SDL_SetWindowTitle(m_Window, title);
		}

		void GetSize(int& w, int &h)
		{
			SDL_GetWindowSize(m_Window, &w, &h);
		}

		void SetDrawColor(int r, int g, int b, int a = 255)
		{
			SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
		}

		void DrawLine(int x1, int y1, int x2, int y2)
		{
			SDL_RenderDrawLine(m_Renderer, x1, y1, x2, y2);
		}

		void DrawPixel(int x, int y)
		{
			SDL_RenderDrawPoint(m_Renderer, x, y);
		}

		void DrawRect(int x, int y, int w, int h)
		{
			SDL_Rect r;
			r.x = x;
			r.y = y;
			r.w = w;
			r.h = h;

			SDL_RenderFillRect(m_Renderer, &r);
		}

		void GetMousePos(int &x, int &y)
		{
			SDL_GetMouseState(&x, &y);
		}

		SDL_Renderer* GetRenderer()
		{
			return m_Renderer;
		}
	private:
		SDL_Renderer* m_Renderer;
		SDL_Window* m_Window;
		SDL_Event m_Event;
		bool m_ShouldClose;
	};
}