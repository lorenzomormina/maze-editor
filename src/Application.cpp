﻿#include "Application.h"

#include <SDL2/SDL_ttf.h>



Application::Application() :
    sdlManager(),
    font{ "resource/font/RobotoMono-Regular.ttf", 16 },
    eventHandler(*this),
    grid(screen),
    toolbar(fileName)
{
    toolbar.load(screen, font.font);
    confPrompt.setRect(screen, font.font);
    filePrompt.setRect(screen, font.font);
    Load();
    eventHandler.OnApplicationStart();
}

void Application::Load()
{
    MObject obj;
    for (std::vector<std::string>::size_type i = 0; i < mObjectName.size(); i++) {
        obj.id = static_cast<MObjectId>(i);
        obj.name = mObjectName[i];
        obj.texture = screen.GetRenderer().LoadTexture("resource/sprite/" + obj.name + ".png");
        tiles.push_back(obj);
    }

    selectedObject.SwitchTo(MObjectId::SELECTED, tiles);
}

void Application::Run()
{
    auto ticks1 = SDL_GetTicks();
    while (running) {

        eventHandler.Handle();

        const SDL_Color color = { 255,255,255,255 };
        const auto& renderer = screen.GetRenderer();
        renderer.SetDrawColor(color);
        renderer.Clear();
        Draw();
        renderer.Present();

        ///ensures fixed fps
        const auto ticks2 = SDL_GetTicks();
        const auto delta = static_cast<int>(ticks2 - ticks1);
        if (1000 / fps - delta > 0)
            SDL_Delay(1000 / fps - static_cast<Uint32>(delta));
        ticks1 = ticks2;
        ///
    }
}



void Application::Draw()
{
    grid.Draw(screen);
    maze.Draw(screen, grid);
    if(!confPrompt.active && !filePrompt.active)
        selectedObject.Draw(screen,grid);
    else {
        confPrompt.Draw(screen);
    }
    if (filePrompt.active) {
        filePrompt.Draw(screen);
    }
    toolbar.Draw(screen);
}

void Application::Stop()
{
    running = false;
}

void Application::SetFPS(const int fps)
{
    this->fps = fps;
}

Screen& Application::GetScreen()
{
    return screen;
}


Grid& Application::GetGrid()
{
    return grid;
}

Toolbar& Application::GetToolbar()
{
    return toolbar;
}

MObject& Application::GetSelectedObject()
{
    return selectedObject;
}

std::vector<MObject>& Application::GetTiles()
{
    return tiles;
}

Maze& Application::GetMaze()
{
    return maze;
}







