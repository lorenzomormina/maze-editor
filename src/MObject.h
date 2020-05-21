#pragma once
#include <string>
#include <vector>


#include "Grid.h"
#include "Screen.h"


enum struct MObjectId {
    START,
    EXIT,
    WALL_ROCK,
    COIN,
    SELECTED,
    ERASER,
    NONE,
    ERROR
};

extern std::vector<std::string> mObjectName;


struct MObject {
    MObjectId id;
    std::string name;
    Texture texture;
    Point position;

    void Draw(Screen& screen, const Grid& grid);
    void SwitchTo(MObjectId id, const std::vector<MObject>& mObjects);
    void SwitchTo(const std::string& name, const std::vector<MObject>& mObjects);
    void update(const std::vector<MObject>& mObjects) {
        texture = mObjects[static_cast<int>(id)].texture;
        // assign name base on id
        name = mObjectName[static_cast<int>(id)];
    }
};

MObject findMObjectByName(const std::vector<MObject>& v, const std::string& name);