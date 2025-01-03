#pragma once

#include "GameObject.h"
#include <algorithm>

class Selector : public GameObject
{

public:
	Selector() : GameObject("", Vector2{ 0, 0 }, Dimension{ 0, 0 })
	{}

	void drag(InputManager& input);

	bool isInside(const Vector2& pos) {
		Vector2 comparePos{0, 0};
		Dimension compareDim{ 0, 0 };

		// when drag continued from right down to left up 
		if (getDimension().x < 0 && getDimension().y < 0) {
			comparePos = Vector2{ getPosition() + getDimension()};
			compareDim = -1*getDimension();

			return comparePos.x <= pos.x && comparePos.x + compareDim.x > pos.x && comparePos.y <= pos.y && comparePos.y + compareDim.y > pos.y;
		}
		// when drag continued from right up to left down 
		if (getDimension().x < 0) {
			comparePos = Vector2{ getPosition().x + getDimension().x, getPosition().y };
			compareDim = Dimension{ -1 * getDimension().x, getDimension().y };

			return comparePos.x <= pos.x && comparePos.x + compareDim.x > pos.x && comparePos.y <= pos.y && comparePos.y + compareDim.y > pos.y;
		}
		// when drag continued from left down to right up 
		if (getDimension().y < 0) {
			comparePos =Vector2{ getPosition().x, getPosition().y + getDimension().y };
			compareDim = Dimension{ getDimension().x, -1 * getDimension().y };

			return comparePos.x <= pos.x && comparePos.x + compareDim.x > pos.x && comparePos.y <= pos.y && comparePos.y + compareDim.y > pos.y;
		}
		// when drag continued from left up to right down 
		return getPosition().x <= pos.x && getPosition().x + getDimension().x > pos.x && getPosition().y <= pos.y && getPosition().y + getDimension().y > pos.y;
	}
};

