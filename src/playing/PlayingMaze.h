#pragma once

#include <vector>
#include "MObject.h"
#include "Vector2.h"


struct PlayingMaze {

	std::vector<MObject> mobjects;
	Vector2 cameraOffset;
	MObject* player = nullptr;

	void SetMaze(std::vector<MObject> tiles) {
		mobjects = tiles;
		auto it = std::find_if(mobjects.begin(), mobjects.end(), [](const MObject& obj) {
			return obj.id == MObjectId::START;
			});
		if (it != mobjects.end()) {
			player = &(*it);
			cameraOffset = player->position;
		}
		else {
			// TODO: what if it doesn't exist?
		}
	}

	void Clear() {
		mobjects.clear();
	}

	void Draw(Screen& screen) {
		for (auto& mobject : mobjects) {
			mobject.DrawForPlay(screen, cameraOffset);
		}
	}
};