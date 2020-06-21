#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Exception.h"
#include "GameState.h"
#include "GofLApp.h"
#include "GameWindow.h"

GofLApp::GofLApp():
	_quiting(false)
{
	initSDL();
}

GofLApp::~GofLApp()
{
	shutdownSDL();
}

void GofLApp::init(char * const title)
{
	_gameWindow.init(title);
	GameState::getInstance().init();
}

class FrameRater {
	public:
		FrameRater(int fps = target_FPS) {
			init(fps);
		}
		void start() {
			_startTicks_in_ms = SDL_GetTicks();
		}
		void pauseForNextFrame() {
			Uint32 currentTicks_in_ms = SDL_GetTicks();
			Uint32 elapseTicks_in_ms = currentTicks_in_ms - _startTicks_in_ms;
			if ( elapseTicks_in_ms < _target_frame_time_in_ms ) {
				SDL_Delay(_target_frame_time_in_ms - elapseTicks_in_ms);
			}
		}

		void init(int fps) {
			_target_frame_time_in_ms = 1000 / fps;
		}

	private:
		Uint32 _startTicks_in_ms;
		Uint32 _target_frame_time_in_ms;

		static constexpr int target_FPS = 60;
};

bool GofLApp::run()
{
	FrameRater frameRate;
	while ( ! _quiting )
	{
		frameRate.start();
		{
			// main loop
			handleEvents();
			update();
			render();
		}
		frameRate.pauseForNextFrame();
	}

	return true;
}

void GofLApp::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO < 0)) {
		throw SDLException(SDL_GetError());
	}
}

void GofLApp::shutdownSDL()
{
	SDL_Quit();
}

void GofLApp::handleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_quiting = true;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_q) {
					_quiting = true;
				}
				if (event.key.keysym.sym == SDLK_r) {
					SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Running the game");
					GameState::getInstance().run();
				}
				if (event.key.keysym.sym == SDLK_s) {
					SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Stopping the game");
					GameState::getInstance().stop();
				}
				if (event.key.keysym.sym == SDLK_p) {
					SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "(Un)Pausing the game");
					GameState::getInstance().pause();
				}
				if (event.key.keysym.sym == SDLK_c) {
					GameState::getInstance().clear();
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				_gameWindow.onMouseButtonDown(event);
				break;

			default:
				break;
		}
	}
}

void GofLApp::update()
{
	GameState::getInstance().update();
}

void GofLApp::render()
{
	_gameWindow.render();
}

/* vim: set ts=4 sw=4 sts=4: */
