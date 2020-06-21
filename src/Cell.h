#ifndef _INCLUDED_CELL_H
#define _INCLUDED_CELL_H

class Cell {
	public:
		enum class State { DEAD_CELL, ALIVE_CELL };

		Cell(int x = 0, int y = 0, Cell::State state = State::DEAD_CELL);
		int getX() const;
		int getY() const;
		void setAlive();
		void setDead();
		bool isAlive() const;

		void setCountAliveNeighbor(int count);

	private:
		int _x;
		int _y;
		int _aliveNeighbor;
		State _state;

};

#endif // _INCLUDED_CELL_H
