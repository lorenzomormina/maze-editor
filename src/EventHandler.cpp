#include "EventHandler.h"

#include <SDL2/SDL.h>

#include "Application.h"
#include "Vector2.h"

EventHandler::EventHandler(Application& app) :
    app(app),
    mouseDown(Point(-1, -1)),
    windowSize(RectSize(app.GetScreen().GetWindow().GetSize())) {}

void EventHandler::Handle()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        switch (app.GetState()) {
        case AppState::EDITOR:
			OnEditorEvents(event);
            break;
        case AppState::PLAYING:
            OnPlayingEvents(&event);
            break;
        }    
    }
}

// ---

void EventHandler::OnPlayingEvents(SDL_Event* event)
{
	switch (event->type) {
    case SDL_WINDOWEVENT:
        switch (event->window.event) {

        case SDL_WINDOWEVENT_CLOSE:
            OnWindowClose_Playing();
            break;
        case SDL_WINDOWEVENT_RESIZED:
            OnWindowResize_Playing();
            break;
        case SDL_WINDOWEVENT_LEAVE:
            OnWindowLeave_Playing();
            break;
        default:
            break;
        }
    case SDL_MOUSEBUTTONDOWN:
        OnMouseButtonDown_Playing(event->button.button);
        break;
	}
}

void EventHandler::OnMouseButtonDown_Playing(const Uint8 button)
{
	switch (button) {
	case SDL_BUTTON_LEFT:
		OnLeftMouseButtonDown_Playing(button);
		break;
	default:
		break;
	}
}

void EventHandler::OnLeftMouseButtonDown_Playing(const Uint8 button)
{
    SDL_GetMouseState(&mouseDown.x, &mouseDown.y);
    if (app.GetPToolbar().GetRect().Contains(mouseDown)) {
		if (app.GetPToolbar().backBtn.IsPointInside(mouseDown)) {
			app.SetState(AppState::EDITOR);
			return;
		}
        if (app.GetPToolbar().resetBtn.IsPointInside(mouseDown)) {
            // TODO
        }
    }
}

void EventHandler::OnWindowClose_Playing() const
{
	app.Stop();
}

void EventHandler::OnWindowResize_Playing()
{
	
}

void EventHandler::OnWindowLeave_Playing() const
{
}


// ---

void EventHandler::OnEditorEvents(SDL_Event event)
{
    switch (event.type) {

    case SDL_WINDOWEVENT:
        switch (event.window.event) {

        case SDL_WINDOWEVENT_CLOSE:
            OnWindowClose();
            break;
        case SDL_WINDOWEVENT_RESIZED:
            OnWindowResize();
            break;
        case SDL_WINDOWEVENT_LEAVE:
            OnWindowLeave();
            break;
        default:
            break;

        }

    case SDL_MOUSEBUTTONDOWN:
        OnMouseButtonDown(event.button.button);
        break;

    case SDL_MOUSEBUTTONUP:
        OnMouseButtonUp(event.button.button);
        break;

    case SDL_MOUSEWHEEL:
        OnMouseWheel(event.wheel.y);
        break;

    case SDL_MOUSEMOTION:
        OnMouseMotion();
        break;

    default:
        break;

    }

}



void EventHandler::OnWindowClose() const
{
    app.Stop();
}


void EventHandler::OnApplicationStart() const
{
    const auto& window = app.GetScreen().GetWindow();
    window.SetTitle("Maze Editor");
    window.Show();
}


void EventHandler::OnWindowResize()
{
    app.GetScreen().GetWindow().UpdateSize();
    const auto newSize = app.GetScreen().GetWindow().GetSize();
    app.GetGrid().AddOffset(Point((newSize.w - windowSize.w) / 2, (newSize.h - windowSize.h) / 2));
    windowSize = newSize;

    app.GetToolbar().SetSize(RectSize(windowSize.w, 32));

}

void EventHandler::OnMouseWheel(Sint32 y) const
{
    int mx, my;
    SDL_GetMouseState(&mx, &my);

    if (app.GetToolbar().GetRect().Contains(Point(mx, my))) return;
    if (app.confPrompt.active) return;
    if (app.filePrompt.active) return;

    if (y > 0) // scroll up
    {
        if (app.GetGrid().GetZoomSpriteSize() < 64) {

            app.GetGrid().AddOffset(
                Vector2(
                    -(mx - app.GetGrid().GetOffset().x) * 4 / app.GetGrid().GetZoomSpriteSize(),
                    -(my - app.GetGrid().GetOffset().y) * 4 / app.GetGrid().GetZoomSpriteSize()
                )
            );

            app.GetGrid().AddZoomSpriteSize(4);
        }
    }
    else // scroll down
    {
        if (app.GetGrid().GetZoomSpriteSize() > 4) {

            app.GetGrid().AddOffset(
                Vector2(
                    (mx - app.GetGrid().GetOffset().x) * 4 / app.GetGrid().GetZoomSpriteSize(),
                    (my - app.GetGrid().GetOffset().y) * 4 / app.GetGrid().GetZoomSpriteSize()
                )
            );

            app.GetGrid().AddZoomSpriteSize(-4);
        }
    }
}

