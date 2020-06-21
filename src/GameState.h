#ifndef _INCLUDED_GAMESTATE_H
#define _INCLUDED_GAMESTATE_H

#include <vector>
#include "Cell.h"
#include "GameConfig.h"

class GameState {
	public:
		using CellGrids = Cell[GameConfig::maxCellX][GameConfig::maxCellY];
		enum class State { 
			Invalid, Initial, 
			Running, Paused, 
			Stopped 
		};

		static GameState& getInstance();
		~GameState();

		void init();
		void run();
		void stop();
		void pause();
		void update();
		void clear();
		
		int getCellMaxX() const;
		int getCellMaxY() const;
		Cell& getCellAt(int x, int y);	
		const Cell& getCellAt(int x, int y) const;	

	private:
		GameState();

		State _prevState;
		State _state;
		std::vector<Cell> getCellNeighbor(Cell c);
		void computeNextGeneration();

		CellGrids _cellGrids;
};

#endif  //_INCLUDED_GAMESTATE_H
