#ifndef _INCLUDED_MEMPUZZLEAPP_H
#define _INCLUDED_MEMPUZZLEAPP_H

#include "GameWindow.h"

class GofLApp {
	public:
		GofLApp();
		~GofLApp();

		// Can't be copied. There should only be one app
		GofLApp(const GofLApp& other) = delete;
		GofLApp& operator=(const GofLApp& other) = delete;
		GofLApp(const GofLApp&& other) = delete;
		GofLApp& operator=(const GofLApp&& other) = delete;

		void init(char * const title);
		bool run();

		void onExit();

	protected:
		void initSDL();
		void shutdownSDL();
		
		void handleEvents();
		void update();
		void render();

	private:
		bool _quiting;
		GameWindow _gameWindow;
};


#endif /* _INCLUDED_MEMPUZZLEAPP_H */
/* vim: set ts=4 sw=4 sts=4: */
