#ifndef _INCLUDED_GAMECONFIG_H
#define _INCLUDED_GAMECONFIG_H


class GameConfig {
	public:
		static constexpr int maxGameWindowWidth  = 800;
		static constexpr int maxGameWindowHeight = 600;

		static constexpr int cellBoxWidth  = 20;
		static constexpr int cellBoxHeight = 20;

		static constexpr int maxCellY = maxGameWindowHeight / cellBoxHeight;
		static constexpr int maxCellX = maxGameWindowWidth  / cellBoxWidth;

};

#endif // _INCLUDED_GAMECONFIG_H
