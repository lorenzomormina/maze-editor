﻿#pragma once
//#include <vector>
#include <SDL2/SDL_ttf.h>

#include "Screen.h"
#include "Grid.h"
/*#include "Maze.h"
#include "MObject.h"*/
#include "constants.h"
#include "EventHandler.h"
#include "Maze.h"
#include "SDLManager.h"
#include "Toolbar.h"
#include "Font.h"
#include "ConfirmationPrompt.h"
#include "FilePrompt.h"
#include "playing/PToolbar.h"
#include "playing/PlayingMaze.h"


enum class ConfirmationType
{
	None,
	Clear,
	Save,
	Load,
	JustExit
};

enum class AppState {
	EDITOR,
	PLAYING,
};

enum class MoveDir {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct MoveDirT {
	MoveDir dir;
	int ticks;
};

class Application
{
	SDLManager sdlManager;
	Screen screen;
	EventHandler eventHandler;
	Grid grid;
	Toolbar toolbar;
	Maze maze;

	std::vector<MObject> tiles;
	MObject selectedObject;
	bool running = true;
	int fps = FPS;

	AppState state = AppState::EDITOR;

	PToolbar ptoolbar;
	MoveDirT moveQueue[4] = { {MoveDir::NONE, 0},{MoveDir::NONE, 0},{MoveDir::NONE, 0},{MoveDir::NONE, 0} };

	void Draw();
	void Load();

public:
	Application();
	void Run();
	void Stop();

	void SetFPS(int fps);
	Screen& GetScreen();
	Grid& GetGrid();
	Toolbar& GetToolbar();
	PToolbar& GetPToolbar();
	MObject& GetSelectedObject();
	std::vector<MObject>& GetTiles();
	Maze& GetMaze();

	// --
	Font font;
	ConfirmationPrompt confPrompt;
	ConfirmationType confType{ ConfirmationType::None };
	FilePrompt filePrompt;
	std::string fileName;

	// --
	void SetState(AppState newState) {
		state = newState;
		if (state == AppState::PLAYING)
		{
			playingMaze.SetMaze(maze.GetObjects());
		}
		else if (state == AppState::EDITOR)
		{
			playingMaze.Clear();
		}
	}
	AppState GetState() const { return state; }

	// --
	PlayingMaze playingMaze;

	void PushToMoveQueue(MoveDir dir, int ticks);

	void PopFromMoveQueue(MoveDir dir, int ticks);

	MoveDir tapDir = MoveDir::NONE;

	MoveDir GetMoveDir() {
		return moveQueue[0].dir;
	}

	int GetMoveTicks() {
		return moveQueue[0].ticks;
	}

	void ChangeInMoveQueue(MoveDir dir, int ticks) {
		for (int i = 0; i < 3; i++) {
			if (moveQueue[i].dir == dir) {
				moveQueue[i].ticks = ticks;
				return;
			}
		}
	}

	long moveFrames[5] = { 0, 0, 0, 0, 0 };
	MoveDir removeDirLater = MoveDir::NONE;
};


