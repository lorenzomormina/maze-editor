#include "MObject.h"

#include "constants.h"

std::vector<std::string> mObjectName = {
    "start",
    "exit",
    "wall-rock",
    "coin",
    "selected",
    "eraser"
};

MObject findMObjectByName(const std::vector<MObject>& v, const std::string& name)
{
    for (auto i : v)
    {
        if (i.name == name) return i;
    }

    MObject o = {
        MObjectId::ERROR,
        "error",
        Texture(),
        Point()
    };
    return o;
}

void MObject::Draw(Screen& screen, const Grid& grid)
{
    if (id == MObjectId::NONE) return;

    if (position.x == MOUSE_DRAG_UNINITIALIZED) return;
    
    const RectSize windowSize = screen.GetWindow().GetSize();
    const auto xRight = position.x * grid.GetZoomSpriteSize() > windowSize.w - grid.GetOffset().x;
    const auto xLeft = position.x * grid.GetZoomSpriteSize() + grid.GetOffset().x < -grid.GetZoomSpriteSize();
    const auto yDown = position.y * grid.GetZoomSpriteSize() > windowSize.h - grid.GetOffset().y;
    const auto yUp = position.y * grid.GetZoomSpriteSize() + grid.GetOffset().y < -grid.GetZoomSpriteSize();

    if (xRight || xLeft || yDown || yUp) {
        return;
    }

    const auto dRect = Rect(
        position.x * grid.GetZoomSpriteSize() + grid.GetOffset().x,
        position.y * grid.GetZoomSpriteSize() + grid.GetOffset().y,
        grid.GetZoomSpriteSize(),
        grid.GetZoomSpriteSize()
        );
    screen.GetRenderer().DrawTexture(texture, Rect(), dRect);
}


void MObject::SwitchTo(MObjectId id, const std::vector<MObject>& mObjects)
{
    this->id = id;
    this->name = mObjects[static_cast<int>(id)].name;
    texture = mObjects[static_cast<int>(id)].texture;
}

void  MObject::SwitchTo(const std::string& name, const std::vector<MObject>& mObjects)
{
    for (const auto& i : mObjects)
    {
        if (i.name == name)
        {
            id = i.id;
            texture = i.texture;
        }
    }
}

void MObject::DrawForPlay(Screen& screen, const Vector2& cameraOffset)
{
    /*if (id == MObjectId::NONE) return;

    if (position.x == MOUSE_DRAG_UNINITIALIZED) return;

	Grid grid(screen);
	grid.SetOffset(cameraOffset);

    const RectSize windowSize = screen.GetWindow().GetSize();
    const auto xRight = position.x * grid.GetZoomSpriteSize() > windowSize.w - grid.GetOffset().x;
    const auto xLeft = position.x * grid.GetZoomSpriteSize() + grid.GetOffset().x < -grid.GetZoomSpriteSize();
    const auto yDown = position.y * grid.GetZoomSpriteSize() > windowSize.h - grid.GetOffset().y;
    const auto yUp = position.y * grid.GetZoomSpriteSize() + grid.GetOffset().y < -grid.GetZoomSpriteSize();

    if (xRight || xLeft || yDown || yUp) {
        return;
    }

    const auto dRect = Rect(
        position.x * grid.GetZoomSpriteSize() + grid.GetOffset().x,
        position.y * grid.GetZoomSpriteSize() + grid.GetOffset().y,
        grid.GetZoomSpriteSize(),
        grid.GetZoomSpriteSize()
    );
    screen.GetRenderer().DrawTexture(texture, Rect(), dRect);*/

    auto screenPos = (position - cameraOffset)*32 + (screen.GetWindow().GetSize()/2) - Vector2(16,16);
	const auto dRect = Rect(
		screenPos.x,
		screenPos.y,
		32,
		32
	);
	screen.GetRenderer().DrawTexture(texture, Rect(), dRect);


}
