#pragma once

#include <vector>
#include "MObject.h"
#include "Vector2.h"


struct PlayingMaze {

	std::vector<MObject> mobjects;
	Vector2 cameraOffset;


	void SetMaze(std::vector<MObject> tiles) {
		mobjects = tiles;
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