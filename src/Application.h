#pragma once
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
	void SetState(AppState newState) { state = newState; }
	AppState GetState() const { return state; }
};


