#include <algorithm>
#include "SDL2/SDL.h"
#include "GameState.h"

GameState& GameState::getInstance()
{
	static GameState _instance;
	return _instance;
}

GameState::GameState():
	_prevState(State::Invalid),
	_state(State::Stopped)
{
}

GameState::~GameState()
{
}

void GameState::init()
{
	for (int x = 0; x < getCellMaxX(); ++x) {
		for (int y = 0; y < getCellMaxY(); ++y) {
			getCellAt(x, y) = Cell(x, y);
		}
	}

	getCellAt(10, 10).setAlive();
	getCellAt(10, 11).setAlive();
	getCellAt(10, 12).setAlive();
	getCellAt(10, 13).setAlive();
	getCellAt(11, 13).setAlive();
	getCellAt(12, 13).setAlive();
	getCellAt(13, 13).setAlive();

	getCellAt(26, 10).setAlive();
	getCellAt(26, 11).setAlive();
	getCellAt(26, 12).setAlive();
	getCellAt(27, 13).setAlive();
	getCellAt(27, 14).setAlive();
	getCellAt(27, 15).setAlive();

	_state = State::Initial;
}

void GameState::run()
{
	if (_state == State::Paused)
		pause();

	if (_state == State::Stopped || _state == State::Initial)
		_state = State::Running;
}

void GameState::stop()
{
	if (_state == State::Running || _state == State::Paused)
		_state = State::Stopped;
}

void GameState::pause()
{
	if (_state == State::Running) {
		_prevState = _state;
		_state = State::Paused;
	} else {
		if (_state == State::Paused &&
			_prevState == State::Running) {
			_state = State::Running;
			_prevState = State::Invalid;
		}
	}
}

void GameState::update()
{
	// No need to compute next generation
	if (_state != State::Running)
		return;

	bool isAllDead = true;
	for (auto &cellInX: _cellGrids) {
		for (auto &cell: cellInX) {
			if (cell.isAlive()) {
				isAllDead = false;
				break;
			}
		}
	}

	if (isAllDead) {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
				"All cell has died. Stopping the game");
		_state = State::Stopped;
	} else {
		computeNextGeneration();
	}
}

void GameState::clear()
{
	if (_state == State::Stopped || _state == State::Initial) {
		for (auto &cellInX: _cellGrids) {
			for (auto &cell: cellInX)
				cell.setDead();
		}
	}
}

int GameState::getCellMaxX() const
{
	return GameConfig::maxCellX; 
}

int GameState::getCellMaxY() const
{
	return GameConfig::maxCellY; 
}

Cell& GameState::getCellAt(int x, int y)
{
	return _cellGrids[x][y];
}

const Cell& GameState::getCellAt(int x, int y) const
{
	return _cellGrids[x][y];
}

std::vector<Cell> GameState::getCellNeighbor(Cell c)
{
	int x = c.getX();
	int y = c.getY();
	std::vector<Cell> neighbor;

	for (int dx = -1; dx < 2; ++dx) {
		for (int dy = -1; dy < 2; ++dy) {
			int nx = x + dx;
			int ny = y + dy;

			// skip current cell
			if (nx == x && ny == y)
				continue;

			if (nx >= 0 && ny >= 0) {
				if (nx < getCellMaxX() && ny < getCellMaxY()) {
					const Cell cell = getCellAt(nx, ny);
					neighbor.push_back(cell);
				}
			}
		}
	}
	return neighbor;
}

void GameState::computeNextGeneration()
{
	for (int x = 0; x < getCellMaxX(); ++x) {
		for (int y = 0; y < getCellMaxY(); ++y) {
			int aliveCount = 0;
			Cell &current = getCellAt(x, y);

			std::vector<Cell> myNeighbors = getCellNeighbor(current);

			std::for_each(begin(myNeighbors), end(myNeighbors),
				[&aliveCount](const auto& cell) {
					if (auto isAlive = cell.isAlive(); isAlive)
						aliveCount++;
				});

			current.setCountAliveNeighbor(aliveCount);
		}
	}
}