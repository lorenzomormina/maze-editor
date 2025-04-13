#pragma once

#include <list>
#include <fstream>
#include <sstream>

#include "Grid.h"
#include "MObject.h"


class Maze
{
    std::list<MObject> objects;

public:
    void Draw(Screen& screen, const Grid& grid);
    void Put(const MObject& object);
    void PutIfEmpty(const MObject& object);

    // ---

    void Clear()
    {
        objects.clear();
    }

    void Save(const std::string& filename)
    {
        std::ofstream file(filename);
        for (const auto& object : objects)
        {
            std::string line = std::to_string((int)object.id) + " " + std::to_string(object.position.x) + " " + std::to_string(object.position.y) + "\n";
            file << line;
        }
    };

    void Load(const std::string& filename, std::vector<MObject>& tiles)
    {
        Clear();
        std::ifstream file(filename);
        if (!file.is_open())
            return;
        // read file line by line
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            int id;
            ivec2 pos;
            iss >> id >> pos.x >> pos.y;
            MObject object;
            object.id = (MObjectId)id;
            object.position = pos;
            object.update(tiles);
            Put(object);
        }
    }

	std::vector<MObject> GetObjects() const
	{
		return std::vector<MObject>(objects.begin(), objects.end());
	}
};