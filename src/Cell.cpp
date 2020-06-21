#include "Cell.h"

Cell::Cell(int x, int y, Cell::State state):
	_x(x), _y(y), _aliveNeighbor(0), _state(state)
{  }

int Cell::getX() const
{
	return _x;
}

int Cell::getY() const
{
	return _y;
}

void Cell::setAlive()
{
	_state = State::ALIVE_CELL;
}

void Cell::setDead()
{
	_state = State::DEAD_CELL;
}

bool Cell::isAlive() const
{
	return _state == State::ALIVE_CELL;
}

void Cell::setCountAliveNeighbor(int count)
{
	_aliveNeighbor = count;
	if (isAlive()) {
		if (_aliveNeighbor < 2) {
			setDead();
		} else if (_aliveNeighbor > 3) {
			setDead();
		}
	} else { // Dead cell
		if (_aliveNeighbor == 3)
			setAlive();
	}
}
