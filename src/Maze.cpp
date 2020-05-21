#include "Maze.h"

void Maze::Draw(Screen& screen, const Grid& grid)
{
    for (auto& obj : objects) {
        if (obj.id != MObjectId::NONE) {
            obj.Draw(screen, grid);
        }
    }
}


void Maze::Put(const MObject& object)
{

    if (object.id == MObjectId::ERASER)
    {
        objects.remove_if(
            [object](const MObject& obj) {return obj.position.x == object.position.x && obj.position.y == object.position.y; }
        );
    }
    else if (object.id == MObjectId::START || object.id == MObjectId::EXIT)
    {
        objects.remove_if(
            [object](const MObject& obj) {return (obj.position.x == object.position.x && obj.position.y == object.position.y)||object.id==obj.id; }
        );
        objects.push_back(object);
    }
    else if (object.id == MObjectId::SELECTED)
    {
        
    }
    else
    {
        for (auto& obj : objects)
        {
            if (obj.position.x == object.position.x && obj.position.y == object.position.y)
            {
                obj.id = object.id;
                obj.name = object.name;
                obj.texture = object.texture;
                obj.position = object.position;
                return;
            }
        }
        objects.push_back(object);
    }
}

void Maze::PutIfEmpty(const MObject& object)
{

    if (object.id == MObjectId::NONE || object.id == MObjectId::ERASER)
    {
        objects.remove_if(
            [object](const MObject& obj) {return obj.position.x == object.position.x && obj.position.y == object.position.y; }
        );
    }
    else if (object.id == MObjectId::START || object.id == MObjectId::EXIT)
    {
        for (auto& obj : objects)
        {
            if (obj.position.x == object.position.x && obj.position.y == object.position.y)
            {
                return;
            }
        }
        objects.remove_if(
            [object](const MObject& obj) {return (obj.position.x == object.position.x && obj.position.y == object.position.y) || object.id == obj.id; }
        );
        objects.push_back(object);
    }
    else if (object.id == MObjectId::SELECTED)
    {

    }
    else
    {
        for (auto& obj : objects)
        {
            if (obj.position.x == object.position.x && obj.position.y == object.position.y)
            {
                return;
            }
        }

        objects.push_back(object);
    }

}