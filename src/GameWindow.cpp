#include <math.h>
#include <cassert>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Exception.h"
#include "GameConfig.h"
#include "GofLApp.h"
#include "GameWindow.h"
#include "GameState.h"

#define assertm(exp, msg) assert(((void)msg, exp))

GameWindow::GameWindow():
    _sdl_window(nullptr),
    _renderer(nullptr)
{
}

GameWindow::~GameWindow()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
    if (_sdl_window) {
        SDL_DestroyWindow(_sdl_window);
    }
}

// TODO: change the param type to const char *
bool GameWindow::init(std::string title)
{
    _title = title;
    _sdl_window = SDL_CreateWindow(title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            GameConfig::maxGameWindowWidth,
            GameConfig::maxGameWindowHeight,
            0);

    if (! _sdl_window) {
        throw SDLException(SDL_GetError());
    }

    _renderer = SDL_CreateRenderer(_sdl_window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (! _renderer) {
        throw SDLException(SDL_GetError());
    }
    return true;
}

void GameWindow::render()
{
    GameState& gameState = GameState::getInstance();

    int status;
    status = SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    if (status != 0)
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s", SDL_GetError());
    
    status = SDL_RenderClear(_renderer);
    if (status != 0)
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s", SDL_GetError());

    drawCellGrid();

    for (int x = 0 ; x < gameState.getCellMaxX(); ++x) {
        for (int y = 0 ; y < gameState.getCellMaxY(); ++y) {
            const Cell &cell = gameState.getCellAt(x, y);
            SDL_Rect r;
            r.x = cell.getX() * GameConfig::cellBoxWidth + 2;
            r.y = cell.getY() * GameConfig::cellBoxHeight + 2;
            r.w = GameConfig::cellBoxWidth - 3;
            r.h = GameConfig::cellBoxHeight - 3;
            
            if (cell.isAlive()) {
                status = SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
                if (status != 0)
                    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s", SDL_GetError());
            } else {
                status = SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
                if (status != 0)
                    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s", SDL_GetError());
            }
            status = SDL_RenderFillRect(_renderer, &r);
            if (status != 0)
                SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s", SDL_GetError());
        }
    }

    SDL_RenderPresent(_renderer);
}

void GameWindow::onMouseButtonDown(SDL_Event e)
{
    switch (e.button.button) {
        case SDL_BUTTON_LEFT:
            {
                int mx, my;
                (void)SDL_GetMouseState(&mx, &my);
                Cell cell = makeCellAtWindowPos(mx, my);

                GameState& gameState = GameState::getInstance();
                Cell &curr = gameState.getCellAt(cell.getX(), cell.getY());

                if (curr.isAlive()) {
                    curr.setDead();
                } else {
                    curr.setAlive();
                }
            }
            break;
        default:
            break;
    }
}

Cell GameWindow::makeCellAtWindowPos(int x, int y)
{
    GameState& gameState = GameState::getInstance();
    SDL_Point mpos = { x, y };

    for (int x = 0; x < gameState.getCellMaxX(); ++x) {
        for (int y = 0; y < gameState.getCellMaxY(); ++y) {
            int left = x * GameConfig::cellBoxHeight;
            int top  = y * GameConfig::cellBoxWidth;
            SDL_Rect rect = { left, top, GameConfig::cellBoxWidth,
                                GameConfig::cellBoxHeight };
            if (SDL_PointInRect(&mpos, &rect)) {
                return Cell{ x, y };
            }
        }
    }
    return Cell();
}

void GameWindow::drawCellGrid()
{
    int status;
    status = SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE );
    if (status != 0)
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s", SDL_GetError());

    // Draw vertical lines
    const int xmax = GameConfig::maxGameWindowWidth - GameConfig::cellBoxWidth;
    const int xdelta = GameConfig::cellBoxWidth;
    for (int x = 0 ; x <= xmax ; x += xdelta) {
        status = SDL_RenderDrawLine(_renderer, x, 0, x, GameConfig::maxGameWindowHeight);
        if (status != 0)
            SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s", SDL_GetError());
    }

    // Draw horizontal lines
    const int ymax = GameConfig::maxGameWindowHeight - GameConfig::cellBoxHeight;
    const int ydelta = GameConfig::cellBoxHeight;
    for (int y = 0 ; y <= ymax; y += ydelta) {
        status = SDL_RenderDrawLine(_renderer, 0, y, GameConfig::maxGameWindowWidth, y);
        if (status != 0)
            SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s", SDL_GetError());
    }
}

/* vim: set ts=4 sw=4 et: */
