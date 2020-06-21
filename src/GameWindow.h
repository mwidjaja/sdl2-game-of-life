#ifndef _INCLUDED_GAMEWINDOW_H
#define _INCLUDED_GAMEWINDOW_H

#include <string>
#include <SDL2/SDL.h>
#include "Cell.h"

class GameWindow {
	public:
		// static GameWindow& getInstance();
		GameWindow();
		~GameWindow();

		GameWindow(const GameWindow& other) = delete;
		GameWindow& operator=(const GameWindow& other) = delete;
		GameWindow(const GameWindow&& other) = delete;
		GameWindow& operator=(const GameWindow&& other) = delete;

		bool init(std::string title);
		void render();

		void onMouseButtonDown(SDL_Event e);

	private:
		Cell makeCellAtWindowPos(int x, int y);
		void drawCellGrid();

		SDL_Window   *_sdl_window;
		SDL_Renderer *_renderer;

		std::string _title;
};

#endif // _INCLUDED_GAMEWINDOW_h