void EventHandler::OnMouseMotion() const
{
    int mouseX, mouseY;
    const auto mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (app.confType == ConfirmationType::None && app.filePrompt.type == FilePromptType::None) {
        if (mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
            int newX, newY;
            SDL_GetMouseState(&newX, &newY);
            if (app.GetGrid().GetMouseDrag().x != MOUSE_DRAG_UNINITIALIZED) {
                app.GetGrid().AddOffset(
                    Vector2(newX - app.GetGrid().GetMouseDrag().x, newY - app.GetGrid().GetMouseDrag().y)
                );
                app.GetGrid().SetMouseDrag(Point(newX, newY));
            }
        }
        else if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {

            if (!app.confPrompt.active && !app.filePrompt.active) {
                auto obj = app.GetSelectedObject();
                obj.position = app.GetGrid().GetTileCoordinates(Point(mouseX, mouseY));

                //insert mazeObject into the vector
                app.GetMaze().PutIfEmpty(obj);
            }
        }
        else if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {

        }
    }

    if (!app.GetToolbar().GetRect().Contains(Point(mouseX, mouseY)))
    {
        app.GetSelectedObject().position = app.GetGrid().GetTileCoordinates(Point(mouseX, mouseY));
    }
    else
    {
        app.GetSelectedObject().position.x = MOUSE_DRAG_UNINITIALIZED;
    }

}


void EventHandler::OnMouseButtonDown(const Uint8 button)
{
    switch (button) {
    case SDL_BUTTON_MIDDLE:
        OnMiddleMouseButtonDown();
        break;
    case SDL_BUTTON_LEFT:
        OnLeftMouseButtonDown();
        break;
    default:
        break;
    }
}

void EventHandler::OnMiddleMouseButtonDown() const
{
    // if mouse outside toolbar && confirmation prompt is not active

    int mdx, mdy;
    SDL_GetMouseState(&mdx, &mdy);
    if (!app.GetToolbar().GetRect().Contains(Point(mdx, mdy)) && !app.confPrompt.active && !app.filePrompt.active)
    {
        app.GetGrid().SetMouseDrag(Vector2(mdx, mdy));
    }
}


void EventHandler::OnMouseButtonUp(Uint8 button) const
{
    switch (button) {
    case SDL_BUTTON_MIDDLE:
        OnMiddleMouseButtonUp();
        break;
    case SDL_BUTTON_LEFT:
        OnLeftMouseButtonUp();
        break;
    default:
        break;
    }
}

void EventHandler::OnMiddleMouseButtonUp() const
{
    app.GetGrid().SetMouseDrag(Vector2(MOUSE_DRAG_UNINITIALIZED, MOUSE_DRAG_UNINITIALIZED));
}

void EventHandler::OnLeftMouseButtonDown()
{
    SDL_GetMouseState(&mouseDown.x, &mouseDown.y);

    if (app.confPrompt.active)
    {
        if (app.confPrompt.yesBtn.IsPointInside(mouseDown))
        {
            switch (app.confType)
            {
            case ConfirmationType::Clear:
                app.GetMaze().Clear();
                break;
            default:
                break;
            }
            app.confPrompt.active = false;
            app.confType = ConfirmationType::JustExit;
        }
        else if (app.confPrompt.noBtn.IsPointInside(mouseDown))
        {
            app.confPrompt.active = false;
            app.confType = ConfirmationType::JustExit;
        }
    }

    else if (app.filePrompt.active)
    {
        if (app.filePrompt.yesBtn.IsPointInside(mouseDown))
        {
            switch (app.filePrompt.type)
            {
            case FilePromptType::Save:
                app.fileName = "maze.txt";
                app.GetToolbar().fileNameChanged(app.GetScreen());
                app.GetMaze().Save(app.fileName);
                break;
            case FilePromptType::Load:
                app.fileName = "maze.txt";
                app.GetToolbar().fileNameChanged(app.GetScreen());
                app.GetMaze().Load("maze.txt", app.GetTiles());
                break;
            default:
                break;
            }
            app.filePrompt.active = false;
            app.filePrompt.type = FilePromptType::JustPressed;
        }
        else if (app.filePrompt.noBtn.IsPointInside(mouseDown))
        {
            app.filePrompt.active = false;
            app.filePrompt.type = FilePromptType::JustPressed;
        }
    }

    else {
        const auto r = app.GetToolbar().GetRect();
        if (r.Contains(mouseDown))
        {
            for (const auto& b : app.GetToolbar().GetTileButtons())
            {
                if (b.IsPointInside(mouseDown))
                {
                    app.GetSelectedObject().SwitchTo(b.GetName(), app.GetTiles());
                    return;
                }
            }

            if (app.GetToolbar().clearBtn.IsPointInside(mouseDown))
            {
                app.confPrompt.active = true;
                app.confType = ConfirmationType::Clear;
                return;
            }

            if (app.GetToolbar().centerBtn.IsPointInside(mouseDown))
            {
                app.GetGrid().Center(windowSize);
                return;
            }

            if (app.GetToolbar().saveBtn.IsPointInside(mouseDown))
            {
                app.filePrompt.active = true;
                app.filePrompt.type = FilePromptType::Save;
                return;
            }

            if (app.GetToolbar().loadBtn.IsPointInside(mouseDown))
            {
                app.filePrompt.active = true;
                app.filePrompt.type = FilePromptType::Load;
                return;
            }

			if (app.GetToolbar().playBtn.IsPointInside(mouseDown))
			{
				app.SetState(AppState::PLAYING);
				return;
			}
        }
        else
        {
            auto obj = app.GetSelectedObject();
            obj.position = app.GetGrid().GetTileCoordinates(mouseDown);

            //insert mazeObject into the vector
            app.GetMaze().Put(obj);
        }
    }
}


void EventHandler::OnLeftMouseButtonUp() const
{
    if (app.confType == ConfirmationType::JustExit) {
        app.confType = ConfirmationType::None;
    }
    if(app.filePrompt.type == FilePromptType::JustPressed) {
        app.filePrompt.type = FilePromptType::None;
    }
}

void EventHandler::OnWindowLeave() const
{
    app.GetSelectedObject().position.x = MOUSE_DRAG_UNINITIALIZED;
}
