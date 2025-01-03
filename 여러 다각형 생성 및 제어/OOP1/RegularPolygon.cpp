#include "RegularPolygon.h"
#include "InputManager.h"

void RegularPolygon::update(InputManager& input)
{
	// adjust num of sides of polygon
	if (input.getKeyDown(VK_RIGHT)) { ++(*this); }
	if (input.getKeyDown(VK_LEFT)) { (*this)--; }

	// adjust radius of polygon
	if (input.getKey(VK_UP)) { adjustRadius(1); }
	if (input.getKey(VK_DOWN)) { adjustRadius(-1); }

	// rotate polygon
	if (input.getKey(VK_SPACE)) { rotatePolygon(); }
	if (input.getKeyUp(VK_SPACE)) { resetRotatingSpeed(); }

	// move polygon
	if (input.getKey('A')) { moveLeft(); }
	if (input.getKey('D')) { moveRight(); }
	if (input.getKey('W')) { moveUp(); }
	if (input.getKey('S')) { moveDown(); }
}